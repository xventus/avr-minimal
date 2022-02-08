//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   i2c_display.h
/// @author Vanek

#pragma once
#include "i2c.h"

/*
LCD TC2004A : https://cdn-shop.adafruit.com/datasheets/TC2004A-01.pdf
Expander:
https://www.ti.com/lit/ds/symlink/pcf8574.pdf?ts=1636353239996&ref_url=https%253A%252F%252Fwww.google.com%252F

*/

/**
 * @brief wrapped I2C base LCD 4x20 display and connected via PCF8574
 * DATA must be wired at D4-D7
 * 
 *  CPU PINS:  PC5 - SCL
 *             PC4 - SDA
 * 
 */
class LCDI2C {
  // fixed data bits
 static constexpr uint8_t  _d4 = 4;
 static constexpr uint8_t  _d5 = 5;
 static constexpr uint8_t  _d6 = 6;
 static constexpr uint8_t  _d7 = 7;

public:

  /**
   * @brief initialize interface
   * 
   * @param address - display address
   * @param enable  - enable pin position 
   * @param rw  - RW pin
   * @param rs - RS pin
   * @param backlight  - back light pin
   */
  void init(uint8_t address = 0x27,
            uint8_t enable = 2, // CS
            uint8_t rw = 1, uint8_t rs = 0, uint8_t backlight = 3);

  /**
   * @brief  Clear display
   * 
   */
  void clear();

  /**
   * @brief Set to Home position (0,0)
   * 
   */
  void home();

  /**
   * @brief switch off backlight
   * 
   */
  void noBacklight();

  /**
   * @brief switch on backlight
   * 
   */
  void backlight();

  /**
   * @brief print NULL terminate string
   * 
   * @param str 
   */
  void print(const char *str);

  /**
   * @brief pritn integer
   * 
   * @param in 
   */
  void print(int32_t in);

  /**
   * @brief print double
   * 
   * @param in 
   */
  void print(double in);

  /**
   * @brief print char
   * 
   * @param o 
   */
  void oneChar(uint8_t o);

  /**
   * @brief set cursor at position
   * 
   * @param line line 0-3
   * @param row  row 0 - 19
   */
  void cursorAt(uint8_t line, uint8_t row);

private:
  /**
   * @brief write nibble
   * 
   * @param data 
   */
  void write4bits(uint8_t data);

  /**
   * @brief write commnad to the display
   * 
   * @param value 
   */
  void command(uint8_t value);
  
  /**
   * @brief send send data splitted to the two nibbles
   * 
   * @param value 
   * @param mode 
   */
  void send(uint8_t value, uint8_t mode);

  /**
   * @brief write data to PCF8574
   * 
   * @param data 
   */
  void writeIO(uint8_t data);

private:
  I2C _i2c;
  uint8_t _address;
  uint8_t _enable;
  uint8_t _rw;
  uint8_t _rs;
  uint8_t _backlight;
  uint8_t _displaycontrol{0};
  bool _backlightval{true};
};
