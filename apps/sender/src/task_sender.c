#include "task_sender.h"
#include "console/console.h"
#include "hal/hal_gpio.h"

#include "global/m_seq.h"

static struct m_seq_register_16 *m_reg;


void sender_task_init(void)
{
    os_eventq_init(&sender_event_queue);

    os_task_init(&os_task_sender, "sender", sender_work_task, NULL,
                 SENDER_TASK_PRIO, OS_WAIT_FOREVER, sender_task_stack,
                 SENDER_STACK_SIZE);
}

void sender_work_task(void *arg)
{
    console_printf("Sender Task gestarted!!\n");

    m_reg = m_seq_create_16(0x0111, 16);

    while (1)
    {
        os_eventq_run(&sender_event_queue);
        
        console_printf("Event dispached\n");
    }
}

void sender_send_bytes(struct os_event *ev)
{
    struct sender_data *data = (struct sender_data *)ev->ev_arg;

   
    u8 value = m_seq_next_bit_16(m_reg);
    console_printf("%d\n",value);
    //Sende Bytes hier
    hal_gpio_toggle(data->gpio);

}
