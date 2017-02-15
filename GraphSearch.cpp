#include "GraphSearch.h"

GraphSearch::GraphSearch(Grid g, int heur) : root(g, heur), frontier()
{
    frontier.push(root);
    visited_map.emplace(root.getid(), 1);
}


// This is the primary driver function for GraphSearch.
Node* GraphSearch::Search()
{
    Node top(Grid(std::vector<std::vector<unsigned>>(), 0, 0), 0);
    while ( !frontier.empty() && 
            (top = frontier.top()).Solved() == NULL )
    {
        if ( explored_map.count(frontier.top().getid() ) > 0 )     // If top of frontier IS in explored set, do not push into PQ.
        {                                                          // Instead pop the top Node from the frontier.
            frontier.pop();
        }

        else
        {
            top = frontier.top();
            frontier.pop();
            this->Expand(top);                             // Call GraphSearch.Expand() to add top's Children to priQ
            explored_map.emplace( top.getid(), 1 );
        }
    }

    if ( frontier.empty() ) {                   // If frontier is empty, return NULL. Could not find a solution.
        std::cout << "FUCK" << std::endl;
        return NULL;
    }
    else
    {
        std::cout << "SHIT" << std::endl;
        return this->Solved();
    }

    // 1. Is frontier empty? If yes, done. If no, go to 2.
    // 2. Is frontier.top() the goal? If yes, done! If no, go to 3.
    // 3. Is frontier.top() in the explored_map? If yes, do not expand, just pop(). If no, go to 4.
    // 4. Add frontier.top() to explored_map. Go to 5.
    // 5. frontier.top()->Expand();
    // 6. for all children()
    //    {
    //      if (child is in Visited)
    //          delete child;
    //
    //      else 
    //      {
    //          frontier.push(child);
    //          visited.push(child);
    //      }
    //    }
    // 
    //    Go to 1.
}


// Solved() checks the Node at the top of the frontier. If that Node contains a tolved Grid, Solved() returns
// a pointer to that Node. If the Node does not contain a solved Grid, Solved() returns NULL.
Node* GraphSearch::Solved() const 
{
    Node top = frontier.top();
    return ( top.Solved() );
}


void GraphSearch::Expand(Node& toad)
{
    std::vector<Node> temp = toad.Expand();               // Expand the Node and prepare to examine its children.

    for (unsigned i = 0; i < temp.size(); ++i)                   // For all children produced by toad's expansion...
    {
        if ( visited_map.count(temp.at(i).getid()) == 0 )        // ...if child is NOT in the visited_map...
        {
            visited_map.emplace( temp.at(i).getid(), 1 );        // ...insert child into the visited set...
            frontier.push( temp.at(i) );                         // ...and push it into the frontier.
        }
    }
}
