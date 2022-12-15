//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Fall 2022
    
//  This file contains a C++ test program for the CellularAutomata class
//  relating to the setup of the model

//  datatypes.h  Contains the C++ Class definitions for the
//               Cellular Automata Model
#include "datatypes.h"
// random.h  Contains the API for the random seed generator
#include "random.h"

int main(){
    int err; 
    CellularAutomata CA;                     // create a CellularAutomata object

    err = CA.setup_dimension(2, 5, 10);           // 2D, 5x10 grid
    if(err == -1){
        cout << "Error: Invalid dimension" << endl;
        return -1;
    }

    err = CA.setup_neighborhood(2);                // Moore neighborhood
    if(err == -1){
        cout << "Error: Invalid neighborhood" << endl;
        return -1;
    }

    err = CA.setup_boundtype(0, 1);                // periodic boundary conditions, radius 1
    if(err == -1){
        cout << "Error: Invalid boundary type" << endl;
        return -1;
    } else if(err == -2){
        cout << "Error: Invalid radius" << endl;
        return -2;
    }

    err = CA.setup_cell_states(2);                 // 2 states
    if(err == -1){
        cout << "Error: Invalid number of states" << endl;
        return -1;
    }

    err = CA.setup_rule(2);                        // priority rule
    if(err == -1){
        cout << "Error: Invalid rule" << endl;
        return -1;
    }

    CA.print_setup_info();       // print all the setup information inputted
    return 0;
}