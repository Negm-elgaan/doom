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
					_BalanceFactor = _LeftSubTreeHeight - _RightSubTreeHeight;
					
					return _BalanceFactor;
				}

				int _HeightPostOrder(Node* node , int Temp = -1)
				{
					if (node == NULL)
					{
						/*if (Temp > _Height)
							_Height = Temp;*/

						return -1;
					}

					_HeightPostOrder(node->_Left, Temp);

					_HeightPostOrder(node->_Right, Temp);

					if (node->_Left == NULL && node->_Right == NULL)
					{
						_LeftSubTreeHeight = -1;
						_RightSubTreeHeight = -1;
						_GetBalanceFactor();
						_Height = 0;
						return;
					}

				}

			friend class clsAVLTree;

			

			
		};

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

