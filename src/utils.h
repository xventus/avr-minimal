//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   utils.h
/// @author Vanek

#pragma once

#define lowByte(w) (uint8_t)((w)&0xFFu)
#define highByte(w) (uint8_t)(((w) >> 8) & 0xFFu)

#define bitPosition(b) (1 << (b))
#define isBitSet(x, b) (((x) & (bitPosition(b))) != 0u)
#define isBitClr(x, b) (((x) & (bitPosition(b))) == 0u)

#define ord2Ascii(v) ((v) + 0x30)
#define ascii2Ord(v) ((v)-0x30)
#define hex2Ascii(h) (((h) > 0x09) ? ((h) + 0x37) : ((h) + 0x30))
#define ascii2Hex(a) (((a) > 0x39) ? ((a)-0x37) : ((a)-0x30))

#define mod32(dividend, divisor)                                               \
  (uint32_t)(dividend - (divisor * (uint32_t)(dividend / divisor)))

/**
 * @brief convert uint64 to string 
 * 
 * @param v number to be converted
 * @param buf buffer for string
 * @param base numeric base 
 */
void ui64toa(uint64_t v, char * buf, uint8_t base);