<u>Created by:</u> Giovanni Alteri, Dylan Do, Yara Khoury<br>
<u>Modified by: </u> Yara Khoury <br>
<u>Date of Created:</u> December 14, 2023 <br>
<u>Last updated: </u> December 15, 2023 <br>
<u>Directory Path: </u> Cellular_Automata_Library/Utils/Plot

This directory contains a visualization tool for the CA. <br>

# Cellular Automata Visualization Tool

### Overview
- display.py: is a Python script that reads the states of the cells from the CA from a CSV file, and visualizes each state as a color-coded matrix. The matrices are plotted and saved as PNG images using Matplotlib. 

- Makefile: helps to execute the python script and clean up the resulting png files and csv files if necessary. 

### Prerequisites
In order to be able to run this python script you will need the following prerequisites: 

Python 3.11.4 
matplotlib
csv

### How to run the CA 
To visualize the cellular automata, simply run the following command in the terminal:

'make all'

To clean up and remove all generated PNG files, use:

'make clean'