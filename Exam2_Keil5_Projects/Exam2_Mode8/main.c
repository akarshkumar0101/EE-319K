// main.c
// Runs on LM3S1968
// Grading engine for Exam2_Mode8
// Do not modify any part of this file
// This Exam2 has never been given, it is for practice

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

#include "PLL.h"
#include "UART.h"
#include <stdint.h>

#define COUNT1 3
struct TestCase1{
  uint8_t buf[20]; 
  uint32_t Correct;   // proper result of Size()
  uint32_t  Score;    // points to add if Size() correct
};
typedef const struct TestCase1 TestCase1Type;
TestCase1Type Tests1[COUNT1]={
{{3,1,2,3},     3,10},
{{0xA0,1,0,0},  0xA0,10},
{{0},           0,10}};

struct TestCase2{
  uint8_t buf[30]; 
  unsigned char data;
  uint32_t  Correct;  // proper result of Count()
  uint32_t  Score;    // points to add if Count() correct
};
typedef const struct TestCase2 TestCase2Type;
#define COUNT2 6
TestCase2Type Tests2[COUNT2]={
{{3,1,2,3,4},4,                               0,5},
{{5,12,13,4,12,3,12},12,                      2,5},
{{12,1,1,1,2,1,1,2,1,2,1,2,1, 1,1},1,          8,5},
{{9,30,30,30,30,30,30,30,30,30,30},30, 9,5},
{{7,50,10,50,10,50,0,0,50},50, 3,5},
{{0,0,0},0,                                   0,10}};

struct TestCase3{
  uint8_t buf[20]; 
  uint8_t Correct;   // proper result of Mode()
  long Score;     // points to add if Sum() correct
};
typedef const struct TestCase3 TestCase3Type;
#define COUNT3 6
TestCase3Type Tests3[COUNT3]={
{{3,1,1,3,5,6,0,0},                            1,5},
{{5,12,13,4,12,3,6,7,7,7,7,7,0},               12,5},
{{14,1,1,1,2,1,1,2,1,2,1,2,1,1,1,5,6,0,0},     1,5},
{{13,10,10,10,20,10,10,20,10,2,10,2,10,10,10,5,6,0,0},     10,5},
{{12,41,41,41,2,41,41,2,41,41,41,2,1,1,6,0,0},  41,5},
{{0,4,5,0},                                    0,10}};


//test code
uint32_t Size(const  uint8_t *buffer);
uint32_t Count(const  uint8_t *buffer, uint8_t value);
uint8_t Mode(const uint8_t *buffer);
int main(void){ long result2;
  unsigned long result,n,score;
  score = 0;
  PLL_Init();

  UART_Init();              // initialize UART
  UART_OutCRLF();

  UART_OutString("Exam2_Mode8\n\r");
  UART_OutString("Test of Size\n\r");
  for(n = 0; n < COUNT1 ; n++){
    result = Size(Tests1[n].buf);
    UART_OutString("Your="); UART_OutUDec(result);  
    if(result == Tests1[n].Correct){
      UART_OutString("  Yes, Score = ");
      score = score + Tests1[n].Score;
    }else{
      UART_OutString("  No, Score = ");
    }
    UART_OutUDec(score);  UART_OutCRLF();
  }

  UART_OutString("Test of Count\n\r");
  for(n = 0; n < COUNT2 ; n++){
    result = Count(Tests2[n].buf,Tests2[n].data);
    UART_OutString("Your="); UART_OutUDec(result);  
    if(result == Tests2[n].Correct){
      UART_OutString("  Yes, Score = ");
      score = score + Tests2[n].Score;
    }else{
      UART_OutString("  No, Score = ");
    }
    UART_OutUDec(score);  UART_OutCRLF();
  }
  UART_OutString("Test of Mode\n\r");
  for(n = 0; n < COUNT3 ; n++){
    result2 = Mode(Tests3[n].buf);
    UART_OutString("Your = "); UART_OutUDec(result2);  
    if(result2 == Tests3[n].Correct){
      UART_OutString("  Yes, Score = ");
      score = score + Tests3[n].Score;
    }else{
      UART_OutString("  No, Score = ");
    }
    UART_OutUDec(score);  UART_OutCRLF();
  }
  UART_OutString("End of Exam2_Mode8, Practice\n\r");
  while(1){
  }
}
