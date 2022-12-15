//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Fall 2022

//  This file 

// random.h in ../../Include/random.h contains the API for the random number generator
#include "random.h"

// Function: set_rseed sets the seed of the C++ random number generator
// Input: random_type, an integer that sets the seed of the random number 
//        generator (see above for possible values)
// Output: none
// Return: 0 (success)
//        -5 (fail)
int set_rseed(int random_type){
    if(random_type == GEN_FIXED_RSEED){
        srand(FIXED_RSEED);
    }
    else if(random_type == GEN_NEW_RSEED){
        srand(time(NULL));
    }
    else{
        return -5;
    }
    return 0;
}