// StepperMotorController.c starter file EE319K Lab 5
// Runs on TM4C123
// Finite state machine to operate a stepper motor.  
// Jonathan Valvano
// January 18, 2019

// Hardware connections (External: two input buttons and four outputs to stepper motor)
//  PA5 is Wash input  (1 means pressed, 0 means not pressed)
//  PA4 is Wiper input  (1 means pressed, 0 means not pressed)
//  PE5 is Water pump output (toggle means washing)
//  PE4-0 are stepper motor outputs 
//  PF1 PF2 or PF3 control the LED on Launchpad used as a heartbeat
//  PB6 is LED output (1 activates external LED on protoboard)

#include "SysTick.h"
#include "TExaS.h"
#include <stdint.h>
#include <stdbool.h>
#include "../inc/tm4c123gh6pm.h"


void EnableInterrupts(void);
// edit the following only if you need to move pins from PA4, PE3-0      
// logic analyzer on the real board
#define PA4       (*((volatile unsigned long *)0x40004040))
#define PE50      (*((volatile unsigned long *)0x400240FC))
	
//GPIO_PORTE_DATA_R  EQU 0x400243FC;
//GPIO_PORTE_DIR_R   EQU 0x40024400;
//GPIO_PORTE_AFSEL_R EQU 0x40024420
//GPIO_PORTE_DEN_R   EQU 0x4002451C
/*
; PortF device registers
GPIO_PORTF_DATA_R  EQU 0x400253FC
GPIO_PORTF_DIR_R   EQU 0x40025400
GPIO_PORTF_AFSEL_R EQU 0x40025420
GPIO_PORTF_PUR_R   EQU 0x40025510
GPIO_PORTF_DEN_R   EQU 0x4002551C
GPIO_PORTF_LOCK_R  EQU 0x40025520
GPIO_PORTF_CR_R    EQU 0x40025524
GPIO_LOCK_KEY      EQU 0x4C4F434B  ; Unlocks the GPIO_CR register
*/
//#define SYSCTL_RCGCGPIO_R		(*((volatile unsigned long *)0x400FE608))




void SendDataToLogicAnalyzer(void){
  UART0_DR_R = 0x80|(PA4<<2)|PE50;
}

struct State {
	uint8_t wiperState;
	uint8_t heartBeatState;
	uint8_t soapState;
	uint8_t sleepTime;
	uint8_t nextState[4];
	
};

#define HS1 0
#define HS2 1
#define WS 2
#define WSS 20
#define UWSS 38

#define IN00 0 
#define IN01 1
#define IN10 2
#define IN11 3


uint8_t wiperCycle[18] = {1, 2, 4, 8, 16, 1, 2, 4, 8, 16, 8, 4, 2, 1, 16, 8, 4, 2};
#define wiperCycleLength 18

struct State FSM[56];
#define FSMnumStates 56


#define HP1SLEEP 100
#define HP2SLEEP 100
#define STATESLEEP 100
#define ULTRASTATESLEEP 50
	
int getBlockNum(int iabs){
	return (iabs-2)/18;
}
int getAbsIndexInBlock(int reli, int block){
	return block*18+reli+2;
}
int getRelIndexWithinBlock(int absi){
	int block = getBlockNum(absi);
	return absi-block*18-2;
}
int nextReli(int reli){
	return (reli+1)%18;
}
bool isFirstIndex(int iabs){
	return getRelIndexWithinBlock(iabs) == 0;
}
bool isLastIndex(int iabs){
	return getRelIndexWithinBlock(iabs) == 17;
}

int absIndexOfFirst(int block){
	return getAbsIndexInBlock(0, block);
}
int absIndexOfLast(int block){
	return getAbsIndexInBlock(17, block);
}

int nextAbsi(int absi){
	int block = getBlockNum(absi);
	int reli = getRelIndexWithinBlock(absi);
	int newreli = nextReli(reli);
	return getAbsIndexInBlock(newreli,block);
}


void FSM_Init(){
	int i, reli, nextState, block;
	struct State HomePos = {1, 1, 0, HP1SLEEP, {HS2,WS,WSS,UWSS}};
	struct State HomePosHBOff = {1, 0, 0, HP2SLEEP, {HS1,WS,WSS,UWSS}};
	
	FSM[0] = HomePos;
	FSM[1] = HomePosHBOff;
	
	for (i = 2; i < FSMnumStates; i++){
		FSM[i].sleepTime = STATESLEEP;
		FSM[i].wiperState = wiperCycle[(i-2) % wiperCycleLength];
		FSM[i].heartBeatState = i % 2;
		
		block = getBlockNum(i);
		if(block == 1 || block == 2){
				FSM[i].soapState = i%2;
		}
		else{
			FSM[i].soapState = 0;
		}
		if(block == 2){
			FSM[i].sleepTime = ULTRASTATESLEEP;
		}
	}
	
	for(i = 2; i < FSMnumStates; i++){
		if(isFirstIndex(i)){
			FSM[i].nextState[IN00] = HS1;
		}
		/*
		else{
			if(isLastIndex(i)){
				FSM[i].nextState[IN00] = absIndexOfFirst(getBlockNum(i));
			}
			else{
				FSM[i].nextState[IN00] = (i+1);
			}
		}
		*/
	}
	
	for(reli = 0; reli < 18;reli++){
		if(reli!=0){
			//INPUT 00
			
			//block 0
			i = getAbsIndexInBlock(reli, 0);
			nextState = nextAbsi(i);
			FSM[i].nextState[IN00] = nextState;
			
			//block 1
			i = getAbsIndexInBlock(reli, 1);
			FSM[i].nextState[IN00] = nextState;
			
			//block 2
			i = getAbsIndexInBlock(reli, 2);
			FSM[i].nextState[IN00] = nextState;
		}
		
		
		//INPUT 01
		
		//block 0
		i = getAbsIndexInBlock(reli, 0);
		nextState = nextAbsi(i);
		FSM[i].nextState[IN01] = nextState;
		
		//block 1
		i = getAbsIndexInBlock(reli, 1);
		FSM[i].nextState[IN01] = nextState;
		
		//block 2
		i = getAbsIndexInBlock(reli, 2);
		FSM[i].nextState[IN01] = nextState;
		
		
		//INPUT 10
		
		//block 1
		i = getAbsIndexInBlock(reli, 1);
		nextState = nextAbsi(i);
		FSM[i].nextState[IN10] = nextState;
		
		//block 0
		i = getAbsIndexInBlock(reli, 0);
		FSM[i].nextState[IN10] = nextState;
		
		//block 2
		i = getAbsIndexInBlock(reli, 2);
		FSM[i].nextState[IN10] = nextState;
		
		//INPUT 11
		
		//block 2
		i = getAbsIndexInBlock(reli, 2);
		nextState = nextAbsi(i);
		FSM[i].nextState[IN11] = nextState;
		
		//block 0
		i = getAbsIndexInBlock(reli, 0);
		FSM[i].nextState[IN11] = nextState;
		
		//block 1
		i = getAbsIndexInBlock(reli, 1);
		FSM[i].nextState[IN11] = nextState;
	}
}

void Ports_Init(){
	//E [4-0] is motor output
	//A [3,2] is switch inputs
	SYSCTL_RCGCGPIO_R |= 49; // turn on clock for ports A, E and F
	//ABCDEF
	//100011
	
	//sleep for some time
	SysTick_Wait(10);
	
	//LDR R1, =GPIO_PORTF_LOCK_R
	 //LDR R0, =GPIO_LOCK_KEY
	 //STR R0, [R1]
	 GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	 //LDR R1, =GPIO_PORTF_CR_R
	 //LDR R0, [R1]
	 //ORR R0, #0xFF
	 GPIO_PORTF_CR_R |= 0xFF;
	 //STR R0, [R1]
	 
	 //LDR R1, =GPIO_PORTF_PUR_R
	 //LDR R0, [R1]
	 //ORR R0, #0x10
	 GPIO_PORTF_PUR_R |= 0x10;
	 //STR R0, [R1]
	
	GPIO_PORTA_DIR_R &= ~12; // pins 3-2 are input
	GPIO_PORTE_DIR_R |= 31; // pins 4-0 are output
	GPIO_PORTF_DIR_R |= 0xFF; //all pins are output
	
	GPIO_PORTA_DEN_R |= 12; // turn on pins 3-2
	GPIO_PORTE_DEN_R |= 31; // turn on pins 4-0
	GPIO_PORTF_DEN_R |= 0xFF; // turn on all pins
	
}


int main(void){
	uint8_t currentState = HS1;
	uint8_t input;
	uint8_t lightOut;
	
  TExaS_Init(&SendDataToLogicAnalyzer);    // activate logic analyzer and set system clock to 80 MHz
  SysTick_Init();   
// you initialize your system here
	
	Ports_Init();
	
	FSM_Init();
	
	
  EnableInterrupts();   
	
	
	
  while(1){
// output
		GPIO_PORTE_DATA_R = FSM[currentState].wiperState;
		//GPIO_PORTE_DATA_R &= ~(FSM[currentState].wiperState);
		//GPIO_PORTE_DATA_R = out;
		lightOut = 0;
		lightOut |= (FSM[currentState].heartBeatState << 1);
		lightOut |= (FSM[currentState].soapState << 2);
		GPIO_PORTF_DATA_R = lightOut;
		
// wait
		SysTick_Wait1ms(FSM[currentState].sleepTime);
// input
		input = GPIO_PORTA_DATA_R & 12;// pins 3 and 2 are input
		input = input >> 2;
// next
		currentState = FSM[currentState].nextState[input];
  }
}



