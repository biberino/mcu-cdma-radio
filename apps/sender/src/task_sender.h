#ifndef __TASK_SENDER_H__
#define __TASK_SENDER_H__

#include "os/os.h"


#define SENDER_STACK_SIZE OS_STACK_ALIGN(128) //x4 bytes
#define SENDER_TASK_PRIO (10)

struct sender_data
{
    uint8_t *buffer;
    int size;
    int gpio;
};

void sender_send_bytes(struct os_event *ev);

struct os_eventq sender_event_queue;



struct os_task os_task_sender;
os_stack_t sender_task_stack[SENDER_STACK_SIZE];
void sender_task_init(void);
void sender_work_task(void *arg);

#endif // __TASK_SENDER_H__
