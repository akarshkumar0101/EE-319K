;Exam2AsmPart.s  
; EE319K Spring 2018 exam 2, April 6, 2018
; ***Put your name here***
; -5 points if you do not add your name
; This is the assembly Part of the Exam (See Exam2CPart.c for the C part)
; You have to complete one subroutine in assembly: String2Int

    PRESERVE8
    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
    EXPORT  String2Octal
        
; Octal means base 8, with digits 0-7
; ASCII '0' is 0x30
;       '1' is 0x31
; ...
;       '7' is 0x37
    
     
;*** Question 2 ***** String2Octal **********
; Accepts a null-terminated string of ASCII octal digits
; and calculates the unsigned integer value represented by those digits
; Input: R0 is a pointer to a null-terminated ASCII string 
;        each ASCII character is an 8-bit number from 0 to 127
; Output: R0 should be returned as the unsigned 32-bit value
;         return 0xFFFFFFFF if any character in the string is not an octal digit
;         return 0xFFFFFFFF if the numerical result of the conversion exceeds 65535
; Note: the grader will run many test cases, there are only a few of them
; input string                     description    return
; 0x35,0                           "5"            5 
; 0x31,0x32,0                      "12"           10 
; 0x33,0x37,0x31,0                 "371"          249 
; 0x30,0x35,0x34,0x32,0x31,0       "05421"        2833
; 0x31,0x37,0x37,0x37,0x37,0x37,0  "177777"       65535
; 0x32,0x30,0x30,0x30,0x30,0x30,0  "200000"       0xFFFFFFFF
; 0x38,0x34,0                      "84"           0xFFFFFFFF
; 0x33,0x2C,0x31,0                 "3,1"          0xFFFFFFFF
; 0                                null string    0
ZEROASCII EQU 0x30
allF DCD 0xFFFFFFFF
	
String2Octal
	PUSH {R1-R10}
	
stringLoopInit
	 LDRB R1, [R0]
	 CMP R1, #0
	 ADD R0, #1
	BNE stringLoopInit
	
	SUB R0,#2
	
	
	MOV R7, #0
	MOV R2, #1
	
	MOV R3, #8
	
	MOV R4, #0 ;error bit
	
stringLoop
	 LDRB R1, [R0]
	 CMP R1, #0
	 BEQ normal
	 
	 SUB R1, #ZEROASCII
	 CMP R1, #0
	 BMI error
	 CMP R1, #8
	 BPL error
	 
	 
	 MUL R1, R2
	 MUL R2, R3
	 
	 ADD R7, R1
	 
	 
	 SUB R0, #1
	 B stringLoop
	 

error
	LDR R0, allF
	B return
normal
     MOV R0, R7
	 CMP R0, #65536
	 BPL error
return
	POP {R1-R10}
     BX   LR

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file