#pragma once
#include <iostream>

using namespace std;

template <class Key = int , class Value = int , class Value2 = char , class Value3 = double , class Value4 = bool , class Value5 = string /*, class Value6 = int*, class Value7 = char*, class Value8 = double*, class Value9 = bool*, class Value10 = string * */ > class clsBinaryTree
{
private:
	static class Node
	{
	public:
		void* DataPtr;
		Key KeyValue;
		Value Data;
		Value2 Data2;
		Value3 Data3;
		Value4 Data4;
		Value5 Data5;
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
		cout << "Key : " << node->KeyValue << "{ " << node->Data << " , " << node->Data2 << " , " << node->Data3 << " , " << node->Data4 << " , " << node->Data5 << " }" << endl;

		// Traverse the right subtree
		PrintHelper(node->Right);
	}

	Node* _Search(Node* node, Key KeyValue ,Value Data = NULL, Value2 Data2 = NULL , Value3 Data3 = NULL , Value4 Data4 = NULL , Value5 = NULL)
	{
		if (node == NULL)
			return NULL;

		if (node->KeyValue == KeyValue)
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

	clsBinaryTree(int Size, int levels, int Height)
	{
		_Size = Size;
		_Levels = levels;
		_Height = Height;
		return;
	}

	void Insert(Key KeyValue , Value Data = Value(), Value2 Data2 = Value2(), Value3 Data3 = Value3(), Value4 Data4 = Value4(), Value5 Data5 = Value5())
	{
		bool x = true;
		if (ParentNode == NULL)
		{
			ParentNode = new Node();
			ParentNode->KeyValue = KeyValue;
			ParentNode->Data = Data;
			ParentNode->Data2 = Data2;
			ParentNode->Data3 = Data3;
			ParentNode->Data4 = Data4;
			ParentNode->Data5 = Data5;
			ParentNode->Left = NULL;
			ParentNode->Right = NULL;
			ParentNode->Prev = NULL;
			Temp1 = ParentNode;
			return;
		}
		Node* TempNode = ParentNode;
		Node* NewNode = new Node();
		NewNode->KeyValue = KeyValue;
		NewNode->Data = Data;
		NewNode->Data2 = Data2;
		NewNode->Data3 = Data3;
		NewNode->Data4 = Data4;
		NewNode->Data5 = Data5;

		while (x)
		{
			if (NewNode->KeyValue == TempNode->KeyValue)
			{
				cout << "Key already exists!\n";
				return;
			}
			NewNode->KeyValue > TempNode->KeyValue ? TempNode->Right == NULL ? x = false : TempNode = TempNode->Right : TempNode->Left == NULL ? x = false : TempNode = TempNode->Left;
		}

		NewNode->KeyValue > TempNode->KeyValue ? TempNode->Right = NewNode : TempNode->Left = NewNode;
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

	/*Value search(Value Data)
	{
		Node* node = _Search(ParentNode, Data);
		return node->Data;
	}*/

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
		DeleteHelper(ParentNode);
	}

};


