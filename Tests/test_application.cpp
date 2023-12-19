// Creator: Giovanni Battista Alteri
// Modified by: Giovanni Battista Alteri
// Date Created: December 13, 2023
// Last revisited: December 15, 2023
//
//  test_application.cpp: C++ Test code of the Cellular automata Class. The program will test different dimensions/neighborhoods/boundaries 
//  with a variety of rule spread.

#include <iostream>
#include <utility>
#include "myCellularAutomata.h"

int main()
{

    cellularAutomata FirstAutomata; // create instance of cellularAutomata

    FirstAutomata.setup_dimension(2, 10, 10);                            // set up cellularAutomata dimensions for 2D
    int neighType = 1;                                                   // set up neighborhood type (2 for Moore neighborhood)
    int boundType = 1;                                                   // set up boundary type (1 for inifinite space)
    int ruleType = 1;                                                    // setup rule_type
    FirstAutomata.setup_cell_states(3);                                  // setup 3 possible states for cell
    FirstAutomata.setup_neighborhood(0, 0, neighType);                   // setup neighborhood
    FirstAutomata.setup_boundtype(boundType, 0);                         // set boundary type
    FirstAutomata.init_condition_rewrite(FirstAutomata.affected, 0.5); // initialize cellular automata
                                                                         // w/ ceratin probablity for unaffected state

    std::cout << "Starting Configuration: " << std::endl;
    for (int i = 0; i < FirstAutomata.getHeight(); i++) // get current height
    {
        for (int j = 0; j < FirstAutomata.getWidth(); j++) // get current width
        {
            std::cout << FirstAutomata.getCurrentState()[i][j] << " "; // print current matrices state
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    FirstAutomata.step(1, 10, neighType); // update cellular automata after 10 steps using majority rule

    std::cout << "Configuration After the ten steps: " << std::endl;
    for (int i = 0; i < FirstAutomata.getHeight(); i++)
    {
        for (int j = 0; j < FirstAutomata.getWidth(); j++)
        {
            std::cout << FirstAutomata.getCurrentState()[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "______________________________________________________________________________________________" << endl;

    cellularAutomata FirstAutomata2; // create instance of cellularAutomata

    FirstAutomata2.setup_dimension(2, 50, 50);                            // set up cellularAutomata dimensions for 2D
    neighType = 1;                                                   // set up neighborhood type (2 for Moore neighborhood)
    boundType = 1;                                                   // set up boundary type (1 for inifinite space)
    ruleType = 1;                                                    // setup rule_type
    FirstAutomata2.setup_cell_states(3);                                  // setup 3 possible states for cell
    FirstAutomata2.setup_neighborhood(0, 0, neighType);                   // setup neighborhood
    FirstAutomata2.setup_boundtype(boundType, 0);                         // set boundary type
    FirstAutomata2.init_condition_rewrite(FirstAutomata2.affected, 0.5); // initialize cellular automata
                                                                         // w/ ceratin probablity for unaffected state

    std::cout << "Starting Configuration: " << std::endl;
    for (int i = 0; i < FirstAutomata2.getHeight(); i++) // get current height
    {
        for (int j = 0; j < FirstAutomata2.getWidth(); j++) // get current width
        {
            std::cout << FirstAutomata2.getCurrentState()[i][j] << " "; // print current matrices state
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    FirstAutomata2.step(ruleType, 2, neighType); // update cellular automata after 10 steps using majority rule

    std::cout << "Configuration After two steps: " << std::endl;
    for (int i = 0; i < FirstAutomata2.getHeight(); i++)
    {
        for (int j = 0; j < FirstAutomata2.getWidth(); j++)
        {
            std::cout << FirstAutomata2.getCurrentState()[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "______________________________________________________________________________________________" << endl;
    cout << "Simulation of cells for Neighborhood: Moore || Fixed boundaries || Majority Rule" << endl;
    int numStates = 3;     // setup number of cancer cell states(healthy, affected, dead)
    int numRows = 30;      // initial number of rows
    int numColumns = 30;   // initial number of columns
    int radius = 1;        // set radius for boundary effect
    int num_steps = 10;    // 10 steps after cellular automata has been set
    int dimensionType = 2; // setup dimension size
    neighType = 2;     // set up neighborhood type (1 for von Neumann neighborhood) (2 for Moore)
    boundType = 3;     // set up boundary type (1 for inifinite space) (2 for periodic)(*3 for fixed boundary)
    ruleType = 1;      // setup rule_type (2 for straight conditional) (1 for majority) (3 for conditional transition rule)

    cellularAutomata cancerAutomata;                                        // instance of cellular automata
    cancerAutomata.setup_dimension(dimensionType, numRows, numColumns);     // set up cellularAutomata dimensions (2D, 20 rows & columns)
    cancerAutomata.setup_cell_states(numStates);                            // setup 3 possible states for cell
    cancerAutomata.setup_neighborhood(0, 0, neighType);                     // von Neumann neighborhood setup. initial row/column at (0,0)
    cancerAutomata.setup_boundtype(boundType, radius);                      // infinite boundaries
    cancerAutomata.change_state_cell(numRows/2, numColumns/2, 1);
    cancerAutomata.init_condition_rewrite(cancerAutomata.affected, 0.05); // initialize cellular automata
                                                                            // w/ ceratin probablity for unaffected state
    std::cout << "Counting states and exporting to CSV..." << std::endl;
    cancerAutomata.countAllStates();
    cancerAutomata.exportToCSV("../Display/Data/final_test.csv");
    cout << "Initial Configuration of Cellular Automata: " << endl;
    cancerAutomata.draw();
    cout << endl;

    for (int step = 0; step < num_steps; step++){
        cancerAutomata.step(ruleType, step, neighType);

        std::cout << "Counting states and exporting to CSV..." << std::endl;
        cancerAutomata.countAllStates();
        cancerAutomata.exportToCSV("../Display/Data/final_test.csv");
        cout << "Cellular Automata after " << step << " steps: " << endl;
        cancerAutomata.draw();
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "______________________________________________________________________________________________" << endl;
    cout << "Simulation of cells for Neighborhood: Neumann || No boundaries || Majority Rule" << endl;
    numStates = 3;     // setup number of cancer cell states(healthy, affected, dead)
    numRows = 30;      // initial number of rows
    numColumns = 30;   // initial number of columns
    radius = 1;        // set radius for boundary effect
    num_steps = 10;    // 10 steps after cellular automata has been set
    dimensionType = 2; // setup dimension size
    neighType = 2;     // set up neighborhood type (1 for von Neumann neighborhood) (2 for Moore)
    boundType = 1;     // set up boundary type (1 for inifinite space) (2 for periodic)(*3 for fixed boundary)
    ruleType = 1;      // setup rule_type (2 for straight conditional) (1 for majority) (3 for conditional transition rule)

    cellularAutomata cancerAutomata2;                                        // instance of cellular automata
    cancerAutomata2.setup_dimension(dimensionType, numRows, numColumns);     // set up cellularAutomata dimensions (2D, 20 rows & columns)
    cancerAutomata2.setup_cell_states(numStates);                            // setup 3 possible states for cell
    cancerAutomata2.setup_neighborhood(0, 0, neighType);                     // von Neumann neighborhood setup. initial row/column at (0,0)
    cancerAutomata2.setup_boundtype(boundType, radius);                      // infinite boundaries
    cancerAutomata2.change_state_cell(numRows/2, numColumns/2, 1);
    cancerAutomata2.init_condition_rewrite(cancerAutomata2.affected, 0.05); // initialize cellular automata
                                                                            // w/ ceratin probablity for unaffected state
    std::cout << "Counting states and exporting to CSV..." << std::endl;
    cancerAutomata2.countAllStates();
    cancerAutomata2.exportToCSV("../Display/Data/final_test.csv");
    cout << "Initial Configuration of Cellular Automata: " << endl;
    cancerAutomata2.draw();
    cout << endl;

    for (int step = 0; step < num_steps; step++){
        cancerAutomata2.step(ruleType, step, neighType);

        std::cout << "Counting states and exporting to CSV..." << std::endl;
        cancerAutomata2.countAllStates();
        cancerAutomata2.exportToCSV("../Display/Data/final_test.csv");
        cout << "Cellular Automata after " << step << " steps: " << endl;
        cancerAutomata2.draw();
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cout << "______________________________________________________________________________________________" << endl;
    cout << "Simulation of cells for Neighborhood: Moore || No boundaries || Majority Rule" << endl;
    numStates = 3;     // setup number of cancer cell states(healthy, affected, dead)
    numRows = 30;      // initial number of rows
    numColumns = 30;   // initial number of columns
    radius = 1;        // set radius for boundary effect
    num_steps = 10;    // 10 steps after cellular automata has been set
    dimensionType = 2; // setup dimension size
    neighType = 2;     // set up neighborhood type (1 for von Neumann neighborhood) (2 for Moore)
    boundType = 2;     // set up boundary type (1 for inifinite space) (2 for periodic)(*3 for fixed boundary)
    ruleType = 1;      // setup rule_type (2 for straight conditional) (1 for majority) (3 for conditional transition rule)

    cellularAutomata cancerAutomata3;                                        // instance of cellular automata
    cancerAutomata3.setup_dimension(dimensionType, numRows, numColumns);     // set up cellularAutomata dimensions (2D, 20 rows & columns)
    cancerAutomata3.setup_cell_states(numStates);                            // setup 3 possible states for cell
    cancerAutomata3.setup_neighborhood(0, 0, neighType);                     // von Neumann neighborhood setup. initial row/column at (0,0)
    cancerAutomata3.setup_boundtype(boundType, radius);                      // infinite boundaries
    cancerAutomata3.change_state_cell(numRows/2, numColumns/2, 1);
    cancerAutomata3.init_condition_rewrite(cancerAutomata3.affected, 0.05); // initialize cellular automata
                                                                            // w/ ceratin probablity for unaffected state
    std::cout << "Counting states and exporting to CSV..." << std::endl;
    cancerAutomata3.countAllStates();
    cancerAutomata3.exportToCSV("../Display/Data/final_test.csv");
    cout << "Initial Configuration of Cellular Automata: " << endl;
    cancerAutomata3.draw();
    cout << endl;

    for (int step = 0; step < num_steps; step++){
        cancerAutomata3.step(ruleType, step, neighType);

        std::cout << "Counting states and exporting to CSV..." << std::endl;
        cancerAutomata3.countAllStates();
        cancerAutomata3.exportToCSV("../Display/Data/final_test.csv");
        cout << "Cellular Automata after " << step << " steps: " << endl;
        cancerAutomata3.draw();
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "______________________________________________________________________________________________" << endl;
    cout << "Simulation of cells for Neighborhood: Moore || fixed boundaries || straight conditional Rule" << endl;
    numStates = 3;     // setup number of cancer cell states(healthy, affected, dead)
    numRows = 30;      // initial number of rows
    numColumns = 30;   // initial number of columns
    radius = 1;        // set radius for boundary effect
    num_steps = 10;    // 10 steps after cellular automata has been set
    dimensionType = 2; // setup dimension size
    neighType = 2;     // set up neighborhood type (1 for von Neumann neighborhood) (2 for Moore)
    boundType = 3;     // set up boundary type (1 for inifinite space) (2 for periodic)(*3 for fixed boundary)
    ruleType = 2;      // setup rule_type (2 for straight conditional) (1 for majority) (3 for conditional transition rule)

    cellularAutomata cancerAutomata4;                                        // instance of cellular automata
    cancerAutomata4.setup_dimension(dimensionType, numRows, numColumns);     // set up cellularAutomata dimensions (2D, 20 rows & columns)
    cancerAutomata4.setup_cell_states(numStates);                            // setup 3 possible states for cell
    cancerAutomata4.setup_neighborhood(0, 0, neighType);                     // von Neumann neighborhood setup. initial row/column at (0,0)
    cancerAutomata4.setup_boundtype(boundType, radius);                      // infinite boundaries
    cancerAutomata4.change_state_cell(numRows/2, numColumns/2, 1);
    cancerAutomata4.init_condition_rewrite(cancerAutomata4.affected, 0.05); // initialize cellular automata
                                                                            // w/ ceratin probablity for unaffected state
    std::cout << "Counting states and exporting to CSV..." << std::endl;
    cancerAutomata4.countAllStates();
    cancerAutomata4.exportToCSV("../Display/Data/final_test.csv");
    cout << "Initial Configuration of Cellular Automata: " << endl;
    cancerAutomata4.draw();
    cout << endl;

    for (int step = 0; step < num_steps; step++){
        cancerAutomata4.step(ruleType, step, neighType);

        std::cout << "Counting states and exporting to CSV..." << std::endl;
        cancerAutomata4.countAllStates();
        cancerAutomata4.exportToCSV("../Display/Data/final_test.csv");
        cout << "Cellular Automata after " << step << " steps: " << endl;
        cancerAutomata4.draw();
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "______________________________________________________________________________________________" << endl;
    cout << "Simulation of cells for Neighborhood: Neumann || No boundaries || Majority Rule" << endl;
    numStates = 3;     // setup number of cancer cell states(healthy, affected, dead)
    numRows = 30;      // initial number of rows
    numColumns = 30;   // initial number of columns
    radius = 1;        // set radius for boundary effect
    num_steps = 10;    // 10 steps after cellular automata has been set
    dimensionType = 2; // setup dimension size
    neighType = 1;     // set up neighborhood type (1 for von Neumann neighborhood) (2 for Moore)
    boundType = 1;     // set up boundary type (1 for inifinite space) (2 for periodic)(*3 for fixed boundary)
    ruleType = 1;      // setup rule_type (2 for straight conditional) (1 for majority) (3 for conditional transition rule)

    cellularAutomata cancerAutomata_final;                                        // instance of cellular automata
    cancerAutomata_final.setup_dimension(dimensionType, numRows, numColumns);     // set up cellularAutomata dimensions (2D, 20 rows & columns)
    cancerAutomata_final.setup_cell_states(numStates);                            // setup 3 possible states for cell
    cancerAutomata_final.setup_neighborhood(0, 0, neighType);                     // von Neumann neighborhood setup. initial row/column at (0,0)
    cancerAutomata_final.setup_boundtype(boundType, radius);                      // infinite boundaries
    cancerAutomata_final.change_state_cell(numRows/2, numColumns/2, 1);
    cancerAutomata_final.init_condition_rewrite(cancerAutomata_final.affected, 0.05); // initialize cellular automata
                                                                            // w/ ceratin probablity for unaffected state
    std::cout << "Counting states and exporting to CSV..." << std::endl;
    cancerAutomata_final.countAllStates();
    cancerAutomata_final.exportToCSV("../Display/Data/final_test.csv");
    cout << "Initial Configuration of Cellular Automata: " << endl;
    cancerAutomata_final.draw();
    cout << endl;

    for (int step = 0; step < num_steps; step++){
        cancerAutomata_final.step(ruleType, step, neighType);

        std::cout << "Counting states and exporting to CSV..." << std::endl;
        cancerAutomata_final.countAllStates();
        cancerAutomata_final.exportToCSV("../Display/Data/final_test.csv");
        cout << "Cellular Automata after " << step << " steps: " << endl;
        cancerAutomata_final.draw();
        cout << endl;
    }


    return 0;
}