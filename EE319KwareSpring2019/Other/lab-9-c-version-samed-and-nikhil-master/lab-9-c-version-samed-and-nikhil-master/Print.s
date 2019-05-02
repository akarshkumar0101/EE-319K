; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 


    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

	
    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
	
LCD_OutDec
Carry 	EQU 	0
PlCtr   EQU     4
FP RN 11

	SUB SP, #8 ;adjusting stack for local variables
	MOV R11, SP		
	PUSH {R4, LR};initialize local variables : Place-Holders and Carry Bit for Mod
    MOV	R3, #0
	STR R3, [FP, #PlCtr]
	STR R0, [FP, #Carry]
	MOV R2, #10
	
Mod	
	LDR R0, [FP, #Carry] ; check to make sure R0 isn't 0-9
	CMP R0, #9
	BLS Inc ; if it is a single digit, branch to increment Place-Holder and to prepare for print
	UDIV R4, R0, R2 ;divide by 10
	STR R4, [FP, #Carry]
	MUL R4, R4, R2 ;multiply by 10, effectively modulating equation
	SUB R4, R0, R4 ;subtract 'mod'ed # from r0 to get digit to push onto stack
	PUSH {R5, R4}
	LDR R3, [FP, #PlCtr]
	ADD R3, R3, #1 ;increment Place-Holder
	STR R3, [FP, #PlCtr]
	B Mod
Inc 	
	PUSH {R5, R0} 
	LDR R3, [FP, #PlCtr] ;final incrementing of place holder
	ADD R3, #1 
	STR R3, [FP, #PlCtr]
Print	
	POP	{R0,R4} ;pop digits off of stack, add 0x30 to get ascii value and feed into outchar function
	ADD	R0, #0x30
	BL	ST7735_OutChar
	LDR R3, [FP, #PlCtr] ;decrement place-holder, keep popping until all digits are off
	SUB	R3, #1
	STR R3, [FP, #PlCtr]
	CMP R3, #0
	BNE	Print
	POP {R4, LR}
	ADD     SP, #8 ;restore stack
	BX  	LR
	ALIGN
			
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix

Carry1 	EQU 	0
PlCtr1   EQU     4
FP RN 11

	SUB 	SP, #8 ;adjusting stack for local variables
	MOV     R11, SP
		
	PUSH {R4, LR}	
	MOV R4, #9999	;hardcode in for >9999 exception case
	CMP R0, R4
	BGT PrintGT
	MOV R4, #0xFFFFFFFF ;exception for 0xFFFFFFFF
	CMP R0, R4
	BEQ PrintGT
	MOV R4, #0
    MOV	R3, #0
	STR R3, [FP, #PlCtr1] ;R3 is Place-Holder, R0 is your original data/carry variable, r2 has mod arithmetic #
	STR R0, [FP, #Carry1] ;initialize local variables : Place-Holders and Carry Bit for Mod
	MOV R2, #10
	
Mod1
	LDR R0, [FP, #Carry1] ;same as previous mod function 
	CMP R0, #9
	BLS Inc1
	UDIV R4, R0, R2
	STR R4, [FP, #Carry1]
	MUL R4, R4, R2
	SUB R4, R0, R4
	PUSH {R5, R4}
	LDR R3, [FP, #PlCtr1]
	ADD R3, R3, #1
	STR R3, [FP, #PlCtr1]
	B Mod1
Inc1 	
	PUSH {R5, R0} ;does a final increment of place-holder
	LDR R3, [FP, #PlCtr1]
	ADD R3, #1
	STR R3, [FP, #PlCtr1]
	CMP R3, #1 ;next 3 "BEQ"s check to see how many places of 0s are needed to get desired format
	BEQ PUSH3
	CMP R3, #2
	BEQ PUSH2
	CMP R3, #3
	BEQ PUSH1
	SUB R4, R3, #1 
Print1
	POP	{R0,R5} ;printing is same as last function
	ADD	R0, #0x30
	BL	ST7735_OutChar
	LDR R3, [FP, #PlCtr1]
	SUB	R3, #1
	STR R3, [FP, #PlCtr1]
	CMP R4, R3 ;94 is used in this scenario to know when to print the "."
	BEQ PrintS
Ret	CMP R3, #0
	BNE	Print1
EndM
	POP {R4, LR} ;AAPCS compliant
	ADD     SP, #8 ;restore stack pointer
	BX  	LR
	ALIGN
			
PrintS	
	MOV R0, #0x2E ;print "."
	BL ST7735_OutChar
	B Ret
PrintGT 
	MOV	R0, #0x2A ;string to print if number is > than 9999
	PUSH	{LR,R1}
	BL	ST7735_OutChar
	POP	{LR,R1}
	MOV	R0, #0x2E
	PUSH	{LR,R1}
	BL	ST7735_OutChar
	POP	{LR,R1}
	MOV	R0, #0x2A
	PUSH	{LR,R1}
	BL	ST7735_OutChar
	POP	{LR,R1}
	MOV	R0, #0x2A
	PUSH	{LR,R1}
	BL	ST7735_OutChar
	POP	{LR,R1}
	MOV	R0, #0x2A
	PUSH	{LR,R1}
	BL	ST7735_OutChar
	POP	{LR,R1}
	B EndM
		
PUSH3	
	MOV R0, #0 ; pushes 0s onto stack that are needed as filler for desired output format
	PUSH {R5, R0}
	LDR R3, [FP, #PlCtr]
	ADD R3, #1
	STR R3, [FP, #PlCtr]
PUSH2
	MOV R0, #0
	PUSH {R5, R0}
	LDR R3, [FP, #PlCtr]
	ADD R3, #1
	STR R3, [FP, #PlCtr]
PUSH1
	MOV R0, #0
	PUSH {R5, R0}
	LDR R3, [FP, #PlCtr]
	ADD R3, #1
	STR R3, [FP, #PlCtr]
	SUB R4, R3, #1 
	B Print1
		


;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file                                               