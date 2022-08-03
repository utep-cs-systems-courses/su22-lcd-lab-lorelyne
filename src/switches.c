#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"
#include "buzzer.h"

char SW1down, SW2down, SW3down, SW4down, bttnState, musicSwi, switch_state_changed;
char switch_update_interrupt_sense(){
char p2val = P2IN;

  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void
switch_init(){
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  SW1down = (p2val & SW1) ? 0 : 1;
  SW2down = (p2val & SW2) ? 0 : 1;
  SW3down = (p2val & SW3) ? 0 : 1;
  SW4down = (p2val & SW4) ? 0 : 1;

  if(SW1down){
    bttnState = 0;
  }else if(SW2down){
      bttnState = 1;
  }else if(SW3down){
      bttnState = 2;
  }else if(SW4down){
      bttnState = 3;
  }
}
