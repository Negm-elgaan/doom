#pragma once
#include <iostream>

using namespace std;

class clsAVLTree
{
	private:

		int LTreeHeight = 0;
		int RTreeHeight = 0;
		int TreeHeight = 0;
		int _Size = 0;

		class Node
		{
			private:

				int _Data = 0;
				Node* _Right = nullptr;
				Node* _Left = nullptr;
				Node* _Prev = nullptr;
				int _Height = 0;
				int _LeftSubTreeHeight = 0;
				int _RightSubTreeHeight = 0;
				int _BalanceFactor = 0;

				int _GetBalanceFactor()
				{
					LeftSubTreeHeight(_Left);
					RightSubTreeHeight(_Right);
					_BalanceFactor = _LeftSubTreeHeight - _RightSubTreeHeight;
					
					return _BalanceFactor;
				}

				

				void LeftSubTreeHeight(Node* node , int Temp = -1)
				{
					if (node == NULL)
					{
						if (Temp > _LeftSubTreeHeight)
							_LeftSubTreeHeight = Temp;

						return;
					}

					Temp++;

					LeftSubTreeHeight(node->_Left, Temp);

					LeftSubTreeHeight(node->_Right, Temp);
				}

				void RightSubTreeHeight(Node* node, int Temp = -1)
				{
					if(node == NULL)
					{
						if (Temp > _RightSubTreeHeight)
							_RightSubTreeHeight = Temp;

						return;
					}

					Temp++;

					RightSubTreeHeight(node->_Left, Temp);

					RightSubTreeHeight(node->_Right, Temp);
				}

			friend class clsAVLTree;

			

			
		};

		void _LeftRotation(Node* &node)
		{
			Node* temp = node;
			node = node->_Right;
			node->_Prev = temp->_Prev;
			temp->_Right = node->_Left;
			node->_Left = temp;
			if (temp != ParentNode)
			{
				if (temp->_Prev->_Right == temp)
					temp->_Prev->_Right = node;
				else
					temp->_Prev->_Left = node;
			}
			temp->_Prev = node;
			// add a way to calculate height after rotation
		}

		Node* ParentNode = nullptr;

		void _Height(Node* node , int Temp = -1)
		{
			if (node == NULL)
			{
				if (Temp > TreeHeight)
					TreeHeight = Temp;

				return;
			}

			Temp++;

			_Height(node->_Left , Temp);

			_Height(node->_Right , Temp);
		}

		

	public:

		void Insert(int Data, bool Re = false)
		{

			if (ParentNode == NULL)
			{
				ParentNode = new Node();
				ParentNode->_Data = Data;
				ParentNode->_Left = NULL;
				ParentNode->_Right = NULL;
				ParentNode->_Prev = NULL;
				ParentNode->_Height = 0;
				/*Temp1 = ParentNode;
				_Max = Data;
				_Min = Data;*/
				//cout << endl << ParentNode->Data << " ";
				return;
			}

			Node* TempNode = ParentNode;
			Node* NewNode = new Node();
			NewNode->_Data = Data;
			while (true)
			{
				if (NewNode->_Data == TempNode->_Data)
				{
					cout << "Key already exists!\n";
					return;
				}

				TempNode->_Height++;

				if (NewNode->_Data > TempNode->_Data)
				{
					if (TempNode->_Right == NULL)
					{
						break;
					}
					else
					{
						TempNode = TempNode->_Right;
					}
				}

				else if (NewNode->_Data < TempNode->_Data)
				{
					if (TempNode->_Left == NULL)
					{
						break;
					}
					else
					{
						TempNode = TempNode->_Left;
					}
				}

			}

			
			NewNode->_Data > TempNode->_Data ? TempNode->_Right = NewNode : TempNode->_Left = NewNode;
			TempNode->_Right == NULL ? TempNode->_Left->_Prev = TempNode : TempNode->_Right->_Prev = TempNode;
			TempNode->_Height = 0;

			_Size++;
			
			_Height(TempNode);
			
			return;

		}

		int Height()
		{
			return ParentNode->_Height;
		}

};

