# Final Project 
# University of California - Berkeley 

# Creators: Charis Liao, Jeffy Jeffy, Joshua Blomgren  
# Data: 12/14/2022 

# This makefile creates the object file containing the random number generator function.
# These files are then moved to the ../../Libdir subdirectory

# The makefile is called by the main makefile in the main directory.

# GNU C++ Compiler
CPP         = g++      # C++ Compuler

# compiler flags -g debug, -c creates a library object
CPPFLAGS    = -g -c    

# The directory where the include files needed to create the library objects are
INC_DIR = ../../Include

# The directory where all object files are going to moved afer creation
LIB_DIR     = ../../Libdir

# The next line contains the random number generating object file created by this Makefile.
RANDOM_GEN = randseed.o

randseed.o: $(INC_DIR)/random.h
	$(CPP) $(CPPFLAGS) randseed.cpp -I$(INC_DIR) 
	mv randseed.o $(LIB_DIR)

all: $(RANDOM_GEN)

cleanall: 
	cd $(LIB_DIR); rm $(RANDOM_GEN)