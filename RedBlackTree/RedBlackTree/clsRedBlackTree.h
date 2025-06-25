#pragma once
#include <iostream>

using namespace std;

template <class T> class clsRedBlackTree
{
	private:

		long long _Size;
		long long _Max;
		long long _Min;

		enum enColor { Red = 0 , Black = 1};
		enum enInsertionRebalanceCases { UncleIsRed = 0 , UncleIsBlackOrNullAndOppositeOrientation = 1 , UncleIsBlackOrNullAndSameOrientation = 2};
		class Node
		{
			private:

				T _Data;
				enColor _Color;
				Node* _Right;
				Node* _Left;
				Node* _Prev;
				int _Height;
				int _BlackNodes;

				friend class clsRedBlackTree;

			public:

				Node()
				{
					_Data = T();
					_Right = nullptr;
					_Left = nullptr;
					_Prev = nullptr;
					_Height = 0;
					_BlackNodes = 1;
					_Color = enColor::Red;
				}
		};

		bool CheckRedAdjacency(Node* node)
		{
			return node->_Color == enColor::Red && node->_Prev->_Color == enColor::Red;
		}

		void _LeftRotation(Node* &node)
		{
			//Not implemented yet
		}

		void _RightRotation(Node* &node)
		{
			//Not implemented yet
		}

		void _Recolor(Node* &node)
		{
			if (node->_Color == Black)
				node->_Color = Red;
			else
				node->_Color = Black;
		}

		void _InsBackTrack(Node* node)
		{

			if (!node)
				return;

			if (CheckRedAdjacency(node)) 
			{

				if (node->_Prev == node->_Prev->_Prev->_Right) // uncle is left of grandparent
				{
					if (!node->_Prev->_Prev->_Left || node->_Prev->_Prev->_Left->_Color == Black) // Uncle is NIL/Black
					{
						if (node == node->_Prev->_Right) // node is Right of parent
						{
							if (node->_Prev == node->_Prev->_prev->_Right) // parent is right of grandparent
							{
								_Recolor(node->_Prev);
								_Recolor(node->_Prev->_Prev);
								_LeftRotation(node->_Prev->_Prev);
							}
							
							else // parent is Left of grandparent
							{
								_LeftRotation(node->_Prev);
								_Recolor(node);
								_Recolor(node->_Prev);
								_RightRotation(node->_Prev);
							}
						}

						else // node is Left of parent
						{
							if (node->_Prev == node->_Prev->_prev->_Left)// parent is Left of grandparent
							{
								_Recolor(node->_Prev);
								_Recolor(node->_Prev->_Prev);
								_RightRotation(node->_Prev->_Prev);
							}
							
							else
							{
								_RightRotation(node->_Prev);
								_Recolor(node);
								_Recolor(node->_Prev);
								_LeftRotation(node->_Prev);
							}
						}
					}

					else // Uncle is Red
					{
						_Recolor(node->_Prev);
						_Recolor(node->_Prev->_Prev->_Left);
						_Recolor(node->_Prev->_Prev);
					}
				}
				else // uncle is Right of grandparent
				{
					if (node->_Prev->_Prev->_Right->_Color == Red) // Uncle is Red
					{
						_Recolor(node->_Prev);
						_Recolor(node->_Prev->_Prev->_Right);
						_Recolor(node->_Prev->_Prev);
					}
				}
			}

			_InsBackTrack(node->_Prev);
		}

		Node* _RootNode;

	public:

		clsRedBlackTree()
		{
			_RootNode = nullptr;
		}

		void Insert(T Data)
		{

			if (!_RootNode)
			{
				_RootNode = new Node();
				_RootNode->_Data = Data;
				_RootNode->_Height = 0; // _RootNode->_Height = 1; if rotations don't work use this  as rotations are made for min height =  1
				_RootNode->_Color = enColor::Black;
			}

			Node* TempNode = _RootNode;
			Node* NewNode = new Node();
			NewNode->_Data = Data;
			while (true)
			{
				if (NewNode->_Data == TempNode->_Data)
				{
					cout << "Key already exists!\n";
					return;
				}

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
			NewNode->_Prev = TempNode;
			NewNode->_Height = 1;

			if (NewNode->_Data < _Min)
			{
				_Min = NewNode->_Data;
			}

			if (NewNode->_Data > _Max)
			{
				_Max = NewNode->_Data;

			}


			_Size++;
			_InsBackTrack(NewNode);

			return;


		}
};

