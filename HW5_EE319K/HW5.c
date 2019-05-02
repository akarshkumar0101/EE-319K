// This HW5
// Jonathan Valvano
// Spring 2019 EE319K
// You will implement the mode function
#include <stdint.h>
char myEID[]="ak39969"; // edit this line with your student EID
char Semester[]="Spring 2019";


int indexOfMax(int array[], int arrLength);

char mode(const char string[30]){ 
// write this function
	
	int charCount[26];
	for(int i=0; i < 26; i++){
		charCount[i]=0;
	}
	
	int i = 0;
	while(string[i] != '\0'){
		char c = string[i];
		int charIndex = c-'a';
		charCount[charIndex]++;
		i++;
	}
	int maxCharIndex = indexOfMax(charCount, 26);
	char modeChar = maxCharIndex + 'a';
	
	
  return modeChar;
}
int indexOfMax(int array[], int arrLength){
	int max = -2000000000;
	int maxI = -1;
	for(int i=0; i <arrLength;i++){
		if(array[i]>max){
			max = array[i];
			maxI = i;
		}
	}
	return maxI;
}




