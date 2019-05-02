// File: Exam2CPart.c 
// Akarsh Kumar
// -5 points if you do not add your name
// This is Exam2
//EE319K Spring 2018 exam 2, April 6, 2018
// This is the C Part of the Exam (See Exam2AsmPart.s for the assembly part)  
#include <stdint.h>
//****you may not use string.h************




int power(int a, int exp){
	if(exp==0)return 1;
	for(;exp>1;exp--){
		a*=a;
	}
	return a;
}

void pushNumString(int digit, char retString[], int strlen){
	char digitChar = digit+'0';
	int i=strlen-1;
	for(;i>=0;i--){
		retString[i+1] = retString[i];
	}
	retString[0] = digitChar;
}

// *** Question 1***Octal2String***************
// convert an unsigned integer to an ASCII string in base 8 (octal)
// input: n unsigned 32-bit number
//           valid numbers should range from 0 to 16777215
//           invalid numbers are above 16777215
//        retString pointer to an empty array of at least 10 bytes
// output: return 0 on success and return 1 if the input is invalid
// however, you should fill retString with a null-terminated ASCII string 
//    representing the octal value of the input n
// error condition, if the n is invalid, set retString="*" and return 1  
// Note: the grader will run many test cases, there are only a few of them
//  n         octal   meaning           return retString
//  0         0       0                 0      0x30,0
//  66        102     1*64+0*8+2        0      0x31,0x30,0x32,0
//  123       173     1*64+7*8+3        0      0x31,0x37,0x33,0
//  5123      12003   1*(8^4)+2*(8^3)+3 0      0x31,0x32,0x30,0x30,0x33,0
//  16777215  77777777                  0      0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0
//  16777216 100000000 too big          1      0x2A,0
int Octal2String(uint32_t n, char retString[]){
	if(n>16777215){
		retString[0] = '*';
		retString[1] = '\0';
		return 1;
	}
	if(n==0){
		retString[0] = '0';
		retString[1] = '\0';
		return 0;
	}
	
	retString[0] = '\0';
	int strlen=1;
	
	
	while(n>0){
		int r = n%8;
		int d = n/8;
		pushNumString(r,retString,strlen);
		strlen++;
		n=d;
	}
		
  return 0;  // remove and replace this line
}



// if valid, there will be an even number of students in EE319K
// if valid, each student will be paired with exactly one other student, 
//    such that they have the same groupId
// EIDs and groupId can be any 32-bit unsigned value
typedef struct{
  uint32_t EID;       // student ID number
  uint32_t groupId;   // each student is in a group
}Student_t;
// if there are size students, then there are (size/2) LabTables
// the LabTables are numbered (indexed) from 0 to (size/2)-1
typedef struct{     // Lab table seating chart
  uint32_t EID1;    // first student ID number
  uint32_t EID2;    // second student ID number
  uint32_t groupId; // the groupId of the two students at this lab table
}LabTable_t;



int numStudentsWithGroupID(Student_t const EE319K[],uint8_t const size, uint32_t groupID){
	int num = 0;
	for(int i=0; i <size;i++){
		if(EE319K[i].groupId==groupID){
			num++;
		}
	}
	return num;
}
int nextStudent(Student_t const EE319K[],uint8_t const size, uint32_t groupID, int i){
	i++;
	for(; i <size;i++){
		if(EE319K[i].groupId==groupID){
			return i;
		}
	}
	return -1;
}
//** Question 3 ***** AssignStudents2LabTables ***************
// EE319K[] is an array of size Student_t elements
// lab[] is an array of (size/2) LabTable_t elements
// Search the EE319K[] array looking for pairs of students with the same groupID
// For each pair of students with the same groupId
//    1) assign them to any free LabTable from index 0 to (size/2)-1
//    2) copy their EIDs and groupID into the lab[] array
// Input: EE319K is a pointer to an array of Student_t entries (initially populated)
//        lab is a pointer to an array of LabTable_t entries (initially empty)
//        size is the number of students, which may be zero, size may be even or odd
// Output: return 0 if successful
//            there are an even number of students
//      and   each student is paired with exactly one other student
//         return 1 if unsuccessful
//            there are an odd number of students
//      or    there are students not grouped with any other students (group of 1)
//      or    there are students grouped with more than one other student (group of 3, 4, ...)
// Note: the order of EID1/EID2 does not matter
// Note: the lab seating order does not matter 
// Note: the grader will run these six test cases
//  EE319K = {12,55},{34,77},{123,77},{1,55}}, size = 4
//  return 0 (valid) and modify lab array as:
//    lab = {{12,1,55},{34,123,77}
//    meaning 12+1 at table 0, 34+123 at table 1 
//---------------------------------------------------------------------------
//  EE319K = {{12,101},{34,103},{54,101},{5,102},{55,102},{4,103}}, size = 6
//  return 0 (valid) and modify lab array as:
//    lab = {{12,54,101},{34,4,103},{5,55,102}
//    meaning 12+54 at table 0, 34+4 at table 1, 5+55 at table 2 
//---------------------------------------------------------------------------
//  EE319K = {{13,99},{36,99},{125,99},{2,99}}, size = 4
//  return 1 (invalid) because more than two students/group 
//---------------------------------------------------------------------------
//  EE319K = {{13,99},{36,99},{125,98}}, size = 3
//  return 1 (invalid) because class size is odd, also invalid because student 125 has no partner
//---------------------------------------------------------------------------
//  EE319K = {{4,33},{3,33}}, size = 2
//  return 0 (valid) and modify lab array as:
//    lab = {{4,3,33}
//    meaning 4+3 at table 0 
//---------------------------------------------------------------------------
//  EE319K = {}, size = 0
//  return 0 (valid) and do not modify lab array because there are no students
//---------------------------------------------------------------------------
//  EE319K = {{12,55},{34,88},{123,88},{1,99},{13,22},{37,55},{54,22},{5,33},{8,33},{4,99}}, size = 10
//  return 0 (valid) and modify lab array as:
//    lab = {{12,37,55},{34,123,88},{1,4,99},{13,54,22},{5,8,33}
//    meaning 12+37 at table 0, 34+123 at table 1, 1+4 at table 2, 13+54 at table 3, 5+8 at table 4 
//---------------------------------------------------------------------------
//  EE319K = {{12,55},{34,88},{123,88},{1,99},{13,22},{37,55},{54,22},{5,33},{8,30},{4,99}, size = 10
//  return 1 (invalid) because class 5 and 8 do not have partners 
//  you are allowed to partially modify lab when inputs are invalid
int AssignStudents2LabTables(Student_t const EE319K[], LabTable_t lab[], uint8_t const size){
	if(size%2!=0){
		return 1;
	}
	
	int labI=0;
	for(int i=0; i <size;i++){
		int numStudentsWithID = numStudentsWithGroupID(EE319K,size,EE319K[i].groupId);
		if(numStudentsWithID!=2){
			return 1;
		}
		int nextI = nextStudent(EE319K,size,EE319K[i].groupId,i);
		if(nextI==-1){
			continue;
		}
		lab[labI].EID1 = EE319K[i].EID;
		lab[labI].EID2 = EE319K[nextI].EID;
		lab[labI].groupId = EE319K[i].groupId;
		
		
		
		labI++;
		
		if(labI==size/2){
			break;
		}
	}
  
  return 0;  // remove and replace this line

}

