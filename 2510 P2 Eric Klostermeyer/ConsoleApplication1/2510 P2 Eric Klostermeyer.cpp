// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

#include "Stack.h"
#include "Leaf.h"
#include "leafSym.h"

using namespace std;

bool isOperator(char cStr) {
	// Do we have an operator? Returns true if so.
	if (cStr == '+')      return true;
	else if (cStr == '-') return true;
	else if (cStr == '*') return true;
	else if (cStr == '/') return true;
	else if (cStr == '(') return true;
	else if (cStr == ')') return true;
	else				  return false;
}

string launch(std::string expression) {
	// Firstly, infix to postfix.
	// Seperate all of the terms by a space
	string spacedExp = "";
	for (unsigned i = 0; i < expression.length(); ++i) {
		if (isdigit(expression.at(i))) {
			while (!isOperator(expression.at(i))) { // Operator
				spacedExp += expression.at(i);
				i++;
			}
			spacedExp += " ";
			if (expression.at(i) != ' ') { // If not a space.
				spacedExp += expression.at(i);
				spacedExp += " ";
			}
		}
		else {
			spacedExp += expression.at(i);
			spacedExp += " ";
		}
	}
	// Second, do stack stuff. Y'know, like actually make it postfix now.
	Stack stack;
	cout << spacedExp << endl;
	expression = ""; // Hey, we can reuse this. Sweet!
	for (unsigned j = 0; j < spacedExp.length(); ++j) {
		if (spacedExp.at(j) == '(') {
			// push '(' to stack.
			stack.push('('); // we know this will be a left parenthesis
		}
		else if (isdigit(spacedExp.at(j))) {
			// while the next character is a digit
			expression += spacedExp.at(j);
		}
		else if (spacedExp.at(j) == ')') {
			// start popping from the stack
			while (stack.head != NULL) {
				if (stack.top() != '(') expression += stack.pop();
				else {
					stack.pop();
					break; // You can stop the pop.
				}
			}
		}
		else if (isOperator(spacedExp.at(j))) {
			// put operator to stack
			stack.push(spacedExp.at(j));
		}
		else if (spacedExp.at(j) == ' ') {
			// add a space
			expression += ' ';
		}
		else {} // skip spaces
	}
	while (stack.head != NULL) {
		// clear stack
		if (stack.top() != '(') expression += stack.pop();
		else stack.pop();
	}
	cout << expression << endl;
	delete stack.head; // we are done with the stack.
	
	// Here comes the binary tree...
	Leaf leaf; // This is actually the tree. It's just a big ol' set of leaves. Just in time for fall!
	for (int i = expression.length() - 1; i > -1; --i) {
		if (!isdigit(expression.at(i)) && expression.at(i) != ' ') {
			// if operator
			string str;
			str += expression.at(i);
			leaf.linkup(str);
			// now create node
		}
		else if (expression.at(i) != ' ' && expression.at(i) != NULL) {
			// if digit
			while (expression.at(i) != ' ' && expression.at(i) != NULL) {
				if (i != 0) --i;
				else break;
			}
			int k = 1;
			string strNum;
			while (expression.at(i + k) != ' ') { // go forward to grab digits
				strNum += expression.at(i + k);
				++k;
			}
			// now create node.
			leaf.linkup(strNum);
		}
		else {} // if space, then skip.
	}
	leaf.walk(leaf.root);
	return expression + " = " + leaf.root->lsym.data; // outputs the postfix and the answer
}


void io() {
	// Do io things here, mostly input.
	// Change "input.txt" to whatever text file you are using.
	ifstream input;
	string inputArray[1000];
	int i = 0;
	input.open("input.txt");
	while (!input.eof()) {
		getline(input, inputArray[i]);
		i++;
	}
	input.close();

	// Infix to Postfix, trees, and math beyond this point.
	for (int j = 0; j < i; j++) {
		cout << inputArray[j] << endl;
		inputArray[j] += " = " + launch(inputArray[j]);
	}

	// output all of the hard work done
	ofstream output;
	output.open("output.txt");
	for (int k = 0; k < i; k++) {
		output << inputArray[k] << endl;
	}
	output.close(); // We're done.
}

int main()
{
	io(); // Main pretty much just sends this off. Yup.
	return 0;
}

