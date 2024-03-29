#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "Grid.h"
#include "Node.h"
#include "GraphSearch.h"

int main()
{
    int algorithm = 0, makeGrid = 0;
    unsigned n = 0;

    std::cout << "N-Tile Sliding Puzzle Solver" << std::endl
              << "============================" << std::endl << std::endl

              << "Choose a dimension n for the grid (n-by-n grid): ";

    std::cin >> n;

    std::cout << std::endl
              << "Choose a search algorithm to use:" << std::endl
              << "Enter '0' for Uniform Cost Search" << std::endl
              << "Enter '1' for A* with Misplaced Tile heuristic" << std::endl
              << "Enter '2' for A* with Manhattan Distance heuristic" << std::endl << std::endl;

    std::cin >> algorithm;

    std::cout << std::endl
              << "Would you like to enter a custom grid?" << std::endl
              << "Enter '1' for yes" << std::endl
              << "Enter '0' for no" << std::endl << std::endl;

    std::cin >> makeGrid;
    std::cin.ignore();

    std::cout << std::endl << std::endl;


    std::vector< std::vector<unsigned> > V2(n, std::vector<unsigned>(n,0) );
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
	        }
        }
    }

    Grid g(V2, zeroRow, zeroCol);
    
    GraphSearch gs(g, algorithm);

    std::cout << "gs.Search() results:" << std::endl;
    
    gs.Search();
    gs.printSolution();

    // Messing with Priority Queue
    /*
    std::cout << "Messing with Priority Queue" << std::endl;
    
    int A[] = {2, 5, 7, 12, 15, 26, 37};

    std::priority_queue<int, std::vector<int>, std::greater<int> > test (A, A+6);

    std::cout << "The top of the test queue is: " << test.top() << std::endl;
*/

    //g.print();

    //g.misplaced_tile();
    //g.manhattan();


    // Test cout: prints "1" if input Grid is in solved state
    //std::cout << std::endl <<std::endl << g.solved() << std::endl << std::endl;

/*
    // Testing vector pointers
    std::vector<int> *v = new std::vector<int>;

    for (unsigned i = 0; i < 10 ; ++i)
    {
        std::cout << "Pushing back " << i << " into the vector..." << std::endl;
        v->push_back(i);
    }

    std::cout << "The contents of the vector (via pointer) are:" << std::endl;
    for (unsigned j = 0; j < v->size() ; ++j)
    {
        std::cout << v->at(j) << std::endl;
    }
*/

    // Construct problem using user-entered parameters

    return 0;
}
