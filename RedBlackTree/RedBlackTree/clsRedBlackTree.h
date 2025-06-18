#pragma once
#include <iostream>

using namespace std;

template <class T> class clsRedBlackTree
{
	private:

		enum enColor { Red = 0 , Black = 1};

		class Node
		{
			private:

				T _Data;
				enColor _Color;
				Node* _Right;
				Node* _Left;
				Node* _Prev;
				int _Height;

				friend class clsRedBlackTree;

			public:

				Node()
				{
					_Data = T();
					_Right = nullptr;
					_Left = nullptr;
					_Prev = nullptr;
					_Height = 0;
					_Color = enColor::Red;
				}
		};

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

		}
};

