// StepperMotorController.c starter file EE319K HW6 
// Runs on TM4C123
// Akarsh Kumar
// EID: ak39969
// March 12, 2019
/*
; You are given a simple stepper motor software system with one input and
; four outputs. This program runs, but you are asked to add minimally intrusive
; debugging instruments to verify it is running properly. 
;   If the input PA4 is low, the stepper motor outputs cycle 10,6,5,9,...
;   If the input PA4 is high, the stepper motor outputs cycle 5,6,10,9,...
;   Insert debugging instruments which gather data (state and timing)
;   to verify that the system is functioning as expected.
; Hardware connections (External: One button and four outputs to stepper motor)
;  PA4 is Button input  (1 means pressed, 0 means not pressed)
;  PE3-0 are stepper motor outputs 
;  PF2 is Blue LED on Launchpad used as a heartbeat
; Instrumentation data to be gathered is as follows:
; After every output to Port E, collect one state and time entry. 
; The state information is the 5 bits on Port A bit 4 and Port E PE3-0
;   place one 8-bit entry in your Data Buffer  
; The time information is the 24-bit time difference between this output and the previous (in 12.5ns units)
;   place one 32-bit entry in the Time Buffer
;    24-bit value of the SysTick's Current register (NVIC_ST_CURRENT_R)
;    you must handle the roll over as Current goes 3,2,1,0,0x00FFFFFF,0xFFFFFE,
; Note: The size of both buffers is 100 entries. Once you fill these
;       entries you should stop collecting data
; The heartbeat is an indicator of the running of the program. 
; On each iteration of the main loop of your program toggle the 
; LED to indicate that your code(system) is live (not stuck or dead).
*/

#include "TExaS.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
void EnableInterrupts(void);

// write these three functions
// Initialize SysTick with RELOAD at 0xFFFFFF running at bus clock.
void SysTick_Init(void){
	// write this
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CTRL_R |= 0x05;
	NVIC_ST_CTRL_R &= ~0x02;
	
}

//States	SPACE 100
uint8_t DataBuffer[100];

//Seperator DCD 0

//Times	SPACE 400
uint32_t TimeBuffer[100];
	
//dataIndexCount DCB 0
uint8_t dataIndexCount = 0;

//prevTimeMeasure DCD 0x00FFFFFF
uint32_t prevTimeMeasure = 0x00FFFFFF;

	
//LEDCountDown DCD 1
uint32_t LEDCountDown = 1;


//FULLF2			   EQU 0xFF
#define FULLF2 0xFF
//FULLF 	 		   EQU 0xFFFFFFFF
#define FULLF 0xFFFFFFFF
//MASK24BIT	       EQU 0x00FFFFFF
#define MASK24BIT 0x00FFFFFF


void Debug_Init(void){
		// write
		uint8_t i = 0;
		int delay = 0;
		SysTick_Init();
		for(i = 0; i < 100; i++){
			DataBuffer[i] = FULLF2;
			TimeBuffer[i] = FULLF;
		}
		
		SYSCTL_RCGCGPIO_R |= 0x20;
		
		for(i=0; i <10; i++){
			delay ++;
			if(delay%2==0){
				delay/=2;
			}
		}
		GPIO_PORTF_DIR_R |= 0x0E;
		GPIO_PORTF_DEN_R |= 0x0E;
		
		GPIO_PORTF_DATA_R |= 0x0E;
}
void Debug_Capture(void){
		// write this
		uint32_t currentTime;
		uint32_t dt;
		if(dataIndexCount<100){
			uint8_t data = 0;
			data |= (GPIO_PORTE_DATA_R & 0x0F);
			data |= (GPIO_PORTA_DATA_R & 0x10);
			DataBuffer[dataIndexCount] = data;
			
			currentTime = NVIC_ST_CURRENT_R & MASK24BIT;
			dt = prevTimeMeasure - currentTime;
			/*
			if(((int32_t) dt) < 0){
				dt += (MASK24BIT);
				dt += 1;
			}
			*/
			TimeBuffer[dataIndexCount++] = dt & MASK24BIT;
			
			prevTimeMeasure = currentTime;
		}
		else{
			
		}
}


uint32_t const Stepper[4]={5,6,10,9};
// Initialize stepper motor interface
void Stepper_Init(void){ volatile int delay;
	SYSCTL_RCGCGPIO_R |= 0x11;   // enable clock to A,E
	delay = 0;
  GPIO_PORTE_DIR_R |= 0x0F;     // output on PE3-0
  GPIO_PORTA_DIR_R &= ~0x10;    // input PA4,
  GPIO_PORTE_DEN_R |= 0x0F;     // enable digital on PE3-0
  GPIO_PORTA_DEN_R |= 0x10;     // enable digital on PA4
}
// Step the motor 
// dir determines the rotational direction
// Input: dir is -1(CCW) 0(stop) 1(CW)
// Output: None
void Stepper_Step(int dir){
static int32_t index;     // index into Stepper table 0,1,2,3
	index = (index+dir)&0x03;
  GPIO_PORTE_DATA_R = Stepper[index]; // change PE3-PE0
  Debug_Capture(); // call to your function
}
void Wait(uint32_t delay){
	while(delay){
		delay--;
	}
}
// edit the following only if you need to move pins from PA4, PE3-0      
// logic analyzer on the real board
#define PA4       (*((volatile unsigned long *)0x40004040))
#define PE30       (*((volatile unsigned long *)0x4002403C))
void SendDataToLogicAnalyzer(void){
  UART0_DR_R = 0x80|PA4|PE30;
}
int main(void){ uint32_t last,now;
	int32_t Direction; // -1 for CCW, 0 for stop 1 for CW
  TExaS_Init(&SendDataToLogicAnalyzer);  // activate logic analyzer and set system clock to 80 MHz
  Stepper_Init();    // initialize stepper motor
  Debug_Init();      // call to your function
  EnableInterrupts();   
	last = GPIO_PORTA_DATA_R&0x10; // PA4
	Direction = 1; // forward
  while(1){
		now = GPIO_PORTA_DATA_R&0x10; // PA4
    if((now==0x10)&&(last==0)){   // new touch
			Direction++; // cycles -1,0,1
			if(Direction==2){
				Direction = -1;
			}
		}
		last = now;   // setup for next loop
		Stepper_Step(Direction);
		Wait(800000); // about 50ms
	}
}




