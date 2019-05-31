#include <stdlib.h>
#include "m_seq.h"

struct m_seq_register_32 *m_seq_create_32(u32 init_value, int reset_at)
{
    struct m_seq_register_32 *ret = (struct m_seq_register_32 *)malloc(sizeof(struct m_seq_register_32));
    ret->reg = init_value;
    ret->init_value = init_value;
    ret->reset_at = reset_at;
    ret->shift_count = 0;
    return ret;
}

void m_seq_destroy_32(struct m_seq_register_32 *reg)
{
    free(reg);
}

u8 m_seq_next_bit_32(struct m_seq_register_32 *reg)
{

    u8 out = reg->reg & 1;
    reg->reg = reg->reg >> 1;

    u32 buffer = (reg->reg & 1) ^ (reg->reg & 2) ^ (reg->reg & 4) ^ (reg->reg & 0x20) ^ out;
    buffer = buffer << 31;
    reg->reg |= buffer;

    reg->shift_count++;

    if (reg->shift_count >= reg->reset_at)
    {
        reg->reg = reg->init_value;
        reg->shift_count = 0;
    }

    return out;
}

struct m_seq_register_16 *m_seq_create_16(u16 init_value, int reset_at)
{
    struct m_seq_register_16 *ret = (struct m_seq_register_16 *)malloc(sizeof(struct m_seq_register_16));
    ret->reg = init_value;
    ret->init_value = init_value;
    ret->reset_at = reset_at;
    ret->shift_count = 0;
    return ret;
}

void m_seq_destroy_16(struct m_seq_register_16 *reg)
{
    free(reg);
}

u8 m_seq_next_bit_16(struct m_seq_register_16 *reg)
{
    u8 out = reg->reg & 1;
    reg->reg = reg->reg >> 1;

    u16 buffer = (reg->reg & 1) ^ (reg->reg & 0x40) ^ out;
    buffer = buffer << 15;
    reg->reg |= buffer;

    reg->shift_count++;
    if (reg->shift_count >= reg->reset_at)
    {
        reg->reg = reg->init_value;
        reg->shift_count = 0;
    }

    return out;
}