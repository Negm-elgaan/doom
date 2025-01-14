#pragma once
#include <iostream>

using namespace std;

class BTree
{
	private:
		int _MaxNumOfKeys = 0;
	public:

		static class Node
		{
			private:

				const int NumOfKeysInNode = 0;
				int* ptr;
				Node* Left;
				Node* Right;
				Node* Prev;
			
			public:

				Node(int Number) : NumOfKeysInNode(Number)
				{
					ptr = new int[NumOfKeysInNode];
				}
		};

		BTree()
		{
			cout << "\nEnter Max Number of Keys in a Node:\n";
			cin >> _MaxNumOfKeys;
		}

		BTree(int Number)
		{
			_MaxNumOfKeys = Number;
		}

};

