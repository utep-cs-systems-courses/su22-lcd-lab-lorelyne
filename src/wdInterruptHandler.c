#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

void __interrupt_vec(WDT_VECTOR) WDT(){

  static char blink_count = 0;
  static char buzzCount = 0;
}
