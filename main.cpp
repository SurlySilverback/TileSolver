#include <iostream>
#include <vector>
#include <string>
#include "Grid.h"

int main()
{
    int n = 0, algorithm = 0, makeGrid = 0;

    std::cout << "N-Tile Sliding Puzzle Solver" << std::endl
              << "============================" << std::endl << std::endl

              << "Choose a dimension n for the grid (n-by-n grid): ";

    std::cin >> n;

    std::cout << std::endl
              << "Choose a search algorithm to use:" << std::endl
              << "Enter '1' for Uniform Cost Search" << std::endl
              << "Enter '2' for A* with Misplaced Tile heuristic" << std::endl
              << "Enter '3' for A* with Manhattan Distance heuristic" << std::endl << std::endl;

    std::cin >> algorithm;

    std::cout << std::endl
              << "Would you like to enter a custom grid?" << std::endl
              << "Enter '1' for yes" << std::endl
              << "Enter '0' for no" << std::endl << std::endl;

    std::cin >> makeGrid;
    std::cin.ignore();

    std::cout << std::endl << std::endl;


    std::vector< std::vector<int> > V2(n, std::vector<int>(n,0) );
    int zeroRow = 0, zeroCol = 0;


    // This block prompts the user to enter a custom tile grid
    if (makeGrid)
    {
        std::cout << "Please enter the tile positions. Enter a 0 for the blank tile." << std::endl << std::endl;
        for (unsigned i = 0; i < n; ++i)
        {
	        for (unsigned j = 0; j < n; ++j)
            {
                std::cout << "Tile at position R" << i << ",C" << j << " : ";
                std::cin >> V2[i][j];

                // Capture the blank tile position to pass to grid constructor
                if(V2[i][j] == 0)
                {
                    zeroRow = i;
                    zeroCol = j;
                }

                //std::cout << std::endl;
	        }
        }
    }

    std::vector< std::vector<int> > V2prime = V2;

    Grid g(V2, zeroRow, zeroCol);

    g.print();

    std::cout << std::endl << g.solved() << std::endl << std::endl;

    g.expand();

    if (V2 == V2prime)
    {
        std::cout << "V2prime equals V2" <<std::endl;
    }

    // Construct problem using user-entered parameters

    return 0;
}
