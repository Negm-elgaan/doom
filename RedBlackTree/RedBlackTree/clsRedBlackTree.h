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
		};


};

