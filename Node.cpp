#include "Node.h"

// This constructor is intended for the root node of the search graph. g_value is set to zeor, because no
// edge traversals have been performed yet.
Node::Node(Grid g)
{
    this->parent = NULL;
    this->children = new std::vector<Node*>;
    
    Node *a = NULL, *b = NULL, *c = NULL, *d = NULL;

    children->push_back(a);
    children->push_back(b);
    children->push_back(c);
    children->push_back(d);
    
    this->grid = g;
    this->g_value = 0;
}


// This constructor is intended for the creation of child nodes. Since the cost of a move in a sliding tile
// is 1, the g_value of the child is always +1 of its parent.
Node::Node(Node* parent, Grid g)
{
    this->parent = parent;
    this->children = new std::vector<Node*>;
    this->grid = g;
    this->g_value = this->parent->g_value()+1;
}


Node* Node::parent() const
{
    return parent;
}


int Node::g_value() const
{
    return g_value;
}


int Node::fitness() const
{
    return ( g_value + grid.h_value() ); // FIXME Grid needs an h_value retrieval method defined
}


void Node::expand() const
{
    std::vector<Grid> temp = grid.expand();                  // Capture the output of Grid's expand().

    for (unsigned i = 0; i < temp.size(); ++i)               // Then, for all of the Node pointers in the children vector...
    {
        children->at(i) = new Node( this, temp.at(i) );      // ...create a new child Node using one of the moved Grids.
    }
}
