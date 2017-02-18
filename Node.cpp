#include "Node.h"

// This constructor is intended for the root node of the search graph. g_value is set to zeor, because no
// edge traversals have been performed yet.
Node::Node(Grid g, int heur) : parent(NULL), children(), grid(g), heuristic(heur), g_value(0), h_value(-1), ptToCostFunction(NULL)
{
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
Node::Node(Node* nodeParent, Grid g, int heur) : parent(nodeParent), children(), grid(g), heuristic(heur), g_value(nodeParent->g_value+1), h_value(-1), ptToCostFunction(NULL)
{
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
/*
    std::cout << "I am a new child node. My grid is:" << std::endl << std::endl;
    grid.print();
    std::cout << std::endl << std::endl;*/
}
/*
Node::~Node() {
	for (unsigned i = 0; i < children.size(); ++i) {
		children[i]->~Node();
		delete children[i];
	}
}*/


// Comparison operator to allow the frontier (implemented as a priority queue) to compare Nodes
// based on their reported costs.
bool Node::operator <(const Node &rhs)
{
    return  Cost() < rhs.Cost();
}


bool Node::operator <(const Node &rhs) const
{
    return ( Cost() < rhs.Cost() );
}


bool Node::operator >(const Node &rhs)
{
    return  Cost() > rhs.Cost();
}


bool Node::operator >(const Node &rhs) const
{
    return  Cost() > rhs.Cost();
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


std::string Node::getid() const
{
    return grid.getid();
}


bool Node::Solved() const
{
    if ( grid.solved() )
        return true;

    return false;
}


void Node::print()
{
    grid.print();
}


std::vector<Node> Node::Expand()
{
    std::vector<Grid> temp = grid.expand();                             // Capture the output of Grid's expand().

    for (unsigned i = 0; i < temp.size(); ++i)                          // Then, for all of the Node pointers in the children vector...
    {        
        Node newChild(this, temp.at(i), this->heuristic);
        children.push_back(newChild);                                   // ...and push it into the vector of this Node's children.
    }

    return children;
}


std::ostream& operator <<(std::ostream& out, Node& n)
{
   n.grid.print();
   return out;
}


