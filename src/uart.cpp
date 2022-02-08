//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   uart.cpp
/// @author Vanek

#include "uart.h"
#include "utils.h"
#include "constants.h"

void Uart::setBaudRate(uint32_t baud) {
  uint16_t speed = (((F_CPU - ((baud)*8L)) / ((baud)*16UL)));
  UBRR0L = lowByte(speed);
  UBRR0H = highByte(speed);
}

void Uart::init(uint32_t baud) {
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UCSR0A = 0x00;
  setBaudRate(baud);
}

void Uart::putByte(uint8_t c) {
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
}

uint8_t Uart::getByte() {
  while (!(UCSR0A & (1 << RXC0)))
    ;
  return UDR0;
}

void Uart::sendNumber(uint32_t number, Number interpretation, uint8_t digits) {

  uint8_t pos = 0;
  uint8_t split[10];

  if (interpretation == Number::bit) {
    // BIN
    while (digits != 0) {
      pos = isBitSet(number, (digits - 1));
      putByte(ord2Ascii(pos));
      digits--;
    }
  } else {
    // HEX, DEC
    for (pos = 0; pos < digits; pos++) {
      if (number != 0) {
        split[pos] = mod32(number, static_cast<uint32_t>(interpretation));
        number = number / static_cast<uint32_t>(interpretation);
      } else if (digits >= 255) {
        // safety germ
        break;
      } else {
        // zeroes are added if needed
        split[pos] = 0;
      }
    }

    // final ASCII conversion
    while (pos) {
      putByte(hex2Ascii(split[pos - 1]));
      pos--;
    }
  }
}

void Uart::sendString(const char *str) {
  while (*str) {
    putByte(*str++);
  }
}

void Uart::printf(const char *args, ...) {

  const char *ptr = nullptr;
  char *str = nullptr;
  char ch;
  uint8_t digits;
  va_list argp;
  int16_t val16;
  int32_t val32;
  uint16_t uval16;
  uint32_t uval32;

  va_start(argp, args);
  for (ptr = args; *ptr != '\0'; ptr++) {

    ch = *ptr;
    if (ch == '%') {
      ptr++;
      ch = *ptr;
      if ((ch >= 0x30) && (ch <= 0x39)) {
        digits = 0;
        while ((ch >= 0x30) && (ch <= 0x39)) {
          digits = (digits * 10) + (ch - 0x30);
          ptr++;
          ch = *ptr;
        }
      } else {
        digits = 255;
      }

      switch (ch) {

      case 'c':
        ch = va_arg(argp, int);
        putByte(ch);
        break;

      case 'd':
        val16 = va_arg(argp, int16_t);
        if (val16 < 0) {
          val16 = -val16;
          putByte('-');
        }
        sendNumber(val16, Number::dec, digits);
        break;

      case 'u':
        uval16 = va_arg(argp, uint16_t);
        sendNumber(uval16, Number::dec, digits);
        break;

      case 'x':
        uval16 = va_arg(argp, uint16_t);
        sendNumber(uval16, Number::hex, digits);
        break;

      case 'b':
        uval16 = va_arg(argp, uint16_t);

        if (digits == 255) {
          digits = 16;
        }
        sendNumber(uval16, Number::bit, digits);

        break;

      case 'B':
        uval32 = va_arg(argp, uint32_t);
        if (digits == 255)
          digits = 32;
        sendNumber(uval32, Number::bit, digits);
        break;

      case 'U':
        uval32 = va_arg(argp, uint32_t);
        sendNumber(uval32, Number::dec, digits);
        break;

      case 'D':
        val32 = va_arg(argp, int32_t);
        if (val32 < 0) {
          val32 = -val32;
          putByte('-');
        }
        sendNumber(val32, Number::dec, digits);
        break;

      case 'X':
        uval32 = va_arg(argp, uint32_t);
        sendNumber(uval32, Number::hex, digits);
        break;

      case 'S':
      case 's':
        str = va_arg(argp, char *);
        sendString(str);
        break;

      case '%':
        putByte('%');
        break;
      }
    } else {
      putByte(ch);
    }
  }

  va_end(argp);
}
