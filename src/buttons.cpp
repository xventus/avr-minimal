//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   i2c_display.h
/// @author Vanek




#include "buttons.h"



void Buttons::isrHandle() {
   
    
    
    
    uint8_t state_changed = ~BUTTON_PIN ^ button_state;
    VC_DEC_OR_SET(vcount_high, vcount_low, state_changed);
    state_changed &= vcount_low & vcount_high;
    button_state ^= state_changed;
    buttons_down |= button_state & state_changed;
}


// Return non-zero if a button matching mask is pressed.
uint8_t Buttons::isDown(uint8_t buttons) {
   
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
	    buttons &= buttons_down;
	    buttons_down ^= buttons;
    }
   
    return buttons;
}

void Buttons::init() {

    button_state = 0;

    // pullup & input
    BUTTON_DDR &= ~(BUTTON_MASK);
    BUTTON_PORT |= BUTTON_MASK;

    //timer 0 
    TCCR0B = 1<<CS02;
    TIMSK0 = 1<<TOIE0;
}
