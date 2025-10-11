#pragma once
#include <iostream>

class clsTrie
{
	class Node;

	Node* _Root;

	public:

		clsTrie();

		void Insert(std::string s);

		void Search(std::string s);
};
