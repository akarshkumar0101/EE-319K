/*
;*****Your name goes here*******
; -5 points if you do not add your name

;This is Exam2_Calculus 
;EE319K Spring 2013
;March 28, 2013
;You edit this file only
*/
#include <stdint.h>
/*
;***** Size subroutine*********************
;Determines the number of elements in a variable-length array
;Each element of the array is a 16-bit signed number
;The array has a termination code of -32768
;The -32768 is not a data point in the array
;Input:   R0 has a pointer to the array of 16-bit numbers
;Output:  R0 is returned as the number of data elements in the array 
;Invariables: You must not permanently modify registers R4 to R11, and LR
;Error conditions: none
;Test cases
;Array0 DCW 35,144,25,36,-32768                 ;size = 4
;Array1 DCW 9,13,-4,-5,100,-2000,7000,-32768    ;size = 7
;Array2 DCW 0,128,0,128,128,-32768              ;size = 5
;Array3 DCW -32768                              ;size = 0
*/
uint32_t Size(const int16_t *buffer){
//; put your code here
  return 42;   // replace this line

}

/*
;***** Derivative subroutine*********************
;Calculates the derivative between two points
;Assumes the two points were measured 0.1 sec apart
;Inputs:  R0 is the first data value
;         R1 is the second data value
;R0 and R1 can vary from -32767 to +32767
;Output:  return R0 = (second-first)*10
;the output value can vary from -655340 to +655340
;overflow can not happen in this function
;Invariables: You must not permanently modify registers R4 to R11, and LR
;Error conditions: none
;Test cases
;R0=10,     R1=-10    yields R0 = -200
;R0=-10,    R1=10     yields R0 = 200
;R0=32767,  R1=-32767 yields R0 = -655340
;R0=-20000, R1=-10000 yields R0 = 100000
*/
int32_t Derivative(int16_t first, int16_t second){ 
//; put your code here

    return 42;   // replace this line
}      

/*
;***** Integration subroutine *********************
;Determines the integral of elements in a variable-length array
;Assumes the points in the array were measured 0.1 sec apart
;Each element of the array is a 16-bit signed number
;The array has a termination code of -32768
;The -32768 is not a data point in the array
;Input:   R0 has a pointer to the array of 16-bit numbers
;Output:  return R0 is returned as the integral of data elements in the array 
;The integral is the sum of all data points divided by 10
;First calculate the sum, and then divide the sum by 10
;Do not worry about overflow during the additions
;Invariables: You must not permanently modify registers R4 to R11, and LR
;Error conditions: none
;Test cases
;Array4 DCW 35,144,25,36,-32768              ;I = (35+144+25+36)/10 = 24
;Array5 DCW 9,13,-4,-5,100,-2000,7000,-32768 ;I = (9+13-4-5+100-2000+7000)/10 = 511
;Array6 DCW 20000,25000,25000,30000,20000,25000,25000,30000,20000,25000,25000,30000,20000,25000,25000,30000,-32768                  ;I = 40000
;Array7 DCW -20000,-25000,-25000,-30000,-20000,-25000,-25000,-30000,-20000,-25000,-25000,-30000,-20000,-25000,-25000,-30000,-32768  ;I = -40000
;Array8 DCW -32768                           ;I = 0
*/
int32_t Integration(const int16_t *buffer){
//; put your code here

    return 42;   // replace this line
}    

/*
;***** MaxDerivative subroutine *********************
;Determines the maximum derivative of elements in a variable-length array
;Assumes the points in the array were measured 0.1 sec apart
;Each element of the array is a 16-bit signed number
;The array has a termination code of -32768
;The -32768 is not a data point in the array
;An array of n elements has n-1 derivatives.
;Each derivative is calculated using adjacent elements: (second-first)*10
;Input:   R0 has a pointer to the array of 16-bit numbers
;Output:  R0 is returned as the maximum derivative of data elements in the array 
;The integral is the sum of all data points divided by 10
;Invariables: You must not permanently modify registers R4 to R11, and LR
;Error conditions: return 0x80000000 if the array has zero or one element
;Test cases
;Array9  DCW 35,144,25,36,-32768              ;derivatives are 1090,-1190,110; max is 1090
;Array10 DCW 9,13,-4,-5,100,-2000,7000,-32768 ;derivatives are 40,-170,-10,1050,-21000,90000; max is 90000
;Array11 DCW 4,2,0,-4,-5,-9,-12,-32768        ;derivatives are -20,-20,-40,-10,-40,-30; max is -10
;Array12 DCW 10,0,-32768                      ;derivative is -100; max is -100
;Array13 DCW 10,-32768                        ;error case, return 0x80000000
;Array14 DCW -32768                           ;error case, return 0x80000000
*/
int32_t MaxDerivative(const int16_t *buffer){    
//; put your code here

    return 42;   // replace this line
}

      
