<u>Created by:</u> Dylan Do<br>
<u>Modified by: </u>Giovanni Alteri<br>
<u>Date of Created:</u> November 21, 2023 <br>
<u>Last updated: </u> December 15, 2023 <br>
<u>Directory Path: </u> Cellular_Automata_Library/Source

This directory contains source C++ implementations of the cellular automata

## cellularAutomata.cpp: Cellular Automata
### Overview
The cellularAutomata.cpp file contains a C++ script of a general Cellular Automata (CA) simulator. It includes a cellularAutomata class that allows users to create CA models with customizable dimensions, neighborhood types, boundary conditions, cell states, and transition rules. </br>

### Features: 
- The CA created supports 1D and 2D cellular automata models.
- Implementation for both von Neumann and Moore neighborhoods.
- Three options for boundary conditions: infinite, periodic, and fixed.
- Multiple transition rules including majority, parity, and conditional rules.
- CA grid can be initialized with random states based on certain probability. 
- Export function to save the CA state to a CSV file.

### How to run: 
A makefile has been added to this directory (Source) to help comiple and run the CA prototype. 
The command 'make all' will run and compile the code. 

# Updates:
- Giovanni's added updates to this directory:
    - created cellularAutomata.cpp
- Dylan's added updates to this directory:
    - updated cellularAutomata.cpp
- Yara's added updates to this directory:
    - updated cellularAutomata.cpp: added two new methods for the class: exportToCSV() and countAllStates()