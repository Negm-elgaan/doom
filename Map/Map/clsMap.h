#pragma once
#include <iostream>
#include <thread>
#include <cstdarg>
#include <vector>
#include <algorithm>
#include <math.h>
#include "clsDynamicArray.h"

using namespace std;

template <class Key = int, class Value = int, class Value2 = char, class Value3 = double, class Value4 = bool, class Value5 = string, class Value6 = clsDynamicArray <int>, class Value7 = clsDynamicArray <string>, class Value8 = clsDynamicArray <char>, class Value9 = clsDynamicArray <double> , class Value10 = const string* , class Value11 = const int*   , class Value12 = const char* , class Value13 = const double* , class Value14 = string* , class Value15 = int* , class Value16 = char* , class Value17 = double* , class... Value18 /*, class Value7 = char*, class Value8 = double*, class Value9 = bool*, class Value10 = string * */ > class clsMap
{
private:

	class Node;

	int _Size = 0;
	int _Levels = 0;
	int _LeftHeight = 0;
	int _RightHeight = 0;
	int _Height = 0;
	int _Temp = 0;
	int _MaxKeyValue = 0;
	int _MinKeyValue = 0;

	vector <Node*> _SortedList;
	vector <Node*> _vList;

	clsDynamicArray <Node*> _List;

	void _GetHeight(Node* node)
	{
		if (node == NULL)
		{
			if (_Temp > _Height)
				_Height = _Temp;

			_Temp = 0;

			return;
		}
		_Temp++;

		_GetHeight(node->Left);

		_GetHeight(node->Right);

		_Temp = 0;
	}

	/*not done*/void _ReBalance()
	{
		vector <Node*> small;
		vector <Node*> large;
		Node* node = new Node();
		Node* TEMPO = new Node();

		for (int i = 0; i < _SortedList.size() / 2; i++)
		{
			small.push_back(_SortedList[i]);
		}

		for (int i = _SortedList.size() / 2 + 1; i < _SortedList.size(); i++)
		{
			large.push_back(_SortedList[i]);
		}

		node = _SortedList[_SortedList.size() / 2];
		Insert(node);

		cout << endl;
		int s = small.size();
		int l = large.size();
		for (int i = 0; i < s; i++)
		{
			node = small[small.size() / 2];
			Insert(node);
			TEMPO = small[small.size() - 1];
			small[small.size() - 1] = small[small.size() / 2];
			small[small.size() / 2] = TEMPO;
			/*small[small.size() - 1] = small[small.size() - 1] ^ small[small.size() / 2];
			small[small.size() / 2] = small[small.size() - 1] ^ small[small.size() / 2];
			small[small.size() - 1] = small[small.size() - 1] ^ small[small.size() / 2];*/
			small.pop_back();
		}

		for (int i = 0; i < l; i++)
		{
			node = large[large.size() / 2];
			Insert(node);
			TEMPO = large[large.size() - 1];
			large[large.size() - 1] = large[large.size() / 2];
			large[large.size() / 2] = TEMPO;
			/*large[large.size() - 1] = large[large.size() - 1] ^ large[large.size() / 2];
			large[large.size() / 2] = large[large.size() - 1] ^ large[large.size() / 2];
			large[large.size() - 1] = large[large.size() - 1] ^ large[large.size() / 2];*/
			large.pop_back();
		}
		delete node;
	}

	void _Rebalance2()
	{

	}

	void _GetIN(Node* node)
	{
		_SortedList = _vList;
	}

	void _GetIn(Node* node)
	{
		if (node == NULL)
			return;

		_GetIn(node->Left);

		_SortedList.push_back(node);

		_GetIn(node->Right);
	}

	//void _GetHeightLeft(Node* node)
	//{
	//	if (node == NULL)
	//	{
	//		if (_Temp > _LeftHeight)
	//			_LeftHeight = _Temp;

	//		_Temp = 0;

	//		return;
	//	}
	//	_Temp++;

	//	_GetHeightLeft(node->Left);

	//	_Temp = 0;
	//}

	//void _GetHeightRight(Node* node)
	//{
	//	if (node == NULL)
	//	{
	//		if (_Temp > _RightHeight)
	//			_RightHeight = _Temp;

	//		_Temp = 0;

	//		return;
	//	}
	//	_Temp++;

	//	_GetHeightRight(node->Right);

	//	_Temp = 0;
	//}

	void PrintHelperIn(Node* node)
	{
		if (node == NULL)
			return;

		// Traverse the left subtree
		PrintHelperIn(node->Left);
		/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
		// Print the data of the current node
		cout << "Key : " << node->KeyValue << " { " << node->Data << " , " << node->Data2 << " , " << node->Data3 << " , " << node->Data4 << " , " << node->Data5 << " }" << endl;

		// Traverse the right subtree
		PrintHelperIn(node->Right);
		/*thread T2(&clsMap::PrintHelper, this, node->Right);
		T1.join();
		T2.join();*/
	}

	void PrintHelperPre(Node* node)
	{
		if (node == NULL)
			return;

		cout << "Key : " << node->KeyValue << " { " << node->Data << " , " << node->Data2 << " , " << node->Data3 << " , " << node->Data4 << " , " << node->Data5 << " }" << endl;
		// Traverse the left subtree
		PrintHelperPre(node->Left);
		/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
		// Print the data of the current node


		// Traverse the right subtree
		PrintHelperPre(node->Right);
		/*thread T2(&clsMap::PrintHelper, this, node->Right);
		T1.join();
		T2.join();*/
	}

	void PrintHelperPost(Node* node)
	{
		if (node == NULL)
			return;


		// Traverse the left subtree
		PrintHelperPost(node->Left);
		/*thread T1(&clsMap::PrintHelper, this, node->Left);*/
		// Print the data of the current node


		// Traverse the right subtree
		PrintHelperPost(node->Right);
		/*thread T2(&clsMap::PrintHelper, this, node->Right);
		T1.join();
		T2.join();*/

		cout << "Key : " << node->KeyValue << " { " << node->Data << " , " << node->Data2 << " , " << node->Data3 << " , " << node->Data4 << " , " << node->Data5 << " }" << endl;
	}

	Node* _Search(Key KeyValue /*, Value Data = NULL, Value2 Data2 = NULL, Value3 Data3 = NULL, Value4 Data4 = NULL, Value5 = NULL*/)
	{
		Node* node = ParentNode;

		if (node == NULL)
			return NULL;

		while (node != NULL)
		{
			if (node->KeyValue == KeyValue)
				return node;
			node->KeyValue > KeyValue ? node = node->Left : node = node->Right;
		}

		return NULL;
	}

	void ClearHelper1(Node* node , int size = 0)
	{
		if (node == NULL)
			return;

		if (size == 0)
			return;

		ClearHelper1(node->Left, size - 1);
		ClearHelper1(node->Right, size - 1);

		node = NULL;
	}

	void DeleteHelper1(Node* node)
	{
		if (node == NULL)
			return;

		// Recursively delete the left and right subtrees
		DeleteHelper1(node->Left);
		DeleteHelper1(node->Right);

		// Delete the current node
		delete node;
	}

	void DeleteHelper2(Node* node)
	{
		if (node == NULL)
			return;

		// Recursively delete the left and right subtrees
		thread T1(&clsMap::DeleteHelper2, this, node->Left);
		thread T2(&clsMap::DeleteHelper2, this, node->Right);
		T1.join();
		T2.join();

		// Delete the current node
		delete node;
	}

public:

	static class Node
	{

	public:
		//void* DataPtr;
		clsDynamicArray <va_list> List;
		Key KeyValue;
		Value Data;
		Value2 Data2;
		Value3 Data3;
		Value4 Data4;
		Value5 Data5;
		Value6 Data6;
		Value7 Data7;
		Value8 Data8;
		Value9 Data9;
		Value10 Data10;
		Value11 Data11;
		Value12 Data12;
		Value13 Data13;
		//Value14 Data14;
		Node* Right;
		Node* Left;
		Node* Prev;
		int Levels = 0;

		template <class T> class Noder
		{
		public:
			T Data;
		};

	};

	clsMap::Node* ParentNode = NULL;
	clsMap::Node* Temp1 = ParentNode;

	clsMap()
	{
		_Size = 1;
		_Levels = 1;
		_Height = 1;
	}

	clsMap(int Size, int levels, int Height)
	{
		_Size = Size;
		_Levels = levels;
		_Height = Height;
		return;
	}

	clsMap(clsMap&& obj)
	{
		ParentNode = obj.ParentNode;
		obj.ParentNode = nullptr;
	}

	clsMap& operator^=(int Number)
	{
		for (Node* node : this->_vList)
		{
			Key TTT = node->KeyValue;

			for (int i = 0; i < Number - 1; i++)
			{
				node->KeyValue *= TTT;
			}
		}

		return *this;
	}

	clsMap& operator<<(clsMap& obj)
	{
		obj.Print();
		return obj;
	}

	clsMap& operator+=(clsMap& obj)
	{
		for (Node* node : obj._vList)
		{
			this->Insert(node->KeyValue, node->Data, node->Data2, node->Data3, node->Data4, node->Data5);
		}
		return *this;
	}

	clsMap& operator+(clsMap& obj)
	{
		for (Node* node : obj._vList)
		{
			this->Insert(node->KeyValue, node->Data, node->Data2, node->Data3, node->Data4, node->Data5);
		}
		return *this;
	}

	clsMap& operator-(clsMap& obj)
	{
		for (Node* node1 : obj._vList)
		{
			for (Node* node2 : this->_vList)
			{
				if (node1->KeyValue == node2->KeyValue)
					this->Remove(node2->KeyValue);
			}
		}
		return *this;
	}

	bool operator>(clsMap& obj)
	{
		return this->Size > obj.Size;
	}

	clsMap& operator>>(clsMap& obj)
	{
		obj.Insert();

		return obj;
	}

	/*clsMap& operator/(clsMap& obj)
	{
		for (Node* node1 : obj._vList)
		{
			for (Node* node2 : this->_vList)
			{
				node2->KeyValue /= node1->KeyValue;
			}
		}

		return *this;
	}*/

	int operator/(clsMap& obj)
	{
		return this->Size / obj.Size;
	}

	clsMap& operator-=(clsMap& obj)
	{
		for (Node* node1 : obj._vList)
		{
			for (Node* node2 : this->_vList)
			{
				if (node1->KeyValue == node2->KeyValue)
					this->Remove(node2->KeyValue);
			}
		}
		return *this;
	}

	clsMap& operator--()
	{
		this->Remove(_vList[_vList.size() - 1]);
		return *this;
	}

	clsMap& operator*(clsMap& obj)
	{
		for (Node* node1 : obj._vList)
		{
			for (Node* node2 : this->_vList)
			{
				node2->KeyValue *= node1->KeyValue;
			}
		}
		return *this;
	}

	bool operator<(clsMap& obj)
	{
		return this->Size < obj.Size;
	}

	int operator%(clsMap& obj)
	{
		return this->_Size % obj._Size;
	}

	Node* operator[](Key KeyValue)
	{
		Node* node = _Search(KeyValue);

		if (node == NULL)
			return NULL;

		return node;
	}

	template <typename... Args>void Insert2(Key Value, Args...args)
	{
		ParentNode->List.SetItem(0, std::forward<Args>(args)...);
	}

	/*Not Properly handled not done yet*/void Insert(Node* node, bool duplicate = false)
	{
		bool x = true;

		if (ParentNode == NULL)
		{
			ParentNode = new Node();
			ParentNode->KeyValue = node->KeyValue;
			ParentNode->Data = node->Data;
			ParentNode->Data2 = node->Data2;
			ParentNode->Data3 = node->Data3;
			ParentNode->Data4 = node->Data4;
			ParentNode->Data5 = node->Data5;
			ParentNode->Left = NULL;
			ParentNode->Right = NULL;
			ParentNode->Prev = NULL;
			Temp1 = ParentNode;
			_MaxKeyValue = node->KeyValue;
			_MinKeyValue = node->KeyValue;
			_vList.push_back(ParentNode);
			_Size++;
			return;
		}

		Node* TempNode = ParentNode;

		while (x)
		{
			if (node->KeyValue == TempNode->KeyValue && duplicate == false)
			{
				cout << "Key already exists!\n";
				return;
			}
			node->KeyValue > TempNode->KeyValue ? TempNode->Right == NULL ? x = false : TempNode = TempNode->Right : TempNode->Left == NULL ? x = false : TempNode = TempNode->Left;
		}

		node->KeyValue > TempNode->KeyValue ? TempNode->Right = node : TempNode->Left = node;

		TempNode->Right == NULL ? TempNode->Left->Prev = TempNode : TempNode->Right->Prev = TempNode;

		_Size++;

		if (node->KeyValue < _MinKeyValue)
			_MinKeyValue = node->KeyValue;

		if (node->KeyValue > _MaxKeyValue)
			_MaxKeyValue = node->KeyValue;

		_vList.push_back(node);

		/*_GetHeight(ParentNode);

		if (_Height > log(_Size))
			ReBalance();*/

		return;
	}

	void Insert(bool duplicate = false)
	{
		bool x = true;
		if (ParentNode == NULL)
		{
			ParentNode = new Node();
			cout << "\nEnter Key: ";
			cin >> ParentNode->KeyValue;
			cout << "\nEnter Data1: ";
			cin >> ParentNode->Data;
			cout << "\nEnter Data2: ";
			cin >> ParentNode->Data2;
			cout << "\nEnter Data3: ";
			cin >> ParentNode->Data3;
			cout << "\nEnter Data4: ";
			cin >> ParentNode->Data3;
			cout << "\nEnter Data5: ";
			cin >> ParentNode->Data5;
			ParentNode->Left = NULL;
			ParentNode->Right = NULL;
			ParentNode->Prev = NULL;
			Temp1 = ParentNode;
			_vList.push_back(ParentNode);
			return;
		}

		Node* TempNode = ParentNode;
		Node* NewNode = new Node();
		cout << "\nEnter Key: ";
		cin >> NewNode->KeyValue;
		cout << "\nEnter Data1: ";
		cin >> NewNode->Data;
		cout << "\nEnter Data2: ";
		cin >> NewNode->Data2;
		cout << "\nEnter Data3: ";
		cin >> NewNode->Data3;
		cout << "\nEnter Data4: ";
		cin >> NewNode->Data4;
		cout << "\nEnter Data5: ";
		cin >> NewNode->Data5;

		while (x)
		{
			if (NewNode->KeyValue == TempNode->KeyValue && duplicate == false)
			{
				cout << "Key already exists!\n";
				return;
			}
			NewNode->KeyValue > TempNode->KeyValue ? TempNode->Right == NULL ? x = false : TempNode = TempNode->Right : TempNode->Left == NULL ? x = false : TempNode = TempNode->Left;
		}

		NewNode->KeyValue > TempNode->KeyValue ? TempNode->Right = NewNode : TempNode->Left = NewNode;
		TempNode->Right == NULL ? TempNode->Left->Prev = TempNode : TempNode->Right->Prev = TempNode;
		_Size++;
		_vList.push_back(NewNode);

		return;

	}

	void Insert(Key KeyValue , Value Data = Value(), Value2 Data2 = Value2(), Value3 Data3 = Value3(), Value4 Data4 = Value4(), Value5 Data5 = Value5() , Value12 Data12 = Value12() , bool duplicate = false , bool Re = false)
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
			ParentNode->Data12 = Data12;
			ParentNode->Left = NULL;
			ParentNode->Right = NULL;
			ParentNode->Prev = NULL;
			Temp1 = ParentNode;
			_vList.push_back(ParentNode);
			_SortedList.push_back(ParentNode);
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
		NewNode->Data12 = Data12;
		while (x)
		{
			if (NewNode->KeyValue == TempNode->KeyValue  && duplicate == false)
			{
				cout << "Key already exists!\n";
				return;
			}
			NewNode->KeyValue > TempNode->KeyValue ? TempNode->Right == NULL ? x = false : TempNode = TempNode->Right : TempNode->Left == NULL ? x = false : TempNode = TempNode->Left;
		}

		NewNode->KeyValue > TempNode->KeyValue ? TempNode->Right = NewNode : TempNode->Left = NewNode;
		TempNode->Right == NULL ? TempNode->Left->Prev = TempNode : TempNode->Right->Prev = TempNode;
		_Size++;
		_vList.push_back(NewNode);
		_SortedList.push_back(NewNode);
		/*if (_RightHeight - _LeftHeight != 0)
		{
			_GetIn(ParentNode);
			Clear();
			_ReBalance(ParentNode);
		}*/


		/*_GetHeight(ParentNode);

		if (_Height > log(_Size))
			ReBalance();*/

		return;


	}

	void PrintInOrder()
	{
		PrintHelperIn(ParentNode);
	}

	void PrintPreOrder()
	{
		PrintHelperPre(ParentNode);
	}

	void PrintPostOrder()
	{
		PrintHelperPost(ParentNode);
	}

	void PrintByInsertionOrder()
	{
		for (Node* node : _vList)
		{
			cout << "Key : " << node->KeyValue << " { " << node->Data << " , " << node->Data2 << " , " << node->Data3 << " , " << node->Data4 << " , " << node->Data5 << " , ";
			if (node->Data12 != NULL)
			{
				for (int i = 0; node->Data12[i] != '\0'; i++)
					cout << node->Data12[i];
			}
			cout << " }" << endl;
		}
	}

	int Size()
	{
		return _Size;
	}

	void Clear()
	{
		/*cout << "clear:\n\n";
		for (Node* node : _SortedList)
		{
			cout << "Key : " << node->KeyValue << " { " << node->Data << " , " << node->Data2 << " , " << node->Data3 << " , " << node->Data4 << " , " << node->Data5 << " , ";
			if (node->Data12 != NULL)
			{
				for (int i = 0; node->Data12[i] != '\0'; i++)
					cout << node->Data12[i];
			}
			cout << " }" << endl;
		}*/
		ClearHelper1(ParentNode,_Size);
		/*_vList.~vector();
		_vList = vector<Node*>();*/
		_vList.clear();
		//ParentNode = NULL;
		_Size = 0;
		_Height = 0;
	}

	void ReBalance()
	{
		//_GetIn(ParentNode);
		sort(_SortedList.begin(), _SortedList.end());
		Clear();
		_ReBalance();
	}

	bool Remove(Key Data)
	{
		if (ParentNode == NULL)
			return false;

		Node* node = _Search(Data);
			
		if (node == NULL)
			return false;

		if (node->Right == NULL && node->Left == NULL)
		{
			node->Prev->Right == node ? node->Prev->Right = NULL : node->Prev->Left = NULL;
			delete node;
			_Size--;
			return true;
		}

		if (node->Right == NULL && node->Left != NULL)
		{
			node->Prev->Right == node ? node->Prev->Right = node->Left : node->Prev->Left = node->Left;
			delete node;
			_Size--;
			return true;
		}

		if (node->Right != NULL && node->Left == NULL)
		{
			node->Prev->Right == node ? node->Prev->Right = node->Right : node->Prev->Left = node->Right;
			delete node;
			_Size--;
			return true;
		}

		Node* Temp = node;
		node = node->Right;
			
		while (node->Left != NULL)
		{
			node = node->Left;
		}

		if (node->Right != NULL)
		{
			node->Prev->Left = node->Right;
			Temp->Data = node->Data;
		}

		else 
		{
			node->Prev->Left = NULL;
			Temp->Data = node->Data;
		}

		delete node;
		_Size--;
		return true;
	}

	bool ContainsKey(Key Value)
	{
		//function to check if key exists
		Node* node = _Search(Value);

		return node != NULL;
	}

	Node* Find(Key Value)
	{
		Node* node = _Search(Value);

		return node;
	}

	int MinKeyValue()
	{
		return _MinKeyValue;
	}

	int MaxKeyValue()
	{
		return _MaxKeyValue;
	}

	int Height()
	{
		_GetHeight(ParentNode);
		return _Height;
	}

	bool IsEmpty()
	{
		return ParentNode == NULL;
	}

	bool Update(Key KeyValue)
	{
		Node* node = ParentNode;

		if (node == NULL)
			return false;

		while (node != NULL)
		{
			if (node->KeyValue == KeyValue)
			{
				cin >> node->Data >> node->Data2 >> node->Data3 >> node->Data4 >> node->Data4 >> node->Data5;
				return true;
			}
			node->KeyValue > KeyValue ? node = node->Left : node = node->Right;
		}

		return false;
		
	}

	bool Update(Key KeyValue, Value Data = Value(), Value2 Data2 = Value2(), Value3 Data3 = Value3(), Value4 Data4 = Value4(), Value5 Data5 = Value5(), bool duplicate = false)
	{
		Node* node = ParentNode;

		if (node == NULL)
			return false;

		while (node != NULL)
		{
			if (node->KeyValue == KeyValue)
			{
				node->Data = Data;
				node->Data2 = Data2;
				node->Data3 = Data3;
				node->Data4 = Data4;
				node->Data5 = Data5;
				return true;
			}
			node->KeyValue > KeyValue ? node = node->Left : node = node->Right;
		}

		return false;
	}

	bool Replace(Key KeyValue , Node* node2)
	{
		Node* node = ParentNode;

		if (node == NULL)
			return false;

		while (node != NULL)
		{
			if (node->KeyValue == KeyValue)
			{
				node = node2;
				return true;
			}
			node->KeyValue > KeyValue ? node = node->Left : node = node->Right;
		}

		return false;
	}

	void PrintKeys()
	{
		for (Node* &I : _vList)
			cout << I->KeyValue << " ";
	}

	void Values()
	{
		for (Node*& I : _vList)
			cout << "{ " << I->Data << " , " << I->Data2 << " , " << I->Data3 << " , " << I->Data4 << " , " << I->Data5  << " }" << endl;
	}

	bool SwapValues(Key Key1, Key Key2)
	{
		Node* Node1 = _Search(Key1);

		if (Node1 == NULL)
			return false;

		Node* Node2 = _Search(Key2);

		if (Node2 == NULL)
			return false;

		Node* Temp = new Node();
		Temp->Data = Node1->Data;
		Temp->Data2 = Node1->Data2;
		Temp->Data3 = Node1->Data3;
		Temp->Data4 = Node1->Data4;
		Temp->Data5 = Node1->Data5;
		Node1->Data = Node2->Data;
		Node1->Data2 = Node2->Data2;
		Node1->Data3 = Node2->Data3;
		Node1->Data4 = Node2->Data4;
		Node1->Data5 = Node2->Data5;
		Node2->Data = Temp->Data;
		Node2->Data2 = Temp->Data2;
		Node2->Data3 = Temp->Data3;
		Node2->Data4 = Temp->Data4;
		Node2->Data5 = Temp->Data5;

		return true;
	}

	int Levels()
	{
		return _Height - 1;
	}

	int KeysBetween(int From, int To , bool FromInclusive = false , bool ToInclusive = false)
	{
		int Counter = 0;

		int Arr[_Size];

		if (FromInclusive && ToInclusive)
		{
			for (Node*& I : _vList)
				if (I->KeyValue >= FromInclusive && I->KeyValue <= ToInclusive)
				{
					Arr[Counter] = I->KeyValue;
					Counter++;
				}
		}

		else if (FromInclusive)
		{
			for (Node*& I : _vList)
				if (I->KeyValue >= FromInclusive && I->KeyValue < ToInclusive)
				{
					Arr[Counter] = I->KeyValue;
					Counter++;
				}
		}

		else if (ToInclusive)
		{
			for (Node*& I : _vList)
				if (I->KeyValue > FromInclusive && I->KeyValue <= ToInclusive)
				{
					Arr[Counter] = I->KeyValue;
					Counter++;
				}
		}

		else
		{
			for (Node*& I : _vList)
				if (I->KeyValue > FromInclusive && I->KeyValue < ToInclusive)
				{
					Arr[Counter] = I->KeyValue;
					Counter++;
				}
		}

		return Arr;
	}

	int* KeysBetween2(int From, int To, bool FromInclusive = false, bool ToInclusive = false)
	{
		int Counter = 0, counter = 0;

		int* ptr = new int[Counter];
	}

	void Print()
	{
		cout << "Print By Insertion Order:\n";
		PrintByInsertionOrder();
		cout << endl << endl << endl;
		cout << "Print InOrder:\n";
		PrintInOrder();
		cout << endl << endl << endl;
		cout << "Print PostOrder:\n";
		PrintPostOrder();
		cout << endl << endl << endl;
		cout << "Print PreOrder:\n";
		PrintPreOrder();
	}

	~clsMap()
	{
		DeleteHelper2(ParentNode);
	}

};


