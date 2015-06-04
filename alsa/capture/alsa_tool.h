#ifndef __ALSA_TOOL_H__
#define __ALSA_TOOL_H__


#ifdef __cplusplus
extern "C" {
#endif

/*
    will clreate a thread.
*/
typedef void (*capture_data_ind_t)(unsigned char *data, int len);


int alsa_capture_start(void);
void alsa_capture_data_ind(unsigned char * data, unsigned int len);
void alsa_tool_init(capture_data_ind_t cd);

int  alsa_tool_play_start(void);
void alsa_play_data_send(void *data, int len);



#ifdef __cplusplus
}
#endif

#endif  //#ifndef __ALSA_TOOL_H__

