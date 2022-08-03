#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char count = 0;

void countToThree(){

  switch(count){
  case 0:
   buzzer_set_period(1000);
   red_on = 0;
   green_on = 0;
   count = 1;
   break;

  case 1:
   buzzer_set_period(800);
   red_on = 1;
   green_on = 0;
   count = 2;
   break;

  case 2:
   buzzer_set_period(600);
   red_on = 0;
   green_on = 1;
   count = 3;
   break;

  case 3:
   buzzer_set_period(400);
   red_on = 1;
   green_on = 1;
   count = 0;
   break;
  }
  led_changed = 1;
  led_update();
}

void rest(){
  buzzer_set_period(0);
  count = 0;
  red_on = 0;
  green_on = 0;
  led_changed = 1;
  led_update();
}
    
