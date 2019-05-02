/*
;*****Your name goes here*******
; -5 points if you do not add your name

;This is Exam2_DataBase 
;EE319K Practice exam
;You edit this file only
*/   
#include <stdint.h>

/*
***************** Size****************************
 Determines the length of a null-terminated string.  
 Input parameter: pt points to variable-length string 
 sentinel is 0
 Output parameter: Return the length of string
 Error conditions: if string is empty, return 0 
Test cases
"Jony"                 size = 4
"Ramesh Yerraballi"    size = 17
{4,1,2,3,0}            size = 4,
"Jonathan Valvano"     size = 16
""                     size = 0
*/      
uint32_t Size(const char *string){ 
// put your code here
	 int length = 0;
	 for(int i=0;;i++){
		 if(string[i] == '\0'){
			 return length;
		 }
		 else{
			 length++;
		 }
	 }
  
   return -1;  // change this line
}

/****************** Average ****************************
Find the average of the data in a variable length buffer 
The data in the buffer range from -127 to +127
Input: size is the number of elements in the buffer
       pt is a pointer to the buffer
Output: average of the data in the buffer
Error conditions: Return 0 if the buffer is empty.
Test cases
  size value buffer
   5,    {1,4,3,3,4}                  //Average=3
  10,    {-3,-10,0,0,0,0,1,2,0,0}     //Average=-1
   5,    {-1,2,3,-3,4}                //Average=1
   7,    {-6,-9,-7,-8,-8,-9,-9}       //Average=-8
   0,    {}                           //Average=0
*/
int8_t Average(uint32_t size, const int8_t *pt){ 
// put your code here
	if(size==0){
		return 0;
	}
	
	int32_t sum = 0;
	int32_t size_ = size;
	int i=0;
	for(i=0; i <size;i++){
		sum+=pt[i];
	}
	int32_t average = sum/size_;
	return average;
}
struct student{
  char name[20];
  int8_t data[8]; // skip if data=-128
};
typedef struct student student_t;

/* ****************** Grade ****************************
Finds the average student grade
Skip grades that are -128
Input: one student record
Error conditions: Return -128 if there are no grades in the list.
Test cases
   "Jony",   { 100, 100, 100, 100,-128,-128,-128,-128}  //Grade=100
   "Ramesh", {  90,  90,  90,  90,-128,  90,-128,  90}  //Grade=90
   "Mattan", {  95, 100,  95,  90,-128,  80,-128, 110}  //Grade=95
   "Woosek", { 110, 100, 100, 100, 100,  98, 100, 100}  //Grade=101
   "",       {-128,-128,-128,-128,-128,-128,-128,-128}  //Grade=-128
*/
int8_t Grade(student_t s){ 
// put your code here
	int8_t gradeCount=0;
	int16_t gradeSum=0;
	
	for(int i=0;i <8;i++){
		
		if(s.data[i]!=-128){
			gradeCount++;
			gradeSum += s.data[i];
		}
	}
	if(gradeCount==0){
		return -128;
	}
	else{
		return gradeSum/gradeCount;
	}
}


/* ****************** TopStudent ****************************
Find the student with the highest average 
Input: Array of 10 students
Output: index value of the student with highest average
Error conditions: none
Test case
   "Jony",     { 100, 100, 100, 100,-128,-128,-128,-128}  //Grade=100
   "Ramesh",   {  90,  90,  90,  90,-128,  90,-128,  90}  //Grade=90
   "Mattan",   {  95, 100,  95,  90,-128,  80,-128, 110}  //Grade=95
   "Ben",      { 110,-128,-128,-128,-128,   0,-128,-128}  //Grade=55
   "Sourabh",  { 100,-128,-128,-128,-128,  90,-128,-128}  //Grade=95
   "Dylan",    {  80,-128,-128,-128,-128,  80,-128,-128}  //Grade=80
   "Kei",      {  90,-128,-128,-128,-128,  90,-128,-128}  //Grade=90
   "Sean",     {  99,  99,  99,  99,-128,  99,-128,-128}  //Grade=99
   "Nagaraja", {  98,-128,-128,-128,-128,  98,-128,-128}  //Grade=98
   "Woosek",   { 110, 100, 100, 100, 100,  98, 100, 100}  //Grade=101 <-return 9
*/
uint32_t TopStudent(const student_t EE319K[10]){ 
// put your code here
	uint32_t bestStudent = -1;
	int8_t bestGrade = -128;
	
	for(int i=0; i <10;i++){
		int8_t grade = Grade(EE319K[i]);
		if(grade>bestGrade){
			bestGrade = grade;
			bestStudent = i;
		}
	}
  
  return bestStudent;
}

