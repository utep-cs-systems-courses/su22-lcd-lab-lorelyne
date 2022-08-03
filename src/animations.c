#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include <p2switches.h>
#include <shape.h>
#include <stdio.h>
#include "stateMachines.h"
#include <stdlib.h>
#include "buzzer.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;

//up and down 
u_char U_D = 10;
u_char nextU_D = 10;

//left to right
u_char L_R = 10;
u_char nextL_R = 10; 

signed char distance = 1; 
int sleep = 1;
static int time = 0;

void wdt_c_handler()
{
  static int secCount = 0;
  static int dsecCount = 0; 
  secCount ++;
  dsecCount ++;
  time++;
  //sleep mode
  if(time >= 1800){
    sleep = 0;
    fillRectangle(0,0,screenWidth, screenHeight, COLOR_BLACK);
    time = 0;
  }
  //reset sound 
  if (secCount == 150) {    
    buzzer_set_period(0);
    secCount = 0;
  }
  //how fast the animation moves 
  if(dsecCount == 30){
    dsecCount = 0;
    redrawScreen = 1;
  }
}
  

void StartGame()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  shapeInit();//
  p2sw_init(15);// 
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  
  clearScreen(COLOR_BLACK);
  while (1) { /* forever */
    
    u_int switches = p2sw_read(), i;
    char str[5];

    for(i=0; i<4; i++){
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;
      //down
      if(str[0] == '0'){ 
	buzzer_set_period(500);
	nextU_D += distance;
	sleep = 1;
	time = 0;
      }
      //up
      if(str[1] == '1'){
	nextU_D -= distance;
	sleep = 1;
	time = 0;
      }
      //right
      if(str[2] == '2'){
	nextL_R -= distance;
	sleep =1;
	time =0;
      }
      //left 
      if(str[3] == '3'){
	nextL_R += distance;
	sleep = 1;
	time=0;
      }
    }
    str[4] = 0;
    //CPU off
    if (sleep == 0){
      P1OUT &= ~LED_GREEN;
      or_sr(0x10);
    }
    
  
    
    if(redrawScreen && sleep == 1){
      redrawScreen = 0;

      fillRectangle(L_R,U_D,10,10,COLOR_BLACK);
      fillRectangle(nextL_R, nextU_D, 10, 10, COLOR_RED);
    
      
    //drawString5x7(20,20, "hello", COLOR_WHITE, COLOR_BLACK);
    // drawString11x16(30,30, "wassup", COLOR_WHITE, COLOR_BLACK);
      //one pixel behind
      L_R = nextL_R;
      U_D = nextU_D;
    }
    //turning on 
    if(sleep ==1){
      P1OUT &= ~LED_GREEN;	/* green off */
      or_sr(0x10);		/**< CPU OFF */
      P1OUT |= LED_GREEN;		/* green on */
    }
  }
}



