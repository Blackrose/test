#ifndef  __LIST_TOOL_H__
#define __LIST_TOOL_H__

/*

    list tool; 

    the maloc of data_t will modify
    
*/

void* list_tool_data_get(int * len);
void list_tool_data_push(void * data, int len);
void list_tool_init(void);

#endif
