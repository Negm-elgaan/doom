#pragma once
#include <iostream>

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
		int _Height = 0;
		int _Temp = -1;
		void PrintHelper(Node* node)
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
			Node* TempNode = ParentNode;
			Node* NewNode = new Node();
			NewNode->Data = Data;
			
			while (x)
			{
				NewNode->Data > TempNode->Data ? TempNode->Right == NULL ? x = false : TempNode = TempNode->Right : TempNode->Left == NULL ? x = false : TempNode = TempNode->Left;
			}

			NewNode->Data > TempNode->Data ? TempNode->Right = NewNode : TempNode->Left = NewNode;
			TempNode->Right == NULL ? TempNode->Left->Prev = TempNode : TempNode->Right->Prev = TempNode;
			_Size++;
			return;

			
		}

		void Print()
		{
			PrintHelper(ParentNode);
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

		~clsBinaryTree()
		{
			delete ParentNode;
		}
		
};

