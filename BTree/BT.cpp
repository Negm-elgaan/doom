#include <iostream>

using namespace std;

class BTree
{
    class Node
    {
        private:

            int MaxKeysInNode = 0;
            int* DataPtr;
            int CurrentNumOfElementsInNode = 0;
            Node** Children = nullptr;
            int CurrentNumberOfChildrenInNode = 0;
            Node* Prev;

        public:

            Node(int MaxKeys)
            {
                MaxKeysInNode = MaxKeys;
                DataPtr = new int[MaxKeys + 1]; // each Node can hold up to (M - 1) number of keys where m is MaxKeysInNode but we allocate up to m to detect overflow
                Children = new Node* [MaxKeys + 2]; // Each Node can Hold up to M number of children but we ... to detect overflow
                for (int i = 0 ; i <= MaxKeys ; i++)
                {
                    Children[i] = nullptr;
                }
                Prev = nullptr;
            }

            bool SplitChild(int index) // what remains is handling segfault then testing by hand and paper
            {
                if (index < 0 || index > MaxKeysInNode)
                {
                    return false;
                }

                for (int i = CurrentNumberOfChildrenInNode ; i > index ; i--) // shifting children to index
                {
                    //Node* Temp = children[i];
                    Children[i] = Children[i - 1] ;
                }

                Children[index + 1] = new Node(MaxKeysInNode);

                int j = 0;

                for (int i = (MaxKeysInNode / 2) + 1 ; i < MaxKeysInNode ; i++)
                {
                    Children[index + 1]->DataPtr[j] = Children[index]->DataPtr[i];
                    Children[index + 1]->Children[j] = Children[index]->Children[i];
                    Children[index]->Children[i]->Prev = Children[index + 1];
                    Children[index]->DataPtr[i] = -1;
                    j++;
                }

                Children[index + 1]->Children[j] = Children[index]->Children[MaxKeysInNode];

                if (Children[index + 1]->Children[j] != nullptr)
                {
                    Children[index + 1]->Children[j]->Prev = Children[index + 1];
                }

                j++;
                //int parentindex = BinarySearch(Children[index]->DataPtr[MaxKeysInNode / 2] , 0 , CurrentNumOfElementsInNode) // Binary search to get the index to insert the median of the child into the parent

                for (int i = CurrentNumOfElementsInNode; i > index ; i--) // shifting elements one index to fit the child's median
                {
                    DataPtr[i + 1] = DataPtr[i];
                }

                DataPtr[index] = Children[index]->DataPtr[MaxKeysInNode / 2];

                for (int i = j ; i < MaxKeysInNode ; i++)
                {
                    Children[index + 1]->DataPtr[i] = -1;
                }

                Children[index]->CurrentNumberOfChildrenInNode = (MaxKeysInNode / 2) + 1;
                Children[index]->CurrentNumOfElementsInNode = MaxKeysInNode / 2;
                Children[index + 1]->CurrentNumberOfChildrenInNode = j;
                Children[index + 1]->CurrentNumOfElementsInNode = MaxKeysInNode / 2;

                CurrentNumberOfChildrenInNode++;
                CurrentNumOfElementsInNode++;

                return true;
            }
    };
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
