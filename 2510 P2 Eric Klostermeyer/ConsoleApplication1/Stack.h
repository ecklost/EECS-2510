#pragma once

#include "stdafx.h"
#include <string>
#include "stackSym.h"

class Stack {
public: // Code for the stack. Nothing beyond that. Has your standard push, pop, and top.
	struct Node {
		stackSym sym;
		Node *link = NULL;
	};
	void push(char id);
	char pop();
	char top();
	Node *head;

	Stack();
	~Stack();
};