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
            cout << _Data << endl;
            _Next.Print();
        }
};

template <typename T, typename... Args> class clsTupleArray
{
    clsTuple<T , Args...>* _TuplePtr;
    int _Size = 0;

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

        int Size()
        {
            return _Size;
        }

        void SetItem(int Index, T&& Data, Args&&... args)
        {
            _TuplePtr[Index].Insert(forward<T>(Data), forward<Args>(args)...);
        }

        clsTuple<T, Args...> GetItem(int Index = 0)
        {
            return _TuplePtr[Index];
        }

        void print()
        {
            for (int i = 0; i < _Size; i++)
            {
                _TuplePtr[i].Print();
            }
        }

        ~clsTupleArray()
        {
            delete[] _TuplePtr;
        }
};
