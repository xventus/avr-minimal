//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   uart.h
/// @author Vanek

#pragma once
#include <stdio.h>

/**
 * @brief UART class, wrapping serial line into an object for ATMEGA CPU - line
 *0
 *
 * example:
 *  Uart uart;
 * 	uart.init(9600);
 *	uart.printf("Text, signed int16=%d, hex=%2x and  sting[%s] bin[%8b]",
 *123, 11, "my string", 11);
 *
 * Output> "Text, signed int16=123, hex=0B and  sting[my string] bin[00001011]""
 */

class Uart {
public:
  /**
   * @brief serial link speed, call this function first
   *
   * @param baud  speed in Bd
   */
  void init(uint32_t baud);

  /**
   * @brief sends a character/byte to the serial link
   *
   * @param c  - char
   */
  void putByte(uint8_t c);

  /**
   * @brief Get the byte from serial line, if not exist, then blocked
   *
   * @return uint8_t
   */
  uint8_t getByte();

  /**
   * @brief complex print function to the serial line with supported formating
   * chars. Note:  %d - 16bits, %D - 32bits and etc.
   *
   * @param args formatting string
   * @param ... argument - optionally
   */
  void printf(const char *args, ...);

  /**
   * @brief send string \0 terminated
   *
   * @param str
   */
  void sendString(const char *str);

   

private:
  // type of number interpretation
  enum class Number : int {
    bit = 2,
    dec = 10,
    hex = 16,

  };

  /**
   * @brief Set the Baud Rate of UART0
   *
   * @param baud e.g. 9600
   */
  void setBaudRate(uint32_t baud);

 
/**
   * @brief print number with predefined interpretation
   *
   * @param number  - own number to print
   * @param interpretation  - numeric representation
   * @param digits  - number of digits
   */
  void sendNumber(uint32_t number, Number interpretation, uint8_t digits = 8);
  
};
