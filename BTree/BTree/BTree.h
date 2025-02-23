#pragma once
#include <iostream>
#include <vector>

using namespace std;

class BTree
{
	private:

		class Node;

		int _MaxNumOfKeys = 0;
		int _NumOfNodes = 0;
		bool _FirstFillPNode = true;


		/*not done*/bool _InsertAtParentNode(int Data)
		{

			if (!ParentNode->IsFull())
			{
				int pos = ParentNode->_BinarySearch(Data, 0, ParentNode->GetCurrentNumberElementsInNode());

				ParentNode->_Shift(pos);

				if (ParentNode->SetItem(pos, Data))
				{
					return true;
				}

				return false;
			}

			/*if (ParentNode->IsFull())
			{
				bool x = true;

				int counter = 1;

				for (int i = 0; i < ParentNode->CurrentNumOfElementsInNode / 2; i++)
				{
					ParentNode->Children[0]->ptr[i] = ParentNode->ptr[i];
				}

				for (int i = (ParentNode->CurrentNumOfElementsInNode / 2) + 1; i < ParentNode->CurrentNumOfElementsInNode; i++)
				{
					ParentNode->Children[1]->ptr[i] = ParentNode->ptr[i];
				}

				ParentNode->ptr[0] = ParentNode->ptr[ParentNode->CurrentNumOfElementsInNode / 2];

				ParentNode->Flush();

				return true;
			}*/

			bool x = true;

			int counter = 1;

			for (int i = 0; i < ParentNode->CurrentNumOfElementsInNode / 2; i++)
			{
				ParentNode->Children[0]->ptr[i] = ParentNode->ptr[i];
			}

			for (int i = (ParentNode->CurrentNumOfElementsInNode / 2) + 1; i < ParentNode->CurrentNumOfElementsInNode; i++)
			{
				ParentNode->Children[1]->ptr[i] = ParentNode->ptr[i];
			}

			ParentNode->ptr[0] = ParentNode->ptr[ParentNode->CurrentNumOfElementsInNode / 2];

			ParentNode->Flush();

			return true;

			//if (!ParentNode->IsChildrenEmpty())
			//{

			//	return true;
			//}
			////if parent is full but right and left are not


			//return false;
		}

	public:

		static class Node
		{
			private:

				const int NumOfKeysInNode = 0;
				int* ptr;
				int Arr[1];
				int CurrentNumOfElementsInNode = 0;
				vector <Node*> VChildren;
				Node** Children;
				Node* Prev;


				

			public:

				

				Node(int Number) : NumOfKeysInNode(Number)
				{
					ptr = new int[NumOfKeysInNode + 1];
					Arr[NumOfKeysInNode + 1];
					Children = new Node* [NumOfKeysInNode];
				}

				bool IsFull()
				{
					return CurrentNumOfElementsInNode == NumOfKeysInNode + 1;
				}

				bool IsChildrenEmpty()
				{
					return Children == NULL;
				}

				bool Flush()
				{
					int x = ptr[0];
					
					delete[] ptr;

					ptr = new int[NumOfKeysInNode + 1];
					ptr[0] = x;
				}

				/*not done*/void Insert(int Data)
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

				int _BinarySearch(int Data, int Start, int End)
				{
					int mid = Start + (End - Start) / 2;

					if (End < Start)
					{
						if (End < 0)
							return 0;

						if (Start > CurrentNumOfElementsInNode)
							return CurrentNumOfElementsInNode + 1;
					}

					if (ptr[mid] == Data)
						return mid;

					if (ptr[mid] > Data)
						return _BinarySearch(Data, Start, mid - 1);

					if (ptr[mid] < Data)
						return _BinarySearch(Data, mid + 1, End);

				}

				void _Shift(int pos)
				{
					for (int i = CurrentNumOfElementsInNode - 1; i >= pos; i--)
					{
						ptr[i + 1] = ptr[i];
					}

					return;
				}

				int GetCurrentNumberElementsInNode()
				{
					return CurrentNumOfElementsInNode;
				}

				/*not done*/bool SetItem(int pos, int Data)
				{
					if (pos > NumOfKeysInNode + 1)
						return false;

					ptr[pos] = Data;

					return true;
				}

				/*bool IsRightEmpty()
				{
					return Right == NULL;
				}

				bool IsLeftEmpty()
				{
					return Left == NULL;
				}*/

				friend class BTree;

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

			if (ParentNode == NULL)
			{
				ParentNode = new Node(_MaxNumOfKeys);

				_InsertAtParentNode(Data);

				return;
			}

			if (ParentNode->IsChildrenEmpty() && !ParentNode->IsFull())
			{
				_InsertAtParentNode(Data);

				return;
			}



		}

		bool IsEmpty()
		{
			return ParentNode == NULL;
		}
};


