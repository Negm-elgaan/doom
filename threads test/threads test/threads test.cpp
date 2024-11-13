// threads test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
* 
*/
#include <iostream>

#include <thread>
using namespace std;

int int_index(int* arr, int s, int (*cmp)(int))
{
    int i;
    for (i = 0; i < s; i++)
    {
        if (cmp(arr[i]) != 0)
            return i;
    }
    return -1;
}
int is_98(int elem)
{
    return (98 == elem);
}
int is_strictly_positive(int elem)
{
    return (elem > 0);
}
int abs_is_98(int elem)
{
    return (elem == 98 || -elem == 98);
}

int main()
{
    int x, i;
    cin >> x;
    int* arr;
    arr = new int[x];
    for (i = 0; i < x; i++)
    {
        cin >> arr[i];
    }
    std::thread tt2(is_98, 1);
    std::thread tt1(is_98, 98);

    int index;
    index = int_index(arr, i, is_98);
    cout << index << endl;
    index = int_index(arr, i, abs_is_98);
    cout << index << endl;
    index = int_index(arr, i, is_strictly_positive);
    cout << index << endl;
    tt2.join();
    tt1.join();
    delete[] arr;
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
