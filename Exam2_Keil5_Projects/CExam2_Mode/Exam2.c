/*
;*****Your name goes here*******
; -5 points if you do not add your name

;This is Exam2_Mode 
;EE319K Practice exam
;You edit this file only
*/   
#include <stdint.h>
/*
***************** Size****************************
 Determines the length of a variable-length buffer.  
 Input parameter: pt points to variable length buffer 
 sentinel is -128
 Output parameter: Return the length of buffer.  
 Error conditions: if buffer is empty, return 0 
Test cases
buffer is {1,2,3,-128}                   ;size=3
buffer is {-2,-1,2,0,2,-128}             ;size=5
buffer is {-127,127,0,0,0,1,2,3,-128}    ;size=8
buffer is {0,-128}                       ;size=1
buffer is {-128}                         ;size=0
*/      
uint32_t Size(const int8_t *pt){ 
// put your code here

  return(42);  // change this line
}

/****************** Count ****************************
Count the number of instances of the value in a buffer. 
The data in the buffer range from -127 to +127
Input: size is the number of elements in the buffer.  
       value is the number in the buffer to search for and count
       pt is a pointer to the buffer
Output: number of instances of the value in the buffer
Error conditions: Return 0 if the value is not found or if the buffer is empty.
Test cases
  size value buffer
   5,    3,  {1,2,3,3,4}                  ;count=2
  10,    0,  {-3,-10,0,0,0,0,1,2,0,0}     ;count=6
   5,    6,  {-1,2,3,-3,4}                ;count=0
   7,   -8,  {-8,-8,-8,-8,-8,-8,-8}       ;count=7
   0,  -100, {}                           ;count=0
*/
uint32_t Count(uint32_t size, int8_t value, const int8_t *pt){ 
// put your code here
 
  return(42);  // change this line
}
/* ****************** Mode ****************************
Finds the element in the buffer that occurs most frequently. 
Input: size is the number of elements in the buffer 
       pt is a pointer to the buffer
Error conditions: Return -128 if the buffer is empty.
Test cases
  size value buffer
   5,    {10,20,30,30,40}             //mode=30
  10,    {-3,-10,0,0,0,0,1,2,0,0}     //mode=0
   8,    {-1,2,3,-3,4,-1,3,-1}        //mode=-1
   7,    {-8,+8,-8,+8,-8,-8,+8}       //mode=-8
   0,    {}                           //mode=-128
*/
int8_t Mode(uint32_t size, const int8_t *pt){ 
// put your code here
   return(42);  // change this line
}

struct buffer{
  uint32_t size;
  int8_t data[100];
};
typedef struct buffer buffer_t;
/* ****************** Mode2 ****************************
Finds the element in the buffer that occurs most frequently. 
Input: struct buffer that has a size and data array 
Output: Return the most frequently occurring element
Error conditions: Return -128 if the buffer is empty.
Test cases
    size,data
 {  5, {20,20,30,30,20} }        //mode2=20
 { 10, {-3,-10,2,0,2,0,1,2,0,2}} //mode2=2
 {  8, {-9,2,3,-3,4,-9,3,-9}}    //mode2=-9
 {  7, {+8,+8,-8,+8,-8,-8,+8}}   //mode2=+8
 {  0, {}}                       //mode2=-128
*/
int8_t Mode2(buffer_t buf){ 
// put your code here
  return(42);  // change this line
}

