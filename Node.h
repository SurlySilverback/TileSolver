#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include "Grid.h"

typedef int (Grid::*costFunc_t)() const;

class Node
{
    public:
        Node(Grid g, int heuristic);                // Constructor without Node pointer (used for root node).
        Node(Node* parent, Grid g, int heuristic);  // Constructor with Node* pointing back to its parent.

        Node* Parent() const;           // Returns the node's parent.
        int G() const;                  // Returns the node's g_value.
        int H() const;                  // Returns the node's h_value.
        int Cost() const;               // Returns the sum (g_value + h_value).

        void Expand() const;            // Calls Grid's expand() function to make new moves, assigns those
                                        // moves to new Nodes, and pushes those Nodes into the children vector.
     
    private:
        Node* parent;                   // Pointer to parent.
        std::vector<Node*> *children;   // Vector of pointer(s) to children.
        Grid grid;                      // Grid containing current game state.
        
        int heuristic;                  // Holds the user's selection for the seach heuristic:
                                        // 0 = uniform cost, 1 = misplaced tile, 2 = Manhattan distance.

        int g_value, h_value;           // These two integers are used to determine the Node's
                                        // order in the GraphSearch's priority queue.

        costFunc_t ptToCostFunction;    // Function pointer to the user-selected heuristic.
};

#endif
