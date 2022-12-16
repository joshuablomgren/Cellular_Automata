//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Fall 2022 
    
//  This file contains the appliBatterytion for battery cell using the Battery model 

//  datatypes.h  Contains the C++ Class definitions for the

//               Cellular Automata Model

#include "datatypes.h"

// random.h  Contains the API for the random seed generator

#include "random.h"

// Function: main   
// Input: none
// Output: none
// Return: 0: success


int main(void) {
    int err; 
    CellularAutomata Battery;                     // create a CellularAutomata object

    err = Battery.setup_dimension(2, 10, 10);           // 2D, 10x10 grid
    if(err == -1){
        cout << "Error: Invalid dimension" << endl;
        return -1;
    }

    err = Battery.setup_neighborhood(2);                // Moore neighborhood
    if(err == -1){
        cout << "Error: Invalid neighborhood" << endl;
        return -1;
    }

    err = Battery.setup_boundtype(0, 1);                // periodic boundary conditions, radius 1
    if(err == -1){
        cout << "Error: Invalid boundary type" << endl;
        return -1;
    } else if(err == -2){
        cout << "Error: Invalid radius" << endl;
        return -2;
    }

    err = Battery.setup_cell_states(3);                 // 2 states
    if(err == -1){
        cout << "Error: Invalid number of states" << endl;
        return -1;
    }

    err = Battery.setup_rule(1);                        // majority rule
    if(err == -1){
        cout << "Error: Invalid rule" << endl;
        return -1;
    }

    err = Battery.init_cond(1, 0.9);                    // random initial condition, 50% chance of being 1 from 0
    if(err == -1){
        cout << "Error: Invalid state" << endl;
        return -1;
    } else if(err == -2){
        cout << "Error: Invalid probability" << endl;
        return -2;
    } else if(err == -5){
        cout << "Error: No grid is set up. Please Batteryll setup_dimension()" << endl;
        return -5;
    }
    cout << "Initial condition: " << endl;
    Battery.print_grid();                         // print the initial condition grid to the screen
    cout << endl;
    cout << "Rewrite condition: " << endl;
    err = Battery.init_cond_rewrite(1, 2, 0.6);         // rewrite the initial condition grid, 40% chance of being 2 from 1
    if(err == -1){
        cout << "Error: Invalid state" << endl;
        return -1;
}