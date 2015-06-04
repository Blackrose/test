#include<stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
static pthread_mutex_t list_mutex;
typedef struct _data_t
{
    int len;
    struct _data_t* next;
    void* data;
}data_t;

typedef struct
{
    data_t* first;
    data_t* tail;
    int count;
}list_t;

list_t list_cb;
/*
    list tool init
    
*/
void list_tool_init(void)
{
    pthread_mutex_init(&list_mutex, NULL);
    list_cb.first = NULL;
    list_cb.tail = NULL;
    list_cb.count = 0;
}
/*
    list tool data push
    
*/
void list_tool_data_push(void* data, int len)
{
    data_t* listData = (data_t*)malloc(sizeof(data_t));
    memset((void*)listData, 0x00, sizeof(data_t));
    /* */
    if(listData == NULL)
    {
        printf("malloc Fail\n");
        return;
    }
    listData->data = data;
    listData->len = len;
    pthread_mutex_lock(&list_mutex);
    if(list_cb.tail == NULL)
    {
        list_cb.first = listData;
        list_cb.first = listData;
    }
    else
    {
        list_cb.tail->next = listData;
        list_cb.tail = listData;
    }
    list_cb.count++;
    pthread_mutex_unlock(&list_mutex);
    
}


/*
    list tool data get
    
*/
void*  list_tool_data_get(int* len)
{
    void* data;
    if(len == NULL)
    {
        printf("The len is NULL\n");
        return NULL;
    }
    if(list_cb.first != NULL)
    {
        *len = list_cb.first->len;
        data = list_cb.first->data;
        list_cb.count--;
        /*modify the first*/
        pthread_mutex_lock(&list_mutex);
        if(list_cb.first->next == NULL)
        {
            list_cb.first = NULL;
            list_cb.tail = NULL;
        }
        else
        {
            list_cb.first = list_cb.first->next;
        }
        pthread_mutex_unlock(&list_mutex);
        free(list_cb.first);
        return data;
    }
    else
    {
        *len = 0;
        return NULL;
    }
}

#if 0
void* listGetThread(void *arg)
{
    char* data;
    int len;
    while(1)
    {
        if((data = list_tool_data_get(&len) )!= NULL)
        {
            printf("Rec data: %s", data);
            free(data);
        }
    }
}

int main(int argc, char* argv[])
{
    pthread_t thread_id;
    thread_id = pthread_create(&thread_id, NULL, listGetThread, NULL);
    if(thread_id < 0)
    {
        printf("Thread Create Fial\n");
    }
    char* str = "test--------> foo\n";
    list_tool_init();
    while(1)
    {

        char* data =(char *) malloc(strlen(str) + 1);
        memset(data, 0x00, strlen(str) + 1);
        memcpy(data, str, strlen(str));
        list_tool_data_push(data, strlen(str) + 1);
    }
}


#endif
