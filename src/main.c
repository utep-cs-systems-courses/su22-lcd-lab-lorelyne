#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "animations.h"
int main(void){
  configureClocks();
  enableWDTInterrupts();
  led_init();
  buzzer_init();
  buzzer_set_period(0);
  switch_init();
  StartGame();
  or_sr(0x18);
}
