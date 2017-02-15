#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>

class Grid;

typedef int (Grid::*costFunc_t)() const;

class Grid
{
    public:
        Grid( std::vector< std::vector<unsigned> > data, int blankRow, int blankCol ); // Constructor accepts completed Grid
	    //Grid(int n = 3): data(n, std::vector<int>(n,0)){}                       // Default constructor for Grid of size 3

        bool operator <(const Grid& rhs);     // Compares grids by looking at their "id" string member.

    	void randomize();               // Creates a random grid.
    	bool solved() const;            // Checks if the current grid is in a solved state.
        void print();                   // Prints the tile grid to the console.

        int h(costFunc_t);              // Function for directing the function pointer.
        int uniform_cost() const;       // Function for determining uniform cost search h(n).
        int misplaced_tile() const;     // Function for determining misplaced tile h(n).
        int manhattan() const;          // Function for deterining Manhattan distance h(n).
        
        std::string getid() const;           // Returns string id.

        std::vector<Grid> expand() const;   // Checks all legal moves, returns a std::vector of Grids
	                                        // containing those moves.

    private:
        std::vector< std::vector<unsigned> > data;  // 2D vector representing the grid state.
	    int blankRow, blankCol;                     // These ints store the coordinates of the blank tile.

        std::string id;                                  // Unique string identifying the grid configuration.

        void serialize();                           // Turns 'data' into a uniqe identifying string. This is used
                                                    // for comparisons with other grids in the explored and visited
                                                    // sets.
};

#endif
