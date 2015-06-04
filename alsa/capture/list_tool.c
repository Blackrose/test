#include<stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
static pthread_mutex_t list_mutex;
#define DEBUG_LOG
#ifdef DEBUG_LOG
#define LISTLOG(arg, ...) {printf("[list]:"arg,##__VA_ARGS__);};

#else
#define LISTLOG(arg, ...) {}
#endif


typedef struct _data_t
{
    int len;
    int seqid;
    struct _data_t* next;
    void* data;
}data_t;

typedef struct
{
    data_t* first;
    data_t* tail;
    int count;
    int seqid;
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
    memset((void *)&list_cb, 0, sizeof(list_cb));
}
/*
    list tool data push
    
*/
void list_tool_data_push(void* data, int len)
{
   // LISTLOG("------>list_tool_data_push\n");
    data_t* listData = (data_t*)malloc(sizeof(data_t));
    memset((void*)listData, 0x00, sizeof(data_t));
    /* */
    if(data == NULL)
    {
       return;
    }
    if(listData == NULL)
    {
        LISTLOG("malloc Fail\n");
        return;
    }
    listData->data = data;
    listData->len = len;
    
    pthread_mutex_lock(&list_mutex);
    LISTLOG("the Count is %d\n", list_cb.count);
    
    if(list_cb.tail == NULL)
    {
        list_cb.tail = listData;
        list_cb.first = listData;
        LISTLOG("set the first\n");
    }
    else
    {
        list_cb.tail->next = listData;
        list_cb.tail = listData;
    }
    list_cb.count++;
    list_cb.seqid ++;
    listData->seqid = list_cb.seqid;
    
    pthread_mutex_unlock(&list_mutex);
    
}


/*
    list tool data get
    
*/
void*  list_tool_data_get(int* len)
{
    static int count;
    void* data;
    data_t* curent;
    if(len == NULL)
    {
        LISTLOG("The len is NULL\n");
        return NULL;
    }
    //LISTLOG("list_cb cout %d\n",list_cb.count);
    //LISTLOG("list_cb.first %x\n", list_cb.first);
    if(list_cb.first != NULL)
    {

        LISTLOG(" first id %d\n", list_cb.first->seqid);
    
        *len = list_cb.first->len;
        data = list_cb.first->data;
        curent = list_cb.first;
        /*modify the first*/        
        pthread_mutex_lock(&list_mutex);
        
        list_cb.count--;
        if(list_cb.first->next == NULL)
        {
            if(list_cb.count != 0)
            {
                LISTLOG("count is not 0\n");
            }
            list_cb.first = NULL;
            list_cb.tail = NULL;
            LISTLOG("list_cb.first is NULL\n");
        }
        else
        {
            if((list_cb.first->seqid + 1) != list_cb.first->next->seqid)
            {
                LISTLOG("--------->error\n");
            }
         //   LISTLOG(" first id %d\n", list_cb.first->seqid);
          //  LISTLOG(" next id %d\n", list_cb.first->next->seqid);
            list_cb.first = list_cb.first->next;
        }
        pthread_mutex_unlock(&list_mutex);
        free(curent);
        if(data == NULL)
        {
            LISTLOG("data == NULL");
        }
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
            LISTLOG("Rec data: %s", data);
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
        LISTLOG("Thread Create Fial\n");
    }
    char* str = "test--------> foo\n";
    list_tool_init();
    LISTLOG("list test\n");
    while(1)
    {

        char* data =(char *) malloc(strlen(str) + 1);
        memset(data, 0x00, strlen(str) + 1);
        memcpy(data, str, strlen(str));
        list_tool_data_push(data, strlen(str) + 1);
    }
}


#endif
