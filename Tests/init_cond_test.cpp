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

    err = CA.setup_dimension(2, 10, 10);           // 2D, 10x10 grid
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

    err = CA.setup_rule(1);                        // majority rule
    if(err == -1){
        cout << "Error: Invalid rule" << endl;
        return -1;
    }

    err = CA.init_cond(1, 0.5);                    // random initial condition, 50% chance of being 1 from 0
    if(err == -1){
        cout << "Error: Invalid state" << endl;
        return -1;
    } else if(err == -2){
        cout << "Error: Invalid probability" << endl;
        return -2;
    } else if(err == -5){
        cout << "Error: No grid is set up. Please call setup_dimension()" << endl;
        return -5;
    }
    cout << "Initial condition: " << endl;
    CA.print_grid();                         // print the initial condition grid to the screen
    cout << endl;
    cout << "Rewrite condition: " << endl;
    err = CA.init_cond_rewrite(1, 2, 0.4);         // rewrite the initial condition grid, 40% chance of being 2 from 1
    if(err == -1){
        cout << "Error: Invalid state" << endl;
        return -1;
    } else if(err == -2){
        cout << "Error: Invalid probability" << endl;
        return -2;
    } else if(err == -5){
        cout << "Error: No grid is set up. Please call setup_dimension()" << endl;
        return -5;
    }
    CA.print_grid();                         // print the rewritten initial condition grid to the screen
    return 0;
}