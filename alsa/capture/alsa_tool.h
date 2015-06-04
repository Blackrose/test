#ifndef __ALSA_TOOL_H__
#define __ALSA_TOOL_H__


#ifdef __cplusplus
extern "C" {
#endif

/*
    will clreate a thread.
*/
void alsa_capture_start(void);
extern void alsa_capture_data_ind(unsigned char * data, unsigned int len);

void alsa_tool_init(void);

void alsa_tool_play_start(void);
void alsa_play_data_send(void *data, int len);



#ifdef __cplusplus
}
#endif

#endif  //#ifndef __ALSA_TOOL_H__

