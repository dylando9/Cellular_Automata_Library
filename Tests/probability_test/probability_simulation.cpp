// Creator: Yara Khoury
// Modified by: Yara Khoury
// Date Created: December 15, 2023
// Last revisited: December 15, 2023
//
//  probability_simulation.cpp:  implementation of the CA library for 
//  a cancer growth application using different initial probabilities. 


#include "../../Include/myCellularAutomata.h"
#include <iostream>
#include <fstream>

int main(void) 
{
    // fixed simulation paramters for prob testing 
    const int numStates = 3;        // setup number of cancer cell states(healthy, affected, dead)
    const int numRows = 100;        // initial number of rows
    const int numColumns = 100;     // initial number of columns
    const int numSteps = 10;        // 10 steps after cellular automata has been set
    const int dimensionType = 2;    // setup dimension size

    // varying paramters 
    const int neighType = 1;        // set up neighborhood type (1 for von Neumann neighborhood) (2 for Moore)
    const int boundType = 1;        // set up boundary type (1 for infinite space) (2 for periodic) (3 for fixed boundary)
    const int ruleType = 1;         // setup rule_type (2 for straight conditional) (1 for majority) (3 for conditional transition rule)

    // defining the range of the initial probabilities
    const double startProb = 0.01;   // start 
    const double endProb = 0.1;     // end 
    const double probStep = 0.01;    // increment by 0.01

    // create csv file to store the final values of cells in every state
    std::ofstream resultFile("../Utils/Data/Prob_results.csv");
    resultFile << "Initial_Probability,Final_Affected_Count,Final_Unaffected_Count,Final_Dead_Count\n";

    for (double P = startProb; P <= endProb; P += probStep) 
    {
        cellularAutomata cancerAutomata;
        cancerAutomata.setup_dimension(dimensionType, numRows, numColumns);
        cancerAutomata.setup_cell_states(numStates);
        cancerAutomata.setup_boundtype(boundType, 1);
        cancerAutomata.init_condition_rewrite(cancerAutomata.affected, P);

        for (int step = 0; step < numSteps; step++) {
            cancerAutomata.step(ruleType, 1, neighType);
        }

        std::unordered_map<int, int> stateCounts = cancerAutomata.countAllStates();
        resultFile << P << ","
                   << stateCounts[cancerAutomata.affected] << ","
                   << stateCounts[cancerAutomata.unaffected] << ","
                   << stateCounts[cancerAutomata.dead] << "\n";
    }

    resultFile.close();
    return 0;
}