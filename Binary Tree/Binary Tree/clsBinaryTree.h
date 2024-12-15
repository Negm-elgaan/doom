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
		};

		int _Size = 0;
		int _Levels = 0;
		int _Height = 0;
	

	public:
		
		clsBinaryTree::Node* ParentNode = NULL;
		//clsBinaryTree::Node* CurrentLeftNode = NULL;
		//clsBinaryTree::Node* CurrentRightNode = NULL;

		clsBinaryTree()
		{
			_Size = 1;
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
				//CurrentLeftNode = new Node();
				//CurrentRightNode = new Node();
				ParentNode->Data = Data;
				ParentNode->Left = NULL;
				ParentNode->Right = NULL;
				//CurrentLeftNode = ParentNode;
				//CurrentRightNode = ParentNode;
				return;
			}
			Node* TempNode = ParentNode;
			//cout << TempNode->Data << " " << ParentNode->Data;
			Node* NewNode = new Node();
			NewNode->Data = Data;
			/*if (TempNode->Left != NULL && NewNode->Data < TempNode->Data)
			{
				TempNode->Left = NewNode;
				return;
			}
			if (TempNode->Right != NULL && NewNode->Data > TempNode->Data)
			{
				TempNode->Right = NewNode;
				return;
			}
			while (TempNode->Data != NULL || TempNode->Data != NULL)
			{
				NewNode->Data > TempNode->Data ? TempNode = TempNode->Right : TempNode = TempNode->Left;
			}
			NewNode->Data > TempNode->Data ? TempNode->Right = NewNode : TempNode->Left = NewNode;*/
			while (x)
			{
				NewNode->Data > TempNode->Data ? TempNode->Right == NULL ? x = false : TempNode = TempNode->Right : TempNode->Left == NULL ? x = false : TempNode = TempNode->Left;
			}

			NewNode->Data > TempNode->Data ? TempNode->Right = NewNode : TempNode->Left = NewNode;

			return;

			
		}

		void printLeft()
		{
			Node* Temp = ParentNode;
			cout << Temp->Data << " ";
			Temp = Temp->Left;
			while (Temp != NULL)
			{
				cout << Temp->Data << " ";
				if (Temp->Right != NULL)
					cout << Temp->Right->Data << " ";
				Temp = Temp->Left;
			}

			cout << endl;

			return;
		}

		void printRight()
		{

			Node* Temp = ParentNode;
			cout << Temp->Data << " ";
			Temp = Temp->Right;
			while (Temp != NULL)
			{
				cout << Temp->Data << " ";
				if (Temp->Left != NULL)
					cout  << Temp->Left->Data << " ";
				Temp = Temp->Right;
			}

			cout << endl;

			return;
		}

		void print()
		{

		}
};

