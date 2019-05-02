// ****Your name goes here*******
// -5 points if you do not add your name

// This is Exam2_ManhattanDistance 
// EE319K Spring 2016 exam 2, April 7, 2016
// You edit this file only  
#include <stdint.h>

//***************** Pack****************************
// Pack two 4-bit numbers into one 8-bit result 
// Note that the two 4-bit inputs are the lower 4 bits of the 
// 8-bit variables passed to the function.
// Input parameter:  x is a 4-bit unsigned value (most significant nibble)
//                   y is a 4-bit unsigned value (least significant nibble)
// Output parameter:  8-bit packed value
// Error conditions: none
// Test Cases as (x, y) pairs: 
// (0,0),(3,0),(4,15),(5,9),(11,12)
uint8_t Pack(uint8_t x, uint8_t y){
  // put your answer here
  
  return 42; // replace this line with your solution
}

//***************** ManhattanDistance****************************
// Calculate Manhattan distance between two points
// each point is two 4-bit unsigned numbers packed into an 8-bit value
// Input parameter:  n1 = (x1,y1) is position of first point
//                   n2 = (x2,y2) is position of second point
// Output parameter:  |x1-x2| plus |y1-y2|
// Error conditions: none
// Test Cases: 
//  n1   x1,y1    n2   x2,y2  ManhattanDistance
// 0x00 ( 0, 0), 0x30 ( 3, 0)    3+0=3
// 0x4F ( 4,15), 0x58 ( 5, 8)    1+7=8  
// 0xCE (12,14), 0x1A ( 1,10)   11+4=15
// 0x2D ( 2,13), 0x2D ( 2,13)    0+0=0
// 0xF0 (15, 0), 0x0F ( 0,15)  15+15=30
uint32_t ManhattanDistance(uint8_t n1, uint8_t n2){
  // put your answer here
 
  return 42; // replace this line with your solution
}

//******************Highest**************************
// You are given two numbers a and m
// Your function should find the largest number n such that
// a^n is less than or equal to m
// Input:  a is a 32-bit unsigned value
//         m is a 32-bit unsigned value
// Output: largest possible 32-bit value n
// Error conditions: ignore overflow possibilities
// Test Cases:
// a^n is less than or equal to m
// 2^4 is less than or equal to 16
// 3^5 is less than or equal to 250
// 4^6 is less than or equal to 10000
// 10^1 is less than or equal to 10
// 24^0 is less than or equal to 20
uint32_t Highest(uint32_t a, uint32_t m){
  // put your answer here
  
  return 42;
}

struct point{
  uint8_t x;  // 0 to 255
  uint8_t y;  // 0 to 255
};
typedef struct point point_t;

// **************MaxManhattanDistance****************
//   Find the maximum Manhattan distance from a set of points
//   You will be given from two to ten points
//   For each pair of points in the array calculate Manhattan distance
//   For numpoints points there are numpoints*(numpoints-1)/2 pairs to check
// Input:  numpoints is the number of points in the array
//         points is an array of point_t 
// Output: the maximum Manhattan distance between points in the array
// Error conditions: none
//------------------------------------------------------------------
//Case 1: three points in array (3*2/2 is 3 cases to check)
// 3, {{0,2},{1,1}{2,0}} 
// max Manhattan distance is 2+2=4, between {0,2} and {2,0} 
//------------------------------------------------------------------
//Case 2: four points in array (4*3/2 is 6 cases to check)
// {4, {{1,1},{1,4},{0,2},{6,0}} 
// max Manhattan distance is 5+4=9, between {1,4} and {6,0}
//------------------------------------------------------------------
//Case 3: five points in array (5*4/2 is 10 cases to check)
// {5, {{1,1},{1,4},{7,0},{0,2},{1,15}} 
// max Manhattan distance is 7+15=17, between {7,0} and {1,15}
//------------------------------------------------------------------
//Case 4: two points in array (2*1/2 is 1 case to check)
// {2, {{2,11},{1,4},
// max Manhattan distance is 1+7=8, between {2,11} and {1,4}
//------------------------------------------------------------------
//Case 5: six points in array (6*5/2 is 15 cases to check)
// {6, {{1,1},{0,15},{1,4},{0,2},{7,0},{1,10}} 
// max Manhattan distance is 7+15=22, between {0,15} and {7,0}
//------------------------------------------------------------------
//Case 6: nine points in array (9*8/2 is 36 cases to check)
// {9, {{1,1},{1,4},{2,4},{1,9},{3,4},{2,0},{8,1},{1,0},{4,4}
// max Manhattan distance is 7+8=15, between {1,9} and {8,1}
uint32_t MaxManhattanDistance(uint32_t numpoints, point_t *points){
  // put your answer here
 
  return 42; // replace this line with your solution
}

