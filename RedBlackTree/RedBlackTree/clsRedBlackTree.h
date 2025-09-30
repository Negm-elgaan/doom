#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <class T> class clsRedBlackTree
{
	private:

		long long _Size;
		long long _Capacity;
		T _Max;
		T _Min;
		bool _MemPool;

		enum enColor { Red = 0 , Black = 1 , Orange = 2};
		
		class Node;

		//Node* _MemoryNodeAllocatorArray[10000000];

		bool CheckRedAdjacency(Node* node)
		{
			if (node == _RootNode)
			{
				return false;
			}

			return node->_Color == enColor::Red && node->_Prev->_Color == enColor::Red;
		}

		void PrintHelperPre(Node* node) const
		{
			if (node == NULL)
				return;

			cout << node->_Data << " ";

			PrintHelperPre(node->_Left);

			PrintHelperPre(node->_Right);
		}

		void PrintHelperPost(Node* node) const
		{
			if (node == NULL)
				return;

			PrintHelperPost(node->_Left);

			PrintHelperPost(node->_Right);

			cout << node->_Data << " ";

		}

		void PrintHelperIn(Node* node) const
		{
			if (node == nullptr)
				return;

			PrintHelperIn(node->_Left);

			cout << node->_Data << " ";

			PrintHelperIn(node->_Right);

		}

		void PrintColorsHelperPre(Node* node)
		{
			if (node == NULL)
				return;

			cout << node->_Data << " " << node->_Color << " " << endl;

			PrintHelperPre(node->_Left);

			PrintHelperPre(node->_Right);
		}

		void PrintColorsHelperPost(Node* node)
		{
			if (node == NULL)
				return;

			PrintHelperPost(node->_Left);

			PrintHelperPost(node->_Right);

			cout << node->_Data << " " << node->_Color << " " ;
		}

		void PrintColorsHelperIn(Node* node)
		{
			if (node == nullptr)
				return;

			PrintHelperIn(node->_Left);

			cout << node->_Data << " " << node->_Color << " " ;

			PrintHelperIn(node->_Right);
		}

		void DeleteHelper(Node* node)
		{
			if (node == nullptr)
				return;

			DeleteHelper(node->_Left);
			DeleteHelper(node->_Right);

			delete node;

			return;
		}

		void _LeftRotation(Node* &node)
		{
			if (node == nullptr || node->_Right == nullptr)
			{
				return;
			}

			//cout << node->_Data << endl;
			Node* x = node;
			Node* y = node->_Right;
			Node* z = node->_Right->_Left;
			node = y;
			y->_Left = x;
			if (x == _RootNode)
			{
				//cout << "yes";
				y->_Prev = nullptr;
				_RootNode = y;
				y->_Color = Black;
			}
			else
			{
				y->_Prev = x->_Prev;
				if (x->_Prev->_Right == x)
					x->_Prev->_Right = y;
				else
					x->_Prev->_Left = y;
			}
			x->_Prev = y;
			if (z != nullptr)
			{
				x->_Right = z;
				z->_Prev = x;
			}
			else
			{
				x->_Right = nullptr;
			}
		}

		void _RightRotation(Node* &node)
		{
			if (node == nullptr || node->_Left == nullptr)
			{
				return;
			}

			//cout << node->_Data << endl;
			Node* x = node;
			Node* y = node->_Left;
			Node* z = node->_Left->_Right;
			node = y;
			y->_Right = x;

			if (x == _RootNode)
			{
				//cout << "yes";
				y->_Prev = nullptr;
				_RootNode = y;
				y->_Color = Black;
			}

			else
			{
				y->_Prev = x->_Prev;
				if (x->_Prev->_Left == x)
					x->_Prev->_Left = y;
				else
					x->_Prev->_Right = y;
			}

			x->_Prev = y;

			if (z != nullptr)
			{
				x->_Left = z;
				z->_Prev = x;
			}

			else
			{
				x->_Left = nullptr;
			}

		}

		void _Recolor(Node* &node)
		{
			if (!node)
				return;

			if (node->_Color == Black)
				node->_Color = Red;
			else
				node->_Color = Black;
		}

		void _InsBackTrack(Node* node)
		{

			if (!node || node == _RootNode || node->_Prev == _RootNode)
				return;

			if (CheckRedAdjacency(node))
			{

					if (node->_Prev == node->_Prev->_Prev->_Right) // uncle is left of grandparent
					{
						if (!node->_Prev->_Prev->_Left || node->_Prev->_Prev->_Left->_Color == Black) // Uncle is NIL/Black
						{
							if (node == node->_Prev->_Right) // node is Right of parent
							{
								if (node->_Prev == node->_Prev->_Prev->_Right) // parent is right of grandparent
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
								if (node->_Prev == node->_Prev->_Prev->_Left)// parent is Left of grandparent
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
						if (!node->_Prev->_Prev->_Left || node->_Prev->_Prev->_Left->_Color == Black) // Uncle is NIL/Black
						{
							if (node == node->_Prev->_Right) // node is Right of parent
							{
								if (node->_Prev == node->_Prev->_Prev->_Right) // parent is right of grandparent
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
								if (node->_Prev == node->_Prev->_Prev->_Left)// parent is Left of grandparent
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
							_Recolor(node->_Prev->_Prev->_Right);
							_Recolor(node->_Prev->_Prev);
						}
					}
				}
				_InsBackTrack(node->_Prev);
		}

		void _BackTrack(Node* node)
		{
			if (node == nullptr)
				return;

			if (node->_Left == nullptr && node->_Right == nullptr)
			{
				node->_Height = 1;
			}

			if (node->_Left == nullptr && node->_Right != nullptr)
			{
				node->_Height = node->_Right->_Height + 1;
			}

			else if (node->_Right == nullptr && node->_Left != nullptr)
			{
				node->_Height = node->_Left->_Height + 1;
			}

			else if (node->_Left != nullptr && node->_Right != nullptr)
			{
				if (node->_Left->_Height > node->_Right->_Height)
				{
					node->_Height = node->_Left->_Height + 1;
				}
				else
				{
					if (node->_Right != nullptr)
						node->_Height = node->_Right->_Height + 1;
				}
			}



			int LeftSubTreeHeight = node->_Left ? node->_Left->_Height : 0;
			int RightSubTreeHeight = node->_Right ? node->_Right->_Height : 0;


			_BackTrack(node->_Prev);

		}		

		void _DelBackTrack(Node*& node) // newest version/ current working on version
		{
			// هنعتمد هنا علي اننا نبعت النود الي هنمسحها قبل ما تتمسح ويكون لونها برتقالي 
			
			if (!node->_Prev) //rootnode is the node to be deleted
			{
				// some code
				return;
			}

			if ((node->_Prev->_Right && node->_Prev->_Right->_Color == Orange) || !node->_Prev->_Left) // node to be deleted is right
			{
				if (!node->_Prev->_Left) // sibling is NIL
				{
					if (node->_Prev->_Color == Red)
					{
						_Recolor(node->_Prev);
						return;
					}

					node->_Color = Black;
					node->_Prev->_Color = Orange;
					_DelBackTrack(node->_Prev);
					
				}

				else if (node->_Prev->_Left->_Color == Black) //sibling is Black
				{
					if ((!node->_Prev->_Left->_Right && !node->_Prev->_Left->_Left) || (!node->_Prev->_Left->_Right && node->_Prev->_Left->_Left->_Color == Black)  || (!node->_Prev->_Left->_Left && node->_Prev->_Left->_Right->_Color == Black) || (node->_Prev->_Left->_Right->_Color == Black && node->_Prev->_Left->_Left->_Color == Black)  ) // siblings children are black or nil
					{
						_Recolor(node->_Prev->_Left);

						if (node->_Prev->_Color == Red)
						{
							_Recolor(node->_Prev);
							return;
						}

						node->_Color = Black;
						node->_Prev->_Color = Orange;
						_DelBackTrack(node->_Prev);
					}

					else if (node->_Prev->_Left->_Left && node->_Prev->_Left->_Left->_Color == Red) // far child is red
					{
						node->_Prev->_Left->_Color = node->_Prev->_Color;
						node->_Prev->_Color = Black;
						node->_Prev->_Left->_Left->_Color = Black;
						_RightRotation(node->_Prev);
					}

					else
					{
						node->_Prev->_Left->_Right->_Color = Black;
						node->_Prev->_Left->_Color = Red;
						_LeftRotation(node->_Prev);
						node->_Prev->_Left->_Color = node->_Prev->_Color;
						node->_Prev->_Color = Black;
						node->_Prev->_Left->_Left->_Color = Black;
						_RightRotation(node->_Prev);
					}
				}

				else // sibling is red
				{
					node->_Prev->_Left->_Color = Black;
					node->_Prev->_Color = Red;
					_LeftRotation(node->_Prev);
					_DelBackTrack(node);
				}
			}

			else // node to be deleted is left
			{
				if (!node->_Prev->_Right) // sibling is NIL
				{
					if (node->_Prev->_Color == Red)
					{
						_Recolor(node->_Prev);
						return;
					}

					node->_Color = Black;
					node->_Prev->_Color = Orange;
					_DelBackTrack(node->_Prev);

				}

				else if (node->_Prev->_Right->_Color == Black) //sibling is Black
				{
					if ((!node->_Prev->_Right->_Right && !node->_Prev->_Right->_Left) || (!node->_Prev->_Right->_Right && node->_Prev->_Right->_Left->_Color == Black) || (!node->_Prev->_Right->_Left && node->_Prev->_Right->_Right->_Color == Black) || (node->_Prev->_Right->_Right->_Color == Black && node->_Prev->_Right->_Left->_Color == Black)) // siblings children are black or nil
					{
						_Recolor(node->_Prev->_Right);

						if (node->_Prev->_Color == Red)
						{
							_Recolor(node->_Prev);
							return;
						}

						node->_Color = Black;
						node->_Prev->_Color = Orange;
						_DelBackTrack(node->_Prev);
					}

					else if (node->_Prev->_Right->_Right && node->_Prev->_Right->_Right->_Color == Red) // far child is red
					{
						node->_Prev->_Right->_Color = node->_Prev->_Color;
						node->_Prev->_Color = Black;
						node->_Prev->_Right->_Right->_Color = Black;
						_LeftRotation(node->_Prev);
					}

					else
					{
						node->_Prev->_Right->_Left->_Color = Black;
						node->_Prev->_Right->_Color = Red;
						_RightRotation(node->_Prev);
						node->_Prev->_Right->_Color = node->_Prev->_Color;
						node->_Prev->_Color = Black;
						node->_Prev->_Right->_Right->_Color = Black;
						_LeftRotation(node->_Prev);
					}

				}

				else // sibling is red
				{
					node->_Prev->_Right->_Color = Black;
					node->_Prev->_Color = Red;
					_RightRotation(node->_Prev);
					_DelBackTrack(node);
				}
			}


		}

		Node* _RootNode;

	public:

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

		clsRedBlackTree()
		{
			_RootNode = nullptr;
			//_MemoryNodeAllocatorArray = nullptr;
			_Size = 0;
			_MemPool = false;
			_Capacity = 0;
			_Min = T();
			_Max = T();
		}

		clsRedBlackTree(long long size)
		{
			_RootNode = nullptr;
			//_MemoryPoolAllocator(size);
			_Size = 0;
			_MemPool = true;
			_Capacity = size;
			_Min = T();
			_Max = T();
		}

		friend ostream& operator<<(ostream& os , const clsRedBlackTree& Tree)
		{
			Tree.Print();
			return os;
		}

		void Insert(T Data)
		{

			if (!_RootNode)
			{
				//if (_MemPool)
				//{
					//_RootNode = _MemoryNodeAllocatorArray[_Size];
				//}
				//else
				//{
					_RootNode = new Node();
				//}
				_RootNode->_Data = Data;
				_RootNode->_Height = 0; // _RootNode->_Height = 1; if rotations don't work use this  as rotations are made for min height =  1
				_RootNode->_Color = enColor::Black;
				_Size++;
				return;
			}

			Node* TempNode = _RootNode;
			Node* NewNode;
			//if (_MemPool)
			//{
				//NewNode = _MemoryNodeAllocatorArray[_Size];
			//}
			//else
			//{
				NewNode = new Node();
			//}
			NewNode->_Data = Data;
			while (true)
			{
				if (NewNode->_Data == TempNode->_Data)
				{
					cout << "Key already exists!\n";
					delete NewNode;
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

			_InsBackTrack(NewNode);
			_BackTrack(NewNode);

			if (_RootNode->_Color == Red)
			{
				_RootNode->_Color = Black;
			}

			_Size++;

			return;
		}

		Node* Search(T Data)
		{
			Node* node = _RootNode;

			if (node == nullptr)
				return nullptr;

			while (node != nullptr)
			{
				if (node->_Data == Data)
				{
					//cout << "\nfound: " << node->_Data;
					return node;
				}

				node->_Data > Data ? node = node->_Left : node = node->_Right;
			}

			return nullptr;
		}

		bool Remove(T Data)
		{
			if (!_RootNode)
				return false;

			Node* node = Search(Data);
			string test = "";

			if (node == nullptr)
				return false;

			if (Data == _Min)
				_Min = node->_Prev->_Data;

			if (node->_Right == nullptr && node->_Left == nullptr)
			{	

				if (node->_Color == Black)
				{
					node->_Color = Orange;
					_DelBackTrack(node);
				}

				Node* Temper = node->_Prev;
				node->_Prev->_Right == node ? node->_Prev->_Right = nullptr : node->_Prev->_Left = nullptr;

				_BackTrack(node->_Prev);
				delete node;
				_Size--;
				
				return true;
			}

			if (node->_Right == nullptr && node->_Left != nullptr)
			{
				
				if (node->_Color == Black)
				{
					node->_Color = Orange;
					_DelBackTrack(node);
				}
				Node* Temper = node->_Left;
				node->_Prev->_Right == node ? node->_Prev->_Right = node->_Left : node->_Prev->_Left = node->_Left;
				node->_Left->_Prev = node->_Prev;

				_BackTrack(node->_Prev);
				delete node;
				_Size--;
				return true;
			}

			if (node->_Right != nullptr && node->_Left == nullptr)
			{
				
				if (node->_Color == Black)
				{
					node->_Color = Orange;
					_DelBackTrack(node);
				}
				Node* Temper = node->_Right;
				node->_Prev->_Right == node ? node->_Prev->_Right = node->_Right : node->_Prev->_Left = node->_Right;
				node->_Right->_Prev = node->_Prev;

				_BackTrack(node->_Prev);
				delete node;
				_Size--;
				return true;
			}

			Node* Temp = node;
			Node* Temper = nullptr;
			node = node->_Right;

			if (!node->_Left)
			{
				
				if (node->_Color == Black)
				{
					node->_Color = Orange;
					_DelBackTrack(node);
				}
				node->_Prev->_Data = node->_Data;
				Temper = node->_Prev;

				_BackTrack(node->_Prev);
				delete node;
				_Size;
				return true;
			}

			while (node->_Left != nullptr)
			{
				node = node->_Left;
			}

			if (node->_Right != nullptr)
			{
				node->_Prev->_Left = node->_Right;
				node->_Right->_Prev = node->_Prev;
				Temp->_Data = node->_Data;
				Temper = node->_Right;
			}

			else
			{
				node->_Prev->_Left = nullptr;
				Temp->_Data = node->_Data;
				Temper = node->_Prev;
			}

			if (node->_Color == Black)
			{
				node->_Color = Orange;
				_DelBackTrack(node);
			}

			_BackTrack(node->_Prev);
			delete node;
			_Size--;

			return true;
		}

		bool IsEmpty()
		{
			return _RootNode == nullptr && _Size == 0;
		}

		int Size()
		{
			return _Size;
		}

		void Height(T Data)
		{
			Node* node = Search(Data);

			if (!node)
			{
				cout << "Node does not exist!\n";
				return;
			}

			cout << node->_Height << endl;
		}

		T Previous(T Data)
		{
			Node* node = Search(Data);

			if (node == nullptr)
				return nullptr;

			node = node->_Prev;

			if (node == nullptr)
				return nullptr;

			return node->_Data;
		}

		T Left(T Data)
		{
			Node* node = Search(Data);

			if (node == nullptr)
				return nullptr;

			node = node->_Left;

			if (node == nullptr)
				return nullptr;

			return node->_Data;
		}

		T Right(T Data)
		{
			Node* node = Search(Data);

			if (node == nullptr)
				return nullptr;

			node = node->_Right;

			if (node == nullptr)
				return nullptr;

			return node->_Data;
		}

		bool Exist(T Data)
		{
			Node* node = Search(Data);

			if (!node)
			{
				return false;
			}

			return true;
		}

		bool IsSibling(Node* node1 , Node* node2)
		{
			if (!node1 || !node2 || !node1->_Prev || !node2->_Prev)
			{
				return false;
			}

			if (node1->_Prev == node2->_Prev)
			{
				return true;
			}

			return false;
		}

		bool IsParent(Node* node1, Node* node2)
		{
			if (!node1 || !node2 || !node2->_Prev)
			{
				return false;
			}

			if (node1 == node2->_Prev)
			{
				return true;
			}

			return false;
		}

		bool IsLeaf(Node* node)
		{
			if (!node)
			{
				return false;
			}

			if (!node->_Right && !node->_Left)
			{
				return true;
			}

			return false;

		}

		T LCA(T Data1, T Data2)
		{
			Node* node1 = Search(Data1);
			Node* node2 = Search(Data2);

			if (node1 == _RootNode || node2 == _RootNode)
			{
				return _RootNode->_Data;
			}

			if (!node1 || !node2 || !node1->_Prev || !node2->_Prev)
			{
				return T();
			}

			while (true)
			{

				/*if (node1->_Prev == _RootNode || node2->_Prev == _RootNode)
				{
					return _RootNode->_Data;
				}*/

				if (node1 == node2)
				{
					return node1->_Data;
				}

				if (node1->_Prev == node2->_Prev)
				{
					return node1->_Prev->_Data;
				}

				if (node1->_Prev == node2)
				{
					return node2->_Data;
				}

				if (node2->_Prev == node1)
				{
					return node1->_Data;
				}

				if (node1->_Height < node2->_Height)
				{
					node2 = node2->_Prev;
				}

				else if (node1->_Height > node2->_Height)
				{
					node1 = node1->_Prev;
				}

				else if (node1->_Height == node2->_Height)
				{
					node1 = node1->_Prev;
					node2 = node2->_Prev;
				}
			}
		}

		T Min()
		{
			return _Min;
		}

		T Max()
		{
			return _Max;
		}

		void Clear()
		{
			DeleteHelper(_RootNode);
			_RootNode = nullptr;
			//_MemoryNodeAllocatorArray = nullptr;
			_Size = 0;
			_MemPool = false;
			_Capacity = 0;
			_Min = T();
			_Max = T();

			return;
		}

		void PrintRootData()
		{
			cout << _RootNode->_Data << endl;
			cout << _RootNode->_Right->_Data << endl;
			cout << _RootNode->_Left->_Data << endl;
			//cout << _RootNode->_Height << endl;
		}

		void PrintColor(T Data)
		{
			Node* node = Search(Data);

			if (!node)
			{
				cout << "Node does not exist!\n";
				return;
			}

			cout << node->_Color;

			return;
		}

		void PrintColors()
		{
			cout << "InOrder: ";
			PrintColorsHelperIn(_RootNode);
			cout << endl;
			cout << "PreOrder: ";
			PrintColorsHelperPre(_RootNode);
			cout << endl;
			cout << "PostOrder: ";
			PrintColorsHelperPost(_RootNode);
			cout << endl;
		}

		void Print() const
		{
			cout << "InOrder: ";
			PrintHelperIn(_RootNode);
			cout << endl;
			cout << "PreOrder: ";
			PrintHelperPre(_RootNode);
			cout << endl;
			cout << "PostOrder: ";
			PrintHelperPost(_RootNode);
			cout << endl;
		}

		~clsRedBlackTree()
		{
			Clear();

			return;
		}
};
