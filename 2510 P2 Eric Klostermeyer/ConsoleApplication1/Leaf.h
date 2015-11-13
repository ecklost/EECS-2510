#pragma once

#include <string>
#include "leafSym.h"

class Leaf
{
	// Leaf is a bit of a misnomer. This creates the tree in reality, but any instantiation of this could be a 'leaf'.
public:
	struct Node {
		leafSym lsym; // Sort of like the symbol from the first project, but more leafy.
		Node *lChild; // the left child.
		Node *rChild; // the right child.
		Node *parent; // refer to an op above
	};
	Node *root; // the root of all evi- erm, trees.
	Node *op; // operator leaf
	bool divideByZero = false; // if dividing by zero

	void linkup(std::string data); // create tree
	void refer(Node *node); // get next operator
	void walk(Node *node); // walk the tree (how can you walk a tree anyway?)
	void doMaths(Node *operand, Node *left, Node *right); // do maths. 
	Leaf();
	~Leaf();
};

