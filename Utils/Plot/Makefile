# Creators:  Giovanni Alteri, Dylan Do, Yara Khoury
# Date Created: December 14, 2023
# Date Updated: December 15, 2023
#
# This makefile runs the python plotting script and cleans up images. 

PYTHON = python3.11 # define python interpreter 
SCRIPT = display.py
FILES = matrix_step*.png
CSV = ../Data/*.csv 

all: plot

plot:
	@echo "Running the plotting Python script..."
	@$(PYTHON) $(SCRIPT)

# clean up target to removed generated png files
clean:
	@echo "Cleaning up png files..."
	@rm -f $(FILES)
	@echo "Cleaning up CSV file..."
	@rm -f $(CSV)

.PHONY: all plot clean