#include <iostream>

using namespace std;

class BinaryHeap
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

        BinaryHeap()
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

        ~BinaryHeap()
        {
            delete[] _BHptr;
        }
};

int main()
{
    std::cout << "Hello World!\n";
}