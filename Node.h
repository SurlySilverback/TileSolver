#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>


class Node
{
    public:
        Node();                     // Default constructor (used for root node).
        Node(Node*)                 // Constructor with Node* pointing back to its parent.

        Node* parent() const;       // Returns the node's parent.
        int fitness() const;        // Returns the sum (g_value + h_value).

        void NewChild();            // Calls Grid's expand() function to make new moves, assigns those
                                    // moves to new Nodes, and pushes those Nodes into the children vector.
     
    private:
        Node* parent;               // Pointer to parent.
        vector<Node*> children;     // Pointer(s) to children.
        Grid grid;                  // Grid containing current game state.
        
        int g_value, h_value;       // These two integers are used to determine the Node's
                                    // order in the GraphSearch's priority queue.
};

#endif
