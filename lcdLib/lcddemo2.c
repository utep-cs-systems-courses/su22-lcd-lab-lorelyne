#include <libTimer.h>

#include "lcdutils.h"

#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */

int main(){

  configureClocks();

  lcd_init();

  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  // draw trianagle
  u_char offset_r = 10, offset_c = 10;
  for(int r=0; r<=50; r++){
    for(int c =0; c<=r; c++){
      drawPixel(offset_c+c+r, offset_r+r-c, COLOR_ORANGE);
    }
  }  
}
