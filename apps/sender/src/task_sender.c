#include "task_sender.h"
#include "console/console.h"
#include "hal/hal_gpio.h"

#include "global/params.h"
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
    console_printf("Sender Task gestarted!\n");
    console_printf("Sender Frequenz: %d KHz\n", SENDER_FREQ_KHZ);
    console_printf("Sender Chip Laenge: %d\n", CHIP_LENGTH);

    m_reg = m_seq_create_16(0x0111, CHIP_LENGTH);

    while (1)
    {
        os_eventq_run(&sender_event_queue);

        console_printf("Sender Task fertig.\n");
    }
}

void sender_send_bytes(struct os_event *ev)
{
    u32 delay_us = (1 / SENDER_FREQ_KHZ) * 1000;
    console_printf("Starte Sendevorgang\n");
    console_printf("DELAY: %d\n", (int)delay_us);
    struct sender_data *data = (struct sender_data *)ev->ev_arg;

    for (size_t i = 0; i < data->size; i++)
    {
        u8 byte_value = data->buffer[i];
        for (size_t j = 0; j < 8; j++)
        {
            //LSB FIRST
            //TODO: we could hange that
            u8 bit_value = (byte_value & (1 << j));
            for (size_t k = 0; k < CHIP_LENGTH; k++)
            {
                u8 chip = m_seq_next_bit_16(m_reg);
                (chip == bit_value) ? hal_gpio_write(data->gpio, 1) : hal_gpio_write(data->gpio, 0);

                //Timer is configured so that 10 ticks are 1 send intervall
                //os_cputime_delay_ticks(1000);
                os_cputime_delay_usecs(delay_us);
            }
        }
    }

    hal_gpio_write(data->gpio, 0);
    console_printf("%d Bytes Gesendet\n", data->size);
}
