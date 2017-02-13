#ifndef GRAPHSEARCH_H
#define GRAPHSEARCH_H

#include "Node.h"
#include <vector>
#include <queue>

class GraphSearch
{
    public:
        GraphSearch(Grid g, int heur);  // Constructor
        
        Node* Search();                 // Main driver function of GraphSearch.

        Node* Solved() const;           // Returns a pointer to the Node at the top of the frontier if that
                                        // contains a solved Grid.
        
        void Expand();                  // Calls the Expand() function of the Node at the top of the frontier.

    private:
        Node* root;                                                                     // Root of the graph
        std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*> > frontier;  // Frontier of the search space
	    // hash map containing the explored set
};

#endif
