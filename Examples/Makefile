# Final Project: Cellular Automata Library
# University of California - Berkeley 

# Creators: Joshua Blomgren, Jeffy Jeffy, Charis Liao
# Data: 12/12/2022 

# This makefile creates the test executable files that test the functionalities 
# of the cellular automata model.

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
EXECUTABLES = battery_model

#The object file for battery_model. The file is saved in Libdir.

battery_model: $(INC_DIR)/datatypes.h $(INC_DIR)/random.h
	$(CPP) $(CPPFLAGS) battery_model battery_model.cpp \
	-I$(INC_DIR) $(LIB_DIR)/libca_model.a \
	$(LIB_DIR)/randseed.o
	mv battery_model $(BIN_DIR)

all: $(EXECUTABLES)

cleanall:
	cd $(BIN_DIR); rm $(EXECUTABLES)



