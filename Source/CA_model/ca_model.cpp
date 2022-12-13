//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Fall 2022
    
//  This file contains the methods for the CellularAutomata class

//  datatypes.h  Contains the C++ Class definitions for the
//               Cellular Automata Model
#include "datatypes.h"
#include <fstream>     // use the STL file class for output files
#include <iostream>    // use the STL input/output class for printing

// Function: setup_dimension
// Setup the dimensions of the cellular automata model
// Input: ndims: number of dimensions (1 or 2)
//        dim1: dimension 1
//        dim2: dimension 2
// Output: Sets up a 1D or 2D grid
// Return: 0: success
//         -1: fail
int CellularAutomata::setup_dimension(int ndims, int dim1, int dim2){
    if (ndims == 1) {
        vector<int> grid1D(dim1);       // 1D cellular automata (size dim1)
        current_grid.push_back(grid1D); 
        next_grid.push_back(grid1D);
        return 0;
    } else if (ndims == 2) {
        vector<vector<int>> grid2D(dim1, vector<int>(dim2));   // 2D cellular automata (size dim1 x dim2)
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
//         -1: fail
int CellularAutomata::setup_neighborhood(int neighbor_type){
    if (neigh_type == 1 || neigh_type == 2) {  // Von Neumann or Moore neighborhood
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
//         -2: fail (invalid radius)
int CellularAutomata::setup_boundtype(int bound_type, int radius){
    if (radius <= 0) {
        return -2;   // Error: invalid radius
    }
    if (bound_type == 0 || bound_type == 1 || bound_type == 2 || bound_type == 3) {  // No boundaries, periodic, fixed, or cut-off boundary
        bound_type = bound_type;
        radius = radius;
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
int CellularAutomata::setup_cell_states(int num_states){
    if (nstates <= 0) {
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
int CellularAutomata::init_cond(int x_state, double prob){
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
// Set the initial configuration of the cellular automata model
// Input: x_state: the potential initial state of a cell 
//        prob: probability of a cell entering state x_state 
// Output: Updates the current grid
// Return: 0: success
//         -1: fail (invalid state)
//         -2: fail (invalid probability)
int CellularAutomata::init_cond_rewrite(int x_state, double prob){
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
                current_grid[i][j] = x_state;    // set the cell to state x_state
            }
        }
    }
    return 0;
}

// Function: setup_rule
// Set the rule of the cellular automata model
// Input: rule_type: the rule to be used (1: majority rule)
// Output: Updates the rule
// Return: 0: success
//         -1: fail (invalid rule)
int CellularAutomata::setup_rule(int rule_type){
    if (rule_type != 1) {
        return -1;   // Error: invalid rule
    }
    rule = rule_type;
    return 0;
}

// Function: step
// Perform one step of the cellular automata model
// Input: None
// Output: Updates the current grid
// Return: 0: success
//         -1: fail (invalid neighborhood type)
//         -2: fail (invalid boundary type)

int CellularAutomata::step(){
    if (neigh_type == 1) {   // Von Neumann neighborhood
        if (bound_type == 0) {   // No boundaries: assumes space is infinite
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    int sum = 0;
                    for (int k = -radius; k <= radius; k++) {
                        for (int l = -radius; l <= radius; l++) {
                            if (k != 0 || l != 0) {
                                sum += current_grid[(i + k + current_grid.size()) % current_grid.size()][(j + l + current_grid[i].size()) % current_grid[i].size()];
                            }
                        }
                    }
                    if (rule == 1) {   // majority rule
                        if (sum >= (2 * radius + 1) * (2 * radius + 1) / 2) {
                            next_grid[i][j] = 1;
                        } else {
                            next_grid[i][j] = 0;
                        }
                    }
                }
            }
        } else if (bound_type == 1) {   // periodic boundary: wrap around
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    int sum = 0;
                    for (int k = -radius; k <= radius; k++) {
                        for (int l = -radius; l <= radius; l++) {
                            if (k != 0 || l != 0) {
                                sum += current_grid[(i + k + current_grid.size()) % current_grid.size()][(j + l + current_grid[i].size()) % current_grid[i].size()];
                            }
                        }
                    }
                    if (rule == 1) {   // majority rule
                        if (sum >= (2 * radius + 1) * (2 * radius + 1) / 2) {
                            next_grid[i][j] = 1;
                        } else {
                            next_grid[i][j] = 0;
                        }
                    }
                }
            }
        } else if (bound_type == 2) {   // fixed boundary
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    int sum = 0;
                    for (int k = -radius; k <= radius; k++) {
                        for (int l = -radius; l <= radius; l++) {
                            if (k != 0 || l != 0) {
                                if (i + k >= 0 && i + k < current_grid.size() && j + l >= 0 && j + l < current_grid[i].size()) {
                                    sum += current_grid[i + k][j + l];
                                }
                            }
                        }
                    }
                    if (rule == 1) {   // majority rule
                        if (sum >= (2 * radius + 1) * (2 * radius + 1) / 2) {
                            next_grid[i][j] = 1;
                        } else {
                            next_grid[i][j] = 0;
                        }
                    }
                }
            }
        } else {
            return -2;   // Error: invalid boundary type
        }
    } else if (neigh_type == 2) {   // Moore neighborhood
        if (bound_type == 0) {   // No boundaries
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    int sum = 0;
                    for (int k = -radius; k <= radius; k++) {
                        for (int l = -radius; l <= radius; l++) {
                            sum += current_grid[(i + k + current_grid.size()) % current_grid.size()][(j + l + current_grid[i].size()) % current_grid[i].size()];
                        }
                    }
                    if (rule == 1) {   // majority rule
                        if (sum >= (2 * radius + 1) * (2 * radius + 1) / 2) {
                            next_grid[i][j] = 1;
                        } else {
                            next_grid[i][j] = 0;
                        }
                    }
                }
            }
        } else if (bound_type == 1) {   // periodic boundary
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    int sum = 0;
                    for (int k = -radius; k <= radius; k++) {
                        for (int l = -radius; l <= radius; l++) {
                            sum += current_grid[(i + k + current_grid.size()) % current_grid.size()][(j + l + current_grid[i].size()) % current_grid[i].size()];
                        }
                    }
                    if (rule == 1) {   // majority rule
                        if (sum >= (2 * radius + 1) * (2 * radius + 1) / 2) {
                            next_grid[i][j] = 1;
                        } else {
                            next_grid[i][j] = 0;
                        }
                    }
                }
            }
        } else if (bound_type == 2) {   // fixed boundary
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    int sum = 0;
                    for (int k = -radius; k <= radius; k++) {
                        for (int l = -radius; l <= radius; l++) {
                            if (i + k >= 0 && i + k < current_grid.size() && j + l >= 0 && j + l < current_grid[i].size()) {
                                sum += current_grid[i + k][j + l];
                            }
                        }
                    }
                    if (rule == 1) {   // majority rule
                        if (sum >= (2 * radius + 1) * (2 * radius + 1) / 2) {
                            next_grid[i][j] = 1;
                        } else {
                            next_grid[i][j] = 0;
                        }
                    }
                }
            }
        } else {
            return -2;   // Error: invalid boundary type
        }
    } else {
        return -1;   // Error: invalid neighborhood type
    }
    return 0;
}

//Function: Analyze the grid
// Input: none
// Output: 0 (success)
//         -1 (fail)
// Return: sum of all the states in the grid
int CellularAutomata::analyze_grid(int *arr){
    if(arr == NULL){
        return -1;
    }
    for(int i = 0; i < current_grid.size(); i++){
        for(int j = 0; j < current_grid[i].size(); j++){
            arr[current_grid[i][j]]++;
        }
    }
    return 0; 
}

// Function: Print the grid to the screen
// Input: none
// Output: none
// Return: 0 (success)
int CellularAutomata::print_grid() {
    for (int i = 0; i < current_grid.size(); i++) {
        for (int j = 0; j < current_grid[i].size(); j++) {
            cout << current_grid[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

// Function: Print the grid to a file
// Input: string filename
// Output: none
// Return: 0 (success)
//         -1 (fail)
int CellularAutomata::print_grid(string filename, int step) {
    ofstream outfile;
    outfile.open(filename.c_str(), std::ios::app);
    if (outfile.is_open()) {
        outfile << "Step: " << i << endl;
        for (int i = 0; i < current_grid.size(); i++) {
            for (int j = 0; j < current_grid[i].size(); j++) {
                outfile << current_grid[i][j] << " ";
            }
            outfile << endl;
        }
        int arr* = new int[nstates] 
        analyze_grid(arr);
        for (int i = 0; i < nstates; i++){
            outfile << "State " << i << " has " << arr[i] << " cells" << endl;
        }
        delete[] arr;
        outfile.close();
        return 0;
    } else {
        cout << "Error: unable to open file" << endl;
        return -1;
    }
}
                    
// Function: Run the simulation
// Perform the simulation for a given number of steps
// Input: int number of steps
//        bool whether to print the grid to the screen
//        bool whether to print the grid to a file
//        string filename
// Output: none
// Return: 0: success
//         -1: fail (invalid number of steps)
//         -2: fail (invalid boundary type)
//         -3: fail (invalid neighborhood type)
//         -4: fail (invalid filename)
int CellularAutomata::run_sim(int steps, bool print_screen, bool print_file, string filename) {
    int err;   // error code    

    if (steps <= 0) {
        cout << "Error: invalid number of steps" << endl;
        return (-1);   // Error: invalid number of steps
    }

    if(print_file == true && filename == "none") {
        cout << "Error: invalid filename" << endl;
        return (-4);   // Error: invalid filename
    }

    //printing the header to the screen if print_screen is true
    if (print_screen == true) {
        cout << "Cellular Automata Specifications: " << endl;
        cout << "Grid size: " << current_grid.size() << " x " << current_grid[0].size() << endl;
        cout << "Number of states: " << nstates << endl;
        cout << "Neighborhood type: " << neigh_type << endl;
        cout << "Boundary type: " << bound_type << endl;
        cout << "Rule: " << rule << endl;
        cout << "Radius: " << radius << endl;
        cout << "Number of steps: " << steps << endl;
        cout << endl;
    }

    //printing the header to the file if print_file is true
    if (print_file == true) {
        ofstream outfile;
        outfile.open(filename.c_str());
        if (outfile.is_open()) {
            outfile << "Cellular Automata Specifications: " << endl;
            outfile << "Grid size: " << current_grid.size() << " x " << current_grid[0].size() << endl;
            outfile << "Number of states: " << nstates << endl;
            outfile << "Neighborhood type: " << neigh_type << endl;
            outfile << "Boundary type: " << bound_type << endl;
            outfile << "Rule: " << rule << endl;
            outfile << "Radius: " << radius << endl;
            outfile << "Number of steps: " << steps << endl;
            outfile << endl;
            outfile.close();
        } else {
            cout << "Error: unable to open file" << endl;
            return (-4);   // Error: unable to open file
        }
    }

    for (int i = 0; i < steps; i++) {
        err = step(); 
        if (err == -1) {
            cout << "Error: invalid neighborhood type" << endl;
            return (-3);   // Error: invalid neighborhood type
        } else if (err == -2) {
            cout << "Error: invalid boundary type" << endl;
            return (-2);   // Error: invalid boundary type
        }
        else if (err == 0){
            cout << "Step " << i << " complete" << endl;
            if (print_screen == true) {
                print_grid();
                int arr* = new int[nstates] 
                analyze_grid(arr);
                for (int i = 0; i < nstates; i++){
                    cout << "State " << i << " has " << arr[i] << " cells" << endl;
                }
                delete[] arr;
            }
            if (print_file == true) {
                print_grid(filename);
            }
        }
    }

    return 0;
}
