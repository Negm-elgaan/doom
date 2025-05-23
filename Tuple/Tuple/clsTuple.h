#include <iostream>
#include <utility>

using namespace std;

int GlobalIndex = 0;

template <typename... Args>
class clsTuple;

template <typename T>
class clsTuple<T>
{
    T _Data;
    int _Index;

    public:

        clsTuple() 
        {
       
        }

        clsTuple(T&& Data)
        {
            _Data = forward<T>(Data);
            _Index = GlobalIndex;
        }

        void Insert()
        {
            cin >> _Data;
        }

        void Insert(T&& Data)
        {
            _Data = forward<T>(Data);
        }

        T Get(int Index)
        {
            if (_Index == Index)
                return _Data;

            return NULL;
        }

        void Print()
        {
            cout << _Data << endl;
        }
};

template <typename T, typename... Args>
class clsTuple<T, Args...>
{
    T _Data;
    int _Index = 0;
    clsTuple<Args...> _Next;  

    public:

        clsTuple()
        {
            cout << "\nTuple Created:\n";
        }

        clsTuple(T&& Data, Args&&... args) : _Next(forward<Args>(args)...)
        {
            _Data = forward<T>(Data);
            _Index = GlobalIndex;
            GlobalIndex++;
        }

        void Insert()
        {
            cin >> _Data;
            _Next.Insert();
        }

        void Insert(T&& Data, Args&&... args)
        {
            _Data = forward<T>(Data); 
            _Index = GlobalIndex;
            GlobalIndex++;
            _Next.Insert(forward<Args>(args)...);  
        }

        T Get(int Index = 0)
        {
            if (_Index == Index)
                return _Data;

            _Next.Get(Index);
        }

        void Print()
        {
            cout << _Data << " ";
            _Next.Print();
        }
};

template <typename T, typename... Args> class clsTupleArray
{
    clsTuple<T , Args...>* _TuplePtr;
    clsTupleArray<T, Args...>** _TuplePtrRef;
    int _Size = 0;
    int _RefSize = 0;

    public:

        clsTupleArray()
        {
            cout << "\nEnter Size:\n";
            cin >> _Size;

            _TuplePtr = new clsTuple<T, Args...>[_Size];
        }

        clsTupleArray(int size)
        {
            _Size = size;
            _TuplePtr = new clsTuple<T, Args...>[_Size];
        }

        void operator<< (clsTupleArray& TupleArray)
        {
            TupleArray.print();
        }

        void operator>> (clsTupleArray& TupleArray)
        {
            TupleArray.Insert();
        }

        clsTuple<T, Args...> Front()
        {
            return _TuplePtr[0];
        }

        clsTuple<T, Args...> Back()
        {
            return _TuplePtr[_Size - 1];
        }

        int Size()
        {
            return _Size;
        }

        bool IsEmpty()
        {
            return _TuplePtr == nullptr;
        }

        void Insert()
        {
            for (int i = 0; i < _Size; i++)
                _TuplePtr[i].Insert();

            return;
        }

        bool SetItem(int Index, T&& Data, Args&&... args)
        {
            if (Index < 0 || Index >= _Size)
                return false;

            _TuplePtr[Index].Insert(forward<T>(Data), forward<Args>(args)...);
            return true;
        }

        clsTuple<T, Args...> GetItem(int Index = 0)
        {
            if (Index < 0 || Index >= _Size)
                return false;

            return _TuplePtr[Index];
        }

        bool InitializeRef(int RefSize)
        {
            if (RefSize <= 0)
                return false;

            _RefSize = RefSize;
            _TuplePtrRef = new clsTupleArray<T, Args...>* [_RefSize];

            return true;
        }

        bool SetRef(int Index, clsTupleArray<T, Args...>* TupleArray)
        {
            if (Index < 0 || Index >= _RefSize)
                return false;

            _TuplePtrRef[Index] = TupleArray;

            return true;
        }

        bool DeleteItemAt(int Index = 0)
        {
            if (Index < 0 || Index >= _Size)
                return false;

            delete _TuplePtr[Index];
        }

        void print()
        {
            for (int i = 0; i < _Size; i++)
            {
                _TuplePtr[i].Print();
            }

            cout << endl;

        }

        ~clsTupleArray()
        {
            delete[] _TuplePtr;

            for (int i = 0; i < _RefSize; i++)
                delete[] _TuplePtrRef[i];

            delete[] _TuplePtrRef;

        }
};
