// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 3-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"

#include "Timer0A.h"

//const unsigned int SineWave[64] = {32,35,38,41,44,47,49,51,54,56,58,59,61,62,62,63,63,63,62,62,61,59,58,56,54,51,49,47,44,41,38,35,32,28,25,22,19,16,13,11,9,7,5,3,2,1,1,0,0,0,1,1,2,3,5,7,9,11,13,16,19,22,25,28};
//unsigned int Index = 0;

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
/*
void PF_Init(void){
	volatile int nop3;
	SYSCTL_RCGCGPIO_R |= 0x020;
	nop3;
	nop3;
	nop3;
	GPIO_PORTF_DIR_R |= 0x0F;
	GPIO_PORTF_DEN_R |= 0x0F;
	GPIO_PORTF_DATA_R = 0x00;
}
*/

#define E0 3792
#define F0 3579
#define Gb0 3378
#define G0 3189
#define Ab0 3010
#define A 2841
#define Bb 2681
#define B 2531
#define C 2389
#define Db 2255
#define D 2128
#define Eb 2009
#define E 1896
#define F 1789
#define Gb 1689
#define G 1594
#define Ab 1505
#define A2 1421
#define Bb2 1341
#define B2 1265
#define L8 30769231
#define L16 15384615
#define L85 46153846
#define L45 92307692
#define L4 61538462
#define L32 7692308



uint16_t songLen = 120;
uint16_t frequencies[] = {B,C,D,E,D,B,A,G0,B,B,B,C,D,E,D,E,D,C,B,C,B,A,G0,B,E0,E0,G0,A,B,A,G0,Gb0,G0,E0,G0,Gb0,E0,Gb0,G0,A,B,A,G0,Gb0,G0,G0,E,G,A2,B2,A2,Gb,E,D,E,E,E,G,A2,B2,A2,B2,A2,G,Gb,G,Gb,E,D,E,E,Gb,G,A2,B2,A2,G,Gb,A2,G,E,Gb,D,D,E,D,C,B,D,C,D,C,B,Bb,C,B,B,D,Eb,Gb,G,F,Eb,F,Eb,D,D,C,B,A,B,C,B,A,G0,G0};
uint32_t timeDuration[] = {L8,L8,L85,L16,L8,L85,L16,L8,L45,L8,L8,L8,L8,L16,L16,L16,L16,L16,L16,L16,L16,L16,L16,L45,L8,L8,L8,L85,L16,L8,L8,L8,L8,L45,L4,L8,L8,L8,L8,L8,L32,L32,L85,L8,L45,L8,L8,L8,L85,L16,L8,L85,L16,L8,L45,L8,L8,L8,L8,L16,L16,L16,L16,L16,L16,L16,L16,L16,L16,L45,L8,L8,L8,L85,L16,L8,L8,L8,L32,L8,L85,L16,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L8,L16,L16,L16,L16,L45,L4,L8,L8,L8,L8,L8,L85,L16,L45};

uint8_t envelope[] = {2,4,6,8,8,7,6,5,4,3,2,1};




int runI = 0;
int playing = 0; 


void switchNotes(void){
	//setVolume(envelope[runI]);
	Sound_Play(frequencies[runI]);
	//Sound_Play(1000);
	//Timer0A_Init(switchNotes, timeDuration[runI]);
	TIMER0_TAILR_R = timeDuration[runI];
	//Timer0A_Init(switchNotes, 80000000);
	runI++;
	runI%=songLen;
	if(runI==0){
		playing = 0;
		Timer0A_Init(switchNotes, 0);
		Sound_Play(0);
	}
}






int main(void){ 
	static int cycleCount = 0;
	// see line 37 question
	//int32_t oldPE = GPIO_PORTE_DATA_R;
	//int32_t PE = GPIO_PORTE_DATA_R ;
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
  // other initialization
  EnableInterrupts();
	//PF_Init();
	
	
  while(1){
		uint32_t pianoIn = Piano_In();
		if(playing == 0){			
			if(pianoIn==7){
				Timer0A_Init(switchNotes, 1);
				playing = 1;
			}
			Sound_Play(1700*pianoIn);
			
		}
		
		if(pianoIn == 2){										// STOP implementation
			playing = 0;
			Timer0A_Init(switchNotes, 0);
		}
		
		cycleCount = (cycleCount+1)%200000;
		if(cycleCount==0){
			GPIO_PORTE_DATA_R ^= 0x10;
		}
		
  }
	
}

