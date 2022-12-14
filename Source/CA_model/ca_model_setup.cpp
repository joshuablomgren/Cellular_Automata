//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Fall 2022
    
//  This file contains the methods for the CellularAutomata class 
//  relating to the setup of the model

//  datatypes.h  Contains the C++ Class definitions for the
//               Cellular Automata Model
#include "datatypes.h"

// Function: CellularAutomata::CellularAutomata() default constructor
//           Initializes the class variables to default values
CellularAutomata::CellularAutomata(){
    neigh_type = 1;  // Von Neumann neighborhood
    bound_type = 0;  // No boundaries
    radius = 1;      // Radius of the neighborhood
    nstates = 2;     // Number of states
    rule = 0;        // Rule
    dim1 = 0;        // Dimension 1
    dim2 = 0;        // Dimension 2
    run_flag = false;  // Simulation is not running
}

// Function: CellularAutomata::~CellularAutomata() destructor
//           Clears the grids
CellularAutomata::~CellularAutomata(){
    current_grid.clear();
    next_grid.clear();
}

// Function: setup_dimension
// Setup the dimensions of the cellular automata model
// Input: ndims: number of dimensions (1 or 2)
//        dim1: dimension 1
//        dim2: dimension 2
// Output: Sets up a 1D or 2D grid
// Return: 0: success
//         -1: fail: invalid number of dimensions
//         -10: fail: simulation is already running, cannot change dimensions
int CellularAutomata::setup_dimension(int ndims, int dim1, int dim2){
    if (run_flag == true) {
        return -10;   // Error: simulation is already running, cannot change dimensions
    }
    if (ndims == 1) {
        vector<int> grid1D(dim1);       // 1D cellular automata (size dim1)
        current_grid.push_back(grid1D); 
        next_grid.push_back(grid1D);
        return 0;
    } else if (ndims == 2) {
        vector<vector<int> > grid2D(dim1, vector<int>(dim2));   // 2D cellular automata (size dim1 x dim2)
        current_grid = grid2D;
        next_grid = grid2D;
        return 0;
    } else {
        return -1;   // Error: invalid number of dimensions
    }
}

// Function: setup_neighborhood
// Set the neighborhood of the cellular automata model
// Input: neigh_type: neighborhood type (1: Von Neumann, 2: Moore)
// Output: Updates the neighborhood type
// Return: 0: success
//         -1: fail (invalid neighborhood type)
//         -10: fail (simulation is already running, cannot change neighborhood type)
int CellularAutomata::setup_neighborhood(int neighbor_type){
    if (run_flag == true) {
        return -10;   // Error: simulation is already running, cannot change neighborhood type
    }
    if (neighbor_type == 1 || neighbor_type == 2) {  // Von Neumann or Moore neighborhood
        neigh_type = neighbor_type;
        return 0;
    } else {
        return -1;   // Error: invalid neighborhood type
    }
}

// Function: setup_boundtype
// Set the boundary type of the cellular automata model
// Input: bound_type: boundary type (0: no boundaries, 1: periodic, 2: fixed, 3: cut-off)
//        radius: radius of the neighborhood
// Output: Updates the radius of the neighborhood and the boundary type
// Return: 0: success
//         -1: fail (invalid boundary type)
//         -10: fail (invalid radius)
int CellularAutomata::setup_boundtype(int b_type, int rad){
    if (run_flag == true) {
        return -10;   // Error: simulation is already running, cannot change boundary type
    }
    if (rad <= 0) {
        return -2;   // Error: invalid radius
    }
    if (b_type == 0 || b_type == 1 || b_type == 2 || b_type == 3) {  // No boundaries, periodic, fixed, or cut-off boundary
        bound_type = b_type;
        radius = rad;
        return 0;
    } else {
        return -1;   // Error: invalid boundary type
    }
}

// Function: setup_cell_states
// Set the number of cell states of the cellular automata model
// Input: nstates: number of states
// Output: Updates the number of states
// Return: 0: success
//         -1: fail (invalid number of states)
//         -10: fail (simulation is already running, cannot change number of states)
int CellularAutomata::setup_cell_states(int num_states){
    if (run_flag == true) {
        return -10;   // Error: simulation is already running, cannot change number of states
    }
    if (num_states <= 0) {
        return -1;   // Error: invalid number of states
    }
    nstates = num_states;
    return 0;
}

// Function: init_cond
// Set the initial configuration of the cellular automata model
// Input: x_state: the potential initial state of a cell
//        prob: probability of a cell entering state x_state
// Output: Updates the current grid
// Return: 0: success
//         -1: fail (invalid state)
//         -2: fail (invalid probability)
//         -5: fail (no grid is set up, call setup_dimension() first)
//         -10: fail (simulation is already running, cannot change initial condition)
int CellularAutomata::init_cond(int x_state, double prob){
    if (run_flag == true) {
        return -10;   // Error: simulation is already running, cannot change initial condition
    }
    if (current_grid.size() == 0) {
        return -5;   // Error: no grid is set up (call setup_dimension() first
    }
    if (x_state < 0 || x_state >= nstates) {
        return -1;   // Error: invalid state
    }
    if (prob < 0 || prob > 1) {
        return -2;   // Error: invalid probability
    }
    srand(time(NULL));   // force a different seed for each run
    for (int i = 0; i < current_grid.size(); i++) {
        for (int j = 0; j < current_grid[i].size(); j++) {
            if (((double) rand() / RAND_MAX) < prob) {    // generate random number between 0 and 1
                if (current_grid[i][j] == 0){
                    current_grid[i][j] = x_state;    // set the cell to state x_state
                }  
            }
        }
    }
    return 0;
}


// Function: init_cond_rewrite
// Rewrite an additional configuration of the cellular automata model given a state. 
// Input: x_state: the initial state of a cell to be rewritten
//        y_state: the potential new state of a cell
//        prob: probability of a cell entering the next state  
// Output: Updates the current grid
// Return: 0: success
//         -1: fail (invalid state)
//         -2: fail (invalid probability)
//         -5: fail (no grid is set up, call setup_dimension() first)
//         -10: fail (simulation is already running, cannot change initial condition)
int CellularAutomata::init_cond_rewrite(int x_state, int y_state, double prob){
    if (run_flag == true) {
        return -10;   // Error: simulation is already running, cannot change initial condition
    }
    if (current_grid.size() == 0) {
        return -5;   // Error: no grid is set up (call setup_dimension() first
    }
    if (x_state < 0 || x_state > nstates) {
        return -1;   // Error: invalid state
    }
    if (y_state < 0 || y_state > nstates) {
        return -1;   // Error: invalid state
    }
    if (prob < 0 || prob > 1) {
        return -2;   // Error: invalid probability
    }
    srand(time(NULL));   // force a different seed for each run 
    for (int i = 0; i < current_grid.size(); i++) {
        for (int j = 0; j < current_grid[i].size(); j++) {
            if (current_grid[i][j] == (x_state - 1)) {
                if (((double) rand() / RAND_MAX) < prob) {    // generate random number between 0 and 1
                    current_grid[i][j] = x_state;    // set the cell to state x_state
                }
            }
        }
    }
    return 0;
}

// Function: setup_rule
// Set the rule of the cellular automata model
// Input: rule_type: the rule to be used (1: majority rule, 2: proximaty rule)
// Output: Updates the rule
// Return: 0: success
//         -1: fail (invalid rule)
int CellularAutomata::setup_rule(int rule_type){
    if (run_flag == true) {
        return -10;   // Error: simulation is already running, cannot change rule
    }
    if (rule_type != 1 || rule_type != 2) {
        return -1;   // Error: invalid rule
    }
    rule = rule_type;
    return 0;
}