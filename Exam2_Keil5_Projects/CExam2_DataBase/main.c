// main.c 
// Runs on LM3S1968 using the simulator
// Grading engine for Exam2_DataBase Practice Exam
// Do not modify any part of this file
// Exam2 practice exam, made up Fall 2014, Valvano

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1
#include <stdint.h>

#include "PLL.h"
#include "UART.h"

#define COUNT1 5
struct TestCase1{
  char   string[30];   // input to Size()
  uint32_t Correct;   // proper result of Size()
  uint32_t Score;     // points to add if Size() correct
};
typedef const struct TestCase1 TestCase1Type;
TestCase1Type Tests1[COUNT1]={
{"Jony",4,5},
{"Ramesh Yerraballi",17,5},
{{4,1,2,3,0},4,5},
{"Jonathan Valvano",16,5},
{"",0,5}
};


struct TestCase2{
  uint32_t size;       // input to Average()
  int8_t   buf[30];    // input to Average()
  int32_t  Correct;    // proper result of Average()
  uint32_t Score;      // points to add if Average() correct
};
typedef const struct TestCase2 TestCase2Type;
#define COUNT2 5
TestCase2Type Tests2[COUNT2]={
{   5,    {1,4,3,3,4}             , 3,5},     //Average=3
{  10,    {-3,-10,0,0,0,0,1,2,0,0},-1,5},     //Average=-1
{   5,    {-1,2,3,-3,4}           , 1,5},     //Average=1
{   7,    {-6,-9,-7,-8,-8,-9,-9}  ,-8,5},     //Average=-8
{   0,    {1,2,3,0}               , 0,5}      //Average=0
};     

struct student{
  char name[20];
  int8_t data[8]; // skip if data=-128
};
typedef struct student student_t;

struct TestCase3{
  student_t s;         // input to Grade()
  int8_t Correct;      // proper result of Grade()
  uint32_t Score;      // points to add if Grade() correct
};
typedef const struct TestCase3 TestCase3Type;
#define COUNT3 5
TestCase3Type Tests3[COUNT3]={
{{   "Jony",   { 100, 100, 100, 100,-128,-128,-128,-128}},100,5},  //Grade=100
{{   "Ramesh", {  90,  90,  90,  90,-128,  90,-128,  90}},90,5},  //Grade=90
{{   "Mattan", {  95, 100,  95,  90,-128,  80,-128, 110}},95,5},  //Grade=95
{{   "Woosek", { 110, 100, 100, 100, 100,  98, 100, 100}},101,5},  //Grade=101
{{   "",       {-128,-128,-128,-128,-128,-128,-128,-128}},-128,5}  //Grade=-128
};

struct TestCase4{
  student_t c[10];        // input to Mode2()
  int8_t Correct;      // proper result of Mode2()
  uint32_t Score;      // points to add if Mode2() correct
};
typedef const struct TestCase4 TestCase4Type;
#define COUNT4 2
TestCase4Type Tests4[COUNT4]={
{
{{   "Jony",     { 100, 100, 100, 100,-128,-128,-128,-128}},  //Grade=100
 {   "Ramesh",   {  90,  90,  90,  90,-128,  90,-128,  90}},  //Grade=90
 {   "Mattan",   {  95, 100,  95,  90,-128,  80,-128, 110}},  //Grade=95
 {   "Ben",      { 110,-128,-128,-128,-128,   0,-128,-128}},  //Grade=55
 {   "Sourabh",  { 100,-128,-128,-128,-128,  90,-128,-128}},  //Grade=95
 {   "Dylan",    {  80,-128,-128,-128,-128,  80,-128,-128}},  //Grade=80
 {   "Kei",      {  90,-128,-128,-128,-128,  90,-128,-128}},  //Grade=90
 {   "Sean",     {  99,  99,  99,  99,-128,  99,-128,-128}},  //Grade=99
 {   "Nagaraja", {  98,-128,-128,-128,-128,  98,-128,-128}},  //Grade=98
 {   "Woosek",   { 110, 100, 100, 100, 100,  98, 100, 100}}},  //Grade=101 <-return 9
  9,10},
{
{{   "Jony",     { 100, 100, 100, 100,-128,-128,-128,-128}},  //Grade=100
 {   "Woosek",   { 110, 100, 100, 100, 100,  98, 100, 100}},  //Grade=101 <-return 1
 {   "Ramesh",   {  90,  90,  90,  90,-128,  90,-128,  90}},  //Grade=90
 {   "Mattan",   {  95, 100,  95,  90,-128,  80,-128, 110}},  //Grade=95
 {   "Ben",      { 110,-128,-128,-128,-128,   0,-128,-128}},  //Grade=55
 {   "Sourabh",  { 100,-128,-128,-128,-128,  90,-128,-128}},  //Grade=95
 {   "Dylan",    {  80,-128,-128,-128,-128,  80,-128,-128}},  //Grade=80
 {   "Kei",      {  90,-128,-128,-128,-128,  90,-128,-128}},  //Grade=90
 {   "Sean",     {  99,  99,  99,  99,-128,  99,-128,-128}},  //Grade=99
 {   "Nagaraja", {  98,-128,-128,-128,-128,  98,-128,-128}}}, //Grade=98
  1,15}
};


//prototypes to student code
uint32_t Size(const char *string);
int8_t Average(uint32_t size, const int8_t *pt);
int8_t Grade(student_t s);
int8_t TopStudent(const student_t EE319K[10]);
int main(void){ long result2;
  unsigned long result,n,score;
  score = 0;
  PLL_Init();

  UART_Init();              // initialize UART

  UART_OutString("\n\rExam2_DataBase\n\r");
  UART_OutString("Test of Size\n\r");
  for(n = 0; n < COUNT1 ; n++){
    result = Size(Tests1[n].string);
    if(result == Tests1[n].Correct){
      UART_OutString(" Yes, Your= "); 
      score = score + Tests1[n].Score;
    }else{
      UART_OutString(" No, Correct= ");
      UART_OutUDec(Tests1[n].Correct);  
      UART_OutString(", Your= "); 
    }
    UART_OutUDec(result);  
    UART_OutString(", Score = "); UART_OutUDec(score);  UART_OutCRLF();
  }

  UART_OutString("Test of Average\n\r");
  for(n = 0; n < COUNT2 ; n++){
    result2 = Average(Tests2[n].size,Tests2[n].buf);
    if(result2 == Tests2[n].Correct){
      UART_OutString(" Yes, Your= "); 
      score = score + Tests2[n].Score;
    }else{
      UART_OutString(" No, Correct= ");
      UART_OutSDec(Tests2[n].Correct);  
      UART_OutString(", Your= "); 
    }
    UART_OutSDec(result2);  
    UART_OutString(", Score = "); UART_OutUDec(score);  UART_OutCRLF();
  }
  
  UART_OutString("Test of Grade\n\r");
  for(n = 0; n < COUNT3 ; n++){
    result2 = Grade(Tests3[n].s);
    if(result2 == Tests3[n].Correct){
      UART_OutString(" Yes, Your= "); 
      score = score + Tests3[n].Score;
    }else{
      UART_OutString(" No, Correct= ");
      UART_OutSDec(Tests3[n].Correct);  
      UART_OutString(", Your= "); 
    }
    UART_OutSDec(result2);  
    UART_OutString(", Score = "); UART_OutUDec(score);  UART_OutCRLF();

  }
  
  UART_OutString("Test of TopStudent\n\r");
  for(n = 0; n < COUNT4 ; n++){
    result2 = TopStudent(Tests4[n].c);
    if(result2 == Tests4[n].Correct){
      UART_OutString(" Yes, Your= "); 
      score = score + Tests4[n].Score;
    }else{
      UART_OutString(" No, Correct= ");
      UART_OutUDec(Tests4[n].Correct);  
      UART_OutString(", Your= "); 
    }
    UART_OutUDec(result2);  
    UART_OutString(", Score = "); UART_OutUDec(score);  UART_OutCRLF();

  }
  
  
  UART_OutString("End of Exam2_DataBase\n\r");
  while(1){
  }
}
