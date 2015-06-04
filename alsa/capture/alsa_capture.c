/*
* This small demo sends a simple sinusoidal wave to your speakers.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <getopt.h>
#include "alsa/asoundlib.h"
#include <sys/time.h>
#include <math.h>
#include <pthread.h>
#include "list_tool.h"
#include "alsa_tool.h"

snd_pcm_t *handle_play;
snd_pcm_t *handle_capture;

FILE* file_capture;
/*if the device is default will can not register the async handler*/
static char *device ="plughw:0,0"; /* playback device */
static snd_pcm_format_t format = SND_PCM_FORMAT_S16; /* sample format */
static unsigned int rate = 8000; /* stream rate */
static unsigned int channels = 1; /* count of channels */
static unsigned int buffer_time = 500000; /* ring buffer length in us */
static unsigned int period_time = 100000; /* period time in us */
static double freq = 440; /* sinusoidal wave frequency in Hz */
static int verbose = 0; /* verbose flag */
static int resample = 1; /* enable alsa-lib resampling */
static int period_event = 0; /* produce poll event after each period */
static snd_pcm_sframes_t buffer_size;
static snd_pcm_sframes_t period_size;/*=======================*/
static snd_output_t *output = NULL;
static snd_pcm_hw_params_t *hwparams;
static snd_pcm_sw_params_t *swparams;

static capture_data_ind_t cpture_data_cb;
static pthread_t capture_thread_id;
static pthread_t play_thread_id;

#define FrameDataSize  910
#define ALSA_DEBUG_LOG
#ifdef ALSA_DEBUG_LOG
#define ALSATLOG(arg, ...) {printf("[alsa]:"arg,##__VA_ARGS__);};
#else
#define ALSATLOG(arg, ...) {}
#endif



/*hard ware parameter set*/
static int set_hwparams(snd_pcm_t *handle,snd_pcm_hw_params_t *params,snd_pcm_access_t access)
{
	unsigned int rrate;
	snd_pcm_uframes_t size;
	int err, dir;
	/* choose all parameters */
	err = snd_pcm_hw_params_any(handle, params);
	if (err < 0) 
	{
		ALSATLOG("Broken configuration for playback: no configurations available: %s\n", snd_strerror(err));
		return err;
	}
	/* set hardware resampling */
	err = snd_pcm_hw_params_set_rate_resample(handle, params, resample);
	if (err < 0) 
	{
		ALSATLOG("Resampling setup failed for playback: %s\n", snd_strerror(err));
		return err;
	}
	/* set the interleaved read/write format */
	err = snd_pcm_hw_params_set_access(handle, params, access);
	if (err < 0)
	{
		ALSATLOG("Access type not available for playback: %s\n", snd_strerror(err));
		return err;
	}
	/* set the sample format */
	err = snd_pcm_hw_params_set_format(handle, params, format);
	if (err < 0) 
	{
		ALSATLOG("Sample format not available for playback: %s\n", snd_strerror(err));
		return err;
	}
	/* set the count of channels */
	err = snd_pcm_hw_params_set_channels(handle, params, channels);
	if (err < 0)
	{
		ALSATLOG("Channels count (%i) not available for playbacks: %s\n", channels, snd_strerror(err));
		return err;
	}
	/* set the stream rate */
	rrate = rate;
	err = snd_pcm_hw_params_set_rate_near(handle, params, &rrate, 0);
	if (err < 0) 
	{
		ALSATLOG("Rate %iHz not available for playback: %s\n", rate, snd_strerror(err));
		return err;
	}
	if (rrate != rate) 
	{
		ALSATLOG("Rate doesn't match (requested %iHz, get %iHz)\n", rate, err);
		return -EINVAL;
	}
	/* set the buffer time */
	err = snd_pcm_hw_params_set_buffer_time_near(handle, params, &buffer_time, &dir);
	if (err < 0)
	 {
		ALSATLOG("Unable to set buffer time %i for playback: %s\n", buffer_time, snd_strerror(err));
		return err;
	}
	err = snd_pcm_hw_params_get_buffer_size(params, &size);
	if (err < 0)
	 {
		ALSATLOG("Unable to get buffer size for playback: %s\n", snd_strerror(err));
		return err;
	}
	buffer_size = size;

	/* set the period time */
	err = snd_pcm_hw_params_set_period_time_near(handle, params, &period_time, &dir);
	if (err < 0)
	 {
		ALSATLOG("Unable to set period time %i for playback: %s\n", period_time, snd_strerror(err));
		return err;
	}
/*
	snd_pcm_uframes_t periodsize=800;
	 err = snd_pcm_hw_params_set_period_size(handle, params,910,0);
	ALSATLOG("period near %d   %d\r\n",dir,periodsize);

	if (err < 0) {
	ALSATLOG("Unable to set period size   %s\n ", snd_strerror(err));
	return err;
	}*/
	err = snd_pcm_hw_params_get_period_size(params, &size, &dir);
	ALSATLOG("size or the period_size: %ld\r\n",size);
	if (err < 0) 
	{
		ALSATLOG("Unable to get period size for playback: %s\n", snd_strerror(err));
		return err;
	}
	period_size = size;
	/* write the parameters to device */
	err = snd_pcm_hw_params(handle, params);
	if (err < 0) 
	{
		ALSATLOG("Unable to set hw params for playback: %s\n", snd_strerror(err));
		return err;
	}
	return 0;
}


static int xrun_recovery(snd_pcm_t *handle, int err)
{
        if (verbose)
                ALSATLOG("stream recovery\n");
        if (err == -EPIPE) {    /* under-run */
                err = snd_pcm_prepare(handle);
                if (err < 0)
                        ALSATLOG("Can't recovery from underrun, prepare failed: %s\n", snd_strerror(err));
                return 0;
        } else if (err == -ESTRPIPE) {
                while ((err = snd_pcm_resume(handle)) == -EAGAIN)
                        sleep(1);       /* wait until the suspend flag is released */
                if (err < 0) {
                        err = snd_pcm_prepare(handle);
                        if (err < 0)
                                ALSATLOG("Can't recovery from suspend, prepare failed: %s\n", snd_strerror(err));
                }
                return 0;
        }
        return err;
}
static void *capture_thread_main(void *arg)
{
    int len;
	unsigned char *samples_buf;
	samples_buf =(unsigned char*) malloc((period_size * channels * snd_pcm_format_physical_width(format)) / 8);
	file_capture = fopen("file_capture","wb");

	if(file_capture == 0)
	{
		ALSATLOG("err file\r\n");
	}
	while(1)
	{
			if ((len = snd_pcm_readi (handle_capture, samples_buf,period_size)) != period_size)
			 {
				fprintf (stderr, "read from audio interface failed (%s)\n",snd_strerror (len));
				exit (1);
			 }
			else
			{	
				//ALSATLOG("capture the data\n");
				fwrite(samples_buf,2,910,file_capture);
                if(cpture_data_cb != 0)
                {
                    cpture_data_cb(samples_buf, len * snd_pcm_format_physical_width(format) / 8);
                }
				/*send the data*/
				
			}		
	}

}

int alsa_capture_start(void)
{
	snd_pcm_t *handle;
	int err, morehelp;

	int method = 0;
	signed short *samples;
	unsigned int chn;

	/*open the capture*/
	if ((err = snd_pcm_open(&handle_capture, device,SND_PCM_STREAM_CAPTURE, 0)) < 0)
	{
		ALSATLOG("Capture open error: %s\n", snd_strerror(err));
		return 0;
	}
	/* set the hard ware parameter*/
	if ((err = set_hwparams(handle_capture, hwparams,SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
	{
		ALSATLOG("Setting of hwparams failed: %s\n", snd_strerror(err));
		exit(EXIT_FAILURE);
	}
	
    int r;
    r = pthread_create(&capture_thread_id, NULL, capture_thread_main, NULL);
    if(r < 0)
    {   
        ALSATLOG("The capture thread create is fail %d\n", r);
    }
    
//	snd_pcm_close(handle);
	
}


void alsa_tool_init(capture_data_ind_t cd)
{
	hwparams = (snd_pcm_hw_params_t *)malloc(snd_pcm_hw_params_sizeof());
    swparams = (snd_pcm_sw_params_t *)malloc(snd_pcm_sw_params_sizeof());
	ALSATLOG("Capture device is %s\n", device);
	ALSATLOG("Stream parameters are %iHz, %s, %i channels\n", rate, snd_pcm_format_name(format), channels);
    //ALSATLOG("data  0x%x\n",data);
    cpture_data_cb = cd;
    list_tool_init();

}

void* alsa_tool_thread_play(void* arg)
{
    unsigned char* data;
    int err;
    int len;
    ALSATLOG("In %s",__func__);
    FILE *file = fopen("fileRec", "w");
    while(1)
    {             
        data = (unsigned char*)list_tool_data_get(&len);
        if(data != NULL)
        {
            err = snd_pcm_writei(handle_play, data,FrameDataSize);
           // ALSATLOG("-------->\n");
            fwrite(data, 2 ,FrameDataSize, file);
    		if (err < 0) 
    		{	
    			if (xrun_recovery(handle_play, err) < 0) 
    			{
    				ALSATLOG("Write error: %s\n", snd_strerror(err));
    				exit(EXIT_FAILURE);
    			}
    			break; /* skip one period */
    		}
    		free(data);
    		
        }
        else
        {
                 //ALSATLOG("-------->3\n");

            usleep(1);
        }
        
    }
}

 int alsa_tool_play_start(void)
{
    int result = 0;
    int err;
    /*open the playback*/
	if ((err = snd_pcm_open(&handle_play, device,SND_PCM_STREAM_PLAYBACK, 0)) < 0)
	{
		ALSATLOG("Capture open error: %s\n", snd_strerror(err));
		return -1;
	}
	/* set the hard ware parameter*/
	if ((err = set_hwparams(handle_play,hwparams,SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
	{
		ALSATLOG("Setting of hwparams failed: %s\n", snd_strerror(err));
		return -2;
	}    

	/*create the play thread*/
	result = pthread_create(&play_thread_id, NULL, alsa_tool_thread_play, NULL);
	if(result < 0)
	{
	    ALSATLOG(" In %s thread create fail\n", __func__);
	}
	else
	{
	    return -3;
	}
	return result;
	
}
void alsa_play_data_send(void *data, int len)
{
    static unsigned char *sdata = NULL;
    static int slen = 0;
    
    int lenleave;
    int lentcopy;
    static FILE* fileunits = NULL;
    if(fileunits == NULL)
    {
        fileunits = fopen("fileunit","wb");
        if(fileunits == NULL)
        {
            return;
        }
    }   
    if(sdata == NULL)
        sdata = (char *)malloc(FrameDataSize * 2);

    /* < 910*/    
    if((slen + len)  < FrameDataSize*2)
    {
        memcpy(sdata + slen, data, len);
        slen = slen + len;
    }
    else
    {
        /*copy the data*/    
        lentcopy = FrameDataSize*2 - slen;
        memcpy(sdata + slen, data, lentcopy);
        list_tool_data_push(sdata, FrameDataSize*2);
        fwrite(sdata, 2,FrameDataSize, fileunits);
        slen = 0;
        sdata = NULL;
        usleep(1000);
        /* copy the leave data*/
        lenleave = len - lentcopy;
        if(lenleave > 0)
        {
            alsa_play_data_send(data +  lentcopy ,lenleave);
        }
    }
    
}

#if 1

void alsa_capture_data_int(unsigned char* data, int len)
{
    ALSATLOG("In %s\n", __func__);
}

int main(int argc, char* argv[])
{
    FILE *file;
    int data_len;
    //utils_init();
    unsigned char* 	samples_buf_play = malloc(FrameDataSize*2);
    if(argc != 2)
    {
        ALSATLOG("Please input the file\n");
        return 0;
    }
    /*  */
    file = fopen( argv[1], "r");
    alsa_tool_init(alsa_capture_data_int);
    alsa_tool_play_start();
    alsa_capture_start();
    if(file == NULL)
    {
        ALSATLOG("File open faile\n");
        return 0;
    }
    while(1)
    {
        data_len = fread(samples_buf_play,2,24,file);
        if(data_len ==0)
        {
            ALSATLOG("data_len is o\n");
            break;
        }
        ALSATLOG("---------<\n");
        alsa_play_data_send(samples_buf_play, data_len*2);
    }
    while(1);
    
    

    
}

#endif

