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
		int _Height = -1;
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

		Node* _Search(Node* node , T Data)
		{
			if (node == NULL)
				return NULL;

			if (node->Data = Data)
				return node;
			// Traverse the left subtree
			PrintHelper(node->Left);

			// Traverse the right subtree
			PrintHelper(node->Right);
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

	public:
		
		clsBinaryTree::Node* ParentNode = NULL;
		clsBinaryTree::Node* Temp1 = ParentNode;

		clsBinaryTree()
		{
			_Size = 0;
			_Levels = 1;
			_Height = 1;
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
			Node* node = _Search(ParentNode, Data);
			return node->Data;
		}

		/*bool DeleteLeaf(T Data)
		{
			if (ParentNode == NULL)
				return false;
			Node* node = _Search(ParentNode, Data);
			if (node == NULL)
				return false;
			if (node->Right != NULL && node->Left != NULL)
			{
				if (node->Right->Data > node->Left->Data)
				{
					node->Right->Prev = node->Prev;
					node->Left->Prev = node->Right;
					if (node->Right->Left)
					node = NULL;
					return true;
				}
				node->Left->Prev = node->Prev;
				node->Right->Prev = node->Leftt;
				node = NULL;
				return true;
			}

			if (node->Right != NULL)
			{
				node->Right->Prev = node->Prev;
				node = NULL;
				return true;
			}

			if (node->Left != NULL)
			{
				node->Left->Prev = node->Prev;
				node = NULL;
				return true;
			}

			node = NULL;
			return true;
		}*/

		~clsBinaryTree()
		{
			delete ParentNode;
			delete Temp1;
		}
		
};

