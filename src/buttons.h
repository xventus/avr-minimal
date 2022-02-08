//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   buttons.h
/// @author Vanek

/*
EXAMPLE>
Buttons g_buttons; // global instance

ISR(TIMER0_OVF_vect) {
    g_buttons.isrHandle();
}

...
sei();  
g_buttons.init();	
...
if (g_buttons.isDown(BUTTON_ENTER)) {
	//action
}

*/

#pragma once
#include "constants.h"
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/io.h>


#define BUTTON_MASK  (BUTTON_ENTER | BUTTON_ESC | BUTTON_UP | BUTTON_DOWN) 

#define VC_DEC_OR_SET(high, low, mask)		\
    low = ~(low & mask);			\
    high = low ^ (high & mask)


class Buttons {
    
    public:

    /**
     * @brief initialize port and timer0, required to enable interrupt, sei();
     * 
     */
    void init();

    /**
     * @brief check if button is pressed
     * 
     * @param buttons - which button is tested
     * @return uint8_t - zero or pressed button
     */
    uint8_t isDown(uint8_t buttons);   

    /**
     * @brief ISR handle routine, must be called from tiemer 0
     * 
     */
    void isrHandle();

    private:
    uint8_t buttons_down {0};
   
    uint8_t button_state {0};

    uint8_t vcount_low  {0xFF};
    uint8_t vcount_high {0xFF};

};