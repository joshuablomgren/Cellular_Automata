# Final Project: Cellular Automata Library
# University of California, Berkeley
# CHEM 274B: Introduction to Software Engineering
# December 2022
#
# Creators: Jeffy Jeffy, Charis Liao, Joshua Blomgren
# Directory Path: the_golden_gopher/ 

# This is the global Makefile for the project. It is used to compile the entire project.
# This makefile calls the makefiles in the subdirectories to build object files and
# executables for the project from the root directory.
# The makefile also cleans the project by removing all object files and executables.

# The object files are found in the Libdir directory
# The executables are found in the Execdir directory

CA_MODEL_DIR = Source
TST_DIR = Tests
EXM_DIR = Examples
UTILS_DIR = Utils
BIN_DIR = Bindir 

all: 
	cd $(UTILS_DIR); make all
	cd $(CA_MODEL_DIR); make all
	cd $(TST_DIR); make all
	cd $(EXM_DIR); make all
	cd $(BIN_DIR); make all

cleanall:
	cd $(UTILS_DIR); make cleanall
	cd $(CA_MODEL_DIR); make cleanall
	cd $(TST_DIR); make cleanall
	cd $(EXM_DIR); make cleanall
	cd $(BIN_DIR); make cleanall
	