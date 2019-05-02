// Lab9.c
// Runs on LM4F120 or TM4C123
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
// Last Modified: 11/14/2018

// Analog Input connected to PE2=ADC1
// displays on Sitronox ST7735
// PF3, PF2, PF1 are heartbeats
// This U0Rx PC4 (in) is connected to other LaunchPad PC5 (out)
// This U0Tx PC5 (out) is connected to other LaunchPad PC4 (in)
// This ground is connected to other LaunchPad ground
// * Start with where you left off in Lab8. 
// * Get Lab8 code working in this project.
// * Understand what parts of your main have to move into the UART1_Handler ISR
// * Rewrite the SysTickHandler
// * Implement the s/w Fifo on the receiver end 
//    (we suggest implementing and testing this first)

#include <stdint.h>

#include "ST7735.h"
#include "PLL.h"
#include "ADC.h"
#include "print.h"
#include "../inc/tm4c123gh6pm.h"
#include "Uart.h"
#include "FiFo.h"

//*****the first three main programs are for debugging *****
// main1 tests just the ADC and slide pot, use debugger to see data
// main2 adds the LCD to the ADC and slide pot, ADC data is on Nokia
// main3 adds your convert function, position data is no Nokia

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
uint32_t Data;      // 12-bit ADC
uint32_t Position;  // 32-bit fixed-point 0.001 cm



void SysTick_Init(void);

uint32_t ADCMail = 1;
uint32_t ADCStatus = 0;

int TxCounter;


#define BUFFERSIZE 1
uint32_t dataBuffer[BUFFERSIZE];
int currentDataBufferIndex = 0;

// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x20;
	uint32_t delay = SYSCTL_RCGCGPIO_R;
	for(int i=0; i <10;i++){
		delay+=(i*delay);
	}
	
	
	//GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	//GPIO_PORTF_CR_R |= 0xFF;
	
	
	 //GPIO_PORTF_PUR_R |= 0x10;
	 
	 
	 //; directional for port F
	GPIO_PORTF_DIR_R |= 0x0E;
	//GPIO_PORTF_DIR_R &= ~0x10;
	 
	 
	// ; data enable for port F
	GPIO_PORTF_DEN_R |= 0xE;
	
}




uint32_t Status[20];             // entries 0,7,12,19 should be false, others true
char GetData[10];  // entries 1 2 3 4 5 6 7 8 should be 1 2 3 4 5 6 7 8
int main1(void){ // Make this main to test FiFo
  Fifo_Init();   // Assuming a buffer of size 6
  for(;;){
    Status[0]  = Fifo_Get(&GetData[0]);  // should fail,    empty
    Status[1]  = Fifo_Put(1);            // should succeed, 1 
    Status[2]  = Fifo_Put(2);            // should succeed, 1 2
    Status[3]  = Fifo_Put(3);            // should succeed, 1 2 3
    Status[4]  = Fifo_Put(4);            // should succeed, 1 2 3 4
    Status[5]  = Fifo_Put(5);            // should succeed, 1 2 3 4 5
    Status[6]  = Fifo_Put(6);            // should succeed, 1 2 3 4 5 6
    Status[7]  = Fifo_Put(7);            // should fail,    1 2 3 4 5 6 
    Status[8]  = Fifo_Get(&GetData[1]);  // should succeed, 2 3 4 5 6
    Status[9]  = Fifo_Get(&GetData[2]);  // should succeed, 3 4 5 6
    Status[10] = Fifo_Put(7);            // should succeed, 3 4 5 6 7
    Status[11] = Fifo_Put(8);            // should succeed, 3 4 5 6 7 8
    Status[12] = Fifo_Put(9);            // should fail,    3 4 5 6 7 8 
    Status[13] = Fifo_Get(&GetData[3]);  // should succeed, 4 5 6 7 8
    Status[14] = Fifo_Get(&GetData[4]);  // should succeed, 5 6 7 8
    Status[15] = Fifo_Get(&GetData[5]);  // should succeed, 6 7 8
    Status[16] = Fifo_Get(&GetData[6]);  // should succeed, 7 8
    Status[17] = Fifo_Get(&GetData[7]);  // should succeed, 8
    Status[18] = Fifo_Get(&GetData[8]);  // should succeed, empty
    Status[19] = Fifo_Get(&GetData[9]);  // should fail,    empty
  }
}

// Get fit from excel and code the convert routine with the constants
// from the curve-fit
uint32_t Convert(uint32_t input){
	if(input<2800){
		
		return (input*2155)/10000+178;
	}
	else{
		return (input*168)/100-4063;
	}
}



// final main program for bidirectional communication
// Sender sends using SysTick Interrupt
// Receiver receives using RX
int main(void){ 
  
  PLL_Init(Bus80MHz);     // Bus clock is 80 MHz 
  ST7735_InitR(INITR_REDTAB);
  ADC_Init();    // initialize to sample ADC
  PortF_Init();
  Uart_Init();       // initialize UART
  ST7735_SetCursor(0,0);
  LCD_OutFix(0);
ST7735_OutString(" cm");
//Enable SysTick Interrupt by calling SysTick_Init
	SysTick_Init();
  EnableInterrupts();
  while(1){
	//	GPIO_PORTF_DATA_R ^=0x8;
    //--UUU--Complete this  - see lab manual
		//ST7735_SetCursor(0,0);
		//ST7735_OutString("hello");
		
		char c;
		char fi;
		while(Fifo_Get(&c) == 0 || c != 0x02){}
			
			
			
			
		//Fifo_Get(&fi);
		ST7735_SetCursor(0,0);
		for(int i = 0; i<5; i++){
		  ST7735_SetCursor(i,0);
			Fifo_Get(&fi);
			ST7735_OutChar(fi);
		}
		
		Fifo_Get(&fi);
		Fifo_Get(&fi);
		ST7735_SetCursor(6,0);
		ST7735_OutString(" cm");
		
	}
		
}

/* SysTick ISR
*/

void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000;
	NVIC_ST_CTRL_R = 0x07;
	NVIC_ST_RELOAD_R = 1333333;
}

void SysTick_Handler(void){
	GPIO_PORTF_DATA_R ^=0x08;
	
	Data = ADC_In();
	
	GPIO_PORTF_DATA_R ^=0x08;
	
	Position = Convert(Data);
	uint8_t msg[8] = {0x02, 0, 0x2E, 0, 0, 0, 0x0D, 0x03};
	
	msg[1] = Position/1000+0x30;
	msg[3] = (Position%1000)/100+0x30;
	msg[4] = (Position%100)/10+0x30;
	msg[5] = (Position%10)/1+0x30;
	
	for(int i=0; i <8;i++){
		Uart_OutChar(msg[i]);
	}
	TxCounter++;
	GPIO_PORTF_DATA_R ^=0x08;
}

