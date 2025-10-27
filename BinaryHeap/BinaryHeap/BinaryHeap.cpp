#include <iostream>

using namespace std;

class MinBinaryHeap
{
        int* _BHptr = nullptr;
        int _Size = 0 , _CurrentNumber = 0;

        void _HeapifyUp(int Index = 0)
        {
            if (Index == 0)
                return;

            if (_BHptr[Index] >= _BHptr[(Index - 1) / 2])
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
            int smallest = Index;

            // Check left child first
            if (left < _CurrentNumber)
            {
                if (_BHptr[left] < _BHptr[smallest])
                    smallest = left;

                // Only check right child if left exists
                if (right < _CurrentNumber && _BHptr[right] < _BHptr[smallest])
                    smallest = right;
            }

            if (smallest != Index)
            {
                /*_BHptr[Index] = _BHptr[Index] ^ _BHptr[smallest];
                _BHptr[smallest] = _BHptr[Index] ^ _BHptr[smallest];
                _BHptr[Index] = _BHptr[Index] ^ _BHptr[smallest];*/
                swap(_BHptr[Index], _BHptr[smallest]);
                _HeapifyDown(smallest);
            }
        }

    public:

        MinBinaryHeap()
        {
            cin >> _Size;

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

        int ExtractMin()
        {
            int Min = _BHptr[0];

            _BHptr[0] = _BHptr[_CurrentNumber - 1];

            _CurrentNumber--;

            _HeapifyDown();

            return Min;
        }

        int GetMin()
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

        ~MinBinaryHeap()
        {
            delete[] _BHptr;
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

int main() {
    // Test case 1: Small heap (size 5)
    {
        cout << "Testing small heap (size 5):\n";
        MinBinaryHeap bh;

        // Insert elements in random order
        bh.Insert(5);
        bh.Insert(3);
        bh.Insert(8);
        bh.Insert(1);
        bh.Insert(2);

        bh.Print(); // Should show heap structure

        cout << "Extracting min: " << bh.ExtractMin() << endl; // Should be 1
        cout << "Extracting min: " << bh.ExtractMin() << endl; // Should be 2
        cout << "Extracting min: " << bh.ExtractMin() << endl; // Should be 3
        cout << "Extracting min: " << bh.ExtractMin() << endl; // Should be 5
        cout << "Extracting min: " << bh.ExtractMin() << endl; // Should be 8

        cout << "Is empty: " << boolalpha << bh.IsEmpty() << endl; // Should be true
    }

    // Test case 2: Edge cases
    {
        cout << "\nTesting edge cases (size 3):\n";
        MinBinaryHeap bh;

        // Test parent/child relationships
        bh.Insert(2);
        bh.Insert(1);
        bh.Insert(3);

        cout << "Parent of index 1: " << bh.BinaryHeapIndexParent(1) << endl; // Should be 1
        cout << "Left child of index 0: " << bh.BinaryHeapIndexLeftChild(0) << endl; // Should be 1
        cout << "Right child of index 0: " << bh.BinaryHeapIndexRightChild(0) << endl; // Should be 3

        // Test invalid indices
        cout << "Parent of index 0: " << bh.BinaryHeapIndexParent(0) << endl; // Should be -1
        cout << "Right child of index 2: " << bh.BinaryHeapIndexRightChild(2) << endl; // Should be -1
    }

    // Test case 3: Duplicate values
    {
        cout << "\nTesting duplicate values (size 6):\n";
        MinBinaryHeap bh;

        bh.Insert(4);
        bh.Insert(2);
        bh.Insert(4);
        bh.Insert(2);
        bh.Insert(1);
        bh.Insert(1);

        bh.Print();

        cout << "Extracting mins: ";
        while (!bh.IsEmpty()) {
            cout << bh.ExtractMin() << " "; // Should be 1, 1, 2, 2, 4, 4
        }
        cout << endl;
    }

    // Test case 4: Large heap
    {
        cout << "\nTesting large heap (size 10):\n";
        MinBinaryHeap bh;

        // Insert in descending order (worst case for heapify up)
        bh.Insert(10);
        bh.Insert(9);
        bh.Insert(8);
        bh.Insert(7);
        bh.Insert(6);
        bh.Insert(5);
        bh.Insert(4);
        bh.Insert(3);
        bh.Insert(2);
        bh.Insert(1);

        bh.Print();

        cout << "Extracting all elements: ";
        while (!bh.IsEmpty()) {
            cout << bh.ExtractMin() << " "; // Should be 1 to 10 in order
        }
        cout << endl;
    }
    // ======== MAX HEAP TESTS ========

    cout << "\n\n========= MAX HEAP TESTS =========\n";

    cout << "\nTesting small heap (size 5):\n";
    {
        MaxBinaryHeap bh;
        // Input 5
        bh.Insert(5);
        bh.Insert(3);
        bh.Insert(8);
        bh.Insert(1);
        bh.Insert(2);
        bh.Print(); // Expected: 8 on top
        cout << "Extracting max: ";
        while (!bh.IsEmpty())
            cout << bh.ExtractMax() << " ";
        cout << endl; // Expected: 8 5 3 2 1
    }

    cout << "\nTesting edge cases (size 3):\n";
    {
        MaxBinaryHeap bh;
        // Input 3
        bh.Insert(2);
        bh.Insert(9);
        bh.Insert(3);
        bh.Print(); // Expected: 9 top
        cout << "Extracted max: " << bh.ExtractMax() << endl; // Expected 9
        bh.Print(); // Remaining heap top should be 3
    }

    cout << "\nTesting duplicates (size 6):\n";
    {
        MaxBinaryHeap bh;
        // Input 6
        bh.Insert(4);
        bh.Insert(2);
        bh.Insert(4);
        bh.Insert(2);
        bh.Insert(1);
        bh.Insert(1);
        cout << "Extracting: ";
        while (!bh.IsEmpty())
            cout << bh.ExtractMax() << " ";
        cout << endl; // Expected: 4 4 2 2 1 1
    }

    cout << "\nTesting large heap (size 10):\n";
    {
        MaxBinaryHeap bh;
        // Input 10
        for (int i = 1; i <= 10; ++i)
            bh.Insert(i);
        cout << "Extracting: ";
        while (!bh.IsEmpty())
            cout << bh.ExtractMax() << " ";
        cout << endl; // Expected: 10 9 8 7 6 5 4 3 2 1
    }

    cout << "\nTesting alternating insertions (size 10):\n";
    {
        MaxBinaryHeap bh;
        // Input 10
        int vals[] = { 10, 5, 8, 3, 7, 2, 9, 1, 6, 4 };
        for (int v : vals)
            bh.Insert(v);
        bh.Print(); // Top should be 10
        cout << "Extracting: ";
        while (!bh.IsEmpty())
            cout << bh.ExtractMax() << " ";
        cout << endl; // Expected: 10 9 8 7 6 5 4 3 2 1
    }

    return 0;
}
