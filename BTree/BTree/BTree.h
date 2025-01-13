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

				int NumOfKeysInNode = 0;
				int* ptr;
				Node* Left;
				Node* Right;
			
			public:

				Node()
				{
					cin >> NumOfKeysInNode;
					ptr = new int[NumOfKeysInNode];
				}

				Node(int Number)
				{
					NumOfKeysInNode = Number;
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

