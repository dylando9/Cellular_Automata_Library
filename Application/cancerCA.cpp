// Creator: Dylan Do
// Modified by: Dylan Do
// Date Created: December 13, 2023
// Last revisited: December 15, 2023
//
//  cancerCA.cpp: C++ Application of the Cellular automata. The application will simulate a cancer growth and
//  how it spreads across a variety of dimensions/neighborhoods/boundaries.

/*

Our application will study the relationship between the probability of a cell to develop cancer in a certain system vs the size of the system itself:
given a certain starting probability P that a cell can became cancerous, and given a certain area of the system (the dimension of the matrix, rows*columns).

We launched several different simulations (used infinite boundaries and von Neumann to simulate real life cancer spread) 
with different sizes and probabilities.
We used Majority rule because it describes well the real system, a cell surrounded by dead cells dies, a cell surrounded by cancer cells became cancerous itself.
The results of the application are in different files texts (one file text fro each simulation) in Utils/Data after running the executable file in Bin/.
The png files include the plotting framework for the library and indicate how many cells are in each state
10 number steps for all the simulations.

The user is free to change the parameters to simulate a cellular automata.
*/

#include "myCellularAutomata.h"
#include <iostream>

int main(void)
{
    // Cellular automata (Neighborhood: von Neumann || No boundaries || Majority Rule)
    cout << "Simulation of cells for Neighborhood: von Neumann || No boundaries || Majority Rule" << endl;
    int numStates = 3;     // setup number of cancer cell states(healthy, affected, dead)
    int numRows = 100;     // initial number of rows
    int numColumns = 100;  // initial number of columns
    int radius = 1;        // set radius for boundary effect
    int num_steps = 10;    // 10 steps after cellular automata has been set
    int dimensionType = 2; // setup dimension size
    int neighType = 1;     // set up neighborhood type (1 for von Neumann neighborhood) (2 for Moore)
    int boundType = 1;     // set up boundary type (1 for inifinite space) (2 for periodic)(3 for fixed boundary)
    int ruleType = 1;      // setup rule_type (1 for majority) (2 for straight conditional)  (3 for conditional transition rule)

    int counter = 0;
    int sizes[] = {10, 50, 100};
    double probabilities[] = {0.001, 0.01, 0.1};
    for (int size : sizes)
    {
        numRows = size;
        numColumns = size;
        for (double P : probabilities)
        {
            for (int step = 0; step < num_steps; step++)
            {
                cellularAutomata cancerAutomata;                                    // instance of cellular automata
                cancerAutomata.setup_dimension(dimensionType, numRows, numColumns); // set up cellularAutomata dimensions (2D, 20 rows & columns)
                cancerAutomata.setup_cell_states(numStates);                        // setup 3 possible states for cell
                cancerAutomata.setup_neighborhood(0, 0, neighType);                 // von Neumann neighborhood setup. initial row/column at (0,0)
                cancerAutomata.setup_boundtype(boundType, radius);                  // infinite boundaries
                cancerAutomata.change_state_cell(numRows / 2, numColumns / 2, 1);
                cancerAutomata.init_condition_rewrite(cancerAutomata.affected, P); // initialize cellular automata
                counter += 1;
                std::cout << "_______________________________" << std::endl;
                std::cout << "_______________________________" << std::endl;
                std::cout << "SIZE[ROWS: " << numRows << "  COlOUMNS: " << numColumns << "]" << std::endl;
                std::cout << "SIMULATION NUMBER: " << counter << std::endl;
                std::cout << "PROBABILITY: " << P << std::endl;
                std::cout << std::endl;
                std::cout << "_______________________________" << std::endl;
                std::cout << "_______________________________" << std::endl;
                cancerAutomata.step(ruleType, step, neighType);
                std::cout << std::endl;
                std::cout << "Counting states and exporting to CSV..." << std::endl;
                cancerAutomata.countAllStates();
                cancerAutomata.exportToCSV("../Utils/Data/Application.csv");
                cout << "Cellular Automata after " << step << " steps: " << endl;
                cancerAutomata.draw();
                cout << endl;
                std::cout << std::endl;
                std::cout << "_______________________________" << std::endl;
                std::cout << "_______________________________" << std::endl;
            }
        }
    }
}