# Creators:  Yara Khoury
# Modified by: Yara Khoury
# Date Created: November 21, 2023
# Date Updated: December 15, 2023

# This makefile compiles and runs the cancer automata simulation for data analysis 
# regarding initial probability influence. 

# GNU C++ Compiler
CPP = g++

# Compiler flags 
CPPFLAGS = -O3 -o

# Directory paths 
INC_DIR = ../../Include
LIB_DIR = ../../Lib
BIN_DIR = ../../Bin

FILES = initial_prob_analysis*.png

EXECUTABLE = probability_simulation

probability_sim : $(INC_DIR)/myCellularAutomata.h
	$(CPP) $(CPPFLAGS) $(EXECUTABLE) probability_simulation.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lmyautomata
	mv $(EXECUTABLE) $(BIN_DIR)

all: probability_sim

# clean up target to remove generated png files
clean:
	@echo "Cleaning up png files..."
	@rm -f $(FILES)
	