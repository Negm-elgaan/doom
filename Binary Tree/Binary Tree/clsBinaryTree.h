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

		int _Max = 0;
		int _Min = 0;
		int _Size = 0;
		int _Levels = 0;
		int _LeftHeight = 0;
		int _RightHeight = 0;
		int _Height = 0;
		int _Temp = 0;
		vector <int> _SortedList;
		vector <int> _vlist;

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


		void _ReBalance()
		{
			vector <int> small;
			vector <int> large;
			Node* node = new Node();

			for (int i = 0; i < _SortedList.size() / 2; i++)
			{
				small.push_back(_SortedList[i]);
			}

			for (int i = _SortedList.size() / 2  + 1 ; i < _SortedList.size(); i++)
			{
				large.push_back(_SortedList[i]);
			}

			node->Data = _SortedList[_SortedList.size() / 2];
			Insert(node->Data);

			cout << endl;
			int s = small.size();
			int l = large.size();
			for (int i = 0; i < s; i++)
			{
				node->Data = small[small.size() / 2];
				Insert(node->Data);
				small[small.size() - 1] = small[small.size() - 1] ^ small[small.size() / 2];
				small[small.size() / 2] = small[small.size() - 1] ^ small[small.size() / 2];
				small[small.size() - 1] = small[small.size() - 1] ^ small[small.size() / 2];
				small.pop_back();
			}

			for (int i = 0; i < l; i++)
			{
				node->Data = large[large.size() / 2];
				Insert(node->Data);
				large[large.size() - 1] = large[large.size() - 1] ^ large[large.size() / 2];
				large[large.size() / 2] = large[large.size() - 1] ^ large[large.size() / 2];
				large[large.size() - 1] = large[large.size() - 1] ^ large[large.size() / 2];
				large.pop_back();
			}
			delete node;
		}

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

		void PrintHelperIn(Node* node)
		{
			if (node == NULL)
				return;


			// Traverse the left subtree
			PrintHelperIn(node->Left);
			/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
			// Print the data of the current node
			cout << node->Data << " ";

			// Traverse the right subtree
			PrintHelperIn(node->Right);
			/*thread T2(&clsMap::PrintHelper, this, node->Right);
			T1.join();
			T2.join();*/

			
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

		/*clsBinaryTree operator*(clsBinaryTree Tree)
		{
			for (int i = 0; i < Tree._SortedList(); i++)
			{
				
			}
		}*/

		clsBinaryTree& operator<<(clsBinaryTree& Tree)
		{
			Tree.Print();
			return Tree;
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
				_Max = Data;
				_Min = Data;
				//cout << endl << ParentNode->Data << " ";
				_vlist.push_back(Data);
				return;
			}

			if (Data > _Max)
				_Max = Data;

			if (Data < _Min)
				_Min = Data;

			Node* TempNode = ParentNode;
			Node* NewNode = new Node();
			NewNode->Data = Data;
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
			//ReBalance();
			//cout << NewNode->Data << " ";
			_vlist.push_back(Data);
			if (_Size > 3)
			{
				_GetHeight(ParentNode);
				if (_Height == _Size)
					ReBalance();
			}
			return;
			
		}

		void Print()
		{
			//PrintTreeStructure(ParentNode);
			PrintHelperIn(ParentNode);
			cout << endl;
			PrintHelperPre(ParentNode);
			cout << endl;
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

		void ReBalance()
		{	
			_GetIn(ParentNode);
			sort(_SortedList.begin(), _SortedList.end());
			Clear();
			_ReBalance();
		}

		void Clear()
		{
			_ClearHelper(ParentNode);
			ParentNode = NULL;
			_Size = 0;
			_Height = 0;
		}

		int Min()
		{
			return _Min;
		}

		int Max()
		{
			return _Max;
		}

		~clsBinaryTree()
		{
			delete ParentNode;
		}
		
};

