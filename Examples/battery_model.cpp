//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Authors: Joshua Blomgren, Charis Liao, Jeffy Jeffy 
//  Fall 2022 
    
//  This file contains the application for battery cell using the Battery model.
//  The general idea is to simulate a battery clusters in electric cars where only certain 
//  batteries are of higher energy. The goal is to see how the battery clusters will evolve
//  over time and reach an equilibrium state. In this example, we will use a 2D grid with
//  3 states: 0, 1, and 2. 0 represents a 1V, 1 represents a 2V, and
//  2 represents a battery at 3V. The rules are as follows:
//  1. If a cell has 3 or more neighbors with state 2, it will become a state 2 cell
//  2. If a cell has 3 or more neighbors with state 1, it will become a state 1 cell
//  3. If a cell has 3 or more neighbors with state 0, it will become a state 0 cell
//  It is important to note that the rules are applied simultaneously to all cells in the grid.
//  This means that the state of a cell in the next time step is determined by the states of
//  all the cells in the current time step. 
//  Additionally, the grid is periodic, meaning that the cells on the edges of the grid are
//  neighbors with the cells on the opposite edges of the grid.
//  As majority rule is being implemented, each state has a probability associated with it 
//  of becoming the next state, this allows to randomly place initial conditions in the grid.

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

    err = Battery.setup_dimension(2, 100, 100);           // 2D, 10x10 grid
    if(err == -1){
        cout << "Error: Invalid dimension" << endl;
        return -1;
    }

    err = Battery.setup_neighborhood(2);                // Moore neighborhood
    if(err == -1){
        cout << "Error: Invalid neighborhood" << endl;
        return -1;
    }

    err = Battery.setup_boundtype(1, 1);                // periodic boundary conditions, radius 1
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

    err = Battery.init_cond(1, 0.75);                    // random initial condition, 75% chance of being 1 from 0
    if(err == -1){
        cout << "Error: Invalid state" << endl;
        return -1;
    } else if(err == -2){
        cout << "Error: Invalid probability" << endl;
        return -2;
    } else if(err == -5){
        cout << "Error: No grid is set up. Use setup_dimension()" << endl;
        return -5;
    }
    cout << "Initial condition: " << endl;
    Battery.print_grid();                         // print the initial condition grid to the screen
    cout << endl;
    cout << "Rewrite condition: " << endl;
    err = Battery.init_cond_rewrite(1, 2, 0.5);         // rewrite the initial condition grid, 50% chance of being 2 from 1
    if(err == -1){
        cout << "Error: Invalid state" << endl;
        return -1;
    } else if(err == -2){
        cout << "Error: Invalid probability" << endl;
        return -2;
    } else if(err == -5){
        cout << "Error: No grid is set up. Use setup_dimension()" << endl;
        return -5;
    } else if (err == 0){
        Battery.print_grid();  // print the rewrite condition of the  grid to the screen
        cout << endl;
    }

    // run the simulation for 10 time steps and print the grid to the screen after each time step
    // the resulting grid will be saved to the file "battery_model.txt"
    err = Battery.run_sim(15,false, true, "battery_model.txt");
    if (err == -1){
        cout << "Error: Invalid number of time steps" << endl;
        return -1;
    } else if (err == -2){
        cout << "Error: Invalid boundary type" << endl;
        return -2;
    } else if (err == -3){
        cout << "Error: Invalid neighborhood type" << endl;
        return -3;
    } else if (err == 0){
        cout << "Simulation complete" << endl;
    }
    return 0;

}