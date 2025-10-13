#pragma once
#include <iostream>

class clsTrie
{
	class Node;

	Node* _Root;

	public:

		clsTrie();

		void Insert(std::string s);

		bool Search(std::string s);

		bool Delete(std::string s);
};
