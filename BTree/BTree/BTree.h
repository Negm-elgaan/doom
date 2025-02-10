#pragma once
#include <iostream>

using namespace std;

class BTree
{
	private:
		int _MaxNumOfKeys = 0;
		int _NumOfNodes = 0;
		bool _FirstFillPNode = true;

		void _InsertAtParentNode(int Data)
		{
			
		}

	public:

		static class Node
		{
			private:

				const int NumOfKeysInNode = 0;
				int* ptr;
				int Arr[1];
				int CurrentNumOfElementsInNode = 0;
				Node* Left;
				Node* Right;
				Node* Prev;


				int _BinarySearch(int Data , int Start , int End)
				{
					int mid = Start + (End - Start) / 2;

					if (End >= CurrentNumOfElementsInNode || Start < 0)
						return -1;

					if (ptr[mid] == Data)
						return mid;

					if (ptr[mid] > Data)
						return _BinarySearch(Data , Start , mid - 1);

					if (ptr[mid] < Data)
						return _BinarySearch(Data , mid + 1 , End);
					
				}

				void _Shift(int pos)
				{
					for (int i = pos; i < CurrentNumOfElementsInNode; i++)
					{

					}
				}

			public:

				Node(int Number) : NumOfKeysInNode(Number)
				{
					ptr = new int[NumOfKeysInNode];
					Arr[NumOfKeysInNode];
				}

				bool IsFull()
				{
					return CurrentNumOfElementsInNode == NumOfKeysInNode;
				}

				void Insert(int Data)
				{

					if (CurrentNumOfElementsInNode == NumOfKeysInNode)
						return;

					if (CurrentNumOfElementsInNode == 0)
					{
						Arr[0] = Data;
						ptr[0] = Data;

						CurrentNumOfElementsInNode++;

						return;
					}

					for (int i = 0; i < CurrentNumOfElementsInNode; i++)
					{
						if (Data < ptr[i])
						{
							_Shift(i);
							ptr[i] = Data;
							return;
						}
					}

					return;
				}

		};

		Node* ParentNode = NULL;

		BTree()
		{
			cout << "\nEnter Max Number of Keys in a Node:\n";
			cin >> _MaxNumOfKeys;
		}

		BTree(int Number)
		{
			_MaxNumOfKeys = Number;
		}

		void Insert(int Data)
		{
			if (ParentNode == NULL /* || !ParentNode->IsFull()*/)
			{
				_InsertAtParentNode(Data);

				return;
			}

		}

};

