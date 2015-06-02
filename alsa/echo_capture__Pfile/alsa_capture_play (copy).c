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
		printf("Broken configuration for playback: no configurations available: %s\n", snd_strerror(err));
		return err;
	}
	/* set hardware resampling */
	err = snd_pcm_hw_params_set_rate_resample(handle, params, resample);
	if (err < 0) 
	{
		printf("Resampling setup failed for playback: %s\n", snd_strerror(err));
		return err;
	}
	/* set the interleaved read/write format */
	err = snd_pcm_hw_params_set_access(handle, params, access);
	if (err < 0)
	{
		printf("Access type not available for playback: %s\n", snd_strerror(err));
		return err;
	}
	/* set the sample format */
	err = snd_pcm_hw_params_set_format(handle, params, format);
	if (err < 0) 
	{
		printf("Sample format not available for playback: %s\n", snd_strerror(err));
		return err;
	}
	/* set the count of channels */
	err = snd_pcm_hw_params_set_channels(handle, params, channels);
	if (err < 0)
	{
		printf("Channels count (%i) not available for playbacks: %s\n", channels, snd_strerror(err));
		return err;
	}
	/* set the stream rate */
	rrate = rate;
	err = snd_pcm_hw_params_set_rate_near(handle, params, &rrate, 0);
	if (err < 0) 
	{
		printf("Rate %iHz not available for playback: %s\n", rate, snd_strerror(err));
		return err;
	}
	if (rrate != rate) 
	{
		printf("Rate doesn't match (requested %iHz, get %iHz)\n", rate, err);
		return -EINVAL;
	}
	/* set the buffer time */
	err = snd_pcm_hw_params_set_buffer_time_near(handle, params, &buffer_time, &dir);
	if (err < 0)
	 {
		printf("Unable to set buffer time %i for playback: %s\n", buffer_time, snd_strerror(err));
		return err;
	}
	err = snd_pcm_hw_params_get_buffer_size(params, &size);
	if (err < 0)
	 {
		printf("Unable to get buffer size for playback: %s\n", snd_strerror(err));
		return err;
	}
	buffer_size = size;

	/* set the period time */
	err = snd_pcm_hw_params_set_period_time_near(handle, params, &period_time, &dir);
	if (err < 0)
	 {
		printf("Unable to set period time %i for playback: %s\n", period_time, snd_strerror(err));
		return err;
	}
/*
	snd_pcm_uframes_t periodsize=800;
	 err = snd_pcm_hw_params_set_period_size(handle, params,910,0);
	printf("period near %d   %d\r\n",dir,periodsize);

	if (err < 0) {
	printf("Unable to set period size   %s\n ", snd_strerror(err));
	return err;
	}*/
	err = snd_pcm_hw_params_get_period_size(params, &size, &dir);
	printf("size or the period_size: %ld\r\n",size);
	if (err < 0) 
	{
		printf("Unable to get period size for playback: %s\n", snd_strerror(err));
		return err;
	}
	period_size = size;
	/* write the parameters to device */
	err = snd_pcm_hw_params(handle, params);
	if (err < 0) 
	{
		printf("Unable to set hw params for playback: %s\n", snd_strerror(err));
		return err;
	}
	return 0;
}
/*
* Transfer method - asynchronous notification
*/
struct async_private_data 
{
	signed short *samples;
	snd_pcm_channel_area_t *areas;
	double phase;
};
static void async_callback(snd_async_handler_t *ahandler)
{
	snd_pcm_t *handle = snd_async_handler_get_pcm(ahandler);
	int err;
	signed short *samples_buf;
	samples_buf = malloc((period_size * channels * snd_pcm_format_physical_width(format)) / 8);
	if(file_capture == 0)
	{
		printf("err file\r\n");
	}
	struct timeval oldtv;
	struct timeval tv;
	/*avasounil = snd_pcm_avail_update(handle);*/

	if ((err = snd_pcm_readi (handle, samples_buf,period_size)) != period_size)
	 {
		fprintf (stderr, "read from audio interface failed (%s)\n",snd_strerror (err));
		exit (1);
	 }
	else
	{
		 gettimeofday(&tv,NULL);
  		 printf("time %lu\n",(tv.tv_sec-oldtv.tv_sec)*1000000+tv.tv_usec-oldtv.tv_usec);
		 oldtv = tv;
	 	 fwrite(samples_buf,2,910,file_capture);		
	}		
}

static int async_loop(snd_pcm_t *handle)
{
	struct async_private_data data;
	snd_async_handler_t *ahandler;
	int err, count;
	err = snd_async_add_pcm_handler(&ahandler, handle, async_callback, &data);
	if (err < 0) 
	{
		printf("Unable to register async handler\n");
		exit(EXIT_FAILURE);
	}
	if (snd_pcm_state(handle) == SND_PCM_STATE_PREPARED)
	 {
		err = snd_pcm_start(handle);
		if (err < 0) 
		{
			printf("Start error: %s\n", snd_strerror(err));
			exit(EXIT_FAILURE);
		}
	}	
	file_capture = fopen("file_capture","w");
	
}

/*
 *   Underrun and suspend recovery
 */
 
static int xrun_recovery(snd_pcm_t *handle, int err)
{
        if (verbose)
                printf("stream recovery\n");
        if (err == -EPIPE) {    /* under-run */
                err = snd_pcm_prepare(handle);
                if (err < 0)
                        printf("Can't recovery from underrun, prepare failed: %s\n", snd_strerror(err));
                return 0;
        } else if (err == -ESTRPIPE) {
                while ((err = snd_pcm_resume(handle)) == -EAGAIN)
                        sleep(1);       /* wait until the suspend flag is released */
                if (err < 0) {
                        err = snd_pcm_prepare(handle);
                        if (err < 0)
                                printf("Can't recovery from suspend, prepare failed: %s\n", snd_strerror(err));
                }
                return 0;
        }
        return err;
}

static void play_callback(snd_async_handler_t *ahandler)
{
	snd_pcm_t *handle = snd_async_handler_get_pcm(ahandler);
	int err;
	signed short *samples_buf;
	samples_buf = malloc((period_size * channels * snd_pcm_format_physical_width(format)) / 8);
	if(file_capture == 0)
	{
		printf("err file\r\n");
	}
	struct timeval oldtv;
	struct timeval tv;
	/*avasounil = snd_pcm_avail_update(handle);*/

	if ((err = snd_pcm_readi (handle, samples_buf,period_size)) != period_size)
	 {
		fprintf (stderr, "read from audio interface failed (%s)\n",snd_strerror (err));
		exit (1);
	 }
	else
	{
		 gettimeofday(&tv,NULL);
  		 printf("time %lu\n",(tv.tv_sec-oldtv.tv_sec)*1000000+tv.tv_usec-oldtv.tv_usec);
		 oldtv = tv;
	 	 fwrite(samples_buf,2,910,file_capture);		
	}		
}


static int write_loop(snd_pcm_t *handle)
{
	double phase = 0;
	signed short *ptr;
	int err, cptr;
	
	size_t data_len;
	signed short *samples_buf_play;
	samples_buf_play = malloc(910*2);

	FILE* file_playback = fopen("file_playback","rb");
	FILE* file_dump = fopen("file_dump","wb");
	if(file_playback== NULL)
	{
		printf("file open err check the file please\r\n");
		return 0;
	}
	while (1)
	 {
		data_len = fread(samples_buf_play,2,910,file_playback);
		fwrite(samples_buf_play,2,data_len,file_dump);
		if(data_len != 910)
		{
			printf("the data is not enough %d\r\n",data_len );
			return 0;
		}
		err = snd_pcm_writei(handle, samples_buf_play,910);
		if (err < 0) 
		{	
			if (xrun_recovery(handle, err) < 0) 
			{
				printf("Write error: %s\n", snd_strerror(err));
				exit(EXIT_FAILURE);
			}
			break; /* skip one period */
		}
	}
}
int main(int argc, char *argv[])
{
	snd_pcm_t *handle;
	snd_pcm_t *handle_play;
	int err, morehelp;
	snd_pcm_hw_params_t *hwparams;
	snd_pcm_sw_params_t *swparams;
	int method = 0;
	signed short *samples;
	unsigned int chn;
	snd_pcm_hw_params_alloca(&hwparams);
	snd_pcm_sw_params_alloca(&swparams);
	
	printf("Capture device is %s\n", device);
	printf("Stream parameters are %iHz, %s, %i channels\n", rate, snd_pcm_format_name(format), channels);

	/*open the playback*/
	if ((err = snd_pcm_open(&handle_play, device,SND_PCM_STREAM_PLAYBACK, 0)) < 0) 
	{
		printf("Capture open error: %s\n", snd_strerror(err));
		return 0;
	}
	/* set the hard ware parameter*/
	if ((err = set_hwparams(handle_play,hwparams,SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) 
	{
		printf("Setting of hwparams failed: %s\n", snd_strerror(err));
		exit(EXIT_FAILURE);
	}

	/*open the capture*/
	if ((err = snd_pcm_open(&handle, device,SND_PCM_STREAM_CAPTURE, 0)) < 0) 
	{
		printf("Capture open error: %s\n", snd_strerror(err));
		return 0;
	}
	/* set the hard ware parameter*/
	if ((err = set_hwparams(handle, hwparams,SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) 
	{
		printf("Setting of hwparams failed: %s\n", snd_strerror(err));
		exit(EXIT_FAILURE);
	}	
	/*async for capture */
	async_loop(handle);	
	/*	*/
	write_loop(handle_play);
	
	/*while(1)
	{
		
	}*/
}











