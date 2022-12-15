//
//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Fall 2022
//
//  random.h contains the methods and API declarations for the random number
//  generator

#pragma once    // Ensures that this file is only included once
                // during compilation

#include <ctime>    // A call to the system time() to init
                    // the seed of the random number generator
#include <iostream>
using namespace std;

// LIST OF FLAGS AND SYMBOLS:
// Predefined value for seed of the C pseudo random 
// number generator.  
#define FIXED_RSEED  123

// Possible integer values for random_type, which 
// sets or resets the C pseudo random number generator
// if random_type=1, uses FIXED_RSEED to set the rseed
// if random_type=2, uses the system time to randomly set
//                   rseed
#define GEN_FIXED_RSEED    1
#define GEN_NEW_RSEED      2

// Function: set_rseed sets the seed of the C++ random number generator
// Input: random_type, an integer that sets the seed of the random number 
//        generator (see above for possible values)
// Output: none
// Return: 0 (success)
//        -5 (fail)
int set_rseed(int random_type);