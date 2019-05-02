//*****Your name goes here*******
// -5 points if you do not add your name

//This is Exam2_Unicode  
//EE319K Spring 2015
//April 9, 2015
//You edit this file only

       
//***** IsDigit subroutine*********************
// Decide whether or not a Unicode character in R0 is a decimal digit  
// Note: Unicode characters 0x0030 to 0x0039 are decimal digits
//Input:   R0 has a Unicode character
//Output:  R0 is 0 if the input is not a decimal digit and -1 if it is a digit
//Invariables: You must not permanently modify registers R4 to R11, and LR
//Here are all 5 test cases:
// Input = 0x002F ; result is 0
// Input = 0x0030 ; result is -1 
// Input = 0x0039 ; result is -1
// Input = 0x003A ; result is 0
// Input = 0x3233 ; result is 0   
long IsDigit(unsigned short letter){
  // put your answer here

  return 32; // replace this line
}

      
//***** StrLen subroutine*********************
// Finds the length of a null-terminated Unicode string
// Each character is 16 bits, terminated with a 0x0000
//Input:   R0 has a pointer to a null-terminated variable length string
//Output:  R0 has the length of the input Unicode string
//Invariables: You must not permanently modify registers R4 to R11, and LR
//Error conditions: none, all Unicode characters are valid in the string
//Here are some test cases:
// Input = 0x0030,0x0031,0x0032,0x0000                      ; Output is 3
// Input = 0x0039,0x0000                                    ; Output is 1
// Input = 0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x0000 ; Output is 14
// Input = 0x10F1,0x20F2,0x30F3,0x40F4,0xFFFF,0x6000,0x0001,0x0100,0x0001,0x00F1,0x00F2,0x00F3,0x00F4,0x00F5,0x00F6,0x0000 ; Output is 15
// Input = 0x0000                                           ; Output is 0
long StrLen(const unsigned short *p){

  // put your answer here
  return 32; // replace this line
}
      

      
//***** Uni2Dec Unicode to Decimal subroutine*********************
// Given a pointer to a null-terminated Unicode string 
// calculate the value the unsigned decimal number between 0 and +4,294,967,294 (2^32 - 2)
// return the unsigned decimal number in R0.  
// valid Unicode decimal digits are 0x0030 to 0x0039, meaning 0 to 9 respectively
//Input:   R0 has a pointer to a null-terminated variable length Unicode string
//Output:  R0 is the decimal number defined by the Unicode string
//Invariables: You must not permanently modify registers R4 to R11, and LR
//Error conditions: return 0xFFFFFFFF if any character is not Unicode decimal digit
//                  return 0 if the string is empty
//Here are the 8 test cases:
// Input = 0x0030,0x0031,0x0032,0x0000,               Output = 12
// Input = 0x0039,0x0000,                             Output = 9
// Input = 0x0032,0x0033,0x0034,                      Output = 234
// Input = 0x0031,0x0032,0x0033,0x0034,0x0035,0x0000, Output = 12345
// Input = 0x0031,0x0032,0x003A,0x0034,0x0035,0x0036,0x0000, Output = 0xFFFFFFFF (illegal char)
// Input = 0x0034,0x0032,0x0039,0x0034,0x0039,0x0036,0x0037,0x0032,0x0039,0x0034,0x0000, Output = 4,294,967,294
// Input = 0x0035,0x0032,0x0039,0x0034,0x0039,0x0032,0x0039,0x3000,0x0000, Output = 0xFFFFFFFF (illegal char)
// Input = 0x0000,                                    Output = 0 (empty string)
unsigned long Uni2Dec(const unsigned short *p){
  // put your answer here

  
  return 32; // replace this line
}
  
      
//***** Convert subroutine*********************
// You are given a pointer (in R0) to a null-terminated ASCII string located in RAM, 
// convert the ASCII string to a null-terminated Unicode string
// Each ASCII character is 1 byte (8 bits), each Unicode character is 16 bits.
// The conversion is done in place (the output buffer is the same as the input buffer).
// If the input string has "n" ASCII characters plus null, 
//   then you are not allowed to access beyond "n" Unicode characters plus Unicode null
//Input:   R0 has a pointer to a null-terminated variable length ASCII string
//         If the ASCII string has "n" ASCII characters plus null,
//            then there is room in the buffer for "n" Unicode characters plus Unicode null 
//Output:  None (The string is converted in place)
//Invariables: You must not permanently modify registers R4 to R11, and LR
//Error conditions: none, all ASCII strings will be valid, 
//                 and the buffer is large enough to hold the new Unicode string
//Here are the 5 test cases:
// Input = 0x30,0x31,0x32,0x00                converted to 0x0030,0x0031,0x0032,0x0000
// Input = 0x39,0x00                          converted to 0x0039,0x0000 
// Input = 0x31,0x32,0x33,0x34,0x35,0x00      converted to 0x0031,0x0032,0x0033,0x0034,0x0035,0x0000
// Input = 0xA1,0xB2,0xC3,0xD4,0xE5,0xF6,0x00 converted to 0x00A1,0x00B2,0x00C3,0x00D4,0x00E5,0x00F6,0x0000
// Input = 0x00                               converted to 0x0000 

void Convert(unsigned short *pt1){ 
  unsigned char *pt2;
  pt2 = (unsigned char *)pt1;
 
  
  // put your answer here
}
      

