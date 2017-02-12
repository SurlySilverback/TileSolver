#include "Node.h"

// This constructor is intended for the root node of the search graph. g_value is set to zeor, because no
// edge traversals have been performed yet.
Node::Node(Grid g, int heur) : parent(NULL), children(), grid(g), heuristic(heur), g_value(0), h_value(-1), prToCostFunction(NULL)
{
    // Initializethe vector of Node pointers to children
    this->children = new std::vector<Node*>;
    
    Node *a = NULL, *b = NULL, *c = NULL, *d = NULL;

    children->push_back(a);
    children->push_back(b);
    children->push_back(c);
    children->push_back(d);

    // These if-elses assign the heuristic function pointer to the correct heuristic function in the Grid class
    // based on the user's selection.
    if (heur == 0)
        ptToCostFunction = &Grid::uniform_cost;
    else if (heur == 1)
        ptToCostFunction = &Grid::misplaced_tile;
    else if (heur == 2)
        ptToCostFunction = &Grid::manhattan;

    // Call to Grid's heuristic.
    h_value = grid.h(ptToCostFunction);
}


// This constructor is intended for the creation of child nodes. Since the cost of a move in a sliding tile
// is 1, the g_value of the child is always +1 of its parent.
Node::Node(Node* nodeParent, Grid g, int heur) : parent(nodeParent), children(), grid(g), heuristic(heur), g_value(nodeParent->g_value+1), h_value(-1), prToCostFunction(NULL)
{
    this->children = new std::vector<Node*>;

    // These if-elses assign the heuristic function pointer to the correct heuristic function in the Grid class
    // based on the user's selection.
    if (heur == 0)
        ptToCostFunction = &Grid::uniform_cost;
    else if (heur == 1)
        ptToCostFunction = &Grid::misplaced_tile;
    else if (heur == 2)
        ptToCostFunction = &Grid::manhattan;

    // Call to Grid's heuristic.
    h_value = grid.h(ptToCostFunction);
}


Node* Node::Parent() const
{
    return parent;
}


int Node::G() const
{
    return g_value;
}


int Node::H() const
{
    return h_value;
}


int Node::Cost() const
{
    return ( g_value + h_value );
}


void Node::Expand() const
{
    std::vector<Grid> temp = grid.expand();                  // Capture the output of Grid's expand().

    for (unsigned i = 0; i < temp.size(); ++i)               // Then, for all of the Node pointers in the children vector...
    {
        children->at(i) = new Node( this, temp.at(i) );      // ...create a new child Node using one of the moved Grids.
    }
}
