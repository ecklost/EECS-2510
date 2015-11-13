#pragma once

#include <iostream>
#include <fstream>
#include <string>
class leafSym
{
public: // Holds data for the tree and its nodes
	std::string data;
	std::string output();

	leafSym();
	leafSym(std::string data);
	~leafSym();
};

