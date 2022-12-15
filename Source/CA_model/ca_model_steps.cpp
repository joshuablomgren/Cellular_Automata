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
    int *state_count = new int[nstates];     // counting neighbors in each state
    int neighbor_count = 0;  // counting total neighbors 
    double majority; // majority of neighbors in a certain state
    int count; // counting neighbors in a certain state
    next_grid = current_grid;   // initialize next_grid to current_grid

    if (neigh_type == 1) {   // Von Neumann neighborhood
        
        if (bound_type == 0) {   // No boundaries: assumes space is infinite
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {

                    if (rule == 1) {    //majority rule 
                        for(int s = 0; s < nstates; s++) {  // initialize state_count
                        state_count[s] = 0;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            auto x = (i + k + current_grid.size()) % current_grid.size();
                            state_count[current_grid[x][j]]++;
                            neighbor_count++;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            auto y = (j + k + current_grid.size()) % current_grid.size();
                            state_count[current_grid[i][y]]++;
                            neighbor_count++;
                        }
                        int max_idx;
                        int max_count = 0;
                        for (int s = 0; s < nstates; s++) {
                            if (state_count[s] > max_count) {
                                max_count = state_count[s];
                                max_idx = s;
                            }
                        }
                        majority = (double) max_count/neighbor_count;
                        if (majority >= 0.5) { 
                            next_grid[i][j] = max_idx;
                        }
                    }
                    delete [] state_count;
                }
            }
            current_grid = next_grid;
            next_grid = current_grid;

        } else if (bound_type == 1) {   // periodic boundary: wrap around
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    
                    if (rule == 1) {    //majority rule 
                        for(int s = 0; s < nstates; s++) {  // initialize state_count
                        state_count[s] = 0;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            auto x = (i + k + current_grid.size()) % current_grid.size();
                            state_count[current_grid[x][j]]++;
                            neighbor_count++;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            auto y = (j + k + current_grid.size()) % current_grid.size();
                            state_count[current_grid[i][y]]++;
                            neighbor_count++;
                        }
                        int max_idx;
                        int max_count = 0;
                        for (int s = 0; s < nstates; s++) {
                            if (state_count[s] > max_count) {
                                max_count = state_count[s];
                                max_idx = s;
                            }
                        }
                        majority = (double) max_count/neighbor_count;
                        if (majority >= 0.5) { 
                            next_grid[i][j] = max_idx;
                        }
                    }
                    delete [] state_count;
                }
            }
            current_grid = next_grid;
            next_grid = current_grid;
        } else if (bound_type == 2) {   // fixed boundary
            for (int i = 1; i < current_grid.size(); i++) {
                for (int j = 1; j < current_grid[i].size(); j++) {
                    
                    if (rule == 1) {    //majority rule 
                        for(int s = 0; s < nstates; s++) {  // initialize state_count
                        state_count[s] = 0;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            if (i + k > 0 && i + k < current_grid.size());
                            state_count[current_grid[i+k][j]]++;
                            neighbor_count++;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            if (j + k > 0 && j + k < current_grid.size())
                            state_count[current_grid[i][j+k]]++;
                            neighbor_count++;
                        }
                        int max_idx;
                        int max_count = 0;
                        for (int s = 0; s < nstates; s++) {
                            if (state_count[s] > max_count) {
                                max_count = state_count[s];
                                max_idx = s;
                            }
                        }
                        majority = (double) max_count/neighbor_count;
                        if (majority >= 0.5) { 
                            next_grid[i][j] = max_idx;
                        }
                    }
                    delete [] state_count;
                }
            }
            current_grid = next_grid;
            next_grid = current_grid;
        } else if (bound_type == 3) { // cut-off boundary
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                    
                    if (rule == 1) {    //majority rule 
                        for(int s = 0; s < nstates; s++) {  // initialize state_count
                        state_count[s] = 0;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            if (i + k >= 0 && i + k <= current_grid.size());
                            state_count[current_grid[i+k][j]]++;
                            neighbor_count++;
                        }
                        for (int k = - radius; k<=radius;k++){
                            if (k == 0) {
                                continue;
                            }
                            if (j + k >= 0 && j + k <= current_grid.size())
                            state_count[current_grid[i][j+k]]++;
                            neighbor_count++;
                        }
                        int max_idx;
                        int max_count = 0;
                        for (int s = 0; s < nstates; s++) {
                            if (state_count[s] > max_count) {
                                max_count = state_count[s];
                                max_idx = s;
                            }
                        }
                        majority = (double) max_count/neighbor_count;
                        if (majority >= 0.5) { 
                            next_grid[i][j] = max_idx;
                        }
                    }
                    delete [] state_count;
                }
            }
            current_grid = next_grid;
            next_grid = current_grid;
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
                        int max_idx;
                        int max_count = 0;
                        for (int s = 0; s < nstates; s++) {
                            if (state_count[s] > max_count) {
                                max_count = state_count[s];
                                max_idx = s;
                            }
                        }
                        majority = (double) max_count/neighbor_count;
                        if (majority >= 0.5) { 
                            next_grid[i][j] = max_idx;
                        }
                    }
                    delete [] state_count;
                }
            }
            current_grid = next_grid;
            next_grid = current_grid; 
        } else if (bound_type == 1) {   // periodic boundary
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
                        int max_idx;
                        int max_count = 0;
                        for (int s = 0; s < nstates; s++) {
                            if (state_count[s] > max_count) {
                                max_count = state_count[s];
                                max_idx = s;
                            }
                        }
                        majority = (double) max_count/neighbor_count;
                        if (majority >= 0.5) { 
                            next_grid[i][j] = max_idx;
                        }
                    }
                    delete [] state_count;
                }
            }
            current_grid = next_grid;
            next_grid = current_grid;
        } else if (bound_type == 2) {   // fixed boundary
            for (int i = 1; i < current_grid.size(); i++) {
                for (int j = 1; j < current_grid[i].size(); j++) {
                  int neighbor_count = 0;
                  int *state_count = new int[nstates];
                  for(int s = 0; s < nstates; s++) {
                    state_count[s] = 0;
                  }
                    for (int k = -radius; k <= radius; k++) {
                        for (int l = -radius; l <= radius; l++) {
                            if (i + k >= 1 && i + k < current_grid.size() && j + l >= 1 && j + l < current_grid[i].size()) {
                                state_count[current_grid[i + k][j + l]]++;
                                neighbor_count++;
                            }
                        }
                    }
                    if (rule == 1) {   // majority rule
                        int max_idx;
                        int max_count = 0;
                        for (int s = 0; s < nstates; s++) {
                            if (state_count[s] > max_count) {
                                max_count = state_count[s];
                                max_idx = s;
                            }
                        }
                        majority = (double) max_count/neighbor_count;
                        if (majority >= 0.5) { 
                            next_grid[i][j] = max_idx;
                        }
                    }
                    delete [] state_count;
                }
            }
            current_grid = next_grid;
            next_grid = current_grid; 
        } else if (bound_type == 3) { //cut-off boundary 
            for (int i = 0; i < current_grid.size(); i++) {
                for (int j = 0; j < current_grid[i].size(); j++) {
                  int neighbor_count = 0;
                  int *state_count = new int[nstates];
                  for(int s = 0; s < nstates; s++) {
                    state_count[s] = 0;
                  }
                    for (int k = -radius; k <= radius; k++) {
                        for (int l = -radius; l <= radius; l++) {
                            if (i + k >= 0 && i + k <= current_grid.size() && j + l >= 0 && j + l <= current_grid[i].size()) {
                                state_count[current_grid[i + k][j + l]]++;
                                neighbor_count++;
                            }
                        }
                    }
                    if (rule == 1) {   // majority rule
                        int max_idx;
                        int max_count = 0;
                        for (int s = 0; s < nstates; s++) {
                            if (state_count[s] > max_count) {
                                max_count = state_count[s];
                                max_idx = s;
                            }
                        }
                        majority = (double) max_count/neighbor_count;
                        if (majority >= 0.5) { 
                            next_grid[i][j] = max_idx;
                        }
                    }
                    delete [] state_count;
                }
            }
            current_grid = next_grid;
            next_grid = current_grid; 
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
