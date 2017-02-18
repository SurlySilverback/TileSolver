#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <vector>

class Problem
{
    public:
        Problem(std::vector< std::vector<int> > Grid, int n, int zeroRow, int zeroCol);
        
        void printGrid() const;                     // couts grid to the screen
        std::vector< <std::vector<int> > Move();    // Checks for legal moves, then generates child problems for those legal moves

    private:
        Grid state;     // Grid object representing the game state
        int n;          // side-length of tile grid
        int zeroRow;    // Row coordinate of blank tile
        int zeroCol;    // Column coordinate of blank tile        
};

#endif
