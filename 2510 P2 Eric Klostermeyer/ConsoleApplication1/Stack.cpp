#include "stdafx.h"
#include "Stack.h"
#include <string>
using namespace std;

// Stack for creating the postfix expression. Nothing much more than that.

Stack::Stack() {

}

void Stack::push(char id) {
	Node *node = new Node; // set data
	node->sym.id = id;

	if (head == NULL) {
		head = node;
	}
	else {
		node->link = head; // Point back to head
		head = node;	   // Current is now head.
	}
}

char Stack::pop() {
	Node *temp = new Node; // pop the stack
	char popId = head->sym.id;

	temp = head;
	head = head->link;
	temp->link = nullptr;
	temp = nullptr;
	delete temp;
	return popId; // add to output
}

char Stack::top() {
	return head->sym.id; // just peeking at the top
}


Stack::~Stack() {
	delete head;
};