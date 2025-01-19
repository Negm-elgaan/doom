#pragma once
#include <iostream>
#include <thread>
#include <cstdarg>
#include <vector>
#include <algorithm>
#include <math.h>
#include "clsDynamicArray.h"

using namespace std;

template <class Key = int , class Value = int , class Value2 = char , class Value3 = double , class Value4 = bool , class Value5 = string , class Value6 = clsDynamicArray <int> , class Value7 = clsDynamicArray <string> , class Value8 = clsDynamicArray <char> , class Value9 = clsDynamicArray <double> , class... Value10 /*, class Value7 = char*, class Value8 = double*, class Value9 = bool*, class Value10 = string * */ > class clsMap
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

	void DeleteHelper(Node* node)
	{
		if (node == NULL)
			return;

		// Recursively delete the left and right subtrees
		thread T1(&clsMap::DeleteHelper , this , node->Left);
		thread T2 (&clsMap::DeleteHelper ,this , node->Right);
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
		//Value10 Data10;
		Node* Right;
		Node* Left;
		Node* Prev;
		template <class T> class Noder
		{
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
			this->Insert(node->KeyValue , node->Data  , node->Data2 , node->Data3 , node->Data4 , node->Data5);
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

	template <typename... Args>void Insert2(Key Value , Args...args)
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

	void Insert(Key KeyValue , Value Data = Value(), Value2 Data2 = Value2(), Value3 Data3 = Value3(), Value4 Data4 = Value4(), Value5 Data5 = Value5() , bool duplicate = false)
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
			ParentNode->Left = NULL;
			ParentNode->Right = NULL;
			ParentNode->Prev = NULL;
			Temp1 = ParentNode;
			_vList.push_back(ParentNode);
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
			cout << "Key : " << node->KeyValue << " { " << node->Data << " , " << node->Data2 << " , " << node->Data3 << " , " << node->Data4 << " , " << node->Data5 << " }" << endl;
		}
	}

	int Size()
	{
		return _Size;
	}

	void Clear()
	{
		DeleteHelper(ParentNode);
		_vList.~vector();
		_vList = vector<Node*>();
		ParentNode = NULL;
		_Size = 0;
	}

	void ReBalance()
	{
		_GetIn(ParentNode);
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

	bool Update(Key Value)
	{
		Node* node = _Search(Value);

		if (node == NULL)
			return false;

		cin >> node->Data >> node->Data2 >> node->Data3 >> node->Data4 >> node->Data4 >> node->Data5;

		return true;
	}

	void PrintKeys()
	{
		for (Node* &I : _vList)
			cout << I->KeyValue << " ";
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
		DeleteHelper(ParentNode);
	}

};


