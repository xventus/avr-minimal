//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   i2c.h
/// @author Vanek

#include "constants.h"
#include "i2c.h"
#include <compat/twi.h>
#include <util/twi.h>


#define BITRATE(TWSR)                                                          \
  ((F_CPU / I2C_CLOCK) - 16) /                                                 \
      (2 * pow(4, (TWSR & ((1 << TWPS0) | (1 << TWPS1)))))

void I2C::init() {
  TWBR = BITRATE(TWSR = 0x00);
}

uint8_t I2C::start(uint8_t address) {
  uint8_t rc = 0;
  uint8_t status; 
  
  do {
  
    TWCR = (1 << TWSTA) | (1 << TWEN) |
          (1 << TWINT); 
    while (!(TWCR & (1 << TWINT))) {};
                      
    status = TWSR & 0xF8; 
    if (status != 0x08)  {
      rc = 0;
      break;
    }  
             
    TWDR = address;      
    TWCR = (1 << TWEN) | (1 << TWINT); 
    while (!(TWCR & (1 << TWINT))) {}
    status = TWSR & 0xF8;
    if (status == 0x18){
      rc = 1;
      break;
    }     
               
    if (status == 0x20)   {
      rc = 2;
      break;
    } else {
      rc = 3;
      break;
    }               
  }while(false);
  return rc;
}

uint8_t I2C::write(uint8_t data) {
  uint8_t status; 
  uint8_t rc = 0;
  do {
    TWDR = data;                       
    TWCR = (1 << TWEN) | (1 << TWINT); 
    while (!(TWCR & (1 << TWINT))) {};
                      
    status = TWSR & 0xF8; 
    if (status == 0x28)  {
        rc = 0;
        break;
      }  
        
    if (status == 0x30) {
        rc = 1;
        break;
      }  else {
        rc = 2;
        break;
      }    
  }while(false); 
  return rc; 
}


void I2C::stop() {
  TWCR =
      (1 << TWSTO) | (1 << TWINT) | (1 << TWEN); 
  while (TWCR & (1 << TWSTO)) {} ; 
}

uint8_t I2C::readAck() {
  TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
  while (!(TWCR & (1 << TWINT))) {};
  return TWDR;
} 


uint8_t I2C::readNak() {
  TWCR = (1 << TWEN) | (1 << TWINT);
  while (!(TWCR & (1 << TWINT))) {}
  return TWDR;
}
