// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 11/6/2018
// Student names: Akarsh Kumar and Rithvik Ramesh
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void){
	//You must turn on bit 0 in RCGCSSI
	//and then wait 4 cycles.Access to SSI0 without a clock.
	//SYSCTL_RCGCSSI_R |= 1;
	
	SYSCTL_RCGCGPIO_R |= 1;
	
	uint32_t delay = SYSCTL_RCGCGPIO_R;
	
	SYSCTL_RCGC2_R |= 0x00000008;   // 1) activate clock for Port D

  delay = SYSCTL_RCGC2_R;         //    allow time for clock to stabilize

  //GPIO_PORTE_DIR_R &= ~0x04;      // 2) make PE4 input
	GPIO_PORTD_DIR_R &= ~0x04;      // 2) make PD2 input

  //GPIO_PORTE_AFSEL_R |= 0x04;     // 3) enable alternate function on PE2
	GPIO_PORTD_AFSEL_R |= 0x04;     // 3) enable alternate function on PD2

  //GPIO_PORTE_DEN_R &= ~0x04;      // 4) disable digital I/O on PE2
	GPIO_PORTD_DEN_R &= ~0x04;      // 4) disable digital I/O on PD2

  //GPIO_PORTE_AMSEL_R |= 0x04;     // 5) enable analog function on PE2
	GPIO_PORTD_AMSEL_R |= 0x04;     // 5) enable analog function on PD2

  SYSCTL_RCGCADC_R |= 0x01;   // 6) activate ADC0

  delay = SYSCTL_RCGC2_R;        

  //SYSCTL_RCGC0_R &= ~0x00000300;  // 7) configure for 125K
	ADC0_PC_R = 0x01;

  ADC0_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority

  ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3

  ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger

  ADC0_SSMUX3_R &= ~0x000F;       // 11) clear SS3 field

  //ADC0_SSMUX3_R += 9;             //    set channel Ain9 (PE4)
	//ADC0_SSMUX3_R += 5;             //    set channel Ain5 (PD2)
	ADC0_SSMUX3_R &= 0xFFFFFFF0;
	ADC0_SSMUX3_R += 5;
	ADC0_SSCTL3_R = 6;

  //ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0

  ADC0_ACTSS_R |= 0x0008;         // 13) enable sample sequencer 3
	
}

//------------ADC_In------------
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


