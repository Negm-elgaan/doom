class KDTree
{
    class Node
    {
        int data[3];
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

        std::cout << "( " << node->data[0] << " , " << node->data[1] << " , " << node->data[2] << " )" << std::endl;

        PrintHelperPre(node->left);

        PrintHelperPre(node->right);
    }

    void PrintHelperPost(Node* node) const
    {
        if (node == nullptr)
            return;

        PrintHelperPost(node->left);

        PrintHelperPost(node->right);

        std::cout << "( " << node->data[0] << " , " << node->data[1] << " , " << node->data[2] << " )" << std::endl;

    }

    void PrintHelperIn(Node* node) const
    {
        if (node == nullptr)
            return;

        PrintHelperIn(node->left);

        std::cout << "( " << node->data[0] << " , " << node->data[1] << " , " << node->data[2] << " )" << std::endl;

        PrintHelperIn(node->right);

    }

    public:

        KDTree()
        {
            _RootNode = nullptr;
        }

        void Insert(int x, int y, int z)
        {
            if (!_RootNode)
            {
                _RootNode = new Node();
                _RootNode->depth = 0;
                _RootNode->prev = nullptr;
                _RootNode->right = nullptr;
                _RootNode->left = nullptr;
                _RootNode->axis = _RootNode->depth % 3;
                _RootNode->data[0] = x;
                _RootNode->data[1] = y;
                _RootNode->data[2] = z;
                return;
            }

            Node* TempNode = _RootNode;
            Node* NewNode = new Node();
            NewNode->data[0] = x;
            NewNode->data[1] = y;
            NewNode->data[2] = z;

            while (true)
            {

                if (NewNode->data[2] == TempNode->data[2] && NewNode->data[0] == TempNode->data[0] && NewNode->data[1] == TempNode->data[1])
                {
                    std::cout << "Key already exists!\n";
                    delete NewNode;
                    return;
                }

                if (TempNode->axis == 0) // X-axis
                {

                    if (NewNode->data[0] >= TempNode->data[0])
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

                    else if (NewNode->data[0] < TempNode->data[0])
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
                else if (TempNode->axis == 1) // Y-axis
                {

                    if (NewNode->data[1] >= TempNode->data[1])
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

                    else if (NewNode->data[1] < TempNode->data[1])
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
                else // Z-axis
                {

                    if (NewNode->data[2] >= TempNode->data[2])
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

                    else if (NewNode->data[2] < TempNode->data[2])
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
            }

            if (TempNode->axis == 0)
            {
                NewNode->data[0] >= TempNode->data[0] ? TempNode->right = NewNode : TempNode->left = NewNode;
                NewNode->prev = TempNode;
                NewNode->depth = TempNode->depth + 1;
                NewNode->axis = NewNode->depth % 3;
            }
            else if (TempNode->axis == 1)
            {
                NewNode->data[1] >= TempNode->data[1] ? TempNode->right = NewNode : TempNode->left = NewNode;
                NewNode->prev = TempNode;
                NewNode->depth = TempNode->depth + 1;
                NewNode->axis = NewNode->depth % 3;
            }
            else
            {
                NewNode->data[2] >= TempNode->data[2] ? TempNode->right = NewNode : TempNode->left = NewNode;
                NewNode->prev = TempNode;
                NewNode->depth = TempNode->depth + 1;
                NewNode->axis = NewNode->depth % 3;
            }

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
