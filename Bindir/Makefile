# Final Assignment 
# University of California - Berkeley 

# Creator: Jeffy Jeffy, Joshua Blomgren, Charis Liao
# Data: 12/16/2022

# This makefile runs the executables generated from the test files as well as the sample test 

# GNU C++ Compiler
CPP         = g++      # C++ Compuler

# compiler flags -g debug, -c creates a library object
CPPFLAGS    = -g -c    

# The next line contains the list of executables run by this Makefile.
EXECUTABLES = battery_model sample_test \
			  init_cond_test input_values_test 

UTILS_DIR = ../Utils/Plots/Data

# The next line will run the battery_model executable
battery_model: battery_model 
	./battery_model
	mv battery_model.txt $(UTILS_DIR)

# The next line will run the sample_test executable
sample_test: sample_test 
	./sample_test
	mv test.txt $(UTILS_DIR)

# The next line will run the init_cond_test executable
init_cond_test: init_cond_test 
	./init_cond_test

# The next line will run the input_values_test executable
input_values_test: input_values_test 
	./input_values_test

# The next line will run all the executables
all: $(EXECUTABLES)

# The next line will remove all the executables 
cleanall:
	rm -f $(EXECUTABLES_NAMES)