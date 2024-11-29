// Double Pointer 2d array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
int main()
{
    int size = 0 , size2 = 0;
    cin >> size;
    int** Dptr = new int* [size];
    for (int i = 0; i < size; i++)
    {
        cin >> size2;
        Dptr[i] = new int[size2];
        for (int j = 0; j < size2; j++)
        {
            cin >> Dptr[i][j];
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size2; j++)
        {
           cout << Dptr[i][j] << " ";
        }
        cout << endl;
    }
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
