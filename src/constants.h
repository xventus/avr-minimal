#pragma once

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef I2C_CLOCK
#define I2C_CLOCK  50000L
#endif

// LCD
#ifndef LCD_I2C_ADDRESS
#define LCD_I2C_ADDRESS 0x27
#endif

// SPI
//  PB5 - SCK
//  PB4 - MISO
//  PB3 - MOSI
#define  DEF_SPI_MOSI 3; 
#define  DEF_SPI_MISO 4;
#define  DEF_SPI_SCK  5;


// BUTTON - connection
// PB5, PB4, PB3, PB2
#define BUTTON_PORT  PORTB
#define BUTTON_PIN   PINB
#define BUTTON_DDR   DDRB
#define BUTTON_ENTER (1<<PB5)
#define BUTTON_ESC (1<<PB4)
#define BUTTON_UP (1<<PB3)
#define BUTTON_DOWN (1<<PB2)
