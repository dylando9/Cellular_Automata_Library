// Creator: Giovanni Alteri, Dylan Do, Yara Khoury
// Modified by: Giovanni Alteri
// Date Created: November 21, 2023
// Last revisited: December 15, 2023
//
//  Include file for the C++ implementations of cellular automata setup

#pragma once // Ensures that this file is only included once
             // during compilation
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <unordered_map>
using namespace std;

class cellularAutomata
{
protected:
    int size;                        // size/area of cellular automata
    int width;                       // width of cellular automata, columns for matrix
    int height;                      // height of cellular automata, rows for matrix
    vector<vector<int> > data;        // vector data for cellular automata
    int num_states;                  // number of states the cell can be in
    vector<vector<int> > config;      // hold current state of cellular automaton
    vector<vector<int> > next_config; // hold next state of cellular automaton

public:
    cellularAutomata();                                                  // default constructor
    cellularAutomata(int ndims, int dim1, int dim2);                     // constructor for cellular automata
    int setup_dimension(int ndims, int dim1, int dim2);                  // create grid for cellular automata
    vector<int> setup_neighborhood(int row, int column, int neigh_type); // create cellular automaton neighborhood
    int setup_boundtype(int bound_type, int radius);                     // create CA boundary type and radius
    int setup_cell_states(int nstates);                                  // create state of cellular automata
    int init_condition(int x_state, double prob);                        // probability of a cell entering state x
                                                                         // from an empty cell
    int init_condition_rewrite(int x_state, double prob);                // probability of cell entering state x
                                                                         // from any other state including empty
    int straight_conditional_rule(int x, int y);                         // Straight conditional transition rule
    int conditional_transition_rule(int x, int y, const vector<int>& neighborhood);                       // Conditional Transition rule on a neighbor
    int majority_rule(int x, int y, vector<int>& neighbor);               // calculate next step using majority rule
    int parity_rule(int x, int y, vector<int>& neighbor);                 // calculate next step using parity(XOR) rule

    void step(int rule_type, int num_steps, int neigh_type);     // update cell states of cellular automata
    void draw() const;                           // print out current state cellular automata matrix
    vector<vector<int> > getCurrentState() const; // retrieve current state of matrix
    int getWidth() const;                        // retrieve width/column of cellular automata
    int getHeight() const;                       // retrieve height/row of cellular automata

    void exportToCSV(const std::string &filename) const;                   // exports the CA grid into a CSV file
    std::unordered_map<int, int> countAllStates() const;                   // counts the number of cells in a particular state
    int change_state_cell(int x, int y, int state);

    int unaffected; // cell is healthy/unaffected
    int affected;   // cell is affected
    int dead;       // cell is dead
    bool is_infinite;
    int new_height;
    int new_width;
    int num_dimensions;

};

// LIST OF ERRORS RETURNED BY CELLULAR AUTOMATA CLASS METHODS
#define NO_ERR 0                            // A method was sucessfully completed
#define CELLARR_ERR_INVALID_PTR -2          // Invalid array pointer
#define CELLARR_ERR_NO_ALLOC -3             // Fail to allocate memory for array
#define CELLARR_ERR_OVERFLOW -4             // Overflow - array is full
#define CELLARR_ERR_UNDERFLOW -5            // Attempting to operate on empty array
#define CELLARR_ERR_INVALID_SZ -6           // Invalid array size
#define CELLARR_ERR_K_NOTFOUND -7           // key was not found in the array
#define CELLARR_ERR_OUTBOUNDS_OP -8         // Attempt to access kth-element of the array outside the matrix bounds
#define CELL_ERR_INVALID_SREQ -9            // Invalid status cell code
#define CELL_ERR_INVALID_WIDTH -10          // invalid size width
#define CELL_ERR_INVALID_HEIGHT -11         // invalid size height
#define CELL_ERR_INVALID_NDIM -12           // invalid number of dimensions
#define CELL_ERR_INVALID_CELL_STAT -14      // invalid status cell code
#define CELL_ERR_INVALID_BOUND -15          // invalid bound rule option
#define CELL_ERR_INVALID_NEIGHBOR -16       // invalid neighbor option
#define CELL_ERR_INVALID_UPRULE -17         // invalid update rule option
#define CELL_ERR_INVALID_NSTAT -18          // invalid number of states
#define CELL_ERR_INVALID_PROB -19           // invalid probability
#define CELL_ERR_INVALID_STEPS -20          // invalid number of steps