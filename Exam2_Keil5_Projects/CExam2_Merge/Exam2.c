/*
;*****Your name goes here*******
; -5 points if you do not add your name

 ;This is Exam2_Merge 
;EE319K Practice exam
;You edit this file only
*/
/*
;***** Init *********************
;Initialize the array to a value
;Each value is 16-bit unsigned
;Inputs:  buffer is a pointer to an empty array of 16-bit unsigned numbers
;         value is the 16-bit unsigned value to be stored into each element
;         size is the number of 16-bit unsigned values in the array
;         The array maybe of zero length (size may be zero)
;Output:  none
;Error conditions: none
;Test cases
;buffer=>empty array, value=3,size=4, result new array is {3,3,3,3}
;buffer=>empty array, value=7,size=1, result new array is {7}
;buffer=>empty array, value=5,size=8, result new array is {5,5,5,5,5,5,5,5}
;buffer=>empty array, value=0,size=0, result is no change to empty array
*/
void Init(unsigned short *buffer,unsigned short value, unsigned long size){
 // put your code here

}

/*
;***** Insert subroutine *********************
; Insert the number into the beginning of the output array
;   copy all the elements of the input array to the output array
;Inputs :  buffer points to input array of 16-bit unsigned numbers
;          size contains the length of the input array
;          value contains number to insert
;          answer is a pointer to an empty array that should be written into
;Outputs: The array at answer is modified
;Error conditions: none.
;test cases
;buffer=>{1,2,3,4,5,6},size=6,value=8,   answer=>{8,1,2,3,4,5,6}
;buffer=>{1},          size=1,value=9,   answer=>{9,1}
;buffer=>{0,0,1,2},    size=4,value=0xFE,answer=>{0xFE,0,0,1,2}
;buffer=>{},           size=0,value=0x45,answer=>{0x45}
*/
void Insert(const unsigned short *buffer, unsigned long size, unsigned short value, unsigned short *answer){
// put your code here

	

}

/*;***** Merge subroutine *********************
; Assume both arrays are initially sorted 16-bit unsigned numbers
; Merge the two input arrays into the output array
;   making the output array contain all the numbers in sorted order
;Inputs : buffer1 points to the first array of 16-bit unsigned numbers
;         buffer2 points to the second array of 16-bit unsigned numbers
;         size1 contains the number of elements in the first array
;         size2 contains the number of elements in the second array
;         answer is a pointer to an empty output array
;Outputs: the array pointed to by answer is modified
;Error conditions: none.
;test cases
;buffer1=>{0x8000},             buffer2=>{0x7000},             size1=1,size2=1,answer=>{0x7000,0x8000}
;buffer1=>{0x01,0x03,0x05,0x07},buffer2=>{0x02,0x04,0x06,0x08},size1=4,size2=4,answer=>{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08}
;buffer1=>{0x01,0x02,0x03,0x04},buffer2=>{0x05,0x06,0x07,0x08},size1=4,size2=4,answer=>{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08}
;buffer1=>{0x01,0x02},          buffer2=>{0x05,0x06,0x07,0x08},size1=2,size2=4,answer=>{0x01,0x02,0x05,0x06,0x07,0x08}
;buffer1=>{0x01,0x02,0x03,0x04},buffer2=>{0x05},               size1=4,size2=1,answer=>{0x01,0x02,0x03,0x04,0x05}
;buffer1=>{0x01,0x02,0x03,0x04},buffer2=>{},                   size1=4,size2=0,answer=>{0x01,0x02,0x03,0x04}
;buffer1=>{},                   buffer2=>{},                   size1=0,size2=0,answer=>{} (no change to output array)
*/
void Merge(const unsigned short *buffer1,const unsigned short *buffer2,unsigned long size1, unsigned long size2, unsigned short *answer){
// put your code here


}
      
