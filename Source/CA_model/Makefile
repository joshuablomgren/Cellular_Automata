# Final Project 
# University of California - Berkeley 

# Creators: Charis Liao, Jeffy Jeffy, Joshua Blomgren  
# Data: 12/12/2022 

# This makefile creates the object files that are the source code of the cellular automata model. 
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

# The next line contains the list of object files created by this Makefile.
CA_MODEL_OBJS = ca_model_setup.o ca_model_steps.o ca_model_vis.o

CA_MODEL_LIB = libca_model.a

libca_model.a: $(CA_MODEL_OBJS)
# create a library file from the object files
	ar ru $(CA_MODEL_LIB) $(CA_MODEL_OBJS)
# check the library
	ranlib $(CA_MODEL_LIB)
	mv $(CA_MODEL_LIB) $(LIB_DIR)/.
	rm $(CA_MODEL_OBJS)

ca_model_setup.o:  $(INC_DIR)/datatypes.h
	$(CPP) $(CPPFLAGS) ca_model_setup.cpp -I$(INC_DIR) 

ca_model_steps.o:  $(INC_DIR)/datatypes.h
	$(CPP) $(CPPFLAGS) ca_model_steps.cpp -I$(INC_DIR) 

ca_model_vis.o:  $(INC_DIR)/datatypes.h
	$(CPP) $(CPPFLAGS) ca_model_vis.cpp -I$(INC_DIR) 

all: $(CA_MODEL_LIB)

cleanall: 
	cd $(LIB_DIR); rm $(CA_MODEL_LIB)
