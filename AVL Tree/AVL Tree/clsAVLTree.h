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
				int _BalanceFactor = 0;

				int _GetBalanceFactor()
				{
					return _BalanceFactor;
				}

			friend class clsAVLTree;
			
		};

		void PrintHelperPre(Node* node)
		{
			if (node == NULL)
				return;

			cout << node->_Data << " ";
			PrintHelperPre(node->_Left);
			/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
			// Print the data of the current node


			// Traverse the right subtree
			PrintHelperPre(node->_Right);
			/*thread T2(&clsMap::PrintHelper, this, node->Right);
			T1.join();
			T2.join();*/
			//cout << endl;
		}
		
		void PrintHelperPost(Node* node)
		{
			if (node == NULL)
				return;


			// Traverse the left subtree
			PrintHelperPost(node->_Left);
			/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
			// Print the data of the current node


			// Traverse the right subtree
			PrintHelperPost(node->_Right);
			/*thread T2(&clsMap::PrintHelper, this, node->Right);
			T1.join();
			T2.join();*/

			cout << node->_Data << " ";

		}

		void PrintHelperIn(Node* node)
		{
			if (node == nullptr)
				return;


			// Traverse the left subtree
			PrintHelperIn(node->_Left);
			/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
			// Print the data of the current node
			cout << node->_Data << " ";

			// Traverse the right subtree
			PrintHelperIn(node->_Right);
			/*thread T2(&clsMap::PrintHelper, this, node->Right);
			T1.join();
			T2.join();*/


		}


		void _LeftRotation(Node* &node)
		{
			if (node == nullptr || node->_Right == nullptr)
			{
				return; // No rotation possible
			}

			cout << node->_Data << endl;
			Node* x = node;       // x = 30
			Node* y = node->_Right;// y = 20
			Node* z = node->_Right->_Left;
			node = y;             // a now points to 20 (new root)
			y->_Left = x;// 20's right = 30
			//cout << "first" << node->_Right->_Prev->_Data << endl;
			// 20's parent = 30's parent (NULL if 30 was root)
			//cout << "mmm" << y->_Right->_Data << endl;
			 // 30's left = NULL (since y->right was NULL)
			if (x == ParentNode)
			{
				cout << "yes";
				y->_Prev = nullptr;
				ParentNode = y;
				/*cout << node->_Data << endl;
				cout << ParentNode->_Data << endl;
				cout << "wow" << node->_Right->_Data << endl;
				cout << ParentNode->_Right->_Data << "wow" << endl;*/
				//ParentNode->_Right->_Prev = node;
			}
			else
			{  // If x wasn't the root
				y->_Prev = x->_Prev;
				if (x->_Prev->_Right == x)
					x->_Prev->_Right = y;
				else
					x->_Prev->_Left = y;
			}
			x->_Prev = y; // 30's parent = 20
			if (z != nullptr)
			{
				x->_Right = z;
				z->_Prev = x;
			}
			else
			{
				x->_Right = nullptr;
			}
			x->_Height = 1 + max(sh(x->_Left), sh(x->_Right));
			y->_Height = 1 + max(sh(y->_Left), sh(y->_Right));

			x->_BalanceFactor = sh(x->_Left) - sh(x->_Right);
			y->_BalanceFactor = sh(y->_Left) - sh(y->_Right);

			/*	if (x == ParentNode)
				{
					cout << "yes";
					ParentNode = node;

				}*/

				// CRASH! (y->right is NULL)
			   /*cout << "final " << ParentNode->_Data << endl;
			   cout << ParentNode->_Right->_Data << " wow" << endl;
			   cout << "prevright " << ParentNode->_Right->_Prev->_Data << endl;
			   cout << ParentNode->_Left->_Data << " end" << endl;
			   cout << "prevleft " << ParentNode->_Left->_Prev->_Data << endl;*/
			   //cout << "wtf " << ParentNode->_Right->_Right->_Data << endl;
			   //cout << "wtf2 " << ParentNode->_Right->_Left->_Data << endl;
		}
		int sh(Node* n) { return n ? n->_Height : 0; }
		void _RightRotation(Node*& node)
		{
			if (node == nullptr || node->_Left == nullptr)
			{
				return; // No rotation possible
			}
			
			cout << node->_Data << endl;
				Node* x = node;       // x = 30
				Node* y = node->_Left;// y = 20
				Node* z = node->_Left->_Right;
				node = y;             // a now points to 20 (new root)
				y->_Right = x;// 20's right = 30
				//cout << "first" << node->_Right->_Prev->_Data << endl;
				// 20's parent = 30's parent (NULL if 30 was root)
				//cout << "mmm" << y->_Right->_Data << endl;
				 // 30's left = NULL (since y->right was NULL)
				if (x == ParentNode)
				{
					cout << "yes";
					y->_Prev = nullptr;
					ParentNode = y;
					/*cout << node->_Data << endl;
					cout << ParentNode->_Data << endl;
					cout << "wow" << node->_Right->_Data << endl;
					cout << ParentNode->_Right->_Data << "wow" << endl;*/
					//ParentNode->_Right->_Prev = node;
				}
				else 
				{  // If x wasn't the root
					y->_Prev = x->_Prev;
					if (x->_Prev->_Left == x)
						x->_Prev->_Left = y;
					else
						x->_Prev->_Right = y;
				}
				x->_Prev = y; // 30's parent = 20
				if (z != nullptr)
				{
					x->_Left = z;
					z->_Prev = x;
				}
				else
				{
					x->_Left = nullptr;
				}
				x->_Height = 1 + max(sh(x->_Left), sh(x->_Right));
				y->_Height = 1 + max(sh(y->_Left), sh(y->_Right));

				x->_BalanceFactor = sh(x->_Left) - sh(x->_Right);
				y->_BalanceFactor = sh(y->_Left) - sh(y->_Right);
			
			/*	if (x == ParentNode)
				{
					cout << "yes";
					ParentNode = node;
					
				}*/
				
				 // CRASH! (y->right is NULL)
				/*cout << "final " << ParentNode->_Data << endl;
				cout << ParentNode->_Right->_Data << " wow" << endl;
				cout << "prevright " << ParentNode->_Right->_Prev->_Data << endl;
				cout << ParentNode->_Left->_Data << " end" << endl;
				cout << "prevleft " << ParentNode->_Left->_Prev->_Data << endl;*/
				//cout << "wtf " << ParentNode->_Right->_Right->_Data << endl;
				//cout << "wtf2 " << ParentNode->_Right->_Left->_Data << endl;
		}

		void _ReBalance(Node*& node , int BalanceFactor)
		{
			//if (BalanceFactor > 1 && node->_Left->_BalanceFactor < 0)
			//{
			//	_LeftRotation(node->_Left);
			//	_BackTrack(node->_Left);
			//	_RightRotation(node);
			//	_BackTrack(node); // to recalculate height and BF
			//}
			//else if (BalanceFactor < 0 && node->_Right->_BalanceFactor > 1)
			//{
			//	_RightRotation(node->_Right);
			//	_BackTrack(node->_Right);
			//	_LeftRotation(node);
			//	_BackTrack(node); // to recalculate height and BF
			//}
			//else if (BalanceFactor > 1)
			//{
			//	_RightRotation(node);
			//	_BackTrack(node);
			//}
			//else
			//{
			//	_LeftRotation(node);
			//	_BackTrack(node);
			//}

			if (BalanceFactor > 1) 
			{
				if (node->_Left->_BalanceFactor >= 0) 
				{  
					// LL case
					_RightRotation(node);
					//_BackTrack(node);
				}
				else 
				{                                
					// LR case
					_LeftRotation(node->_Left);
					//_BackTrack(node->_Left);
					_RightRotation(node);
					//_BackTrack(node);
				}
			}
			else if (BalanceFactor < -1) 
			{
				if (node->_Right->_BalanceFactor <= 0) 
				{ 
					// RR case
					_LeftRotation(node);
					//_BackTrack(node);
				}
				else 
				{                                
					// RL case
					_RightRotation(node->_Right);
					//_BackTrack(node->_Right);
					_LeftRotation(node);
					//_BackTrack(node);
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

		void Insert(int Data, bool Re = false)
		{

			if (ParentNode == NULL)
			{
				ParentNode = new Node();
				ParentNode->_Data = Data;
				ParentNode->_Left = NULL;
				ParentNode->_Right = NULL;
				ParentNode->_Prev = NULL;
				ParentNode->_Height = 1;
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
			//TempNode->_Right == NULL ? TempNode->_Left->_Prev = TempNode : TempNode->_Right->_Prev = TempNode;
			NewNode->_Prev = TempNode;
			//TempNode->_Height = 0;
			NewNode->_Height = 1;

			_Size++;
			_BackTrack(NewNode->_Prev);
			
			return;

		}

		void PrintRootData()
		{
			cout << ParentNode->_Data << endl;
			cout << ParentNode->_Right->_Data << endl;
			cout << ParentNode->_Left->_Data << endl;
		}

		int Height()
		{
			return ParentNode->_Height;
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

};

///*#pragma once
//#include <iostream>
//
//using namespace std;
//
//class clsAVLTree
//{
//	private:
//
//		int LTreeHeight = 0;
//		int RTreeHeight = 0;
//		int TreeHeight = 0;
//		int _Size = 0;
//
//		class Node
//		{
//			private:
//
//				int _Data = 0;
//				Node* _Right = nullptr;
//				Node* _Left = nullptr;
//				Node* _Prev = nullptr;
//				int _Height = 0;
//				int _BalanceFactor = 0;
//
//				int _GetBalanceFactor()
//				{
//					return _BalanceFactor;
//				}
//
//			friend class clsAVLTree;
//
//			
//
//			
//		};
//
//		void PrintHelperPre(Node* node)
//		{
//			if (node == NULL)
//				return;
//
//			cout << node->_Data << " ";
//			PrintHelperPre(node->_Left);
//			/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
//			// Print the data of the current node
//
//
//			// Traverse the right subtree
//PrintHelperPre(node->_Right);
///*thread T2(&clsMap::PrintHelper, this, node->Right);
//T1.join();
//T2.join();*/
////cout << endl;
//		}
//
//		void PrintHelperPost(Node* node)
//		{
//			if (node == NULL)
//				return;
//
//
//			// Traverse the left subtree
//			PrintHelperPost(node->_Left);
//			/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
//			// Print the data of the current node
//
//
//			// Traverse the right subtree
//			PrintHelperPost(node->_Right);
//			/*thread T2(&clsMap::PrintHelper, this, node->Right);
//			T1.join();
//			T2.join();*/
//
//			cout << node->_Data << " ";
//
//		}
//
//		void PrintHelperIn(Node* node)
//		{
//			if (node == NULL)
//				return;
//
//
//			// Traverse the left subtree
//			PrintHelperIn(node->_Left);
//			/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
//			// Print the data of the current node
//			cout << node->_Data << " ";
//
//			// Traverse the right subtree
//			PrintHelperIn(node->_Right);
//			/*thread T2(&clsMap::PrintHelper, this, node->Right);
//			T1.join();
//			T2.join();*/
//
//
//		}
//
//
//		void _LeftRotation(Node*& node)
//		{
//			if (node == nullptr || node->_Right == nullptr)
//			{
//				return; // No rotation possible
//			}
//			Node* temp = node;
//			node = node->_Right;
//			node->_Prev = temp->_Prev;
//			temp->_Right = node->_Left;
//			node->_Left = temp;
//			if (temp == ParentNode)
//			{
//				ParentNode = node;
//				cout << node->_Data << endl;
//				node->_Prev = nullptr;
//			}
//			else
//			{
//				if (temp->_Prev->_Right == temp)
//					temp->_Prev->_Right = node;
//				else
//					temp->_Prev->_Left = node;
//			}
//
//			temp->_Prev = node;
//		}
//
//		void _RightRotation(Node*& node)
//		{
//			if (node == nullptr || node->_Left == nullptr)
//			{
//				return; // No rotation possible
//			}
//
//			if (node == ParentNode)
//			{
//				Node* temp = node;
//				Node* temp2 = node;
//				//cout << endl << temp->_Left->_Data << endl;
//				cout << endl << _Size << endl;
//				cout << node->_Left->_Left->_Data << endl;
//				node = node->_Left;
//				//cout << node->_Data << endl;
//				//cout << temp->_Data << endl;
//				//cout << temp->_Left->_Data << endl;
//				////cout << temp->_Right->_Data << endl;
//				temp->_Prev = node;
//				cout << "prev" << temp->_Prev->_Data << endl;
//				if (node->_Right != nullptr)
//				{
//					temp2 = node->_Right;
//
//				}
//				node->_Right = temp;
//				node->_Right->_Left = temp2;
//				cout << "prev" << node->_Right->_Prev->_Data << endl;
//				cout << "prev" << node->_Left->_Prev->_Data << endl;
//				//node->_Right = temp;
//				cout << node->_Right->_Data << endl;
//				cout << node->_Left->_Data << endl;
//				node->_Prev = ParentNode->_Prev;
//				ParentNode = node;
//				cout << "parent" << ParentNode->_Data;
//
//				cout << "end";
//				/*else
//				{
//					node->_Left = nullptr;
//				}*/
//
//				//cout << endl << node->_Data << endl;
//				////cout << node->_Left->_Data << endl;
//
//				//node = temp;
//				//node->_Left = temp->_Left;
//				//cout << temp2->_Data << endl;
//				//cout << node->_Data << endl;
//				//cout << node->_Left->_Data << endl;
//				//node->_Prev = nullptr;
//				//
//				////temp->_Left = node->_Right ? node->_Right : nullptr;
//				////temp2->_Prev = temp;
//				//node->_Right = temp2;
//				//cout << node->_Right->_Data;
//
//				cout << "parent" << ParentNode->_Data;
//				return;
//			}
//
//			Node* temp = node;
//			node = node->_Left;
//			cout << endl << node->_Data << endl;
//			cout << node->_Prev->_Data << endl;
//			node->_Prev = temp->_Prev;
//			temp->_Left = node->_Right;
//			node->_Right = temp;
//			///*if (temp == ParentNode)
//			//{
//			//	ParentNode = node;
//			//	cout << node->_Data << endl;
//			//	node->_Prev = nullptr;
//			//}*/
//			//else
//			//{
//			//	if (temp->_Prev->_Right == temp)
//			//		temp->_Prev->_Right = node;
//			//	else
//			//		temp->_Prev->_Left = node;
//			//}
//
//			temp->_Prev = node;
//		}
//
//		void _ReBalance(Node*& node, int BalanceFactor)
//		{
//			//if (BalanceFactor > 1 && node->_Left->_BalanceFactor < 0)
//			//{
//			//	_LeftRotation(node->_Left);
//			//	_BackTrack(node->_Left);
//			//	_RightRotation(node);
//			//	_BackTrack(node); // to recalculate height and BF
//			//}
//			//else if (BalanceFactor < 0 && node->_Right->_BalanceFactor > 1)
//			//{
//			//	_RightRotation(node->_Right);
//			//	_BackTrack(node->_Right);
//			//	_LeftRotation(node);
//			//	_BackTrack(node); // to recalculate height and BF
//			//}
//			//else if (BalanceFactor > 1)
//			//{
//			//	_RightRotation(node);
//			//	_BackTrack(node);
//			//}
//			//else
//			//{
//			//	_LeftRotation(node);
//			//	_BackTrack(node);
//			//}
//			cout << "/nYes/n";
//			if (BalanceFactor > 1)
//			{
//				if (node->_Left->_BalanceFactor >= 0)
//				{
//					// LL case
//					_RightRotation(node);
//					//_BackTrack(node);
//				}
//				else
//				{
//					// LR case
//					_LeftRotation(node->_Left);
//					//_BackTrack(node->_Left);
//					_RightRotation(node);
//					//_BackTrack(node);
//				}
//			}
//			else if (BalanceFactor < -1)
//			{
//				if (node->_Right->_BalanceFactor <= 0)
//				{
//					// RR case
//					_LeftRotation(node);
//					//_BackTrack(node);
//				}
//				else
//				{
//					// RL case
//					_RightRotation(node->_Right);
//					//_BackTrack(node->_Right);
//					_LeftRotation(node);
//					//_BackTrack(node);
//				}
//			}
//		}
//
//		Node* ParentNode = nullptr;
//
//		void _Height(Node* node, int Temp = -1)
//		{
//			if (node == NULL)
//			{
//				if (Temp > TreeHeight)
//					TreeHeight = Temp;
//
//				return;
//			}
//
//			Temp++;
//
//			_Height(node->_Left, Temp);
//
//			_Height(node->_Right, Temp);
//		}
//
//		int Height(Node* node)
//		{
//			if (node == nullptr)
//				return -1;
//
//			return 1 + max(Height(node->_Left), Height(node->_Right));
//		}
//		//		void _BackTrack(Node* node) {
//		//    if (!node) return;
//		//
//		//    // 1) recompute this node’s height & balance-factor
//		//    int lh = node->_Left  ? node->_Left->_Height  : -1;
//		//    int rh = node->_Right ? node->_Right->_Height : -1;
//		//    node->_Height        = 1 + max(lh, rh);
//		//    node->_BalanceFactor = lh - rh;
//		//
//		//    // 2) if unbalanced, rotate to fix it
//		//    if (abs(node->_BalanceFactor) > 1)
//		//        _ReBalance(node, node->_BalanceFactor);
//		//
//		//    // 3) always continue up to the root
//		//    _BackTrack(node->_Prev);
//		//}
//
//		
//
//	public:
//
//		void Insert(int Data, bool Re = false)
//		{
//
//			if (ParentNode == NULL)
//			{
//				ParentNode = new Node();
//				ParentNode->_Data = Data;
//				ParentNode->_Left = NULL;
//				ParentNode->_Right = NULL;
//				ParentNode->_Prev = NULL;
//				ParentNode->_Height = 1;
//				_Size++;
//				return;
//			}
//
//			Node* TempNode = ParentNode;
//			Node* NewNode = new Node();
//			NewNode->_Data = Data;
//			while (true)
//			{
//				if (NewNode->_Data == TempNode->_Data)
//				{
//					cout << "Key already exists!\n";
//					return;
//				}
//
//				if (NewNode->_Data > TempNode->_Data)
//				{
//					if (TempNode->_Right == NULL)
//					{
//						break;
//					}
//					else
//					{
//						TempNode = TempNode->_Right;
//					}
//				}
//
//				else if (NewNode->_Data < TempNode->_Data)
//				{
//					if (TempNode->_Left == NULL)
//					{
//						break;
//					}
//					else
//					{
//						TempNode = TempNode->_Left;
//					}
//				}
//
//			}
//
//
//			NewNode->_Data > TempNode->_Data ? TempNode->_Right = NewNode : TempNode->_Left = NewNode;
//			//TempNode->_Right == NULL ? TempNode->_Left->_Prev = TempNode : TempNode->_Right->_Prev = TempNode;
//			NewNode->_Prev = TempNode;
//			//TempNode->_Height = 0;
//			NewNode->_Height = 1;
//			//cout << NewNode->_Data << endl;
//			_Size++;
//			_BackTrack(NewNode->_Prev);
//
//			return;
//
//		}
//
//		void PrintRootData()
//		{
//			cout << ParentNode->_Data;
//		}
//
//		int Height()
//		{
//			return ParentNode->_Height;
//		}
//
//		void Print()
//		{
//			cout << "InOrder: ";
//			PrintHelperIn(ParentNode);
//			cout << endl;
//			cout << "PreOrder: ";
//			PrintHelperPre(ParentNode);
//			cout << endl;
//			cout << "PostOrder: ";
//			PrintHelperPost(ParentNode);
//			cout << endl;
//		}
//
//};
//
//*/