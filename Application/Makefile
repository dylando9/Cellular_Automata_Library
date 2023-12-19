# Creators:  Dylan Do
# Modified by: Dylan Do
# Date Created: December 13, 2023
# Date Updated: December 15, 2023
#
# This makefile make the target for the application

# GNU C++ Compiler
CPP         = g++      

# other compiler flags -g debug, -c create a library object
CPPFLAGS    = -O3 -o

# The directory where the include files needed to create the library objects are
INC_DIR = ../Include

# The directory where all object files are going to be moved after creation
LIB_DIR = ../Lib
BIN_DIR = ../Bin

# The next line contains the list of object files created by this Makefile.
EXECUTABLES = cancerCA

cancerCA:  $(INC_DIR)/myCellularAutomata.h
	$(CPP) $(CPPFLAGS) cancerCA cancerCA.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lmyautomata
	mv cancerCA $(BIN_DIR)


all: $(EXECUTABLES)