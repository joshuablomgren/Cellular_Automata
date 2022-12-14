#include <iostream> 
#include <vector>       // use the STL vector class for the grids
#include <ctime>        // this program calls time() to initialize
                        // the seed of the C++/C random number generator

#include <string>       // use the STL string class for filenames
#include "datatypes.h"

using namespace std;

int main() {
    CellularAutomata CA;
    CA.setup_dimension(2, 10, 10);
    CA.setup_neighborhood(2);
    CA.setup_boundtype(0, 1);
    CA.setup_cell_states(2);
    CA.init_cond(1, 0.5);
    CA.init_cond_rewrite(2, 0.6);
    CA.setup_rule(1);
    CA.run_sim(10, true, false, "none");
    return 0;
    
}