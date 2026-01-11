template <size_t K> class KDTree
{
    class Node
    {
        int data[K];
        int axis; //0 for x , 1 for y , 2      for z
        int depth;
        Node* prev;
        Node* right;
        Node* left;

        friend KDTree;
    };

    Node* _RootNode;

    void PrintHelperPre(Node* node) const
    {
        if (node == nullptr)
            return;

        std::cout << "( ";
        for (size_t i = 0; i < K; i++)
        {
            std::cout << node->data[i] << " , ";
        }
        std::cout << " )" << std::endl;

        PrintHelperPre(node->left);

        PrintHelperPre(node->right);
    }

    void PrintHelperPost(Node* node) const
    {
        if (node == nullptr)
            return;

        PrintHelperPost(node->left);

        PrintHelperPost(node->right);

        std::cout << "( ";
        for (size_t i = 0; i < K; i++)
        {
            std::cout << node->data[i] << " , ";
        }
        std::cout << " )" << std::endl;

    }

    void PrintHelperIn(Node* node) const
    {
        if (node == nullptr)
            return;

        PrintHelperIn(node->left);

        std::cout << "( ";
        for (size_t i = 0; i < K; i++)
        {
            std::cout << node->data[i] << " , ";
        }
        std::cout << " )" << std::endl;

        PrintHelperIn(node->right);

    }

    public:

        KDTree()
        {
            _RootNode = nullptr;
        }

        void Insert(int(&arr)[K])
        {
            if (!_RootNode)
            {
                _RootNode = new Node();
                _RootNode->depth = 0;
                _RootNode->prev = nullptr;
                _RootNode->right = nullptr;
                _RootNode->left = nullptr;
                _RootNode->axis = _RootNode->depth % K;

                for (size_t i = 0; i < K; i++)
                {
                    _RootNode->data[i] = arr[i];
                }

                return;
            }

            Node* TempNode = _RootNode;
            Node* NewNode = new Node();

            for (size_t i = 0; i < K; i++)
            {
                NewNode->data[i] = arr[i];
            }

            while (true)
            {
                bool Dup = true;
                for (size_t i = 0; i < K; i++)
                {
                    if (NewNode->data[i] != TempNode->data[i])
                    {
                        Dup = false;
                        break;
                    }
                }

                if (Dup)
                {
                    std::cout << "Key already exists!\n";
                    delete NewNode;
                    return; 
                }

                if (NewNode->data[TempNode->axis] >= TempNode->data[TempNode->axis])
                {
                    if (TempNode->right == nullptr)
                    {
                        break;
                    }
                    else
                    {
                        TempNode = TempNode->right;
                    }
                }

                else if (NewNode->data[TempNode->axis] < TempNode->data[TempNode->axis])
                {
                    if (TempNode->left == nullptr)
                    {
                        break;
                    }
                    else
                    {
                        TempNode = TempNode->left;
                    }
                }
            }

            NewNode->data[TempNode->axis] >= TempNode->data[TempNode->axis] ? TempNode->right = NewNode : TempNode->left = NewNode;
            NewNode->prev = TempNode;
            NewNode->depth = TempNode->depth + 1;
            NewNode->axis = NewNode->depth % K;
            NewNode->left = nullptr;
            NewNode->right = nullptr;
        }

        void Print() const
        {
            std::cout << "InOrder: ";
            PrintHelperIn(_RootNode);
            std::cout << std::endl;
            std::cout << "PreOrder: ";
            PrintHelperPre(_RootNode);
            std::cout << std::endl;
            std::cout << "PostOrder: ";
            PrintHelperPost(_RootNode);
            std::cout << std::endl;
        }
};
