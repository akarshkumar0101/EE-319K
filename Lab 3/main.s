;****************** main.s ***************
; Program written by: ***Akarsh Kumar and Rithvik Ramesh**update this***
; Date Created: 2/4/2017
; Last Modified: 1/18/2019
; Brief description of the program
;   The LED toggles at 2 Hz and a varying duty-cycle
; Hardware connections (External: One button and one LED)
;  PE2 is Button input  (1 means pressed, 0 means not pressed)
;  PE3 is LED output (1 activates external LED on protoboard)
;  PF4 is builtin button SW1 on Launchpad (Internal) 
;        Negative Logic (0 means pressed, 1 means not pressed)
; Overall functionality of this system is to operate like this
;   1) Make PE3 an output and make PE2 and PF4 inputs.
;   2) The system starts with the the LED toggling at 2Hz,
;      which is 2 times per second with a duty-cycle of 30%.
;      Therefore, the LED is ON for 150ms and off for 350 ms.
;   3) When the button (PE1) is pressed-and-released increase
;      the duty cycle by 20% (modulo 100%). Therefore for each
;      press-and-release the duty cycle changes from 30% to 70% to 70%
;      to 90% to 10% to 30% so on
;   4) Implement a "breathing LED" when SW1 (PF4) on the Launchpad is pressed:
;      a) Be creative and play around with what "breathing" means.
;         An example of "breathing" is most computers power LED in sleep mode
;         (e.g., https://www.youtube.com/watch?v=ZT6siXyIjvQ).
;      b) When (PF4) is released while in breathing mode, resume blinking at 2Hz.
;         The duty cycle can either match the most recent duty-
;         cycle or reset to 30%.
;      TIP: debugging the breathing LED algorithm using the real board.
; PortE device registers
GPIO_PORTE_DATA_R  EQU 0x400243FC
GPIO_PORTE_DIR_R   EQU 0x40024400
GPIO_PORTE_AFSEL_R EQU 0x40024420
GPIO_PORTE_DEN_R   EQU 0x4002451C
; PortF device registers
GPIO_PORTF_DATA_R  EQU 0x400253FC
GPIO_PORTF_DIR_R   EQU 0x40025400
GPIO_PORTF_AFSEL_R EQU 0x40025420
GPIO_PORTF_PUR_R   EQU 0x40025510
GPIO_PORTF_DEN_R   EQU 0x4002551C
GPIO_PORTF_LOCK_R  EQU 0x40025520
GPIO_PORTF_CR_R    EQU 0x40025524
GPIO_LOCK_KEY      EQU 0x4C4F434B  ; Unlocks the GPIO_CR register
SYSCTL_RCGCGPIO_R  EQU 0x400FE608

       IMPORT  TExaS_Init
       THUMB
       AREA    DATA, ALIGN=2
;global variables go here


       AREA    |.text|, CODE, READONLY, ALIGN=2
       THUMB
       EXPORT  Start
		   
ONLRAW	 DCD 3000000, 5000000, 7000000, 9000000, 1000000, 0
OFFLRAW DCD 7000000, 5000000, 3000000, 1000000, 9000000, 0

ONL	 DCD 2326388, 3877314, 5428240, 6979166, 775462, 0
OFFL DCD 5428240, 3877314, 2326388, 775462, 6979166, 0

BREATHPERIOD EQU 14000;200000
BREATH_ONL_INC EQU 8

Start
 ; TExaS_Init sets bus clock at 80 MHz
     BL  TExaS_Init ; voltmeter, scope on PD3
 ; Initialization goes here
 
     ; turn on clock for E and F
     LDR R1, =SYSCTL_RCGCGPIO_R
	 LDR R0, [R1]
	 ORR R0, #0x30
	 STR R0, [R1]
	 
	 ; sleep for a bit
	 NOP
	 NOP
	 NOP
	 NOP
	 
	 LDR R1, =GPIO_PORTF_LOCK_R
	 LDR R0, =GPIO_LOCK_KEY
	 STR R0, [R1]
	 LDR R1, =GPIO_PORTF_CR_R
	 LDR R0, [R1]
	 ORR R0, #0xFF
	 STR R0, [R1]
	 
	 LDR R1, =GPIO_PORTF_PUR_R
	 LDR R0, [R1]
	 ORR R0, #0x10
	 STR R0, [R1]
	 
	 
	 ; directional for port E
	 LDR R1, =GPIO_PORTE_DIR_R
	 LDR R0, [R1]
	 AND R0, R0, #0
	 ADD R0, R0, #8
	 STR R0, [R1]
	 
	 ; directional for port F
	 LDR R1, =GPIO_PORTF_DIR_R
	 LDR R0, [R1]
	 AND R0, R0, #0
	 ADD R0, R0, #0
	 STR R0, [R1]
	 
	 ; data enable for port E
	 LDR R1, =GPIO_PORTE_DEN_R
	 LDR R0, [R1]
	 ORR R0, R0, #0xC
	 STR R0, [R1]
	 
	 ; data enable for port F
	 LDR R1, =GPIO_PORTF_DEN_R
	 LDR R0, [R1]
	 ORR R0, R0, #0x10
	 STR R0, [R1]
	 
	 
	 
	 
     CPSIE  I    ; TExaS voltmeter, scope runs on interrupts
	 
	 
	 ; R0 is temporary register
	 LDR R1, =GPIO_PORTE_DATA_R
	 LDR R2, =GPIO_PORTF_DATA_R
	 ;MOV R3, #0 ; not pressing duty button
	 ;normal times:
	 LDR R4, =ONL
	 LDR R5, =OFFL
	 ;breathing online time (gets inc):
	 MOV R6, #1
	 ;breathing offline time (gets calculated
	 MOV R7, #0
	 MOV R8, #0 ;this is the direction 0 for inc breathing
	 
	 
	 
loop
; main engine goes here
	 LDR R1, =GPIO_PORTE_DATA_R
	 LDR R2, =GPIO_PORTF_DATA_R
	 ;load data from port F
	 LDR R0, [R2]
	 ;based off R0 branch to notBreathing or breathing
	 ADDS R0, R0, #0
	 BNE notBreathing
	 B breathing
	 
notBreathing
	 LDR R0, [R1]
	 ANDS R0, R0, #4
	 BNE dutyPressed
	 B afterDuty
	 
dutyPressed
	 LDR R0, [R1]
	 ANDS R0, R0, #4
	 BNE dutyPressed
	 ;increment the duty
	 ADD R4, R4, #4
	 ADD R5, R5, #4
	 
	 LDR R0, [R4]
	 ADDS R0, R0, #0
	 ;if not zero branch to after duty
	 BNE afterDuty
	 ;else reset back to default duty
	 LDR R4, =ONL
	 LDR R5, =OFFL
	 
	 
afterDuty
	 
	 MOV R0, #8
	 STR R0, [R1]
	 
	 LDR R0, [R4]
wait 
	 SUBS R0, R0, #0x01
	 BNE wait
	 
	 MOV R0, #0
	 STR R0, [R1]
   
	 
	 LDR R0, [R5]
wait1
	 SUBS R0, R0, #0x01
	 BNE wait1
	 
	 MOV R0, #10
tempwait1
	 SUBS R0, R0, #0x01
	 BNE tempwait1
	 
	 B loop
	 
	 

breathing
	 ;increment R6 to increase online time
	 LDR R0, =BREATH_ONL_INC
	 LDR R7, =BREATHPERIOD
	 
	 ;R8 is direction
	 ADDS R8, R8, #0
	 BNE breathingDown
breathingUp
	 ADD R6, R6, R0
	 ADD R9, R6, R0
	 SUBS R9, R7, R9
	 BPL doneDirection
	 MOV R8, #1
	 B doneDirection
	 
breathingDown
	 SUB R6, R6, R0
	 SUBS R9, R6, R0
	 BPL doneDirection
	 MOV R8, #0
	 B doneDirection

doneDirection
	 
	 ;get the offline time:
	 SUBS R7, R7, R6
	 
	 MOV R0, #8
	 STR R0, [R1]
	
	 MOV R0, R6
wait2
	 SUBS R0, R0, #0x01
	 BNE wait2
	 
	 MOV R0, #0
	 STR R0, [R1]
   
	 MOV R0, R7
wait3
	 SUBS R0, R0, #0x01
	 BNE wait3
	 
	 
	 B loop


	 

      
     ALIGN      ; make sure the end of this section is aligned
     END        ; end of file\





