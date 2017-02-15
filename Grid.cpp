#include "Grid.h"

Grid::Grid( std::vector< std::vector<unsigned> > data, int blankRow, int blankCol ) : data(data),
    blankRow(blankRow), blankCol(blankCol)
{
    serialize();
}


bool Grid::operator <(const Grid& rhs)
{
    return id < rhs.id;
}


void Grid::randomize()
{
    std::cerr << "TODO: randomize" << endl;
}


bool Grid::solved() const
{
    unsigned n = data.size();

    for (unsigned i = 0; i < (n*n)-1; ++i)
    {
        // If the tile is the blank tile, ignore it.
        //if ( data[i/n][i%n] == 0)
            //continue;
        
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
    unsigned n = data.size();

    for (unsigned i = 0; i < n; ++i)
    {
        for (unsigned j = 0; j < n; ++j)
        {
            std::cout << data[i][j] << ' ';
        }
        
        std::cout << std::endl;
    }
}


// Capture's Node's function pointer.
int Grid::h(costFunc_t f)
{
    return (*this.*f)();
}


// Uniform cost search function hardcodes h(n) to zero.
int Grid::uniform_cost() const
{
    return 0;
}


// Misplaced tile determines how many tiles are out of place and returns this number.
int Grid::misplaced_tile() const
{
    unsigned n = data.size();
    int misplaced = 0;
    
    for (unsigned i = 0; i < (n*n); ++i)
    {
        // Disregard the blank tile.
        if ( data[i/n][i%n] == 0 )
            continue;

        if ( data[i/n][i%n] != i+1 )
            
            ++misplaced;
    }

    // FIXME: Test cout
    std::cout << "Misplaced distance is: " << misplaced << std::endl;

    return misplaced;
}


// Manhattan determines each tile's distance from its goal position.
int Grid::manhattan() const
{
    unsigned n = data.size();
    int manhattan = 0;          // int for storing the total Manhattan distance.
    unsigned z;                      // int for holding the value of the tile we're currently looking at.

    for (unsigned i = 0; i < (n*n); ++i)                                // For all the tiles...
    {
        z = data[i/n][i%n];                                             // Get the number on the current tile...

       // std::cout << "z is currently " << z << std::endl
         //         << "i is currently " << i << std::endl
         //         << "z's goalRow (z-1/n) is " << (z-1)/n << std::endl
         //         << "z's goalColumn (z-1%n) is " << (z-1)%n << std::endl;

        if (z == 0)
            continue;

        if (z != (i+1))                                                         // ...if the current tile is out of place...
        {
            manhattan += ( abs( (i/n)-((z-1)/n) ) + abs( (i%n)-((z-1)%n) ) );   // ...determine its distance from its goal position
        }                                                                       // and add it to the running total.
   
       // std::cout << "Current Manhattan value is: " << manhattan << std::endl << std::endl;
    }


    // FIXME: Test cout
    //std::cout << "Total Manhattan distance is: " << manhattan << std::endl;

    return manhattan;
}


std::string Grid::getid() const
{
    return id;
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
        std::vector< std::vector<unsigned> > up = data;              // Make a copy of the grid
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
        std::vector< std::vector<unsigned> > down = data;            // Make a copy of the grid
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
        std::vector< std::vector<unsigned> > left = data;            // Make a copy of the grid
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
    if ( blankCol < (n-1) )
    {
        std::vector< std::vector<unsigned> > right = data;               // Make a copy of the grid
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


void Grid::serialize()
{
    std::ostringstream ss;

    for (unsigned i = 0; i < data.size(); ++i)
    {
        for (unsigned j = 0; j < data.size(); ++j)
        {
            ss << data[i][j];
        }
    }

    id = ss.str();
}
