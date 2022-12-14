# Final Project: Cellular Automata Library
# University of California - Berkeley 

# Creators: Charis Liao, Jeffy Jeffy, Joshua Blomgren  
# Data: 12/12/2022 

# This makefile creates the object files that are the source code of the cellular automata model library. 
# These files are then moved to the ../../Libdir subdirectory

# The makefile is called by the main makefile in the main directory.

# GNU C++ Compiler
CPP         = g++      # C++ Compuler

# compiler flags -g debug, -o creates an executable file
CPPFLAGS    = -g -o   

# The directory where the include files needed to create the library objects are
INC_DIR = ../Include

# The directory where all object files are going to be moved afer creation
LIB_DIR     = ../Libdir

# The directory where all executable files are going to be moved afer creation
BIN_DIR     = ../Bindir

# The next line contains the list of executable files that are created by the Makefile
EXECUTABLES: sample_test


#The object file for insertion sort. The file is saved in Libdir.
sample_test: $(INC_DIR)/datatypes.h 
	$(CPP) $(CPPFLAGS) sample_test sample_test.cpp \
	-I$(INC_DIR) $(LIB_DIR)/ca_model_setup.o $(LIB_DIR)/ca_model_steps.o \
	$(LIB_DIR)/ca_model_vis.o
	mv sample_test $(BIN_DIR)

all: $(EXECUTABLES)

cleanall:
	cd $(BIN_DIR); rm $(EXECUTABLES)



