;****************** main.s ***************
; Program initially written by: Yerraballi and Valvano
; Author: Place your name here
; Date Created: 1/15/2018 
; Last Modified: 1/18/2019 
; Brief description of the program: Spring 2019 Lab1
; The objective of this system is to implement odd-bit counting system
; Hardware connections: 
;  Output is positive logic, 1 turns on the LED, 0 turns off the LED
;  Inputs are negative logic, meaning switch not pressed is 1, pressed is 0
;    PE0 is an input 
;    PE1 is an input 
;    PE2 is an input 
;    PE3 is the output
; Overall goal: 
;   Make the output 1 if there is an odd number of 1's at the inputs, 
;     otherwise make the output 0
; The specific operation of this system 
;   Initialize Port E to make PE0,PE1,PE2 inputs and PE3 an output
;   Over and over, read the inputs, calculate the result and set the output

; NOTE: Do not use any conditional branches in your solution. 
;       We want you to think of the solution in terms of logical and shift operations

GPIO_PORTE_DATA_R  EQU 0x400243FC
GPIO_PORTE_DIR_R   EQU 0x40024400
GPIO_PORTE_DEN_R   EQU 0x4002451C
SYSCTL_RCGCGPIO_R  EQU 0x400FE608

      THUMB
      AREA    DATA, ALIGN=2
;global variables go here
      ALIGN
      AREA    |.text|, CODE, READONLY, ALIGN=2
      EXPORT  Start
Start
; setup code (only runs once) here

; load R1 with the address of system clock
	LDR R1, = SYSCTL_RCGCGPIO_R
; load R0 with the value of system clock
	LDR R0, [R1]
; turn on clock for port E
	ORR R0, #0x10
; store this clock back out
	STR R0, [R1]

; wait two clock cycles
	NOP 
	NOP
; load up address of directional register
	LDR R1, = GPIO_PORTE_DIR_R
; get value of directional register
	LDR R0, [R1]
; set value of directional register (in: 00, 01, 02 out: 03);
	AND R0, R0, #0
	ADD R0, R0, #8
; store new directional register back out
	STR R0,[R1]

; load adress of data enable
	LDR R1,= GPIO_PORTE_DEN_R
; get data enable data
	LDR R0,[R1]
; set enable data with (enabled: 00, 01, 02, 03)
	ORR R0,#0xF
; store new enable register back out
	STR R0,[R1]
; load up data register for use in algorithm
	LDR R1, = GPIO_PORTE_DATA_R

loop
; code running constantly to accurately change output
; clear R2 for use
	  AND R2, R2, #0
; load input data into R0
	  LDR R0,[R1]

; XOR raw data with x0 to toggle left most bit (toggle if input 0 is on)
	  EOR R2, R2, R0;
; right shift data by one to get next input
	  LSR R0, #1
; XOR new data with current set (toggle if input 1 is on)
	  EOR R2, R2, R0;
; right shift data by one to get next input
	  LSR R0, #1
; XOR new data with current set (toggle if input 2 is on)
	  EOR R2, R2, R0;

; only get right most bit of set (only one that was being properly toggled)
	  AND R2, R2, #1

; left shift set by 3 in order to push to output (bit 03)
	  LSL R2, R2, #3
	  
; store back out to data register in order to turn on/off output
	  STR R2, [R1]
	  
; run loop again
      B    loop

      ALIGN        ; make sure the end of this section is aligned
      END          ; end of file
          