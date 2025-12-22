#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

#define uLL unsigned long long

template <class T , class F> class clsHashTable
{
private:

	uLL (*HashFunc)(T) = nullptr;
	//static int FirstSeedComponent;
	//static int SecondSeedComponent;

	class Node
	{
		//int index;
		std::vector<std::pair<T,F>> _VTuple;
		friend class clsHashTable;
	};

	template <class T> static unsigned char* CastByte(T& Data)
	{
		return reinterpret_cast<unsigned char*>(&Data);
	}

	int _Size;
	int _Capacity;

	Node * _PtrArray = nullptr;

	//optional<T>* _HashedKeyArray = nullptr;

	//optional<T>** _ValueArray = nullptr;

	//optional<clsTupleArray>** DoubleTupleArray = nullptr;

	uLL _Hash(T Key)
	{
		uLL HashValue = 14695981039346656037ULL;

		//int Seed = FirstSeedComponent * SecondSeedComponent;
		if constexpr (std::is_same_v<T, std::string>)
		{
			for (int i = 0; Key[i] != '\0'; i++)
			{
				HashValue = HashValue ^ int(Key[i]);
				HashValue *= 16777619;
			}
		}
		
		else
		{


			unsigned char* ptr = CastByte(Key);

			for (size_t i = 0; i < sizeof(Key); i++)
			{
				HashValue = HashValue ^ (uLL)ptr[i];
				HashValue *= 16777619;
			}

		}

		HashValue = (HashValue + 5) % _Size;

		return HashValue;
	}

	static uLL _HashFunction(T Key)
	{
		uLL HashValue = 14695981039346656037ULL;

		//int Seed = FirstSeedComponent * SecondSeedComponent;
		if constexpr (std::is_same_v<T, std::string>)
		{
			for (int i = 0; Key[i] != '\0'; i++)
			{
				HashValue = HashValue ^ int(Key[i]);
				HashValue *= 16777619;
			}
		}

		else
		{


			unsigned char* ptr = CastByte(Key);

			for (size_t i = 0; i < sizeof(Key); i++)
			{
				HashValue = HashValue ^ (uLL)ptr[i];
				HashValue *= 16777619;
			}

		}

		return  HashValue;
	}

	uLL _Hasher(T Key)
	{
		uLL HashValue = HashFunc(Key);

		HashValue = (HashValue + 5) % _Size;

		return HashValue;
	}

	void _Resize()
	{
		int OldSize = _Size;
		_Size *= 2;

		Node* TempArray = new Node[_Size];

		_Capacity = 0;

		for (int i = 0 ; i < OldSize ; i++)
		{

			for (std::pair <T, F>& Tuple : _PtrArray[i]._VTuple)
			{
				uLL HashKey = _Hasher(Tuple.first);
				TempArray[HashKey]._VTuple.push_back(std::move(Tuple));
				_Capacity++;
			}
			
		}		

		delete[] _PtrArray;
		_PtrArray = TempArray;
	}

public:

	clsHashTable()
	{
		_Size = 100;
		_Capacity = 0;
		//_HashedKeyArray = new optional<T>[100];
		//_ValueArray = new * optional<T>[100];
		_PtrArray = new Node [100];
		HashFunc = &clsHashTable<T, F>::_HashFunction;
	}

	clsHashTable(int n , uLL(*HashFun)(T) = nullptr)
	{
		if (n <= 0)
		{
			n = 100;
		}
		_Size = n;
		_Capacity = 0;
		//_HashedKeyArray = new optional<T>[n];
		//_ValueArray = new * optional<T>[n];
		_PtrArray = new Node [_Size];
		HashFunc = HashFun;
		if (!HashFunc)
		{
			HashFunc = &clsHashTable<T, F>::_HashFunction;
		}
	}

	void Insert(T Key, F Value)
	{
		uLL HashKey = _Hasher(Key);

		for (std::pair <T, F>& Tuple : _PtrArray[HashKey]._VTuple)
		{
			if (Tuple.first == Key)
			{
				Tuple.second = Value;
				return;
			}
		}

		_PtrArray[HashKey]._VTuple.push_back({ Key, Value });
		_Capacity++;

		if ((float)_Capacity / _Size >= 0.75)
		{
			_Resize();
		}

		return;
	}

	F GetValue(T Key)
	{
		int HashKey = _Hasher(Key);
		for (std::pair <T , F>& Tuple : _PtrArray[HashKey]._VTuple)
		{
			if (Tuple.first == Key)
			{
				return Tuple.second;
			}
		}

		return F();
	}

	int Capacity()
	{
		return _Capacity;
	}

	bool IsEmpty()
	{
		return _Capacity == 0;
	}

	int Size()
	{
		return _Size;
	}

	~clsHashTable()
	{
		delete[] _PtrArray;
	}

};

//template <class T, class F> int clsHashTable<T, F>::FirstSeedComponent = 1;
//template <class T, class F> int clsHashTable<T, F>::SecondSeedComponent = 2;
