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
EXECUTABLES = input_values_test init_cond_test sample_test

#The object file for insertion sort. The file is saved in Libdir.

input_values_test: $(INC_DIR)/datatypes.h $(INC_DIR)/random.h
	$(CPP) $(CPPFLAGS) input_values_test input_values_test.cpp \
	-I$(INC_DIR) $(LIB_DIR)/libca_model.a \
	$(LIB_DIR)/randseed.o
	mv input_values_test $(BIN_DIR)

init_cond_test: $(INC_DIR)/datatypes.h $(INC_DIR)/random.h
	$(CPP) $(CPPFLAGS) init_cond_test init_cond_test.cpp \
	-I$(INC_DIR) $(LIB_DIR)/libca_model.a \
	$(LIB_DIR)/randseed.o
	mv init_cond_test $(BIN_DIR)

sample_test: $(INC_DIR)/datatypes.h $(INC_DIR)/random.h
	$(CPP) $(CPPFLAGS) sample_test sample_test.cpp \
	-I$(INC_DIR) $(LIB_DIR)/libca_model.a \
	$(LIB_DIR)/randseed.o
	mv sample_test $(BIN_DIR)

all: $(EXECUTABLES)

cleanall:
	cd $(BIN_DIR); rm $(EXECUTABLES)



