/*
;*****Your name goes here*******
; -5 points if you do not add your name

 ;This is Exam2_PermutationsCombinations 
;EE319K Summer 2014
;You edit this file only
*/
#include <stdint.h>

/***********Permute*********
  Computes and returns the number of ways 
	N objects can be arranged in K slots (Permutations). 
	One can compute Permute(N,K) as: 
	     N*(N-1)*(N-2)*… *(N-K+1)
	Another way to think about the computation is there are K 
	terms involved in computing Permute(N,K). 
	These K terms start at N and count K terms down.
Inputs: N is 8-bit number indicating number of objects
        K is a 8-bit number indicating number of slots
Output: 32-bit number indicating the number of ways N objects
        can be arranged in K slots
Exceptions: (i) If N or K is zero then result is 1; 
           (ii) If N<K then the result is undefined so you must return -1
Test cases:
  1. N=20,K=3 ==> Result = 20*19*18 = 6840
	2. N=4,K=4 ==> Result = 4*3*2*1 = 24
	3. N=10,K=5 ==> Result = 10*9*8*7*6 = 30240
	4. N=2,K=5 ==> Result = -1 (N<K : 2<5)
	5. N=8,K=0 ==> Result = 1 (K=0)
	6. N=12,K=1 ==> Result = 12
*/
int32_t Permute(uint8_t N, uint8_t K){
  return 42; // replace this line with your code
}

/***********NChooseK*********
  Computes and returns the number of ways 
  k objects can be choosen out of N (Combinations). 
  One can compute NChooseK as :
    (N*(N-1)*(N-2)*… *(N-K+1))/(K*(K-1)*(K-2)…*1)
  You will notice the numerator is simply Permute(N,K), 
  and the denominator can also be calculated by calling 
  the Permute function with appropriate inputs.
Inputs: N is 8-bit number indicating number of objects
        K is a 8-bit number indicating number to choose
Output: 32-bit number indicating the number of ways K objects
        can be choosen from N objects
Exceptions: (i) If N or K is zero then result is 1; 
           (ii) If N<K then the result is undefined so you must return -1
Test cases:
  1. N=10,K=5 ==> Result = (10*9*8*7*6)/(5*4*3*2*1) = 252
	2. N=20,K=4 ==> Result = (20*19*18*17)/(4*3*2*1) = 4845
	3. N=2,K=5 ==> Result = -1 (N<K : 2<5)
	4. N=8,K=0 ==> Result = 1 (K=0)
	5. N=12,K=1 ==> Result = 12/1 = 12
	6. N=0,K=0 ==> Result = 1 (N=0 and K=0)
*/

int32_t NChooseK(uint8_t N, uint8_t K){
  return 42; // replace this line with your code
}

/***********BinomialCoefficients*********
  Computes multiple Combinations which are the 
  coefficients of the binomial expansion. 
  For a given input N, there are (N+1) binomial coefficients: 
        NChooseK(N,0), NChooseK(N,1), NChooseK(N,2),… , NChooseK(N,N).
  Your routine will do two tasks:
    i)	compute the coefficients and put them in the array passed as the second input. 
    ii)	return the sum of the coefficients. 
Inputs: N is 8-bit number indicating number of objects
        BinCoeffs is an array that you have to fill with the computed coefficients 
Output: 32-bit number indicating the sum of the coeeficients
Exceptions: (i) If N zero then result is 1;
Test cases:
  1. N=2 ==> Coeffs = {NChooseK(2,0)=1,NChooseK(2,1)=2,NChooseK(2,2)=1} and returned sum = 1+2+1 = 4
	2. N=7 ==> Coeffs = {1,7,21,35,35,21,7,1} and returned sum = 1+7+21s+35+35+21+7+1 = 128
  3. N=5 ==> Coeffs = {1,5,10,10,5,1} and returned sum = 1+5+10+10+5+1 = 32
  4. N=12 ==> Coeffs = {1,12,66,220,495,792,924,792,495,220,66,12,1} and returned sum = 4096 
  5. N=1 ==> Coeffs = {NChooseK(1,0)=1,NChooseK(1,1)=1} and returned sum = 1+1 = 2
  6. N=0 ==> Coeffs = {NChooseK(0,0)=1} and returned sum = 1
****PLEASE NOTE: There is no partial credit for getting the coefficients right 
                 but getting the sum wrong or vice versa. To earn points in any test case
								 you must get both right.
*/
uint32_t BinomialCoefficients(uint8_t N, int32_t BinCoeffs[]){
	return 42; // replace this line with your code
}

