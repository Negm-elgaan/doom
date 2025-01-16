// Map.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "clsMap.h"
#include "clsDynamicArray.h"

int main()
{
    clsDynamicArray <int> lister(9);
    lister.SetItem(0, 1);
    lister.SetItem(1, 2);
    lister.SetItem(2, 3);
    lister.SetItem(3, 4);
    lister.SetItem(4, 5);
    lister.SetItem(5, 6);
    lister.SetItem(6, 7);
    lister.SetItem(7, 8);
    lister.SetItem(8, 9);
    int* ptr;
    ptr = new int[5];
    ptr[0] = 0;
    ptr[1] = 1;
    ptr[2] = 2;
    ptr[3] = 3;
    ptr[4] = 4;
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
    //BinaryTree.PrintInOrder();
    //BinaryTree.Clear();
    BinaryTree.PrintKeys();
    cout << endl << endl;
    cout << endl << endl;
    BinaryTree.PrintInOrder();
   // BinaryTree.ReBalance();
    cout << endl << endl;

    BinaryTree.Clear();
    BinaryTree.PrintInOrder();
    //BinaryTree.PrintInOrder();
    cout << endl << endl;
    cout << BinaryTree.Height() << endl << endl;
    //BinaryTree.PrintByInsertionOrder();
    //BinaryTree.Remove(10);
    BinaryTree.Insert(50, 21, 'O', 13.333333, true, "Omar");   // Example 1: Key 50, different values for the other parameters
    BinaryTree.Insert(30, 10, 'A', 7.5, false, "Alice");       // Example 2: Key 30, different values for the other parameters
    BinaryTree.Insert(70, 35, 'B', 10.1, true, "Bob");         // Example 3: Key 70, different values for the other parameters
    BinaryTree.Insert(20, 15, 'C', 11.0, false, "Charlie");    // Example 4: Key 20, different values for the other parameters
    BinaryTree.Insert(40, 25, 'D', 9.8, true, "David");       // Example 5: Key 40, different values for the other parameters
    BinaryTree.Insert(10, 5, 'E', 8.5, false, "Eve");         // Example 6: Key 10, different values for the other parameters
    BinaryTree.Insert(25, 30, 'F', 12.7, true, "Frank");      // Example 7: Key 25, different values for the other parameters
    BinaryTree.Insert(60, 50, 'G', 6.5, false, "Grace");      // Example 8: Key 60, different values for the other parameters
    BinaryTree.Insert(80, 40, 'H', 5.5, true, "Hannah");      // Example 9: Key 80, different values for the other parameters
    BinaryTree.Insert(55, 60, 'I', 14.2, false, "Ian");       // Example 10: Key 55, different values for the other parameters
    BinaryTree.Insert(65, 45, 'J', 16.1, true, "Jack");       // Example 11: Key 65, different values for the other parameters
    BinaryTree.Insert(53, 55, 'K', 13.9, false, "Katie");     // Example 12: Key 53, different values for the other parameters
    cout << endl << endl;
    cout << endl << endl;
    BinaryTree.PrintKeys();
    cout << endl << endl;
    cout << endl << endl;
    BinaryTree.PrintInOrder();
    cout << BinaryTree.Height() << endl << endl;
    BinaryTree.PrintInOrder();

    cout << endl << endl << endl;

    /*clsMap <> Map = move(BinaryTree);
    cout << "New Map:";
    Map.PrintInOrder();
    cout << endl << endl << endl;
    cout << "Old Map:";
    BinaryTree.PrintInOrder();*/

    clsMap <> Map2 ;
    Map2.Insert(15, 22, 'X', 10.5, true, "Xander");      // Example 1: Key 15, different values for the other parameters
    Map2.Insert(18, 8, 'Y', 5.6, false, "Yvonne");       // Example 2: Key 18, different values for the other parameters
    Map2.Insert(36, 11, 'Z', 3.4, true, "Zoe");          // Example 3: Key 36, different values for the other parameters
    Map2.Insert(48, 33, 'W', 9.1, false, "William");     // Example 4: Key 48, different values for the other parameters
    Map2.Insert(12, 19, 'V', 7.8, true, "Victoria");     // Example 5: Key 12, different values for the other parameters
    Map2.Insert(29, 17, 'U', 6.3, false, "Uma");         // Example 6: Key 29, different values for the other parameters
    Map2.Insert(41, 24, 'T', 8.9, true, "Tom");          // Example 7: Key 41, different values for the other parameters
    Map2.Insert(32, 14, 'S', 12.0, false, "Sally");      // Example 8: Key 32, different values for the other parameters
    Map2.Insert(77, 29, 'R', 13.2, true, "Riley");       // Example 9: Key 77, different values for the other parameters
    Map2.Insert(51, 26, 'Q', 11.7, false, "Quinn");      // Example 10: Key 51, different values for the other parameters
    BinaryTree += Map2;
    //BinaryTree.PrintInOrder();
    cout << endl << endl << endl;
    BinaryTree << Map2;
    cout << endl << endl << endl;
    BinaryTree.PrintInOrder();
    cout << endl << endl << BinaryTree.Size() << " " << Map2.Size();
    int x = BinaryTree % Map2;
    cout << endl << endl << x << endl << endl;
    cout << "Key : " << BinaryTree[50]->KeyValue << " { " << BinaryTree[50]->Data << " , " << BinaryTree[50]->Data2 << " , " << BinaryTree[50]->Data3 << " , " << BinaryTree[50]->Data4 << " , " << BinaryTree[50]->Data5 << " }" << endl;
    //BinaryTree.PrintPostOrder();
   /* clsMap <int,int,string,char,string,string,bool,float,double> Map;
    Map.Insert(1,100,"Hello" , 'O' , "Omar" , "Negm",1,3.14,17272.334);*/
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
