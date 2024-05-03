# Final Project: Cellular Automata Library
## University of California, Berkeley
## Chem 274B: Introduction to Software Engineering
#
## Creator: Charis Liao, Joshua Blomgren, Jeffy Jeffy
## Date Created: December 2022
## Directory Path: the-golden-gopher/
#

## Directory Structure

This is the main directory which contains the source code for the cellular automata library. The library is written in C++ and is designed to be used in conjunction with jupyter notebook locating in the Utils/Plots/ directory. There is an example model that uses the cellular automata library in the Examples/ directory. 

The directory structure is as follows:
Root Directory contents:

    - README.md: This file which contains a general description of the project and the directory structure

    - Makefile: Global automation script for compiling the library and examples, and cleaning all the subdirectories


Subdirectories: 

    - Bindir/ : This directory contains all the compiled executable programs

    - Libdir/ : This directory contains all the compiled object files (.o files) 

    - Include/ : This directory contains all the header files (.h files) for the library

    - Source/ : This directory contains all the source code for the cellular automata library 
                implemented in C++
    
    - Examples/ : This directory contains the example model that uses the cellular automata library

    - Utils/ : This directory contains the plotting tools for visualizing the results of the CA models

    - Tests/ : This directory contains the unit tests used to test the functionalities of the library 

## Instructions for Compiling and Running the Library

To compile the library as well as tests and an example model, run the following command in the root directory:
```
make all
```

The executable files will be located in the Bindir/ subdirectory. To run the example model, run the following command in the Bindir directory:
```
./example
```

To clean the directory, run the following command in the root directory:
```
make cleanall
```

### Instructions:
- To use the library in your own model, utilize the instructions provided in the Examples/README.md file. 

## Updates:
- 12/1/2022: Initial commit of the project
- 12/6/2022: Added the CellularAutomata class in the Include/datatypes.h 
- 12/7/2022: Added the setup methods for CellularAutomata in the Source/CA_model/
- 12/8/2022: Added the step methods for CellularAutomata in the Source/CA_model/
- 12/9/2022: Added the visualization methods for CellularAutomata in the Source/CA_model/
- 12/12/2022: Added the jupyter notebook for visualizing the results of the CA model in the Utils/Plots/
- 12/13/2022: Separated the setup, step, and visualization methods into separate files in the Source/CA_model/
- 12/14/2022: Added the unit tests for the CellularAutomata class in the Tests/ directory
- 12/15/2022: Added the example model that uses the CA library in the Examples/ directory
- 12/16/2022: Added the Makefile for compiling the library and example model
