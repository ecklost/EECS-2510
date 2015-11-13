#include "stdafx.h"
#include "Leaf.h"
#include "leafSym.h"
#include <string>

using namespace std;

void Leaf::linkup(std::string data)
{
	// Creates the tree. From the top-down.
	Node *node = new Node;
	node->lsym.data = data;
	node->lChild = NULL;
	node->rChild = NULL;

	if (root == NULL) {
		root = node; // set root data
		op = node;
		root->parent = NULL;
	}
	else if (!isdigit(node->lsym.data.at(0))) {
		// if operator
		if (root->rChild == NULL) {
			// start on right
			root->rChild = node;
			node->parent = root;
			op = node;
		}
		else if (op->rChild == NULL) {
			// another op
			op->rChild = node;
			node->parent = op;
			op = node;
		}
		else if (op->lChild == NULL) {
			// go left
			op->lChild = node;
			node->parent = op;
			op = node;
		}
		else {
			// start left part of tree
			root->lChild = node;
			node->parent = root;
			op = node;
		}
	}
	else {
		if (op->rChild == NULL)
		{  // right child first
			op->rChild = node;
			node->parent = op;
			op = node->parent;
		}
		else if (op->lChild == NULL) { // left child next
			op->lChild = node;
			node->parent = op;
			op = node->parent;
		}
		if (op->lChild != NULL && op->rChild != NULL) { // refer up nodes
			while (op->parent != NULL && op->lChild != NULL)
				op = op->parent;
		}
	}
}

void Leaf::refer(Node *node) {
	// Goes up a node. It handles all tree sizes, big and small.
	if (node->rChild == NULL || node->rChild->rChild == NULL ||isdigit(node->rChild->rChild->lsym.data.at(0))) op = node;
	else refer(node->rChild);
}

void Leaf::walk(Node *node) {
	if (node != NULL) { // walk the tree
		walk(node->lChild);
		walk(node->rChild);
		if (divideByZero) {
			root->lsym.data = "CANNOT DIVIDE BY ZERO."; // we can't divide by zero. That would be silly.
			return;
		}
		if (node->rChild != NULL && node->lChild != NULL) doMaths(node, node->lChild, node->rChild);
	}
}

void Leaf::doMaths(Node * node, Node * left, Node * right) {
	// in this case, node will be the operand

	int num1 = std::stoi(left->lsym.data);
	int num2 = std::stoi(right->lsym.data);
	if (node->lsym.data == "+") node->lsym.data = std::to_string((num1 + num2)); // add them
	else if (node->lsym.data == "-") node->lsym.data = std::to_string((num1 - num2)); // subtract them
	else if (node->lsym.data == "*") node->lsym.data = std::to_string((num1 * num2)); // "Go forth and multiply."
	else if (num2 == 0) { //output divide by zero error
		root->lsym.data = "CANNOT DIVIDE BY ZERO.";
		divideByZero = true;
		return; 
	} 
	else if (node->lsym.data == "/") node->lsym.data = std::to_string((num1 / num2));

	delete left; // we're done with these fellas
	delete right;
	node->lChild = nullptr;
	node->rChild = nullptr;
	if (!(root->rChild == NULL && root->lChild == NULL)) { // keep going if we haven't reached the end yet
		if (!isdigit(root->lChild->lsym.data.at(0))) refer(root->lChild);
		else if (isdigit(root->lChild->lsym.data.at(0))) refer(root->rChild);
		else if (!isdigit(root->rChild->lsym.data.at(0))) refer(root->rChild);
	}
	else return;
}

Leaf::Leaf()
{
}


Leaf::~Leaf()
{
}
