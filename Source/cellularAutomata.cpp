// Creator: Dylan Do
// Modified by: Giovanni Alteri
// Date Created: November 21, 2023
// Last revisited: December 15, 2023
//
//  C++ Implementation of the Cellular Automata

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <utility>
#include <fstream>
#include <string>
#include <unordered_map>
#include "myCellularAutomata.h"

bool is_infinite = false;
// function: cellularAutomata
//           default constructor
// inputs: none
cellularAutomata::cellularAutomata() : size(0), width(0), height(0), num_states(0) {}

// function: cellularAutomata
//           constructor for the cellular automata with set matrices dimensions
// inputs: ndims: number of dimensions(for 2D, input would be 2)
//         dim1: width of the matrix
//         dim2: height of the matrix
cellularAutomata::cellularAutomata(int ndims, int dim1, int dim2)
    : size(0), width(0), height(0), num_states(0)
{
    setup_dimension(ndims, dim1, dim2);
}

// function: setup_dimension
//           function to initialize the dimension sizes
//           setup a n x m grid, where <= n, m<= max_size
// inputs: ndims: number of dimensions(for 2D it would be 2)
//         dim1: width of the matrix
//         dim2: height of the matrix
int cellularAutomata::setup_dimension(int ndims, int dim1, int dim2)
{
     if ((ndims > 2) || (ndims < 0))
     {
        return CELLARR_ERR_INVALID_PTR;
     }
    num_dimensions = ndims;
    width = dim1;
    height = dim2;
    new_height = height;
    new_width = width;
    config.resize(height, vector<int>(width));
    next_config.resize(height, vector<int>(width));
    return NO_ERR; // function successful
}

// function: setup_neighborhood
//           function to build the neighborhood type
// inputs: neigh_type: type of neighborhood implemented (1 for von Neumann, 2 for Moore)
//         row: number of rows
//         columns: number of columns
vector<int> cellularAutomata::setup_neighborhood(int row, int column, int neigh_type)
{
    vector<int> neighbor;              // initialize neighborhood
    vector<pair<int, int>> rel_coords; // relative coordinates for neighborhood type
    if (num_dimensions == 1)
    {
        rel_coords = {
            {0, 1},  // North
            {0, -1}}; //South
    }

    if (neigh_type == 1)
    {
        // von Neumann Neighborhood
        rel_coords = {{0, 1},   // North
                      {0, -1},  // South
                      {1, 0},   // East
                      {-1, 0}}; // West
    }
    else if (neigh_type == 2)
    {
        // Moore Neighborhood
        rel_coords = {{0, 1},   // North
                      {0, -1},  // South
                      {1, 0},   // East
                      {-1, 0},  // West
                      {-1, 1},  // NorthWest
                      {-1, -1}, // SouthWest
                      {1, 1},   // Northeast
                      {1, -1}}; // SouthEast
    }
    else
    {
        cerr << "Invalid Neighborhood " << neigh_type << endl;
        return {};
    }
    // iterate over rel_coords to get the neighbors
    for (const auto &coords : rel_coords)
    {
        // row index of neighbor, taking periodic boundary into consideration
        int neighborRow = (height + ((row + coords.first) % height)) % height;

        // column index of neighbor, taking periodic boundary into consideration
        int neighborColumn = (width + ((column + coords.second) % width)) % width;

        // add updated state of neighbor to the vector
        neighbor.push_back(config[neighborRow][neighborColumn]);
    }
    return neighbor; // return type of neighborhood
}


// function: change_state_cell
//           function to change type for a specific cell condition
// inputs: x: the x-coordinates
//         y: the y-coordinates
//         new_state: the new state
int cellularAutomata::change_state_cell(int x, int y, int new_state)
{
    if ((x<0))
    {
        return CELL_ERR_INVALID_WIDTH;
    }

    if ((y<0))
    {
        return CELL_ERR_INVALID_HEIGHT;
    }

    if ((new_state<0))
    {
        return CELL_ERR_INVALID_CELL_STAT;
    }
    config[x][y] = new_state;   
    return NO_ERR;
}


// function: setup_boundtype
//           function to build the neighborhood type and specify boundary conditions
// inputs: bound_type: type of cellular automata boundary
//         radius: distance around the cell
int cellularAutomata::setup_boundtype(int bound_type, int radius)
{
    switch (bound_type)
    {
    case 1:
        // no boundaries(infinite space)
        // set a bool variable that says it is infinite_space. 
        // is_infinite = true; // GIOVANNI 
        // in the step part, if bool infinite_space = true, at each step increases the size of the matrix
        // else continue;
        break;
    case 2:
        // periodic (1D or 2D torus)
        // implementation of periodic boundaries is in setup_neighborhood
        break;
    case 3:
        // code for fixed boundaries
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i < radius || i >= height - radius || j < radius || j >= width - radius)
                {
                    config[i][j] = dead; // fix edges to a dead state
                }
            }
        }
        break;
    default:
        return CELL_ERR_INVALID_BOUND;
    }
    return NO_ERR; // function successful
}

// function: setup_cell_states
//           function to specify states for the variables
// inputs: nstates: number of states each cell can have
int cellularAutomata::setup_cell_states(int nstates)
{
    if (!nstates == 3)
    {
        return CELL_ERR_INVALID_NSTAT;
    }
    // specify states for the variables
    unaffected = 0; // unaffected cell
    affected = 1;   // affected cell
    dead = 2;       // dead cell

    return NO_ERR;
}

// function: straight_conditional_rule(int x, int y)
//           straight conditional transition rule
// inputs:  x: x-position of cell
//           y: y-position of cell
int cellularAutomata::straight_conditional_rule(int x, int y)
{
    int current_state = config[x][y];
    if (current_state == unaffected)
    {
        return affected;
    }
    else if (current_state == affected)
    {
        return dead;
    }
    else if (current_state == dead)
    {
        return dead;
    }
    return current_state;
}

// function: conditional_transition_rule(int x, int y)
//           conditional transition rule
// inputs:  x: x-position of cell (column index)
//           y: y-position of cell (row index)
//           &neighborhood: vector of the surrounding neighborhood
int cellularAutomata::conditional_transition_rule(int x, int y, const vector<int> &neighbor)
{
    if (neighbor[0] == affected)
    {
        return dead;
    }
    else if (neighbor[0] == dead)
    {
        return affected;
    }
    else if (neighbor[0] == unaffected)
    {
        return config[x][y];
    }
    return config[x][y];
}

// function: majority rule
//           function to specify rules, specifically
//           on how the cell will start spreading
// inputs:  x: x-position of cell (column index)
//           y: y-position of cell (row index)
//           neighbor: vector of the surrounding neighborhood
int cellularAutomata::majority_rule(int x, int y, vector<int> &neighbor)
{
    int total = 0; // initialize sum of values
    int cell_state = config[y][x];

    for (int i = 0; i < neighbor.size(); i++)
    {
        total += neighbor[i]; // add up current cell and its neighbors
    }
    double avg = static_cast<double>(total) / neighbor.size();

    if (avg >= 0.5 && cell_state == 0)
    {
        return 1; // 0 become 1 (affected)
    }
    else if (avg >= 0.5 && cell_state == 1)
    {
        return 2; // 1 becomes 2 (dead state)
    }
    else
    {
        return cell_state;
    }
}


// function: init_condition
//           function to initialize the cellular automata
//           by setting the initial state of each cell
// inputs:   x_state: state of cell assigned
//           prob: probability of the cells entering a specified state
int cellularAutomata::init_condition(int x_state, double prob)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    if(x_state < 0)
    {
        return CELL_ERR_INVALID_CELL_STAT;
    }
    
    if(prob < 0)
    {
        return CELL_ERR_INVALID_PROB;
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            double random_value = distribution(rng);
            if (random_value < prob)
            {
                config[x][y] = x_state; // UNKNOWN CHANGE LOGIC LATER
            }
            else
            {
                config[x][y] = unaffected;
            }
        }
    }
    return NO_ERR;
}

/// function: init_condition_rewrite
//           function to initialize the cellular automata
//           by setting the initial state of each cell keeping in mind the
//           cells can be transitioned to any state from any state (including empty)
// inputs:   x_state: state of cell assigned
//           prob: probability of the cells entering a specified state
int cellularAutomata::init_condition_rewrite(int x_state, double prob)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    if(x_state < 0)
    {
        return CELL_ERR_INVALID_CELL_STAT;
    }
    
    if(prob < 0)
    {
        return CELL_ERR_INVALID_PROB;
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            double random_value = distribution(rng);
            if (random_value < prob)
            {
                config[x][y] = x_state;
            }
        }
    }
    return NO_ERR;
}

// function: step
//           function to update step of cell states
// inputs:  rule_type: which transition rule to implement
//           int num_steps: number of steps to take
void cellularAutomata::step(int rule_type, int num_steps, int neigh_type)
{

    // int adjusted_heigth 
    for (int step = 0; step < num_steps; step++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                int state = config[x][y];
                vector<int> neighborhood = setup_neighborhood(x, y, neigh_type); // assume moore neighborhood

                // implement rule_type
                if (rule_type == 1)
                {
                    next_config[x][y] = majority_rule(x, y, neighborhood); // use majority rule
                }
                else if (rule_type == 2) // use straight conditional rule
                {
                    next_config[x][y] = straight_conditional_rule(x, y);
                }
                else if (rule_type == 3) // conditional transition rule 
                {
                    next_config[x][y] = conditional_transition_rule(x, y, neighborhood);
                }
                else
                {
                    cerr << "Invalid rule type " << endl;
                    return;
                }
            }
        }

        config = next_config;
    }
}

// function: draw
//           print out matrix of cellular automata
// inputs:   none
void cellularAutomata::draw() const
{
    for (int i = 0; i < new_height; i++)
    {
        for (int j = 0; j < new_width; j++)
        {
            cout << config[i][j] << ' ';
        }
        cout << endl;
    }
}

// function: getCurrentState
//           retrieve current state matrix
// inputs:   none
vector<vector<int>> cellularAutomata::getCurrentState() const
{
    return config; // return current state matrix
}

// function: getWidth
//           retrieve current width/column of cellular automaton
// inputs:   none
int cellularAutomata::getWidth() const
{
    return width; // return cellular automaton width
}

// function: getHeight
//           retrieve current height/row of cellular automaton
// inputs:   none
int cellularAutomata::getHeight() const
{
    return height; // return cellular automaton width
}

// function: exportToCSV
// export the cellular automaton's grid to a CSV file
// inputs: filename: string that represents the filename and optionally the path
// outputs: creates the CSV file
void cellularAutomata::exportToCSV(const std::string &filename) const
{
    // create output file stream object
    // opened the file in append mode so new matrix doesn't overwrite previous one
    std::ofstream file(filename, std::ios::app);   

    // checkpoint: see if file was successfully opened before proceeding
    if(!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // iterate over each row and column in the current row of the CA grid
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            file << config[i][j];

            // add commas in between cells except for last cell
            if (j < width - 1)
                file << ",";
        }
        // create a new line for the next row
        file << "\n";
    }

    // add the number of cells in each state counts to the file
    std::unordered_map<int, int> stateCounts = countAllStates();
    for (const auto& pair : stateCounts)
    {
        file << "State " << pair.first << ": " << pair.second << ";";
    }

    file << "\n------\n"; // Separator for next matrix

    // close file stream
    file.close();
}

// function: countAllStates
// counts the number of cells in the CA in a particular state
// input: none
// output: a map where the key is the state and the value is the count
std::unordered_map<int, int> cellularAutomata::countAllStates() const {

    // Create an empty unordered map called stateCounts to store the counts
    std::unordered_map<int, int> stateCounts;

    // Iterate over the grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // config will get the cell's state
            // the value corresponding to this state in the map will be incremented by 1.
            stateCounts[config[i][j]]++;
        }
    }

    // Return the map containing counts of all states.
    return stateCounts;
}