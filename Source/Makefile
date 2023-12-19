# Creators:  Giovanni Alteri, Dylan Do, Yara Khoury
# Date Created: November 21, 2023
# Date Updated: December 15, 2023
#
# This makefile make the targets for the testing files
CPP = g++
CPPFLAGS = -O3 -c -std=c++11
INC_DIR = ../Include
LIB_DIR = ../Lib
DATA_OBJS = cellularAutomata.o
DATA_LIB = libmyautomata.a

cellularAutomata.o : $(INC_DIR)/myCellularAutomata.h
	$(CPP) $(CPPFLAGS) cellularAutomata.cpp -I$(INC_DIR)

libmyautomata.a: $(DATA_OBJS)
	ar ru $(DATA_LIB) $(DATA_OBJS)
	mv $(DATA_LIB) $(LIB_DIR)
	rm $(DATA_OBJS)

all: $(DATA_LIB)

cleanall:
	cd $(LIB_DIR); rm $(DATA_LIB)