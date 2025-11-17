#include <iostream>

using namespace std;

template <class T , class F = string>

class MinBinaryHeap
{
    pair<T, F>* _HeapPair  = nullptr;
    pair <T, F>* _TempPair = nullptr;
    int _Size = 0, _CurrentNumber = 0;

    void _HeapifyUp(int Index = 0)
    {
        if (Index == 0)
            return;

        /*if (_PtrArray[Index] >= _PtrArray[(Index - 1) / 2])
            return;*/

        if (_HeapPair[Index].first >= _HeapPair[(Index - 1) / 2].first)
        {
            return;
        }

        /*int Temp = _PtrArray[Index];
        _PtrArray[Index] = _PtrArray[(Index - 1) / 2];
        _PtrArray[(Index - 1) / 2] = Temp;*/

        pair<T, F> Temp = _HeapPair[Index];
        _HeapPair[Index] = _HeapPair[(Index - 1) / 2];
        _HeapPair[(Index - 1) / 2] = Temp;
        _HeapifyUp((Index - 1) / 2);

    }

    void _HeapifyDown(int Index = 0)
    {
        int left = (2 * Index) + 1;
        int right = (2 * Index) + 2;
        int smallest = Index;

        // Check left child first
        if (left < _CurrentNumber)
        {
            if (_HeapPair[left].first < _HeapPair[smallest].first)
                smallest = left;

            // Only check right child if left exists
            if (right < _CurrentNumber && _HeapPair[right].first < _HeapPair[smallest].first)
                smallest = right;
        }

        if (smallest != Index)
        {
            /*_BHptr[Index] = _BHptr[Index] ^ _BHptr[smallest];
            _BHptr[smallest] = _BHptr[Index] ^ _BHptr[smallest];
            _BHptr[Index] = _BHptr[Index] ^ _BHptr[smallest];*/
            swap(_HeapPair[Index], _HeapPair[smallest]);
            _HeapifyDown(smallest);
        }
    }

public:

    MinBinaryHeap()
    {
        cin >> _Size;

        _HeapPair = new pair<T, F>[_Size];
    }

    MinBinaryHeap(int size)
    {
        if (size < 0)
            size = 0;
        _Size = size;
        _HeapPair = new pair<T, F>[_Size];
    }

    bool IsEmpty()
    {
        return _CurrentNumber == 0;
    }

    void Insert(T Data)
    {
        if (_CurrentNumber == _Size)
            return;

        _HeapPair[_CurrentNumber] = { Data , F()};

        _HeapifyUp(_CurrentNumber);

        _CurrentNumber++;
    }

    void Insert(T Data , F Node)
    {
        if (_CurrentNumber == _Size)
            return;

        _HeapPair[_CurrentNumber] = { Data , Node };

        _HeapifyUp(_CurrentNumber);

        _CurrentNumber++;
    }

    pair<T, F> ExtractMin()
    {
        pair<T, F> Min = _HeapPair[0];

        _HeapPair[0] = _HeapPair[_CurrentNumber - 1];

        _CurrentNumber--;

        _HeapifyDown(0);

        return Min;
    }

    pair <T,F> GetMin()
    {
        return _HeapPair[0];
    }

    pair <T,F> BinaryHeapIndexParent(int Index)
    {

        if (Index < 0 || Index >= _CurrentNumber)
        {
            return { T(), F() };
        }

        return _HeapPair[(Index - 1) / 2];
    }

    pair <T,F> BinaryHeapIndexLeftChild(int Index)
    {
        if (Index < 0 || Index >= _CurrentNumber)
        {
            return { T(), F() };
        }

        if ((2 * Index) + 1 >= _CurrentNumber)
            return { T(), F() };

        return _HeapPair[(2 * Index) + 1];
    }

    pair <T,F> BinaryHeapIndexRightChild(int Index)
    {
        if (Index < 0 || Index >= _CurrentNumber)
        {
            return { T(), F() };
        }

        if ((2 * Index) + 2 >= _CurrentNumber)
            return { T(), F() };

        return _HeapPair[(2 * Index) + 2];

    }

    void Print()
    {
        cout << endl;

        for (int i = 0; i < _CurrentNumber; i++)
            cout << _HeapPair[i].first << " " << _HeapPair[i].second;

        cout << endl;
    }

	pair<T,F>& operator[](int x)
	{
		return _HeapPair[x];
	}

	/*bool SetItem(int index, T Data)
	{
		if (index > _Size - 1 || _Size < 0)
			return false;
		_PtrArray[index] = Data;
		_RevArray[_Size - index - 1] = Data;
		return true;
	}*/

	int Size()
	{
		return _Size;
	}

	void Resize(int NewSize = 0)
	{
		if (NewSize == _Size)
			return;

		if (NewSize < 0)
			NewSize = 0;

        _TempPair = new pair<T, F>[NewSize];

		//limit the original size to the new size if it is less.
		if (NewSize < _Size)
			_Size = NewSize;

		for (int i = 0; i < _CurrentNumber; i++)
		{
            _TempPair[i] = _HeapPair[i];
		}

		_Size = NewSize;

        delete[] _HeapPair;
        _HeapPair = _TempPair;
		return;


	}

	/*bool InsertAt(int Index, T Data)
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
	}*/

	bool Remove()
	{
        if (_CurrentNumber < 1)
        {
            return false;
        }

        pair<T,F> temper = _HeapPair[_CurrentNumber - 1];
        _HeapPair[_CurrentNumber - 1] = _HeapPair[0];
        _HeapPair[0] = temper;

        _CurrentNumber--;
        
        _HeapifyDown(0);
		return true;

	}

	int Find(T Data)
	{
		for (int i = 0; i < _CurrentNumber; i++)
		{
			if (_HeapPair[i].first == Data)
				return i;
		}

		return -1;
	}

	/*bool DeleteItem(T Data)
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
	}*/

	pair <T,F> Getitem(int Index = 0)
	{
		if (Index < 0 || Index >= _CurrentNumber)
            return { T() , F() };

		return _HeapPair[Index];
	}

	void Clear()
	{
        delete[] _HeapPair;
	}

	void Delete()
	{
		_Size = 0;
        delete[] _HeapPair;
        _HeapPair = new pair<T, F>[0];
	}

    ~MinBinaryHeap()
    {
        delete[] _HeapPair;
    }
};

class MaxBinaryHeap
{
    int* _BHptr = nullptr;
    int _Size = 0, _CurrentNumber = 0;

    void _HeapifyUp(int Index = 0)
    {
        if (Index == 0)
            return;

        if (_BHptr[Index] <= _BHptr[(Index - 1) / 2])
            return;

        int Temp = _BHptr[Index];
        _BHptr[Index] = _BHptr[(Index - 1) / 2];
        _BHptr[(Index - 1) / 2] = Temp;
        _HeapifyUp((Index - 1) / 2);

    }

    void _HeapifyDown(int Index = 0)
    {
        int left = (2 * Index) + 1;
        int right = (2 * Index) + 2;
        int Biggest = Index;

        // Check left child first
        if (right < _CurrentNumber)
        {
            if (_BHptr[right] > _BHptr[Biggest])
                Biggest = right;
        }

        if (left < _CurrentNumber && _BHptr[left] > _BHptr[Biggest])
            Biggest = left;

        if (Biggest != Index)
        {
            /*_BHptr[Index] = _BHptr[Index] ^ _BHptr[smallest];
            _BHptr[smallest] = _BHptr[Index] ^ _BHptr[smallest];
            _BHptr[Index] = _BHptr[Index] ^ _BHptr[smallest];*/
            swap(_BHptr[Index], _BHptr[Biggest]);
            _HeapifyDown(Biggest);
        }
    }

public:

    MaxBinaryHeap()
    {
        cin >> _Size;

        _BHptr = new int[_Size];

    }

    MaxBinaryHeap(int size)
    {
        _BHptr = new int[_Size];
    }

    bool IsEmpty()
    {
        return _CurrentNumber == 0;
    }

    void Insert(int Data)
    {
        if (_CurrentNumber == _Size)
            return;

        _BHptr[_CurrentNumber] = Data;

        _HeapifyUp(_CurrentNumber);

        _CurrentNumber++;
    }

    int ExtractMax()
    {
        int Max = _BHptr[0];

        _BHptr[0] = _BHptr[_CurrentNumber - 1];

        _CurrentNumber--;

        _HeapifyDown();

        return Max;
    }

    int GetMax()
    {
        return _BHptr[0];
    }

    int BinaryHeapIndexParent(int Index)
    {

        if (Index < 0 || Index >= _Size)
        {
            return -1;
        }

        return _BHptr[(Index - 1) / 2];
    }

    int BinaryHeapIndexLeftChild(int Index)
    {
        if (Index < 0 || Index >= _Size)
        {
            return -1;
        }

        if ((2 * Index) + 1 >= _Size)
            return -1;

        return _BHptr[(2 * Index) + 1];
    }

    int BinaryHeapIndexRightChild(int Index)
    {
        if (Index < 0 || Index >= _Size)
        {
            return -1;
        }

        if ((2 * Index) + 2 >= _Size)
            return -1;

        return _BHptr[(2 * Index) + 2];

    }

    void Print()
    {
        cout << endl;

        for (int i = 0; i < _CurrentNumber; i++)
            cout << _BHptr[i] << " ";

        cout << endl;
    }

    ~MaxBinaryHeap()
    {
        delete[] _BHptr;
    }
};
