#pragma once
#include <iostream>

using namespace std;

template <class Key = int, class Value = int, class Value2 = char, class Value3 = double, class Value4 = bool, class Value5 = string> class clsDynamicArray
{
private:
	int _Size = 0;
	static class Array
	{
	public:
		Value Data;
		Value2 Data2;
		Value3 Data3;
		Value4 Data4;
		Value5 Data5;
		/*Node* Right;
				Node* Left;
				Node* Prev;*/
	};
	Array* _PtrArray;
	Array* _TempArray;
	Array* _RevArray;
	Key* _KeyArray;
	int search(Key KeyValue)
	{
		for (int i = 0; i < _Size; i++)
			if (_KeyArray[i] == KeyValue)
				return i;
		return NULL;
	}
public:
	clsDynamicArray(int Size)
	{
		if (Size < 0)
			Size = 0;
		_Size = Size;
		_PtrArray = new Array[_Size];
		_RevArray = new Array[_Size];
		_KeyArray = new Key[_Size];
	}

	bool SetItem(Key KeyValue, Value Data = NULL, Value2 Data2 = NULL, Value3 Data3 = NULL, Value4 Data4 = NULL, Value5 = NULL)
	{
		if (search(KeyValue) == NULL || _Size < 0)
			return false;
		_PtrArray[search(KeyValue)]->Data = Data;
		_PtrArray[search(KeyValue)]->Data2 = Data2;
		_PtrArray[search(KeyValue)]->Data3 = Data3;
		_PtrArray[search(KeyValue)]->Data4 = Data4;
		_PtrArray[search(KeyValue)]->Dat5 = Data5;
		_RevArray[_Size - search(KeyValue) - 1]->Data = Data;
		_RevArray[_Size - search(KeyValue) - 1]->Data2 = Data2;
		_RevArray[_Size - search(KeyValue) - 1]->Data3 = Data3;
		_RevArray[_Size - search(KeyValue) - 1]->Data4 = Data4;
		_RevArray[_Size - search(KeyValue) - 1]->Data5 = Data5;
		return true;
	}

	bool IsEmpty()
	{
		return _Size == 0;
	}

	int Size()
	{
		return _Size;
	}

	void PrintList()
	{
		for (int i = 0; i < _Size; i++)
		{
			cout << "Key : " << _KeyArray->KeyValue << "{ " << _PtrArray[i]->Data << " , " << _PtrArray[i]->Data2 << " , " << _PtrArray[i]->Data3 << " , " << _PtrArray[i]->Data4 << " , " << _PtrArray[i]->Data5 << " }" << endl;
		}

		cout << "\n";

		return;
	}

	void Resize(int NewSize = 0)
	{
		if (NewSize == _Size)
			return;

		if (NewSize < 0)
			NewSize = 0;

		_TempArray = new T[NewSize];

		//limit the original size to the new size if it is less.
		if (NewSize < _Size)
			_Size = NewSize;

		delete[] _RevArray;
		_RevArray = new T[NewSize];
		//copy all data from original array until the size
		for (int i = 0; i < _Size; i++)
		{
			_TempArray[i] = _PtrArray[i];
			_RevArray[NewSize - i - 1] = _PtrArray[i];
		}

		_Size = NewSize;

		delete[] _PtrArray;
		_PtrArray = _TempArray;
		return;


	}

	bool InsertAt(Key KeyValue, Value Data = NULL, Value2 Data2 = NULL, Value3 Data3 = NULL, Value4 Data4 = NULL, Value5 = NULL)
	{
		if (Index < 0 || Index > _Size)
			return false;

		_Size++;

		delete[] _RevArray;

		_TempArray = new T[_Size];
		_RevArray = new T[_Size];
		int j = 0;
		for (int i = 0; i < _Size; i++)
		{
			if (i == Index)
			{
				_TempArray[i] = Data;
				_RevArray[_Size - i - 1] = Data;
			}
			else
			{
				_TempArray[i] = _PtrArray[j];
				_RevArray[_Size - i - 1] = _PtrArray[j];
				j++;
			}
		}


		delete[] _PtrArray;
		_PtrArray = _TempArray;

		return true;
	}

	bool InsertAtBeginning(T Value)
	{
		return InsertAt(0, Value);
	}

	bool InsertAtEnd(T Value)
	{
		return InsertAt(_Size, Value);
	}

	bool InsertBefore(int Index, T Value)
	{
		return InsertAt(Index - 1, Value);
	}

	bool InsertAfter(int Index, T Value)
	{
		return InsertAt(Index + 1, Value);
	}

	bool DeleteItemAt(int index)
	{

		if (index >= _Size || index < 0)
		{
			return false;
		}

		_Size--;

		delete[] _RevArray;

		_RevArray = new T[_Size];

		_TempArray = new T[_Size];

		//copy all before index
		for (int i = 0; i < index; i++)
		{
			_TempArray[i] = _PtrArray[i];
			_RevArray[_Size - i] = _PtrArray[i];
		}

		//copy all after index
		for (int i = index + 1; i < _Size + 1; i++)
		{
			_TempArray[i - 1] = _PtrArray[i];
			_RevArray[_Size - i] = _PtrArray[i];
		}

		delete[] _PtrArray;
		_PtrArray = _TempArray;
		return true;

	}

	int Find(T Data)
	{
		for (int i = 0; i < _Size; i++)
		{
			if (_PtrArray[i] == Data)
				return i;
		}

		return -1;
	}

	bool DeleteItem(T Data)
	{
		int Index = Find(Data);

		return DeleteItemAt(Index);
	}

	bool DeleteFirstitem()
	{
		return DeleteItemAt(0);
	}

	bool DeleteLastitem()
	{
		return DeleteItemAt(_Size - 1);
	}

	T Getitem(int Index = 0)
	{
		if (Index < 0 || Index >= _Size)
			return NULL;

		return _PtrArray[Index];
	}

	bool Reverse()
	{
		if (_PtrArray == nullptr)
			return false;

		_TempArray = _PtrArray;
		_PtrArray = _RevArray;
		_RevArray = _TempArray;

		return true;
	}

	void Clear()
	{
		delete[] _PtrArray;
		delete[] _RevArray;
	}

	void Delete()
	{
		_Size = 0;
		delete[] _PtrArray;
		delete[] _RevArray;
		_PtrArray = new T[0];
		_RevArray = new T[0];
	}

	/*bool DeleteItem(int Index = 0)
	{
		if (Index < 0 || Index >= _Size)
			return false;
		Resize(_Size - 1 , true , 0);
	}
	void Resize(int NewSize = 0 , bool MarkForDelete = false , int IndexDel = -1)
	{
		if (NewSize == _Size)
			return;

		if (NewSize < 0)
			NewSize = 0;

		_TempArray = new T[NewSize];

		//limit the original size to the new size if it is less.
		if (NewSize < _Size)
			_Size = NewSize;

		delete[] _RevArray;
		_RevArray = new T[NewSize];
		int j = 0;
		//copy all data from original array until the size
		for (int i = 0; i < _Size; i++)
		{
			if (MarkForDelete == true && IndexDel != -1)
				if (j == IndexDel)
				{
					j++;
				}
			if (j == _Size + 1)
				break;
			_TempArray[i] = _PtrArray[j];
			_RevArray[NewSize - i - 1] = _PtrArray[j];
			j++;
		}
		_Size = NewSize;

		delete[] _PtrArray;
		_PtrArray = _TempArray;
		return;


	}*/

	~clsDynamicArray()
	{
		delete[] _PtrArray;
		delete[] _TempArray;
		delete[] _RevArray;
	}
};

