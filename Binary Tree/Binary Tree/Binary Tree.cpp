// Binary Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "clsBinaryTree.h"

using namespace std;

int main()
{
    clsBinaryTree <int> BinaryTree;
    
    /*BinaryTree.Insert(4);
    BinaryTree.Insert(2);
    BinaryTree.Insert(5);
    BinaryTree.Insert(8);
    BinaryTree.Insert(7);
    BinaryTree.Insert(3);*/
    /*BinaryTree.Insert(10);
    BinaryTree.Insert(5);
    BinaryTree.Insert(20);
    BinaryTree.Insert(3);
    BinaryTree.Insert(7);
    BinaryTree.Insert(15);
    //BinaryTree.Insert();
    BinaryTree.Insert(4);
    BinaryTree.Insert(6);
    BinaryTree.Insert(2);*/
    BinaryTree.Insert(50);
    BinaryTree.Insert(30);
    BinaryTree.Insert(70);
    BinaryTree.Insert(20);
    BinaryTree.Insert(40);
    BinaryTree.Insert(10);
    BinaryTree.Insert(25);
    BinaryTree.Insert(60);
    BinaryTree.Insert(80);
    BinaryTree.Insert(55);
    BinaryTree.Insert(65);
    BinaryTree.Insert(53);
    BinaryTree.printLeft();
    BinaryTree.printRight();
    cout << "hi";
    
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
