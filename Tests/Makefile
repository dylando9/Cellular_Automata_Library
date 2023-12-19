# Creators:  Giovanni Alteri
# Modified by: Giovanni Alteri
# Date Created: November 21, 2023
# Date Updated: December 15, 2023
#
# This makefile make the targets for the testing files

CPP = g++
CPPFLAGS = -O3 -o
UINC_DIR = ../Utils/Include
INC_DIR = ../Include
LIB_DIR = ../Lib
ULIB_DIR = ../Utils/Lib
BIN_DIR = ../Bin
EXECUTABLES = test_application

test_application:  $(INC_DIR)/myCellularAutomata.h
	$(CPP) $(CPPFLAGS) test_application test_application.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lmyautomata
	mv test_application $(BIN_DIR)


all: $(EXECUTABLES)