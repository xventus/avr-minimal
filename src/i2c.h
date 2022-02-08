//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   i2c.h
/// @author Vanek

#pragma once

#include <inttypes.h>

/**
 * @brief I@C master implementation
 * PINS:  PC5 - SCL
 *        PC4 - SDA
 * 
 */
class I2C {
public:

/**
 * @brief initialise I2C interface
 * 
 */
  void init();

  /**
   * @brief Start transaction with slave address
   * 
   * @param address - device address
   * @return uint8_t 0 - success
   */
  uint8_t start(uint8_t address);

  /**
   * @brief stop I2C transaction
   * 
   */
  void stop();

  /**
   * @brief write data
   * 
   * @param data data to write
   * @return uint8_t 0 menas success
   */
  uint8_t write(uint8_t data);

  /**
   * @brief Read with ACK
   * 
   * @return uint8_t returned value
   */
  uint8_t readAck();

  /**
   * @brief read with NAK 
   * 
   * @return uint8_t returned value
   */
  uint8_t readNak();
};
