#ifndef GRAPHSEARCH_H
#define GRAPHSEARCH_H

#include "Node.h"
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack> // FIXME New stuff

class GraphSearch
{
    public:
        GraphSearch(Grid g, int heur);  // Constructor
        
        void Search();                 // Main driver function of GraphSearch.

        bool Solved() const;            // Returns a pointer to the Node at the top of the frontier if that
                                        // contains a solved Grid.
        
        void Expand(Node top);          // Calls the Expand() function of the Node at the top of the frontier.

        void printSolution();           // Prints the path in solution_path

    private:
        Node root;                                                                  // Root of the graph
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;  // Frontier of the search space
        std::map<std::string, int> explored_map;                                    // Map of the explored set
        std::map<std::string, int> visited_map; 
        Node* solution;
        //std::stack<Node> solution_path; //FIXME New stuff
};

#endif
