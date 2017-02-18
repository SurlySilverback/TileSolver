#include "GraphSearch.h"

GraphSearch::GraphSearch(Grid g, int heur) : root(g, heur), frontier(), solution(NULL)
{
    frontier.push(root);
    visited_map.emplace(root.getid(), 1);
    //solution_path.push(root); // FIXME New stuff
}


// This is the primary driver function for GraphSearch.
void GraphSearch::Search()
{
    while ( !frontier.empty() || 
            frontier.top().Solved() == false )
    {
        if ( explored_map.count(frontier.top().getid() ) > 0 )     // If top of frontier IS in explored set, do not push into PQ.
        {                                                          // Instead pop the top Node from the frontier.
		//std::cout << "Getting rid of ";
		//std::cout << std::endl;
		//std::cout << frontier.top()->;
            frontier.pop();
        }

        else
        {
		// std::cout << "Expanding " << std::endl << frontier.top();
		// TODO: fix this. using dynamic memory, there could be problems. 
		// perhaps make a new local node object to hold onto top's value for a bit?
		// jsut for deleting purposes
            Node top = frontier.top();
            
            if ( frontier.top().Solved() )
            {
                std::cout << "Solution depth is " << frontier.top().G() << std::endl << std::endl;
            }

            //std::cout << "Top of priQ is:" << std::endl << std::endl;
            //top.print();
            //std::cout << std::endl << std::endl;
            
            frontier.pop();
            this->Expand(top);                             // Call GraphSearch.Expand() to add top's Children to priQ
            explored_map.emplace( top.getid(), 1 );

            //solution_path.push(top); // FIXME New stuff
        }
    }

    if ( frontier.empty() ) {                   // If frontier is empty, return NULL. Could not find a solution.
        std::cout << "Frontier is empty" << std::endl;
        return;
    }
    else
    {
        std::cout << "Solved!" << std::endl;
        return;
    }
}


// Solved() checks the Node at the top of the frontier. If that Node contains a tolved Grid, Solved() returns
// a pointer to that Node. If the Node does not contain a solved Grid, Solved() returns NULL.
bool GraphSearch::Solved() const
{
    if ( frontier.top().Solved() )
        return true;

    return false;
}


void GraphSearch::Expand(Node top)
{
    std::vector<Node> temp = top.Expand();                      // Expand the Node and prepare to examine its children.

    for (unsigned i = 0; i < temp.size(); ++i)                   // For all children produced by toad's expansion...
    {
	    //std::cout << temp.at(i) << std::endl;
        if ( visited_map.count(temp.at(i).getid()) == 0 )        // ...if child is NOT in the visited_map...
        {
            visited_map.emplace( temp.at(i).getid(), 1 );        // ...insert child into the visited set...
            frontier.push( temp.at(i) );                         // ...and push it into the frontier.
        }
    }
}


// FIXME New stuff
void GraphSearch::printSolution()
{
    while (solution != NULL)
    {
        solution->print();
        std::cout << std::endl << std::endl;
        solution = solution->Parent();
    }
}
