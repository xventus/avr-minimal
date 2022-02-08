//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   spi.h
/// @author Vanek

#pragma once
#include <inttypes.h>
#include "constants.h"

/**
 * @brief SPI implementation wrapper for AT328 type
 *  PB5 - SCK
 *  PB4 - MISO
 *  PB3 - MOSI
 */
class SPI {

    static  constexpr uint8_t SPI_MOSI = DEF_SPI_MOSI; 
    static  constexpr uint8_t SPI_MISO = DEF_SPI_MISO;
    static  constexpr uint8_t SPI_SCK  = DEF_SPI_SCK;

    public:

    /**
     * @brief initialize SPI interface
     * 
     * @param lsbfirst true for LSB first order
     * @param master   true for MASTER side
     * @param mode     Clock Phase (CPHA) | Clock Polarity (CPOL) 
     * @param clkrate  SPR0 | SPR1 - speed
     * @param spd2x    double SPI speed (in master mode)
     */
    void init(bool lsbfirst = false, bool master = true, uint8_t mode = 0, uint8_t clkrate = 1, bool spd2x = false);

    /**
     * @brief Send & Receive data to  / from SPI bus
     * 
     * @param value data to send
     * @return uint8_t  received data 
     */
    uint8_t send(uint8_t value);

};

