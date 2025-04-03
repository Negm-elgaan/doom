// Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>

using namespace std;

template <class T> class clsGraph
{
    class Node;

    /*Node* node1 = nullptr;
    Node* node2 = nullptr;*/

    int size = 0 , currentnodenum = 0;

    int** Edges;

    Node** DNodes;

   /* void _Search(Node* node , T Data)
    {
        for (int i = 0; i < size; i++)
        {
            if (DNodes[i]->Data == Data)
            {
                node = DNodes[i];
                return;
            }
        }

    }*/

    //bool _CheckEdge(T Data1, T Data2)
    //{
    //    /*Node* node1 = Search(Data1);
    //    Node* node2 = Search(Data2);*/

    //    thread t1(&clsGraph::_Search, this, node1, Data1);
    //    thread t2(&clsGraph::_Search, this, node2, Data2);

    //    t1.join();
    //    t2.join();

    //    if (node1 == nullptr || node2 == nullptr)
    //        return false;

    //    return Edges[node1->index][node2->index] == 1;

    //}

public:
    
    class Node
    {
        public:
            T Data;
            int index;
    };

    clsGraph()
    {
        cin >> size;
        Edges = new int* [size];
        for (int i = 0; i < size; i++)
        {
            Edges[i] = new int[size];
            for (int j = 0; j < size; j++)
            {
                Edges[i][j] = 0;
            }
        }

        DNodes = new Node * [size]();

        return;
    }

    clsGraph(int Size)
    {
        size = Size;
        Edges = new int* [size];
        for (int i = 0; i < size; i++)
        {
            Edges[i] = new int[size];
            for (int j = 0; j < size; j++)
            {
                Edges[i][j] = 0;
            }
        }

        DNodes = new Node * [size]();

        return;
    }

    void InsertNode(T Data)
    {
        if (currentnodenum == size)
        {
            cout << "\nsize is full!\n";
            return;
        }

        Node* Pnode = new Node;
        Pnode->Data = Data;
        Pnode->index = currentnodenum;

        DNodes[currentnodenum] = Pnode;

        currentnodenum++;

        return;
        
    }

    void InsertEdge(int Index1 , int Index2 , int Weight = 1)
    {
        if (Index1 >= size || Index2 >= size)
        {
            cout << "\nOut of Bounds\n";
            return;
        }

        Edges[Index1][Index2] = Weight;

        return;

    }

    bool CheckNode(T Data)
    {
        for (int i = 0; i < currentnodenum; i++)
        {
            if (DNodes[i]->Data == Data)
                return true;
        }

        return false;
    }
    
    Node* Search(T Data)
    {
        for (int i = 0; i < size; i++)
        {
            if (DNodes[i]->Data == Data)
                return DNodes[i];
        }

        return nullptr;
    }

    bool CheckEdge(T Data1, T Data2)
    {
        Node* node1 = Search(Data1);
        Node* node2 = Search(Data2);

        if (node1 == nullptr || node2 == nullptr)
            return false;

        return Edges[node1->index][node2->index] != 0;

    }

    void PrintEdge(T Data1, T Data2)
    {
        Node* node1 = Search(Data1);
        Node* node2 = Search(Data2);

        if (node1 == nullptr || node2 == nullptr)
        {
            cout << "\nElement not found!\n";
            return;
        }
            
        cout << Edges[node1->index][node2->index] << endl;

        return; 
    }

    bool RemoveEdge(int Index1 , int Index2)
    {
        if (Index1 >= size || Index2 >= size)
        {
            cout << "\nOut of Bounds\n";
            return false;
        }

        Edges[Index1][Index2] = 0;

        return true;
    }

    bool CheckEdge(Node node1, Node node2)
    {

    }

    void PrintMatrix()
    {
        
        cout << "  ";

        for (int i = 0; i < size; i++)
        {
            cout << DNodes[i]->Data << " ";
        }

        cout << endl ;

        for (int i = 0; i < size; i++)
        {
            cout << DNodes[i]->Data << " ";

            for (int j = 0; j < size; j++)
            {
                cout << Edges[i][j] << " ";
            }
            cout << endl;
        }

        return;
    }

    void PrintNodes()
    {
        for (int i = 0; i < currentnodenum; i++)
        {
            cout << DNodes[i]->Data << " ";
        }

        cout << endl;

    }

    ~clsGraph()
    {

        for (int i = 0; i < size; i++)
            delete DNodes[i];

        delete[] DNodes;

        /*delete node1;
        delete node2;*/

        for (int i = 0; i < size; i++)
            delete[] Edges[i];

        delete[] Edges;
    }
};
int main()
{
    clsGraph<char> g;  // Create a graph of integers

    // Insert some nodes
    g.InsertNode('A');  // Insert node with data 1
    g.InsertNode('B');  // Insert node with data 2
    g.InsertNode('C');  // Insert node with data 3
    g.InsertNode('D');
    g.InsertNode('E'); 
    g.InsertNode('F'); // Insert node with data 4

    // Insert some edges
    //g.InsertEdge(0, 1);  // Edge between node 0 and node 1
    //g.InsertEdge(0, 2);  // Edge between node 0 and node 2
    //g.InsertEdge(1, 2);  // Edge between node 1 and node 2
    //g.InsertEdge(2, 3);  // Edge between node 2 and node 3

    g.InsertEdge(0, 1);  
    g.InsertEdge(0, 3);  
    g.InsertEdge(1, 2);  
    g.InsertEdge(2, 4);  
    g.InsertEdge(3, 4);  
    g.InsertEdge(4, 5);  

    g.PrintMatrix();

    cout << g.CheckEdge('A', 'D');

    //cout << endl << g.CheckNode(5);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
