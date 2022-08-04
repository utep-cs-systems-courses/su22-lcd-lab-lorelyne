#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include <stdio.h>
#include "stateMachines.h"
#include <stdlib.h>
#include "buzzer.h"

//extern int soundASS();

#define LED_SLEEP BIT6

short redrawScreen = 1;

//direction of red cube
u_char U_D = 30;
u_char nextU_D = 30;

//left right direction
u_char L_R = 30;
u_char nextL_R = 30;

//cyan collison test
u_char a = 10;
u_char aNex=10;
u_char b = 10;
u_char bNex= 10;

signed char Speed = 1;

//variables for keeping track of the sleep
int sleep = 1;
static int t =0;


void wdt_c_handler()
{
  static int secCount = 0;
  static int dsecCount = 0;
  secCount ++;
  dsecCount ++;
  t++;
  
  // this is the timer for sleep
  if( t >= 1800 ){
    sleep = 0;
    fillRectangle(0,0,screenWidth,screenHeight, COLOR_BLACK);
    t=0;
  }
  
  if (secCount == 10) {		// once/sec 
    buzzer_set_period(0);
    secCount = 0;
  }
  
  if(dsecCount==25){
    dsecCount = 0;
    redrawScreen = 1;
  }
}

void StartGame(){
  
  P1DIR |= LED_SLEEP;		/**< RED led on when CPU on */
  P1OUT |= LED_SLEEP;
  configureClocks();
  lcd_init();
  shapeInit();
  p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */ 

  
  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    u_int switches = p2sw_read(), i;
    char str[5];
    
    for(i=0;i<4;i++){
      str[i] = (switches & (1<<i)) ? ' ' : '0'+i; //Show switch being pressed

      if(str[0]=='0'){
	assemSound(1);  //play buzzer
	nextU_D +=Speed; //up/down (adding) means go down
	sleep =1;
	t=0;
      }
      if(str[1]=='1'){
	assemSound(1); //play buzzer
	nextU_D -=Speed; //up/down (subtracting) means go up
	sleep =1;
	t=0;
    
      }
      if(str[2]=='2'){
	assemSound(2); //play buzzer
	nextL_R -=Speed;	//left/right (subtracting) means go left
	sleep =1;
	t=0;
      }
      if(str[3]=='3'){
	assemSound(3);//play buzzer
    nextL_R +=Speed; //left/right (subtracting) means go left
	sleep =1;
	t=0;
  
      }      
    }
    str[4] = 0;

    //keeping the CPU off
    if(sleep ==0){
      P1OUT &= ~LED_SLEEP;	/* off */
      or_sr(0x10);		/**< CPU OFF */
    }
    
    //we redraw screen here, update cube location and pos
    if (redrawScreen && sleep==1) {
      redrawScreen = 0;

      drawString11x16(30,60,"Cubix", COLOR_BLUE, COLOR_BLACK);

      fillRectangle(L_R,U_D,10,10, COLOR_BLACK);
      fillRectangle(nextL_R,nextU_D,10,10, COLOR_PURPLE);
   
      drawPixel(aNex,aNex,COLOR_RED);

      drawString5x7(20,20,str,COLOR_WHITE, COLOR_BLACK);
      
      L_R = nextL_R;	      
      U_D = nextU_D;
     
      //this is for the collsions with only dots
      if(aNex > nextL_R && aNex < nextL_R + 10 ){
	if( aNex > nextU_D && aNex < nextU_D + 10){
	  drawString5x7(30,90,"Game Over",COLOR_RED,COLOR_BLACK);
	}
      }
    }
    if(sleep==1){
      P1OUT &= ~LED_SLEEP;	/** off */
      or_sr(0x10);		/**< CPU OFF */
      P1OUT |= LED_SLEEP;	/** on */
    }
  }
  
}
