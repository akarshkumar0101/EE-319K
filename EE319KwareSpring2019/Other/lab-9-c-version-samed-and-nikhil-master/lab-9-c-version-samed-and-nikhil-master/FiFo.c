// FiFo.c
// Runs on LM4F120/TM4C123
// Provide functions that implement the Software FiFo Buffer
// Last Modified: 4/10/2017 
// Nikhil Arora
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#define size 20
// --UUU-- Declare state variables for FiFo
//        size, buffer, put and get indexes

// *********** FiFo_Init**********
// Initializes a software FIFO of a
// fixed size and sets up indexes for
// put and get operations
uint8_t putI, getI;
char FiFo[size];

void FiFo_Init() {
	putI = 0;
	getI = 0;
}

// *********** FiFo_Put**********
// Adds an element to the FIFO
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
uint32_t FiFo_Put(char data) {
	if((putI + 1) % size == getI){
		return 0;
	}
	FiFo[putI] = data;
	putI = (putI + 1) % size;
	return(1);
}

// *********** FiFo_Get**********
// Gets an element from the FIFO
// Input: Pointer to a character that will get the character read from the buffer
// Output: 1 for success and 0 for failure
//         failure is when the buffer is empty
uint32_t FiFo_Get(char *datapt){
	if(putI == getI)
		return 0;
	
	*datapt = FiFo[getI];
	getI = (getI + 1) % size;
  return(1); // Replace this
}



