// main.c
// Runs on LM4F120 or TM4C123
// Student names: put your names here
// Last modification date: change this to the last modification date or look very silly
// Last Modified: 4/11/2018 

// Analog Input connected to PD2=ADC5
// displays on Sitronox ST7735
// PF3, PF2, PF1 are heartbeats
// EE319K Lab 9, use U1Rx connected to PC4 interrupt
// EE319K Lab 9, use U1Tx connected to PC5 busy wait
// EE319K Lab 9 hardware
// System 1        System 2
//   PC4 ----<<----- PC5
//   PC5 ---->>----- PC4
//   Gnd ----------- Gnd

// main1 Understand UART interrupts
// main2 Implement and test the FIFO class on the receiver end 
//   import ST7735 code from Lab 7,8
// main3 convert UART0 to UART1, implement busy-wait on transmission
// final main for Lab 9
//   Import SlidePot and ADC code from Lab8. 
//   Figure out what to do in UART1_Handler ISR (receive message)
//   Figure out what to do in SysTickHandler (sample, convert, transmit message)
//   Figure out what to do in main (LCD output)

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "ST7735.h"
#include "PLL.h"
#include "SlidePot.h"
#include "print.h"
#include "UART.h"
#include "FIFO.h"

SlidePot my(1500,0);

extern "C" void DisableInterrupts(void);
extern "C" void EnableInterrupts(void);
extern "C" void SysTick_Handler(void);

// PF1 should be toggled in UART ISR (receive data)
// PF2 should be toggled in SysTick ISR (60 Hz sampling)
// PF3 should be toggled in main program
#define PF1  (*((volatile uint32_t *)0x40025008))
#define PF2  (*((volatile uint32_t *)0x40025010))
#define PF3  (*((volatile uint32_t *)0x40025020))
#define PF4  (*((volatile uint32_t *)0x40025040))

// **************SysTick_Init*********************
// Initialize Systick periodic interrupts
// Input: interrupt period
//        Units of period are 12.5ns
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none
void SysTick_Init(unsigned long period){
  // you write this
}

// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x20;      // activate port F
  while((SYSCTL_PRGPIO_R&0x20) != 0x20){};
  GPIO_PORTF_DIR_R |=  0x0E;   // output on PF3,2,1 (built-in LED)
  GPIO_PORTF_PUR_R |= 0x10;
  GPIO_PORTF_DEN_R |=  0x1E;   // enable digital I/O on PF
}

// main1 is used to run initial code with UART0 interrupts
// this code should run without changing 
// and interact with serial terminal on PC
int main1(void){  // run this program and look at Data
char letter;
  DisableInterrupts();
  PLL_Init(Bus80MHz);     // set system clock to 80 MHz
  PortF_Init();
  UART_Init();   // enable UART
  EnableInterrupts();
  UART_OutString((char *)"1234567890\n\r");
  UART_OutString((char *)"abcdefghij\n\r");
  UART_OutUDec(12345); UART_OutChar(LF); UART_OutChar(CR);
  while(1){   
    letter = UART_InChar();
    UART_OutChar(letter);    
  }
}

// step two, implement the FIFO class
// FIFO.h is prototype
// FIFO.cpp is implementation
// main2 program will test FIFO
Queue FIFO;
int main2(void){
  char data = 0; char out;
  DisableInterrupts();
  PLL_Init(Bus80MHz);     // set system clock to 80 MHz
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  
  while(1){
    int count=0;
    for(int i=0; i<10; i++){
      if(FIFO.Put(data)){
        count++;
        data++;
      }
    }
    FIFO.Print();
    for(int i=0; i<count; i++){
      FIFO.Get(&out);
    }   
    PF2 ^= 0x04;   
  }
}

// step 3
// Convert UART0 to UART1
// Move PA1,PA0 to PC5, PC4
// Use your queue class in receiver interrupt
// change receiver interrupt to 1/2 full only
// change transmitter to busy wait
// PF1 toggles in UART ISR
// PF2 toggles in main
int main3(void){
  char OutData = 'A'; 
  char InData;
  int count = 0;
  uint32_t time=0;
  DisableInterrupts();
  PLL_Init(Bus80MHz);     // set system clock to 80 MHz
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  UART_Init();       // enable UART
  EnableInterrupts();
  while(1){           
    time++;
    if((time%100000)==0){
      UART_OutChar(OutData);
      if(OutData == 'Z'){
        OutData = 'A';
      }else{
        OutData++;
      }
    }
    if(UART_InStatus()){
      InData = UART_InChar();
      ST7735_OutChar(InData);
      count++;
      if((count%16)==0){
        ST7735_OutChar('\n');
      }
      PF3 ^= 0x08;
    }
  }
}


// final main program for bidirectional communication
// Sender sends using SysTick Interrupt
// Receiver receives using RX interrupt
int main(void){   
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  ST7735_InitR(INITR_REDTAB);
  ADC_Init();    // initialize to sample ADC
  PortF_Init();
  UART_Init();    // initialize UART
  // you write this

  while(1){ // runs every 16,67 ms
  // you write this
  }
}



void SysTick_Handler(void){ // every 16.67 ms
 //Similar to Lab8 except rather than grab sample,
// form a message, transmit 
  PF2 ^= 0x04;  // Heartbeat
  PF2 ^= 0x04;  // Heartbeat
  // you write this

  PF2 ^= 0x04;  // Heartbeat
}

