// Map.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "clsMap.h"
#include "clsDynamicArray.h"

int main()
{
    clsDynamicArray <int> lister(9);
    clsMap <> BinaryTree;
    BinaryTree.Insert(50, 21, 'O', 13.333, true, "Omar");
    BinaryTree.Insert(30, 22, 'A', 12.45, false, "Alex");
    BinaryTree.Insert(70, 25, 'B', 15.89, true, "Ben");
    BinaryTree.Insert(20, 19, 'C', 9.876, false, "Clara");
    BinaryTree.Insert(40, 24, 'D', 14.567, true, "David");
    BinaryTree.Insert(10, 17, 'E', 8.123, false, "Ella");
    BinaryTree.Insert(25, 23, 'F', 11.234, true, "Fay");
    BinaryTree.Insert(60, 28, 'G', 16.78, false, "George");
    BinaryTree.Insert(80, 29, 'H', 17.567, true, "Hannah");
    BinaryTree.Insert(55, 26, 'I', 13.456, false, "Ian");
    BinaryTree.Insert(65, 27, 'J', 14.789, true, "Jack");
    BinaryTree.Insert(53, 30, 'K', 12.345, false, "Katie");
    //BinaryTree.Insert(50, 21, 'O', 13.333333, true, "Omar");   // Example 1: Key 50, different values for the other parameters
    //BinaryTree.Insert(30, 10, 'A', 7.5, false, "Alice");       // Example 2: Key 30, different values for the other parameters
    //BinaryTree.Insert(70, 35, 'B', 10.1, true, "Bob");         // Example 3: Key 70, different values for the other parameters
    //BinaryTree.Insert(20, 15, 'C', 11.0, false, "Charlie");    // Example 4: Key 20, different values for the other parameters
    //BinaryTree.Insert(40, 25, 'D', 9.8, true, "David");       // Example 5: Key 40, different values for the other parameters
    //BinaryTree.Insert(10, 5, 'E', 8.5, false, "Eve");         // Example 6: Key 10, different values for the other parameters
    //BinaryTree.Insert(25, 30, 'F', 12.7, true, "Frank");      // Example 7: Key 25, different values for the other parameters
    //BinaryTree.Insert(60, 50, 'G', 6.5, false, "Grace");      // Example 8: Key 60, different values for the other parameters
    //BinaryTree.Insert(80, 40, 'H', 5.5, true, "Hannah");      // Example 9: Key 80, different values for the other parameters
    //BinaryTree.Insert(55, 60, 'I', 14.2, false, "Ian");       // Example 10: Key 55, different values for the other parameters
    //BinaryTree.Insert(65, 45, 'J', 16.1, true, "Jack");       // Example 11: Key 65, different values for the other parameters
    //BinaryTree.Insert(53, 55, 'K', 13.9, false, "Katie");     // Example 12: Key 53, different values for the other parameters

    BinaryTree.PrintPostOrder();
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
