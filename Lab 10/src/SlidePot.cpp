// SlidePot.cpp
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 3/28/2018 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "SlidePot.h"
#include "../inc/tm4c123gh6pm.h"



// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void){ 
	//You must turn on bit 0 in RCGCSSI
	//and then wait 4 cycles.Access to SSI0 without a clock.
	//SYSCTL_RCGCSSI_R |= 1;
	
	
}






//------------ADCIn------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC_In(void){  

	uint32_t res;
	ADC0_PSSI_R = 0x0008;            //init ss 3
	
	
  while((ADC0_RIS_R&0x08)==0){};   // busy wait conversion
  
		
		//reading result
	res = ADC0_SSFIFO3_R&0xFFF;   
		
 
		//let it know completed 
	ADC0_ISC_R = 0x0008;             

  return res;
		
}

// constructor, invoked on creation of class
// m and b are linear calibration coeffients 
SlidePot::SlidePot(uint32_t m, uint32_t b){
// lab 8
}

void SlidePot::Save(uint32_t n){
// lab 9
}
uint32_t SlidePot::Convert(uint32_t n){
  // lab 8
  return 0;
}

void SlidePot::Sync(void){
// lab 8
}

uint32_t SlidePot::ADCsample(void){ // return ADC sample value (0 to 4095)

  return 0;
}

uint32_t SlidePot::Distance(void){  // return distance value (0 to 2000), 0.001cm
// lab 8
  return 0;
}


