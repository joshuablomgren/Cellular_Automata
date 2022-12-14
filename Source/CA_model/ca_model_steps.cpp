//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Fall 2022
    
//  This file contains the methods for the CellularAutomata class
//  relating to the update step of the model

//  datatypes.h  Contains the C++ Class definitions for the
//               Cellular Automata Model
#include "datatypes.h"

// Function: step
// Perform one step of the cellular automata model
// Input: None
// Output: Updates the current grid
// Return: 0: success
//         -1: fail (invalid neighborhood type)
//         -2: fail (invalid boundary type)
int CellularAutomata::step(){
    int state;
    int next_state = state++; // next state of the cell
    int neighbor_count;  // counting total neighbors 
    double majority; // majority of neighbors in a certain state
    int count; // counting neighbors in a certain state

    if (neigh_type == 1) {   // Von Neumann neighborhood
        
        if (bound_type == 0) {   // No boundaries: assumes space is infinite
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    
                    state = current_grid[i][j];
                    if (state == nstates) {
                        state = 0;
                    } else if (state != nstates) {
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            auto x = (i + k + current_grid.size()) % current_grid.size();
                            if (current_grid[x][j] == next_state) {
                                count++;
                            }
                            neighbor_count++;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            auto y = (j + k + current_grid.size()) % current_grid.size();
                            if (current_grid[i][y] == next_state) {
                                count++;
                            }
                            neighbor_count++;
                        }
                        majority = (double) count/neighbor_count;
                        if (rule == 1) {   // majority rule 
                            if (majority >= 0.5) { // majority of neighbors are in state 1
                                state++;
                            }
                        }
                    }
                    next_grid[i][j] = state;
                }
            }
            current_grid = next_grid;
        } else if (bound_type == 1) {   // periodic boundary: wrap around
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    
                    state = current_grid[i][j];
                    if (state == nstates) {
                        state = 0;
                    } else if (state != nstates) {
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            auto x = (i + k + current_grid.size()) % current_grid.size();
                            if (current_grid[x][j] == next_state) {
                                count++;
                            }
                            neighbor_count++;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            auto y = (j + k + current_grid.size()) % current_grid.size();
                            if (current_grid[i][y] == next_state) {
                                count++;
                            }
                            neighbor_count++;
                        }
                        majority = (double) count/neighbor_count;
                        if (rule == 1) {   // majority rule 
                            if (majority >= 0.5) { // majority of neighbors are in state 1
                                state++;
                            }
                        }
                    }
                    next_grid[i][j] = state;
                }
            }
            current_grid = next_grid;
        } else if (bound_type == 2) {   // fixed boundary
            for (int i = 1; i < current_grid.size(); i++) {
                for (int j = 1; j < current_grid[i].size(); j++) {
                    
                    state = current_grid[i][j];
                    if (state == nstates) {
                        state = 0;
                    } else if (state != nstates) {
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            if (i + k >= 0 && i + k < current_grid.size()) {
                                if (current_grid[i + k][j] == next_state) {
                                    count++;
                                }
                                neighbor_count++;
                            }
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            if (j + k >= 0 && j + k < current_grid[i].size()) {
                                if (current_grid[i][j + k] == next_state) {
                                    count++;
                                }
                                neighbor_count++;
                            }
                        }
                        majority = (double) count/neighbor_count;
                        if (rule == 1) {   // majority rule 
                            if (majority >= 0.5) { // majority of neighbors are in state 1
                                state++;
                            }
                        }
                    }
                    next_grid[i][j] = state;
                }
            }
            current_grid = next_grid;
        } else if (bound_type == 3) { // cut-off boundary
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    
                    state = current_grid[i][j];
                    if (state == nstates) {
                        state = 0;
                    } else if (state != nstates) {
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            if (i + k >= 0 && i + k <= current_grid.size()) {
                                if (current_grid[i + k][j] == next_state) {
                                    count++;
                                }
                                neighbor_count++;
                            }
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            if (j + k >= 0 && j + k <= current_grid[i].size()) {
                                if (current_grid[i][j + k] == next_state) {
                                    count++;
                                }
                                neighbor_count++;
                            }
                        }
                        majority = (double) count/neighbor_count;
                        if (rule == 1) {   // majority rule 
                            if (majority >= 0.5) { // majority of neighbors are in state 1
                                state++;
                            }
                        }
                    }
                    next_grid[i][j] = state;
                }
            }
            current_grid = next_grid;
        } else {
            return -2;   // Error: invalid boundary type
        }
    } else if (neigh_type == 2) {   // Moore neighborhood
        if (bound_type == 0) {   // No boundaries
             for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    int neighbor_count = 0;
                    int *state_count = new int[nstates];
                    for(int s = 0; s < nstates; s++) {
                        state_count[s] = 0;
                    }
                    for (int k = -radius; k <= radius; k++) {
                        for (int l = -radius; l <= radius; l++) {
                            state_count[current_grid[(i + k + current_grid.size()) % current_grid.size()][(j + l + current_grid[i].size()) % current_grid[i].size()]]++;
                            neighbor_count++;
                        }
                    }
                    if (rule == 1) {   // majority rule
                        majority = (double) state_count[1]/neighbor_count;
                        if (majority >= 0.5) { // majority of neighbors are in state 1
                            next_grid[i][j] = 1;
                        }
                    }
                    delete [] state_count;
                }
            }
            // older version
            // for (int i = 0; i < current_grid.size(); i++) {
            //     for (int j = 0; j < current_grid[i].size(); j++) {
            //         state = current_grid[i][j];
            //         if (state == nstates) {
            //             state = 0;
            //         } else if (state != nstates) {
            //             for (int k = -radius; k <= radius; k++) {
            //                 for (int l = -radius; l <= radius; l++) {
            //                     if (current_grid[(i + k + current_grid.size()) % current_grid.size()][(j + l + current_grid[i].size()) % current_grid[i].size()] == next_state) {
            //                         count++;
            //                     }
            //                     neighbor_count++;  
            //                 }
            //             }
            //             majority = (double) count/neighbor_count;
            //                 if (rule == 1) {   // majority rule 
            //                     if (majority >= 0.5) { // majority of neighbors are in state 1
            //                         state++;
            //                     }
            //                 }
            //         }
            //         next_grid[i][j] = state;
            //     }
            // }
            // current_grid = next_grid;
        } else if (bound_type == 1) {   // periodic boundary
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    state = current_grid[i][j];
                    if (state == nstates) {
                        state = 0;
                    } else if (state != nstates) {
                        for (int k = -radius; k <= radius; k++) {
                            for (int l = -radius; l <= radius; l++) {
                                if (current_grid[(i + k + current_grid.size()) % current_grid.size()][(j + l + current_grid[i].size()) % current_grid[i].size()] == next_state) {
                                    count++;
                                }
                                neighbor_count++;  
                            }
                        }
                        majority = (double) count/neighbor_count;
                            if (rule == 1) {   // majority rule 
                                if (majority >= 0.5) { // majority of neighbors are in state 1
                                    state++;
                                }
                            }
                    }
                    next_grid[i][j] = state;
                }
            }
            current_grid = next_grid;
        } else if (bound_type == 2) {   // fixed boundary
            for (int i = 1; i < current_grid.size(); i++) {
                for (int j = 1; j < current_grid[i].size(); j++) {
                    state = current_grid[i][j];
                    if (state == nstates) {
                        state = 0;
                    } else if (state != nstates) {
            
                        for (int k = -radius; k <= radius; k++) {
                            for (int l = -radius; l <= radius; l++) {
                                if (i + k >= 0 && i + k < current_grid.size() && j + l >= 0 && j + l < current_grid[i].size()) {
                                    if (current_grid[i + k][j + l] == next_state) {
                                        count++;
                                    }
                                    neighbor_count++;
                                }
                            }
                        }
                        majority = (double) count/neighbor_count;
                            if (rule == 1) {   // majority rule 
                                if (majority >= 0.5) { // majority of neighbors are in state 1
                                    state++;
                                }
                            }
                    }
                    next_grid[i][j] = state;
                }
            }
            current_grid = next_grid;
        } else if (bound_type == 3) { //cut-off boundary 
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    state = current_grid[i][j];
                    if (state == nstates) {
                        state = 0;
                    } else if (state != nstates) {
            
                        for (int k = -radius; k <= radius; k++) {
                            for (int l = -radius; l <= radius; l++) {
                                if (i + k >= 0 && i + k <= current_grid.size() && j + l >= 0 && j + l <= current_grid[i].size()) {
                                    if (current_grid[i + k][j + l] == next_state) {
                                        count++;
                                    }
                                    neighbor_count++;
                                }
                            }
                        }
                        majority = (double) count/neighbor_count;
                            if (rule == 1) {   // majority rule 
                                if (majority >= 0.5) { // majority of neighbors are in state 1
                                    state++;
                                }
                            }
                    }
                    next_grid[i][j] = state;
                }
            }
            current_grid = next_grid;
        } else {
            return -2;   // Error: invalid boundary type
        }
    } else {
        return -1;   // Error: invalid neighborhood type
    }
    if (run_flag == false){  // if the simulation has not been run, set run_flag to true
        run_flag = true;
    }
    return 0;
}
