#include "Grid.h"

Grid::Grid( std::vector< std::vector<int> > data, int blankRow, int blankCol ) 
{
    this->data = data;
    this->blankRow = blankRow;
    this->blankCol = blankCol;
}


void Grid::randomize()
{

}


bool Grid::solved()
{
    int n = data.size();

    for (unsigned i = 0; i < ( (n*n) - 1 ); ++i)
    {
        // This is a generalized algorithm for allowing the ith tile to determine its goal position.
        // When all tiles are at their goal position, the loop will exit with true.
        if ( data[i/n][i%n] != i+1 )
            return false;
    }

    return true;
}


// Prints the grid to the console.
void Grid::print()
{
    int n = data.size();

    for (unsigned i = 0; i < n; ++i)
    {
        for (unsigned j = 0; j < n; ++j)
        {
            std::cout << data[i][j];
        }
        
        std::cout << std::endl;
    }
}


// Checks all legal moves. For each move determined to be legal, the function will generate a Grid
// and push that Grid into the vector.
std::vector<Grid> Grid::expand() const
{
    int n = data.size();        // This int holds the grid size for the boundary checks below
    std::vector<Grid> moves;    // This vector holds all of the Grids with moves performed

    // Check UP move
    if ( blankRow > 0 )
    {
        std::vector< std::vector<int> > up = data;              // Make a copy of the grid
        up[blankRow][blankCol] = up[blankRow-1][blankCol];      // Move numeric tile to the blank tile's old position
        up[blankRow-1][blankCol] = 0;                           // Move blank tile
        
        Grid upMove( up, (blankRow-1), (blankCol) );            // Create a new Grid object with the move applied
        moves.push_back(upMove);                                // Push the new Grid into the output vector
    
        // FIXME Test code
        //std::cout << "UP" << std::endl << std::endl;
        //upMove.print();
        //std::cout << std::endl << std::endl;
    }

    // Check DOWN move
    if ( blankRow < (n-1) )
    {
        std::vector< std::vector<int> > down = data;            // Make a copy of the grid
        down[blankRow][blankCol] = down[blankRow+1][blankCol];  // Move numeric tile to the blank tile's old position
        down[blankRow+1][blankCol] = 0;                         // Move blank tile

        Grid downMove( down, (blankRow+1), (blankCol) );        // Create a new Grid object with the move applied
        moves.push_back(downMove);                              // Push the new Grid into the output vector
    
        // FIXME Test code
        //std::cout << "DOWN" << std::endl << std::endl;
        //downMove.print();
        //std::cout << std::endl << std::endl;
    }

    // Check LEFT move
    if ( blankCol > 0 )
    {
        std::vector< std::vector<int> > left = data;            // Make a copy of the grid
        left[blankRow][blankCol] = left[blankRow][blankCol-1];  // Move numeric tile to the blank tile's old position
        left[blankRow][blankCol-1] = 0;                         // Move blank tile

        Grid leftMove( left, (blankRow), (blankCol-1) );        // Create a new Grid object with the move applied
        moves.push_back(leftMove);                              // Push the new Grid into the output vector
    
        // FIXME Test code
        //std::cout << "LEFT" << std::endl << std::endl;
        //leftMove.print();
        //std::cout << std::endl << std::endl;
    }

    // Check RIGHT move
    if ( blankRow < (n-1) )
    {
        std::vector< std::vector<int> > right = data;               // Make a copy of the grid
        right[blankRow][blankCol] = right[blankRow][blankCol+1];  // Move numeric tile to the blank tile's old position
        right[blankRow][blankCol+1] = 0;                            // Move blank tile

        Grid rightMove( right, (blankRow), (blankCol+1) );          // Create a new Grid object with the move applied
        moves.push_back(rightMove);                                 // Push the new Grid into the output vector
        
        // FIXME Test code
        //std::cout << "RIGHT" << std::endl << std::endl;
        //rightMove.print();
        //std::cout << std::endl << std::endl;
    }

    return moves;
}



