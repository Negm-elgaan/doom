// Binary Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "clsBinaryTree.h"

using namespace std;

int main()
{
    clsBinaryTree <int> BST;
    /*BST.Insert(4);
    BST.Insert(3);
    BST.Insert(5);
    BST.Insert(2);
    BST.Insert(1);
    BST.Insert(6);
    BST.Insert(7);*/
    BST.Insert(10);
    BST.Insert(5);
    BST.Insert(2);
    BST.Insert(1);
    BST.Insert(15);
    BST.Insert(20);
    int x = BST.Previous(2);
    cout << x;
    cout << endl << endl;
    //BST.Print();
    //cout << endl << endl << "after balance\n\n";
    BST.ReBalance();
    cout << endl << endl << "after balance\n\n";
    //BST.Print();
    BST << BST;
    //BST.Insert(50);
  //BST.Insert(30);
  //  BST.Insert(20);
  //  BST.Insert(40);
  //  BST.Insert(10);
  //  BST.Insert(25);
  //  /*BST.Insert(10);
  //  BST.Insert(5);
  //  BST.Insert(20);
  //  BST.Insert(3);
  //  BST.Insert(8);*/
  //  BST.Print();
  //  cout << endl << endl;
  //  BST.ReBalance();
  //  cout << endl << endl;
  //  BST.Print();
  //  //cout << BST.Height();
  //  cout << endl << endl;
    //clsBinaryTree <int> BinaryTree;
    //
    //BinaryTree.Insert(50);
    //BinaryTree.Insert(30);
    //BinaryTree.Insert(70);
    //BinaryTree.Insert(20);
    //BinaryTree.Insert(40);
    //BinaryTree.Insert(10);
    //BinaryTree.Insert(25);
    //BinaryTree.Insert(60);
    //BinaryTree.Insert(80);
    //BinaryTree.Insert(55);
    //BinaryTree.Insert(65);
    //BinaryTree.Insert(53);
    //BinaryTree.Print();
    //cout << endl << endl;
    ////BinaryTree.ReBalance();
    //BinaryTree.Clear();
    //BinaryTree.Print();
    //BinaryTree.Insert(50);
    //BinaryTree.Insert(30);
    //BinaryTree.Insert(70);
    //BinaryTree.Insert(20);
    //BinaryTree.Insert(40);
    //BinaryTree.Insert(10);
    //BinaryTree.Insert(25);
    //BinaryTree.Insert(60);
    //BinaryTree.Insert(80);
    //BinaryTree.Insert(55);
    //BinaryTree.Insert(65);
    //BinaryTree.Insert(53);
    //cout << endl << endl;
    //BinaryTree.Print();
   /* cout << BinaryTree.Height();
    cout << endl;
    BinaryTree.Remove(50);
    BinaryTree.Insert(50);
    BinaryTree.Print();
    cout << endl << BinaryTree.ParentNode->Data << " " << BinaryTree.ParentNode->Left->Data;
    int x = BinaryTree.search(53);*/
    //cout << x << endl;
    //BinaryTree.printRight();
    //BinaryTree.print();
    //cout << "hi";
    
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
