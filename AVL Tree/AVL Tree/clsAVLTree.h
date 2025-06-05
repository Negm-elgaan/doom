#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

template <class T> class clsAVLTree
{
	private:

		int LTreeHeight;
		int RTreeHeight;
		int TreeHeight;
		int _Size;
		vector <T> _SortedList;
		T _Min;
		T _Max;

		class Node
		{
			private:

				T _Data ;
				Node* _Right ;
				Node* _Left ;
				Node* _Prev ;
				int _Height ;
				int _BalanceFactor ;

				int _GetBalanceFactor()
				{
					return _BalanceFactor;
				}

			friend class clsAVLTree;

			public:

				Node()
				{
					_Right = nullptr;
					_Left = nullptr;
					_Prev = nullptr;
					_Height = 0;
					_BalanceFactor = 0;
				}
					
		};


		void PrintHelperPre(Node* node)
		{
			if (node == NULL)
				return;

			cout << node->_Data << " ";
			PrintHelperPre(node->_Left);

			PrintHelperPre(node->_Right);
		}
		
		void PrintHelperPost(Node* node)
		{
			if (node == NULL)
				return;

			PrintHelperPost(node->_Left);
		
			PrintHelperPost(node->_Right);

			cout << node->_Data << " ";

		}

		void PrintHelperIn(Node* node)
		{
			if (node == nullptr)
				return;

			PrintHelperIn(node->_Left);
			
			cout << node->_Data << " ";

			PrintHelperIn(node->_Right);

		}

		void _DeleteHelper(Node* node)
		{
			if (node == nullptr)
				return;

			// Recursively delete the left and right subtrees
			_DeleteHelper(node->_Left);
			_DeleteHelper(node->_Right);

			// Delete the current node
			delete node;
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
			if (x == ParentNode)
			{
				//cout << "yes";
				y->_Prev = nullptr;
				ParentNode = y;
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
			x->_Height = 1 + max(_FastHeight(x->_Left), _FastHeight(x->_Right));
			y->_Height = 1 + max(_FastHeight(y->_Left), _FastHeight(y->_Right));

			x->_BalanceFactor = _FastHeight(x->_Left) - _FastHeight(x->_Right);
			y->_BalanceFactor = _FastHeight(y->_Left) - _FastHeight(y->_Right);

		}

		int _FastHeight(Node* node)
		{ 
			return node ? node->_Height : 0; 
		}

		void _RightRotation(Node*& node)
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

				if (x == ParentNode)
				{
					//cout << "yes";
					y->_Prev = nullptr;
					ParentNode = y;
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

				x->_Height = 1 + max(_FastHeight(x->_Left), _FastHeight(x->_Right));
				y->_Height = 1 + max(_FastHeight(y->_Left), _FastHeight(y->_Right));

				x->_BalanceFactor = _FastHeight(x->_Left) - _FastHeight(x->_Right);
				y->_BalanceFactor = _FastHeight(y->_Left) - _FastHeight(y->_Right);
		}

		void _ReBalance(Node*& node , int BalanceFactor)
		{
			

			if (BalanceFactor > 1) 
			{
				if (node->_Left->_BalanceFactor >= 0) 
				{  
					// LL case
					_RightRotation(node);
					
				}
				else 
				{                                
					// LR case
					_LeftRotation(node->_Left);
					_RightRotation(node);
				}
			}
			else if (BalanceFactor < -1) 
			{
				if (node->_Right->_BalanceFactor <= 0) 
				{ 
					// RR case
					_LeftRotation(node);
				}
				else 
				{                                
					// RL case
					_RightRotation(node->_Right);
					_LeftRotation(node);
				}
			}
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

		int Height(Node* node)
		{
			if (node == nullptr)
				return -1;

			return 1 + max(Height(node->_Left), Height(node->_Right));
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

			node->_BalanceFactor = LeftSubTreeHeight - RightSubTreeHeight;

			if (abs(node->_BalanceFactor) > 1)
			{
				_ReBalance(node, node->_BalanceFactor);
			}

			_BackTrack(node->_Prev);
			
		}

	public:

		clsAVLTree()
		{
			LTreeHeight = 0;
			RTreeHeight = 0;
			TreeHeight = 0;
			_Size = 0;
		}

		/*clsAVLTree& operator<<(clsAVLTree<T>& Tree)
		{
			Tree.Print();
			return Tree;
		}*/

		friend ostream& operator<<(ostream& os, const clsAVLTree<T>& tree)
		{
			tree.Print();
			return os;
		}

		friend istream& operator>>(istream& is, clsAVLTree<T>& tree)
		{
			T data;
			is >> data;
			tree.Insert(data);
			return is;
		}

		/*clsAVLTree& operator>>(clsAVLTree<T>& Tree)
		{
			Tree.Insert();
			return Tree;
		}*/

		clsAVLTree(clsAVLTree<T>&& tree)
		{
			this->ParentNode = tree.ParentNode;
			this->_Min = tree._Min;
			this->_Max = tree._Max;
			this->_Size = tree._Size;
			this->_SortedList = move(tree._SortedList);

			tree.ParentNode = nullptr;
			tree._Size = 0;
			tree._Min = T();
			tree._Max = T();
			tree._SortedList = {};
		}

		void Insert(bool Re = false)
		{
			T Data;

			cin >> Data;

			Insert(Data, Re);

			return;
		}

		void Insert(T Data, bool Re = false)
		{

			if (ParentNode == NULL)
			{
				ParentNode = new Node();
				ParentNode->_Data = Data;
				ParentNode->_Left = NULL;
				ParentNode->_Right = NULL;
				ParentNode->_Prev = NULL;
				ParentNode->_Height = 1;
				_Min = Data;
				_Max = Data;
				_SortedList.push_back(Data);
				_Size++;
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

			_SortedList.push_back(Data);
			_Size++;
			_BackTrack(NewNode->_Prev);
			
			return;

		}

		Node* Search(T Data)
		{
			Node* node = ParentNode;

			if (node == nullptr)
				return nullptr;

			while (node != nullptr)
			{
				if (node->_Data == Data)
				{
					cout << "\nfound: " << node->_Data;
					return node;
				}

				node->_Data > Data ? node = node->_Left : node = node->_Right;
			}

			return nullptr;
		}

		bool Contains(T Data)
		{
			Node* node = Search(Data);

			if (node)
			{
				return true;
			}

			return false;
		}

		bool Update(T Data1, T Data2)
		{
			Node* node = Search(Data1);

			if (!node)
				return false;

			Remove(Data1);

			Insert(Data2);

			return true;
		}

		bool Remove(T Data)
		{
			if (!ParentNode)
				return false;

			Node* node = Search(Data);

			if (node == nullptr)
				return false;

			if (Data == _Min)
				_Min = node->_Prev->_Data;

			if (node->_Right == nullptr && node->_Left == nullptr)
			{
				Node* Temper = node->_Prev;
				node->_Prev->_Right == node ? node->_Prev->_Right = nullptr : node->_Prev->_Left = nullptr;
				delete node;
				_Size--;
				_SortedList.erase(std::find(_SortedList.begin(), _SortedList.end(), Data));
				_BackTrack(Temper);
				return true;
			}

			if (node->_Right == nullptr && node->_Left != nullptr)
			{
				Node* Temper = node->_Left;
				node->_Prev->_Right == node ? node->_Prev->_Right = node->_Left : node->_Prev->_Left = node->_Left;
				node->_Left->_Prev = node->_Prev;
				delete node;
				_Size--;
				_SortedList.erase(std::find(_SortedList.begin(), _SortedList.end(), Data));
				_BackTrack(Temper);
				return true;
			}

			if (node->_Right != nullptr && node->_Left == nullptr)
			{
				Node* Temper = node->_Right;
				node->_Prev->_Right == node ? node->_Prev->_Right = node->_Right : node->_Prev->_Left = node->_Right;
				node->_Right->_Prev = node->_Prev;
				delete node;
				_Size--;
				_SortedList.erase(std::find(_SortedList.begin(), _SortedList.end(), Data));
				_BackTrack(Temper);
				return true;
			}

			Node* Temp = node;
			Node* Temper = nullptr;
			node = node->_Right;

			if (!node->_Left)
			{
				node->_Prev->_Data = node->_Data;
				Temper = node->_Prev;
				delete node;
				_SortedList.erase(std::find(_SortedList.begin(), _SortedList.end(), Data));
				_BackTrack(Temper);
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
			
			_SortedList.erase(std::find(_SortedList.begin(), _SortedList.end(), Data));
			delete node;
			_Size--;
			_BackTrack(Temper);

			return true;
		}

		Node* GetRoot()
		{
			return ParentNode;
		}

		bool IsEmpty()
		{
			return ParentNode == nullptr;
		}

		T Min()
		{
			if (IsEmpty())
				throw runtime_error("Tree is empty, no minimum value.");

			return _Min;
		}

		T Max()
		{
			if (IsEmpty())
				throw runtime_error("Tree is empty, no maximum value.");

			return _Max;
		}

		T Previous(T Data)
		{
			Node* node = _Search(Data);

			if (node == nullptr)
				return nullptr;

			node = node->_Prev;

			if (node == nullptr)
				return nullptr;

			return node->_Data;
		}

		T Left(T Data)
		{
			Node* node = _Search(Data);

			if (node == nullptr)
				return nullptr;

			node = node->_Left;

			if (node == nullptr)
				return nullptr;

			return node->_Data;
		}

		T Right(T Data)
		{
			Node* node = _Search(Data);

			if (node == nullptr)
				return nullptr;

			node = node->_Right;

			if (node == nullptr)
				return nullptr;

			return node->_Data;
		}

		T Successor(T Data)
		{
			if (Data == _Max)
				return NULL;

			sort(_SortedList.begin(), _SortedList.end());

			cout << endl;

			for (int i = 0; i < _SortedList.size(); i++)
				if (_SortedList[i] == Data)
					return _SortedList[i + 1];
		}

		T Predecessor(T Data)
		{
			if (Data == _Min)
				return NULL;

			sort(_SortedList.begin(), _SortedList.end());

			for (int i = 0; i < _SortedList.size(); i++)
				if (_SortedList[i] == Data)
					return _SortedList[i - 1];
		}

		T Median()
		{
			if (_SortedList.size() % 2 == 0)
				return (_SortedList[_SortedList.size() / 2] + _SortedList[(_SortedList.size() / 2) - 1]) / 2;

			return _SortedList[_SortedList.size() / 2];
		}

		void Clear() 
		{
			_DeleteHelper(ParentNode);
			ParentNode = nullptr;
			_Size = 0;
			TreeHeight = 0;
		}

		//int LowestCommonAncestor()

		int Height()
		{
			return ParentNode->_Height;
		}

		int Size()
		{
			return _Size;
		}

		void PrintRootData()
		{
			cout << ParentNode->_Data << endl;
			cout << ParentNode->_Right->_Data << endl;
			cout << ParentNode->_Left->_Data << endl;
		}

		void Print()
		{
			cout << "InOrder: ";
			PrintHelperIn(ParentNode);
			cout << endl;
			cout << "PreOrder: ";
			PrintHelperPre(ParentNode);
			cout << endl;
			cout << "PostOrder: ";
			PrintHelperPost(ParentNode);
			cout << endl;
		}

		~clsAVLTree()
		{
			_DeleteHelper(ParentNode);
			
			cout << "\nAVl Tree Has Been Deleted\n";

			return;
		}
};