//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   i2c_display.h
/// @author Vanek


#include "i2c_display.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

void LCDI2C::init(uint8_t address, uint8_t enable, uint8_t rw, uint8_t rs, uint8_t backlight) {

  _i2c.init();

  _address = address;
  _enable = enable;
  _rw = rw;
  _rs = rs;
  _backlight = backlight;

  writeIO(0);
  _delay_ms(500);
  write4bits((0x01 << _d5) | (0x01 << _d4));
  _delay_us(4500);

  write4bits((0x01 << _d5) | (0x01 << _d4));
  _delay_us(4500);

  write4bits((0x01 << _d5) | (0x01 << _d4));
  _delay_us(150);

  // set # lines, font size, etc.
  command(0x22);
  command(0x80);
  command(0xC0);
  command(0x10);
  clear();
}

void LCDI2C::clear() {
  command(0x01);
  _delay_us(2000);
}

void LCDI2C::home() {
  command(0x02);
  _delay_us(2000);
}

void LCDI2C::command(uint8_t value) { send(value, 0); }

void LCDI2C::send(uint8_t value, uint8_t mode) {
  uint8_t highnib = value & (uint8_t)0xf0;
  uint8_t lownib = (value << 4) & (uint8_t)0xf0;
  write4bits((highnib) | mode);
  write4bits((lownib) | mode);
}

void LCDI2C::write4bits(uint8_t data) {
  data |= _backlightval ? (0x01 << _backlight) : 0;
  writeIO(data | (0x01 << _enable));
  _delay_us(7);
  writeIO(data & ~(0x01 << _enable));
  _delay_us(50);
}

void LCDI2C::oneChar(uint8_t o) { send(o, (0x01 << _rs)); }

void LCDI2C::noBacklight() {
  _backlightval = false;
  writeIO(0);
}

void LCDI2C::backlight() {
  _backlightval = true;
  writeIO(0);
}

void LCDI2C::writeIO(uint8_t data) {
  _i2c.start(_address << 1);
  _i2c.write(data);
  _i2c.stop();
}

void LCDI2C::cursorAt(uint8_t line, uint8_t row) {

  auto data = 0x01 << 7;
  /*
     line 0 - 00-19
         line 1 - 64-83
         line 2 - 20-39
         line 3 - 84-103
  */

  data += row;
  if (line == 1) {
    data += 64;
  } else if (line == 2) {
    data += 20;
  } else if (line == 3) {
    data += 84;
  }
  command(data);
  _delay_us(2000);
}

void LCDI2C::print(const char *str) {
  while (*str) {
    oneChar(*str++);
  }
}

void LCDI2C::print(int32_t in) {
  char str[15];
  sprintf(str, "%ld", in);
  print(str);
}

void LCDI2C::print(double in) {
  char str[20];
  dtostrf(in, 7, 2, str);
  print(str);
}
