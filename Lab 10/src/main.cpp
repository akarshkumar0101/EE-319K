// main.cpp
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10 in C++

// Last Modified: 4/19/2018 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2017

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2017

 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#define RELEASE

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

#include "AKMath.h"
#include "Game.h"
#include "Camera.h"
#include "Matrix3x3.h"
#include "Vector.h"
#include "VectorMath.h"
#include "gamemain.h"
#include "Display.h"
#include "Texture.h"


#ifdef RELEASE

#include "PLL.h"
#include "ST7735.h"
#include "Random.h"
#include "PLL.h"
#include "SlidePot.h"
#include "Images.h"
#include "UART.h"
#include "Timer0.h"
#include "Timer1.h"
#include "PortInit.h"
#include "ADCSWTrigger.h"
#include "DAC.h"

#include "DrawST7735.h"

#else

#include <iostream>
#include "DrawOpenGL.h"

#endif

#ifdef RELEASE
SlidePot my(1500,0);

extern "C" void DisableInterrupts(void);
extern "C" void EnableInterrupts(void);
extern "C" void SysTick_Handler(void);

// Creating a struct for the Sprite.
typedef enum {dead,alive} status_t;
struct sprite{
  uint32_t x;      // x coordinate
  uint32_t y;      // y coordinate
  const unsigned short *image; // ptr->image
  status_t life;            // dead/alive
};          
typedef struct sprite sprite_t;

sprite_t bill={60,9,SmallEnemy20pointB,alive};

uint32_t time = 0;
volatile uint32_t flag;
void background(void){
  flag = 1; // semaphore
  if(bill.life == alive){
    bill.y++;
  }
  if(bill.y>155){
    bill.life = dead;
  }
}
void clock(void){
  time++;
}

#endif


int main(void){
#ifdef RELEASE
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
  Output_Init();
    initPort();
    //SysTick_Init(40000000);

    ADC_Init89();
	
	
  Timer0_Init(&background,1600000); // 50 Hz
  //Timer1_Init(&clock,80000000); // 1 Hz 
  EnableInterrupts();
  ST7735_DrawBitmap(52, 159, PlayerShip0, 18,8); // player ship middle bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);
  ST7735_DrawBitmap(100, 9, SmallEnemy30pointB, 16,10);

#endif
    
	//displayInitScreen();
	
	/*
	while(true){
        ST7735_FillScreen(0);
				//ST7735_FillRect(50,10,50,20,Color(255,0,0).color);
        //ST7735_FillRect(10,20, 10,10, Color(255,255,0).color);
        ST7735_DrawBitmap(50,50,gunTexture,28,32);
        //ST7735_DrawBitmap(50,50,zombieTexture,18,30);
	}
	*/
	
	
	while(false){
		uint32_t joystickdata[4];
		
		ADC_In89(joystickdata);
		
		//joystickdata[0] = ADCConvert(joystickdata[0]);
		//joystickdata[1] = ADCConvert(joystickdata[1]);
		
		//0 is right stick(camera) vertical inverted
		//1 is right stick(camera) horizontal proper
		//2 is left stick(move) vertical proper
		//3 is left stick(move) horizontal inverted
		
		
		ST7735_SetCursor(0,0);
		ST7735_OutString("    ");
		ST7735_SetCursor(0,0);
		ST7735_OutUDec(joystickdata[0]&0xFFF);
		
		ST7735_SetCursor(0,1);
		ST7735_OutString("    ");
		ST7735_SetCursor(0,1);
		ST7735_OutUDec(joystickdata[1] & 0xFFF);
		
		ST7735_SetCursor(0,2);
		ST7735_OutString("    ");
		ST7735_SetCursor(0,2);
		ST7735_OutUDec(joystickdata[2]& 0xFFF);
		
		ST7735_SetCursor(0,3); 
		ST7735_OutString("    ");
		ST7735_SetCursor(0,3);
		ST7735_OutUDec(joystickdata[3] & 0xFFF);
		
			
	}
	
    
	mainf();
	
	/*
  while(bill.life == alive){
    while(flag==0){};
    flag = 0;
    ST7735_DrawBitmap(bill.x,bill.y,bill.image,16,10);
  }

  ST7735_FillScreen(0x0000);            // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString((char*)"GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_SetTextColor(ST7735_WHITE);
  ST7735_OutString((char*)"Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString((char*)"Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_SetTextColor(ST7735_WHITE);
  while(1){
    while(flag==0){};
    flag = 0;
    ST7735_SetCursor(2, 4);
    ST7735_OutUDec(time);
  }
	*/

}



