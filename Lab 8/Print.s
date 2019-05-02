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

 

ORI EQU 0
DIV EQU 4

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
    PUSH {R4, LR}
	PUSH {R0-R5}
	
	SUB SP, #8
	
	STR R0, [SP,#ORI]
	LDR R2, [SP,#ORI]
	
	CMP R2, #10
	BLO singleDigitOut
	
	
	MOV R5, #10
	UDIV R1, R2, R5
	
	STR R1, [SP,#DIV]
	
	;//run OutDec with input R1
	LDR R0, [SP,#DIV]
	BL LCD_OutDec
	
	LDR R1, [SP,#DIV]
	
	MUL R1, R1, R5
	SUB R2, R2, R1
	
	STR R2, [SP,#ORI]
	
	
singleDigitOut

	LDR R0, [SP,#ORI]
	
	
	BL outDigit
	
	
	ADD SP, #8
	
	POP {R0-R5}
	POP {R4, PC}
	
	;commented out
      ;BX  LR
	  
	  
outDigit
	PUSH {R4, LR}
	PUSH {R0-R9}
	ADD R0, R0, #0x30
	BL ST7735_OutChar
	POP {R0-R9}
	POP {R4, LR}

      BX  LR
	  
	  
	  
	  

invalidInputString DCB 0x2A,0x2E,0x2A,0x2A,0x2A,0x00



num9999 DCD 9999
	
	
ORI2 EQU 0
DIV2 EQU 4
	
	
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

	PUSH {R4, LR}
	PUSH {R0-R5}
	
	SUB SP, #8
	
	STR R0,[SP,#ORI2]
	
	LDR R1, =num9999
	LDR R1, [R1]
	
	LDR R0,[SP,#ORI2]
	CMP R0, R1
	BHI printInvalid
	
	MOV R12, #1000
	LDR R1, [SP,#ORI2]
	UDIV R0, R1, R12 ; R0 = R1/1000 = 2
	STR R0,[SP,#DIV2]
	BL outDigit
	LDR R0,[SP,#DIV2]
	MUL R0, R0, R12 ; R0 = R0*1000 = 2000
	LDR R1, [SP,#ORI2]
	SUB R1, R1, R0  ; R1=R1-R0 = 2589-2000=589
	STR R1, [SP,#ORI2]
	
	MOV R0, #0x2E
	PUSH {R0-R5}
	BL ST7735_OutChar
	POP {R0-R5}
	
	MOV R12, #100
	LDR R1, [SP,#ORI2]
	UDIV R0, R1, R12 ; R0 = R1/1000 = 2
	STR R0,[SP,#DIV2]
	BL outDigit
	LDR R0,[SP,#DIV2]
	MUL R0, R0, R12 ; R0 = R0*1000 = 2000
	LDR R1, [SP,#ORI2]
	SUB R1, R1, R0  ; R1=R1-R0 = 2589-2000=589
	STR R1, [SP,#ORI2]
	
	MOV R12, #10
	LDR R1, [SP,#ORI2]
	UDIV R0, R1, R12 ; R0 = R1/1000 = 2
	STR R0,[SP,#DIV2]
	BL outDigit
	LDR R0,[SP,#DIV2]
	MUL R0, R0, R12 ; R0 = R0*1000 = 2000
	LDR R1, [SP,#ORI2]
	SUB R1, R1, R0  ; R1=R1-R0 = 2589-2000=589
	STR R1, [SP,#ORI2]
	
	MOV R12, #1
	LDR R1, [SP,#ORI2]
	UDIV R0, R1, R12 ; R0 = R1/1000 = 2
	STR R0,[SP,#DIV2]
	BL outDigit
	LDR R0,[SP,#DIV2]
	MUL R0, R0, R12 ; R0 = R0*1000 = 2000
	LDR R1, [SP,#ORI2]
	SUB R1, R1, R0  ; R1=R1-R0 = 2589-2000=589
	STR R1, [SP,#ORI2]
	
	B doneOutFix
	
printInvalid
	LDR R0,=invalidInputString
	BL ST7735_OutString
	
	
	
doneOutFix

	ADD SP, #8
	
	POP {R0-R5}
	POP {R4, PC}
 
     
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
