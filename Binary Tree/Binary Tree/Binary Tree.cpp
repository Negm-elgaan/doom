// Binary Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*#include <iostream>
#include "clsBinaryTree.h"
int main()
{
    clsBinaryTree <int> BinaryTree;
    
    BinaryTree.Insert(4);
    BinaryTree.Insert(2);
    BinaryTree.Insert(5);
    BinaryTree.Insert(8);
    BinaryTree.Insert(7);
    BinaryTree.Insert(3);
    BinaryTree.printLeft();
    BinaryTree.printRight();
    cout << "hi";
    
}
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
    Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
    map<int, Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};

class LRUCache : public Cache
{
    int s = 0;
public:
    LRUCache(int cap)
    {
        cp = cap;
    }
    void set(int key, int Val)
    {
        Node* NewNode;
        if (head == NULL)
        {
            NewNode = new Node(key, Val);
            head = NewNode;
            tail = NewNode;
            mp.insert({ key,NewNode });
            s++;
            return;
        }

        NewNode = new Node(tail, NULL, key, Val);
        //tail->next = NewNode;
        NewNode->prev = tail;
        tail = NewNode;
        mp.insert({ key,NewNode });
        s++;

        if (s > cp)
        {
            Node* temp = head;
            head = head->next;
            mp.erase(temp->key);
            s--;
            return;
        }
    }

    int get(int key)
    {
        if (mp.empty())
            return -1;
        if (mp[key] == NULL)
        {
            return -1;
        }
        int val = mp[key]->value;
        return val;


    }
};
int main() {
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        }
        else if (command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
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
