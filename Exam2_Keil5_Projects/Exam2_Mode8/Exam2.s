;This is Exam2_Mode8
;Your name goes here
;You edit Exam2.s and Exam2c.c files only
       PRESERVE8 
       AREA   Data, ALIGN=4
;put RAM variables here
    
       AREA    |.text|, CODE, READONLY, ALIGN=2
       THUMB
;***** Size subroutine*********************
;Determines the number of elements in a variable-length array
;Input:   R0 has a pointer to the array of 8-bit numbers
;Output:  R0 is returned as the number of data elements in the array 
;Invariables: You must not permanently modify registers R4 to R11
;Error conditions: none
;Test cases
;Array1 DCB 3,1,2,3      ;size = 3
;Array2 DCB 0xA0,1...    ;size = 0xA0=160
;Array3 DCB 0            ;size = 0
      EXPORT Size
Size 
; put your code here
  

      
      BX    LR

;***** Count subroutine*********************
;Determine the number of times that a data value occurs in a given array
;Inputs:  R0 has a pointer to the array of 8-bit unsigned numbers
;         R1 is the 8-bit unsigned data value
;Output:  R0 is the number of times the data value occurs in the array
;Invariables: You must not permanently modify registers R4 to R11
;Error conditions: none
;Test cases
;Array1 DCB 3,1,2,3             ;Data=4   Count=0 (4 occurs 0 times)
;Array2 DCB 5,12,13,4,12,3      ;Data=12  Count=2 (12 occurs twice)
;Array3 DCB 12,1,1,1,2,1,1,2,1,2,1,2,1,1,1      ;Data=1  Count=8 (1 occurs 8 times)
;Array4 DCB 9,30,30,30,30,30,30,30,30,30  ;Data=30  Count=9 (30 occurs 9 times)
;Array5 DCB 7,50,10,50,10,50,0,0 ;Data=50   Count=3 (50 occurs 3 times)
;Array6 DCB 0           ;Data=0 Count=0 (0 does not occur in the empty array)
      EXPORT Count
Count 
; put your code here


      
      BX   LR

;***** Mode subroutine *********************
;Find the mode of all values in the array
;Inputs:  R0 has a pointer to the array of 8-bit unsigned numbers
;Output:  R0 is the mode of all the values
;Invariables: You must not permanently modify registers R4 to R11
;test cases
;Array1 DCB 3,1,1,3         ;Mode=1
;Array2 DCB 5,12,13,4,12,3  ;Mode=12
;Array3 DCB 14,1,1,1,2,1,1,2,1,2,1,2,1,1,1   ;Mode=1
;Array4 DCB 0           ;Mode=0 (empty array)
;      EXPORT Mode
;Mode  
;; put your code here

      
 
      
;      BX    LR
      
      ALIGN
      END
      
