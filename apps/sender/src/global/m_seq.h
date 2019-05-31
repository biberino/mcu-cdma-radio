#pragma once

#include "types.h"

struct m_seq_register_32
{
    u32 reg;
    int reset_at;
    u32 init_value;
    int shift_count;
};

struct m_seq_register_32 *m_seq_create_32(u32 init_value, int reset_at);
void m_seq_destroy_32(struct m_seq_register_32 *reg);

u8 m_seq_next_bit_32(struct m_seq_register_32 *reg);

struct m_seq_register_16
{
    u16 reg;
    int reset_at;
    u16 init_value;
    int shift_count;
};

struct m_seq_register_16 *m_seq_create_16(u16 init_value, int reset_at);
void m_seq_destroy_16(struct m_seq_register_16 *reg);

u8 m_seq_next_bit_16(struct m_seq_register_16 *reg);