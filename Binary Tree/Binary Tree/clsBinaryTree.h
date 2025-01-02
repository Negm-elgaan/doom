#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

template <class T> class clsBinaryTree
{
	private:
		static class Node
		{
			public:
				void* DataPtr;
				T Data;
				Node* Right;
				Node* Left;
				Node* Prev;
		};

		int _Size = 0;
		int _Levels = 0;
		int _LeftHeight = 0;
		int _RightHeight = 0;
		int _Height = 0;
		int _Temp = 0;
		vector <int> _SortedList;

		void _GetHeightLeft(Node* node)
		{
			if (node == NULL)
			{
				if (_Temp > _LeftHeight)
					_LeftHeight = _Temp;

				_Temp = 0;

				return;
			}
			_Temp++;

			_GetHeightLeft(node->Left);

			_Temp = 0;
		}

		void _GetHeightRight(Node* node)
		{
			if (node == NULL)
			{
				if (_Temp > _RightHeight)
					_RightHeight = _Temp;

				_Temp = 0;

				return;
			}
			_Temp++;

			_GetHeightRight(node->Right);

			_Temp = 0;
		}

		//void _ReBalance()
		//{
		//	Node* node = new Node();
		//	//cout << "size " << _SortedList.size() << endl;
		//	for (int i = 0; i < _SortedList.size(); i++)
		//	{
		//		node->Data = _SortedList[i];
		//		cout << node->Data << " ";
		//	}

		//	cout << endl;

		//	for (int i = 0; i <= _SortedList.size() ; i++)
		//	{
		//		//cout << _SortedList[i];
		//		//cout << (_SortedList.size() - i) / 2 << " ";
		//		//cout << node->Data << " ";

		//		if (i > (_SortedList.size() / 2 + 2))
		//			break;
		//		node->Data = _SortedList[(_SortedList.size() - i) / 2];
		//		//cout << node->Data << " ";
		//		Insert(node->Data);
		//		//PrintInOrder();
		//	}
		//	//cout << " 2nd ";
		//	for (int i = 0; i <= _SortedList.size(); i++)
		//	{
		//		//cout << _SortedList[i];
		//		//cout << node->Data << " ";
		//		//cout << (_SortedList.size() + i) / 2 << " ";
		//		if (i >( _SortedList.size() / 2) + 1)
		//			break;
		//		node->Data = _SortedList[(_SortedList.size() + i) / 2];
		//		//cout << node->Data << " ";
		//		Insert(node->Data);
		//	}
		//}

		void PrintHelperPre(Node* node)
		{
			if (node == NULL)
				return;

			cout << node->Data << " " ;
			PrintHelperPre(node->Left);
			/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
			// Print the data of the current node


			// Traverse the right subtree
			PrintHelperPre(node->Right);
			/*thread T2(&clsMap::PrintHelper, this, node->Right);
			T1.join();
			T2.join();*/
			//cout << endl;
		}

		void PrintHelperPost(Node* node)
		{
			if (node == NULL)
				return;


			// Traverse the left subtree
			PrintHelperPost(node->Left);
			/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
			// Print the data of the current node


			// Traverse the right subtree
			PrintHelperPost(node->Right);
			/*thread T2(&clsMap::PrintHelper, this, node->Right);
			T1.join();
			T2.join();*/

			cout << node->Data << " ";
		}

		void _GetIn(Node* node)
		{
			if (node == NULL)
				return;

			_GetIn(node->Left);

			_SortedList.push_back(node->Data);

			_GetIn(node->Right);
		}

		void _ClearHelper(Node* node)
		{
			if (node == NULL)
				return;

			_ClearHelper(node->Left);
			_ClearHelper(node->Right);

			delete node;
		}

		void PrintInHelper(Node* node)
		{
			if (node == NULL)
				return;

			// Traverse the left subtree
			PrintHelper(node->Left);

			// Print the data of the current node
			cout << node->Data << " ";

			// Traverse the right subtree
			PrintHelper(node->Right);
		}

		Node* _Search(T Data)
		{
			Node* node = ParentNode;

			if (node == NULL)
				return NULL;

			while (node != NULL)
			{
				if (node->Data == Data)
						return node;
				node->Data > Data ? node = node->Left : node = node->Right;
			}
			
			return NULL;
		}



		void DeleteHelper(Node* node)
		{
			if (node == NULL)
				return;

			// Recursively delete the left and right subtrees
			DeleteHelper(node->Left);
			DeleteHelper(node->Right);

			// Delete the current node
			delete node;
		}

		void _GetHeight(Node* node)
		{
			if (node == NULL)
			{
				if (_Temp > _Height)
					_Height = _Temp;

				_Temp = 0;

				return;
			}
			_Temp++;

			_GetHeight(node->Left);
			
			_GetHeight(node->Right);
		}

	public:
		
		clsBinaryTree::Node* ParentNode = NULL;
		clsBinaryTree::Node* Temp1 = ParentNode;

		clsBinaryTree()
		{
			_Size = 0;
			_Levels = 1;
			_Height = 0;
		}

		clsBinaryTree(int Size, int levels , int Height)
		{
			_Size = Size;
			_Levels = levels;
			_Height = Height;
			return;
		}

		void Insert(T Data)
		{
			bool x = true;

			

			if (ParentNode == NULL)
			{
				ParentNode = new Node();
				ParentNode->Data = Data;
				ParentNode->Left = NULL;
				ParentNode->Right = NULL;
				ParentNode->Prev = NULL;
				Temp1 = ParentNode;
				return;
			}

			if (ParentNode->Data == NULL && ParentNode != NULL)
			{
				ParentNode->Data = Data;
				ParentNode->Left = NULL;
				ParentNode->Right = NULL;
				ParentNode->Prev = NULL;
				Temp1 = ParentNode;
				return;
			}

			Node* TempNode = ParentNode;
			Node* NewNode = new Node();
			NewNode->Data = Data;
			//cout << NewNode->Data << " " << TempNode->Data << endl;
			while (x)
			{
				if (NewNode->Data == TempNode->Data)
				{
					cout << "Key already exists!\n";
					return;
				}
				NewNode->Data > TempNode->Data ? TempNode->Right == NULL ? x = false : TempNode = TempNode->Right : TempNode->Left == NULL ? x = false : TempNode = TempNode->Left;
			}

			NewNode->Data > TempNode->Data ? TempNode->Right = NewNode : TempNode->Left = NewNode;
			TempNode->Right == NULL ? TempNode->Left->Prev = TempNode : TempNode->Right->Prev = TempNode;
			_Size++;
			return;

			
		}

		void Print()
		{
			//PrintTreeStructure(ParentNode);
			//PrintHelper(ParentNode);
			PrintHelperPost(ParentNode);
			cout << endl;
			//PrintHelperPre(ParentNode);
		}

		int NumberOfNodes()
		{
			return _Size;
		}

		T search(T Data)
		{
			Node* node = _Search(Data);

			return node->Data;
		}

		bool Remove(T Data)
		{
			if (ParentNode == NULL)
				return false;

			Node* node = _Search(Data);
			
			if (node == NULL)
				return false;

			if (node->Right == NULL && node->Left == NULL)
			{
				node->Prev->Right == node ? node->Prev->Right = NULL : node->Prev->Left = NULL;
				delete node;
				_Size--;
				return true;
			}

			if (node->Right == NULL && node->Left != NULL)
			{
				node->Prev->Right == node ? node->Prev->Right = node->Left : node->Prev->Left = node->Left;
				delete node;
				_Size--;
				return true;
			}

			if (node->Right != NULL && node->Left == NULL)
			{
				node->Prev->Right == node ? node->Prev->Right = node->Right : node->Prev->Left = node->Right;
				delete node;
				_Size--;
				return true;
			}

			Node* Temp = node;
			node = node->Right;
			
			while (node->Left != NULL)
			{
				node = node->Left;
			}

			if (node->Right != NULL)
			{
				node->Prev->Left = node->Right;
				Temp->Data = node->Data;
			}

			else 
			{
				node->Prev->Left = NULL;
				Temp->Data = node->Data;
			}

			delete node;
			_Size--;
			return true;
		}

		int Height()
		{
			_GetHeight(ParentNode);
			return _Height;
		}

		/*void ReBalance()
		{
			cout << endl;
			_GetHeightLeft(ParentNode);
			_GetHeightRight(ParentNode);
			cout << _LeftHeight << " " << _RightHeight << endl;
			if (abs(_RightHeight - _LeftHeight) > 0)
			{
				_GetIn(ParentNode);
				sort(_SortedList.begin(), _SortedList.end());
				Clear();
				Print();
				_ReBalance();
			}
			_LeftHeight = 0;
			_RightHeight = 0;
			cout << endl;
			_GetHeightLeft(ParentNode);
			_GetHeightRight(ParentNode);
			cout << _LeftHeight << " " << _RightHeight << endl;
		}*/

		void Clear()
		{
			_ClearHelper(ParentNode);
			ParentNode = new Node();
			ParentNode->Data = NULL;
			ParentNode->Left = NULL;
			ParentNode->Right = NULL;
			ParentNode->Prev = NULL;
		}

		~clsBinaryTree()
		{
			delete ParentNode;
		}
		
};

