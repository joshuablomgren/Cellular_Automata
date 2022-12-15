#include <iostream> 
#include <vector>       // use the STL vector class for the grids
#include <ctime>        // this program calls time() to initialize
                        // the seed of the C++/C random number generator

#include <string>       // use the STL string class for filenames
#include "datatypes.h"

using namespace std;

int main() {
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

    err = CA.setup_cell_states(3);                 // 2 states
    if(err == -1){
        cout << "Error: Invalid number of states" << endl;
        return -1;
    }

    err = CA.setup_rule(1);                        // majority rule
    if(err == -1){
        cout << "Error: Invalid rule" << endl;
        return -1;
    }

    err = CA.init_cond(1, 0.9);                    // random initial condition, 50% chance of being 1 from 0
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
    err = CA.init_cond_rewrite(1, 2, 0.6);         // rewrite the initial condition grid, 40% chance of being 2 from 1
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
    
    // CA.run_sim(10, true, true, "test.txt");
    CA.print_grid();
    // CA.step();
    // cout << "step1" << endl;
    // CA.print_grid();
    CA.run_sim(5, true, true, "test.txt");

    return 0;
    
}