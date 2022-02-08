#include "spi.h"

#include <inttypes.h>
#include <avr/io.h>


void SPI::init(bool lsbfirst, bool master, uint8_t mode, uint8_t clkrate, bool spd2x) {
  

  // port setting
  DDRB |= ((1 << SPI_MOSI) | (1 << SPI_SCK));  // out
  DDRB &= ~(1<< SPI_MISO); // in 
  PORTB |= (1<< SPI_MISO); // pull-up
  
  // SPI CONTROL REGISTER
  SPCR = (
           (1 << SPE) |                                 // enable SPI
           ((lsbfirst & 0b00000001) << DORD) |          // MSB / LSB
           ((master & 0b00000001) << MSTR) |            // MASTER/SLAVE
           ((mode & 0b00000011) << CPHA) |              // MODE
           (clkrate & 0b00000011 << SPR0)               // SPEED
         );
  
  // SPI STATUS REGISTER 
  SPSR = ((spd2x & 0b00000001) << SPI2X);              // DOUBLE SPEED
}


uint8_t SPI::send(uint8_t value) {
  uint8_t rc;
  SPDR = value;
  while(!(SPSR & (1<<SPIF))) {}
  rc = SPDR;
  return rc;
}