// Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

template <class T> class clsGraph
{
    class Node
    {
        public:    
            T Data;
            int index;
    };

    int size = 0 , currentnodenum = 0;

    int** Edges;

    Node* Nodes;

public:
    
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

        Nodes = new Node[size];
    }

    void InsertNode(T Data)
    {
        if (currentnodenum == size)
        {
            cout << "\nsize is full!\n";
            return;
        }

        Node node;
        node.Data = Data;
        node.index = currentnodenum;

        Nodes[currentnodenum] = node;

        currentnodenum++;

        return;
        
    }

    void InsertEdge(int Index1, int Index2)
    {
        if (Index1 >= size || Index2 >= size)
        {
            cout << "\nOut of Bounds\n";
            return;
        }

        Edges[Index1][Index2] = 1;

        return;

    }
    
    void PrintMatrix()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << Edges[i][j] << " ";
            }
            cout << endl;
        }

        return;
    }

    ~clsGraph()
    {
        delete[] Nodes;

        for (int i = 0; i < size; i++)
            delete[] Edges[i];

        delete[] Edges;
    }
};
int main()
{
    clsGraph<int> g;  // Create a graph of integers

    // Insert some nodes
    g.InsertNode(1);  // Insert node with data 1
    g.InsertNode(2);  // Insert node with data 2
    g.InsertNode(3);  // Insert node with data 3
    g.InsertNode(4);  // Insert node with data 4

    // Insert some edges
    g.InsertEdge(0, 1);  // Edge between node 0 and node 1
    g.InsertEdge(0, 2);  // Edge between node 0 and node 2
    g.InsertEdge(1, 2);  // Edge between node 1 and node 2
    g.InsertEdge(2, 3);  // Edge between node 2 and node 3

    g.PrintMatrix();
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
