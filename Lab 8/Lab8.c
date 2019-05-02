// Lab8.c
// Runs on LM4F120 or TM4C123
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
// Last Modified: 11/6/2018 

// Specifications:
// Measure distance using slide pot, sample at 60 Hz
// maximum distance can be any value from 1.5 to 2cm
// minimum distance is 0 cm
// Calculate distance in fixed point, 0.001cm
// Analog Input connected to PD2=ADC5
// displays distance on Sitronox ST7735
// PF3, PF2, PF1 are heartbeats (use them in creative ways)
// 

#include <stdint.h>
#include <stdio.h>

#include "ST7735.h"
#include "TExaS.h"
#include "ADC.h"
#include "print.h"
#include "../inc/tm4c123gh6pm.h"

//*****the first three main programs are for debugging *****
// main1 tests just the ADC and slide pot, use debugger to see data
// main2 adds the LCD to the ADC and slide pot, ADC data is on ST7735
// main3 adds your convert function, position data is no ST7735

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
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
uint32_t Data;        // 12-bit ADC
uint32_t Position;    // 32-bit fixed-point 0.001 cm

uint32_t ADCMail = 1;
uint32_t ADCStatus = 0;

char TempADC[8] = {0x02, 0, 0x2E, 0, 0, 0, 0x0D, 0x03};

#define BUFFERSIZE 1
uint32_t dataBuffer[BUFFERSIZE];
int currentDataBufferIndex = 0;




int main_(void){       // single step this program and look at Data
  TExaS_Init();       // Bus clock is 80 MHz 
  ADC_Init();         // turn on ADC, set channel to 5
	
	ST7735_InitR(INITR_REDTAB);
  //ST7735_OutString("Lab 7 Fall 2018\nWelcome to EE319K");
  while(1){                
		//LCD_OutFix(3);
		
    Data = ADC_In();  // sample 12-bit channel 5
  }
}

int main2(void){
  TExaS_Init();       // Bus clock is 80 MHz 
  ADC_Init();         // turn on ADC, set channel to 5
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
	
	//2.75
	//3570 -> 2.75
	//80 -> 0
  while(1){           // use scope to measure execution time for ADC_In and LCD_OutDec           
    PF2 = 0x04;       // Profile ADC
    Data = ADC_In();  // sample 12-bit channel 5
    PF2 = 0x00;       // end of ADC Profile
    ST7735_SetCursor(0,0);
    PF1 = 0x02;       // Profile LCD
		
    LCD_OutDec(Data); 
    ST7735_OutString("    ");  // spaces cover up characters from last output
    PF1 = 0;          // end of LCD Profile
  }
}

// your function to convert ADC sample to distance (0.001cm)
uint32_t Convert(uint32_t input){
	if(input<2800){
		
		return (input*2155)/10000+178;
	}
	else{
		return (input*168)/100-4063;
	}
}
int main3(void){
  TExaS_Init();         // Bus clock is 80 MHz 
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  ADC_Init();         // turn on ADC, set channel to 5
  while(1){  
    PF2 ^= 0x04;      // Heartbeat
    Data = ADC_In();  // sample 12-bit channel 5
    PF3 = 0x08;       // Profile Convert
    Position = Convert(Data); 
    PF3 = 0;          // end of Convert Profile
    PF1 = 0x02;       // Profile LCD
    ST7735_SetCursor(0,0);
    LCD_OutDec(Data); ST7735_OutString("    "); 
    ST7735_SetCursor(6,0);
    LCD_OutFix(Position);
    //PF1 = 0;          // end of LCD Profile
  }
}   
int realmain(void){
  TExaS_Init();
  // your Lab 8
  EnableInterrupts();
  while(1){
  }
}

void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 1000;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000;
	NVIC_ST_CTRL_R = 0x07;
	NVIC_ST_RELOAD_R = 1333333;
}

void SysTick_Handler(void){
	GPIO_PORTF_DATA_R ^= 0x04;
	
	//PF1 ^= 0x7;
	
	if(currentDataBufferIndex == BUFFERSIZE){
		currentDataBufferIndex = 0;
		
		ADCStatus = 1;
		ADCMail = 0;
		
		for(int i=0;  i< BUFFERSIZE;i++){
			ADCMail+= dataBuffer[i];
		}
		ADCMail /= BUFFERSIZE;
		
	}
	else{
		GPIO_PORTF_DATA_R ^= 0x02;
		dataBuffer[currentDataBufferIndex] = ADC_In();
		GPIO_PORTF_DATA_R ^= 0x02;
		currentDataBufferIndex++;
	}
	
}

int ourmain(void){
	TExaS_Init();
	ADC_Init();
	ST7735_InitR(INITR_REDTAB);
	PortF_Init();
	SysTick_Init();
	
	int breath = 0;
	while(1){
		
		breath++;
		breath = breath % 50000000;
		
		if(breath==0){
			//PF2 ^= 0x7;
		}
		
		if(ADCStatus==1){
			ADCStatus = 0;
			Position = Convert(ADCMail);
			
			GPIO_PORTF_DATA_R ^= 0x01;
			ST7735_OutString("    ");
			ST7735_SetCursor(0,0);
			LCD_OutFix(Position);
			GPIO_PORTF_DATA_R ^= 0x01;
		}
		
	}
	
	
}
int main(){
	return ourmain();
}

