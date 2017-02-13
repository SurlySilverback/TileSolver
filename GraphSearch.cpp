#include "GraphSearch.h"

GraphSearch::GraphSearch(Grid g, int heur) : root(NULL), frontier()
{
   this->root = new Node(g, heur);

   frontier.push(root);
}


// This is the primary driver function for GraphSearch.
Node* GraphSearch::Search()
{
    // 1. Check if frontier is empty: If yes, return failure. If no, go to 2.
    // 2. Capture frontier.top()->Expand() in a local vector
    // 3. Add frontier.top() to Explored Set
    // 4. Check the expansion. For each child, if it is NOT in the explored set, frontier.push()
    // 5. Pop the top of the frontier off and go to 1.
}


// Solved() checks the Node at the top of the frontier. If that Node contains a solved Grid, Solved() returns
// a pointer to that Node. If the Node does not contain a solved Grid, Solved() returns NULL.
Node* GraphSearch::Solved() const
{
    return ( frontier.top()->Solved() );
}


void GraphSearch::Expand()
{
    std::vector<Node*> temp = frontier.top()->Expand();

    for (unsigned i = 0; i < temp.size(); ++i)
    {
        // FIXME if temp.at(i) is not in the expored set
        frontier.push(temp.at(i));
    }
}
