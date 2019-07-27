	
#include "../inc/tm4c123gh6pm.h"


void initPort(){
	
	SYSCTL_RCGCGPIO_R |= (0xFF);
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
	
	
	// DAC init
	volatile int nop2;
	SYSCTL_RCGCGPIO_R |= 0x02;
	nop2;
	nop2;
	nop2;
	GPIO_PORTB_DIR_R |= 0x3F;
	GPIO_PORTB_DEN_R |= 0x3F;
	
	//PA init
	volatile int nop3;
	SYSCTL_RCGCGPIO_R |= 0x01;
	nop3;
	nop3;
	nop3;
	GPIO_PORTA_DIR_R |= 0xFF;//FC
	GPIO_PORTA_DEN_R |= 0xFF;//FC
	
	//PE Init
	volatile int nop4;
	SYSCTL_RCGCGPIO_R |= 0x10;
	nop4;
	nop4;
	nop4;
	GPIO_PORTE_DIR_R &= ~0x0F;
	GPIO_PORTE_DEN_R |= 0x0F;
	
	
	//PB Init
	volatile int nop5;
	SYSCTL_RCGCGPIO_R |= 0x02;
	nop5;
	nop5;
	nop5;
	GPIO_PORTB_DIR_R &= ~0xC0;
	GPIO_PORTB_DEN_R |= 0xC0;
	
	GPIO_PORTB_PUR_R |= 0xC0;
	
	
	
	
	
	/*
	// ADC init
	//You must turn on bit 0 in RCGCSSI

	//and then wait 4 cycles.Access to SSI0 without a clock.

	//SYSCTL_RCGCSSI_R |= 1;
	SYSCTL_RCGCGPIO_R |= 1;
	uint32_t delay1 = SYSCTL_RCGCGPIO_R;
	SYSCTL_RCGC2_R |= 0x00000008;   // 1) activate clock for Port D
  delay1 = SYSCTL_RCGC2_R;         //    allow time for clock to stabilize
  //GPIO_PORTE_DIR_R &= ~0x04;      // 2) make PE4 input
	GPIO_PORTD_DIR_R &= ~0x04;      // 2) make PD2 input
  //GPIO_PORTE_AFSEL_R |= 0x04;     // 3) enable alternate function on PE2
	GPIO_PORTD_AFSEL_R |= 0x04;     // 3) enable alternate function on PD2
  //GPIO_PORTE_DEN_R &= ~0x04;      // 4) disable digital I/O on PE2
	GPIO_PORTD_DEN_R &= ~0x04;      // 4) disable digital I/O on PD2
  //GPIO_PORTE_AMSEL_R |= 0x04;     // 5) enable analog function on PE2
	GPIO_PORTD_AMSEL_R |= 0x04;     // 5) enable analog function on PD2
  SYSCTL_RCGCADC_R |= 0x01;   // 6) activate ADC0
  delay1 = SYSCTL_RCGC2_R;        
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
	
	*/
	
	
	//UART init
  SYSCTL_RCGCUART_R |= 0x00000002;  // activate UART1
  SYSCTL_RCGCGPIO_R |= 0x00000004;  // activate port C
	uint32_t delay3;
	for(int i=0;i<100;i++){
		delay3 ++;
	}     //    allow time for clock to stabilize
  UART1_CTL_R &= ~0x00000001;    // disable UART
  UART1_IBRD_R = 43;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
  UART1_FBRD_R = 26;     // FBRD = round(0.40278 * 64) = 26
  UART1_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
  UART1_CTL_R |= 0x00000301;     // enable UART
  GPIO_PORTC_AFSEL_R |= 0x30;    // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0x30;      // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_AMSEL_R &= ~0x30;   // disable analog on PC5-4
	UART1_IM_R |= 0x10;
	UART1_IFLS_R &= ~0x38;
	UART1_IFLS_R |= 0x10;
	NVIC_PRI1_R = (NVIC_PRI1_R&0xFF1FFFFF)+0x00800000;
	NVIC_EN0_R |= 0x40;
	
	
}

void SysTick_Init(unsigned long period){

	/*
	NVIC_ST_CTRL_R = 0;

	NVIC_ST_RELOAD_R = period-1;                                        // putting something here for now

	NVIC_ST_CURRENT_R = 0;

	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000;

	NVIC_ST_CTRL_R = 0x07;
	*/
	
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CTRL_R |= 0x05;
	NVIC_ST_CTRL_R &= ~0x02;
	

}

uint32_t ADCConvert(uint32_t input){
	if(input<2800){
		return (input*2155)/10000+178;
	}
	else{
		return (input*168)/100-4063;
	}
}
