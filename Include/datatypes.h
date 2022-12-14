//
//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Fall 2022
//
//  datatypes.h contains the necessary include files and 
//              data types declarations.
//
#pragma once    // Ensures that this file is only included once
                // during compilation

#include <vector>       // use the STL vector class for the grids
#include <ctime>        // this program calls time() to initialize
                        // the seed of the C++/C random number generator
#include <string>       // use the STL string class for filenames
#include <fstream>     // use the STL file class for output files
#include <iostream>    // use the STL input/output class for printing

using namespace std;

// Cellular Automata Class
class CellularAutomata
{
    private:
        int neigh_type;  // Neighborhood type
        int bound_type;  // Boundary type
        int radius;      // Radius of the neighborhood
        int nstates;     // Number of states
        int rule;        // Rule
        int dim1, dim2;  // Dimensions of the grid
        bool run_flag;   // Flag to indicate if the simulation is running

        vector<vector<int>> current_grid;  // Current grid
        vector<vector<int>> next_grid;     // Next grid

    public:
        CellularAutomata();                                   // Constructor
        ~CellularAutomata();                                  // Destructor
        int setup_dimension(int ndims, int dim1, int dim2);   // Set the dimensions of the cellular automata model
        int setup_neighborhood(int neighbor_type);            // Set the neighborhood of the cellular automata model
        int setup_boundtype(int bound_type, int radius);      // Set the boundary type of the cellular automata model
        int setup_cell_states(int nstates);                   // Set the number of states of the cellular automata model
        int init_cond(int x_state, double prob);              // Set the initial condition of the cellular automata model
        int init_cond_rewrite(int x_state, int y_state, double prob);      // rewrite for other cell states (not just empty)
        int setup_rule(int rule_type);                        // Set the rule of the cellular automata model
        int step();                                           // Step the cellular automata model
        int run_sim(int steps, bool print, bool file, string filename);  // Run the cellular automata model
        int print_grid();                                     // Print the current grid
        int print_grid(string filename, int step);                        // Print the current grid to a file
        int analyze_grid(int *arr);                             // Analyze the current grid
};