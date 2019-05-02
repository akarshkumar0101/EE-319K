// dac.c
// This software configures DAC output
// Lab 6 requires a minimum of 4 bits for the DAC, but you could have 5 or 6 bits
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none


int32_t volume = 8;

void DAC_Init(void){
	volatile int nop2;
	SYSCTL_RCGCGPIO_R |= 0x02;
	nop2;
	nop2;
	nop2;
	GPIO_PORTB_DIR_R |= 0x3F;
	GPIO_PORTB_DEN_R |= 0x3F;
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(unsigned int data){
	int32_t finaldata;
	finaldata = data & 0x3F;
	finaldata = (finaldata * volume) / 16;
	//finaldata = finaldata * 15 / 16;
	GPIO_PORTB_DATA_R = finaldata;
}

void setVolume(int32_t vol){
	volume = vol;
}

