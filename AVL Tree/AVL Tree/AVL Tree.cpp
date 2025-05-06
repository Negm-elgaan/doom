// AVL Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "clsAVLTree.h"

int main() 
{
    clsAVLTree tree;
    clsAVLTree tree2;
    clsAVLTree tree3;
    // Complex Bulk Insert Test (16 nodes)
    // This sequence will force multiple rotations at various depths.
    std::vector<int> seq = {
        50, 20, 70, 10, 30, 25, 27, 26,
        40, 60, 80, 65, 75, 85, 5, 15
    };
    std::vector<int> seq2 = { 50, 20, 70, 10, 30, 25 };
    std::vector<int> seq3 = { 30, 20, 10};
    std::vector<int> seq4 = { 10, 20, 30 };
    for (int x : seq3) {
        tree.Insert(x);
    }
    tree.PrintRootData();
    tree.Print();

    cout << "Tree2:";
    for (int x : seq4) {
        tree2.Insert(x);
    }
    tree2.PrintRootData();
    tree2.Print();

    cout << "Final Test!:";
    for (int x : seq) {
         tree3.Insert(x);
    }
    tree3.PrintRootData();
    tree3.Print();
    // Expected output for a correctly?balanced AVL tree:
    //
    // InOrder:   5 10 15 20 25 26 27 30 40 50 60 65 70 75 80 85 
    // PreOrder:  30 20 10 5 15 26 25 27 60 50 40 70 65 80 75 85 
    // PostOrder: 5 15 10 25 27 26 20 40 50 65 75 85 80 70 60 30 
    cout << endl;
    
    return 0;
}