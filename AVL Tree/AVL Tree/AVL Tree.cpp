// AVL Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "clsAVLTree.h"

int main() 
{
    clsAVLTree <int> tree;
    clsAVLTree <int> tree2;
    clsAVLTree <int> tree3;
    clsAVLTree <int> tree4;
    clsAVLTree <int> tree5;
    // Complex Bulk Insert Test (16 nodes)
    // This sequence will force multiple rotations at various depths.
    std::vector<int> seq = {
        50, 20, 70, 10, 30, 25, 27, 26,
        40, 60, 80, 65, 75, 85, 5, 15
    };
    std::vector<int> seq2 = { 50, 20, 70, 10, 30, 25 };
    std::vector<int> seq3 = { 30, 20, 10};
    std::vector<int> seq4 = { 10, 20, 30 };
    std::vector<int> seq5 = { 50, 25, 75, 15, 35, 60, 90, 10, 20, 30, 40, 55, 65, 80, 95, 5, 12, 28, 33, 45, 52, 58, 63, 70, 85, 92, 97 };
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
    tree3.PrintRootData();
    cout << endl;
    tree3.Remove(30);
    cout << "tree3 after del:\n";
    tree3.PrintRootData();
    tree3.Print();
    // Expected output for a correctly?balanced AVL tree:
    //
    // InOrder:   5 10 15 20 25 26 27 30 40 50 60 65 70 75 80 85 
    // PreOrder:  30 20 10 5 15 26 25 27 60 50 40 70 65 80 75 85 
    // PostOrder: 5 15 10 25 27 26 20 40 50 65 75 85 80 70 60 30 
    cout << endl;
    for (int x : seq5) {
        tree4.Insert(x);
    }
    tree4.PrintRootData();
    tree4.Print();
    cout << endl;
    /*InOrder:   5 10 12 15 20 25 28 30 33 35 40 45 50 52 55 58 60 63 65 70 75 80 85 90 92 95 97
PreOrder:  50 25 15 10 5 12 20 35 30 28 33 40 45 75 60 55 52 58 65 63 70 90 80 85 95 92 97
PostOrder: 5 12 10 20 15 28 33 30 45 40 35 25 52 58 55 63 70 65 60 85 80 92 97 95 90 75 50*/
    std::vector<int> complexSeq = {
    100, 50, 150, 25, 75, 125, 175, 12, 37, 60, 80, 112, 137, 162, 187,
    6, 18, 30, 43, 55, 65, 70, 85, 110, 115, 130, 140, 160, 170, 185, 190,
    5, 7, 17, 19, 29, 31, 42, 44, 54, 56, 64, 66, 69, 71, 84, 86, 109, 111,
    114, 116, 129, 131, 139, 141, 159, 161, 169, 171, 184, 186, 189, 191 
    };

    clsAVLTree <int> complexTree;
    for (int x : complexSeq) {
        complexTree.Insert(x);
    }
    cout << endl << endl;
    complexTree.PrintRootData();
    complexTree.Print();
    cout << endl << endl;

    clsAVLTree<int> tree7;
    std::vector<int> seq100;
    for (int i = 1; i <= 100; ++i) {
        seq100.push_back(i);
        tree7.Insert(i);
    }

    // After all inserts, the AVL property has rebalanced the tree.
    tree7.Print(/*root*/);
    return 0;
}