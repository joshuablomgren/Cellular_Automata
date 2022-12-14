//  UC Berkeley - MSSE Program
//  Chem 274B  Introduction to Software Engineering
//  Fall 2022
    
//  This file contains the methods for the CellularAutomata class
//  relating to the visualization of the model

//  datatypes.h  Contains the C++ Class definitions for the
//               Cellular Automata Model
#include "datatypes.h"

//Function: Analyze the grid
// Input: none
// Output: 0 (success)
//         -1 (fail)
// Return: sum of all the states in the grid
int CellularAutomata::analyze_grid(int *arr){
    if(arr == NULL){
        return -1;
    }
    for (int i = 0; i < nstates; i++){
        arr[i] = 0;
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
        outfile << "Step: " << step << endl;
        for (int i = 0; i < current_grid.size(); i++) {
            for (int j = 0; j < current_grid[i].size(); j++) {
                outfile << current_grid[i][j] << " ";
            }
            outfile << endl;
        }
        int *arr = new int[nstates];
        analyze_grid(arr);
        for (int i = 0; i < nstates; i++){
            outfile << "State " << i << " has " << arr[i] << " cells" << endl;
        }
        outfile <<" " << endl;
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
            if (print_screen == true) {
                cout << "Step: " << i << endl;
                print_grid();
                int *arr = new int[nstates]; 
                analyze_grid(arr);
                for (int i = 0; i < nstates; i++){
                    cout << "State " << i << " has " << arr[i] << " cells" << endl;
                }
                cout <<" " << endl;
                delete[] arr;
            }
            if (print_file == true) {
                print_grid(filename, i);
            }
        }
    }
    return 0;
}