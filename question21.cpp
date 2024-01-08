#include <iostream>

using namespace std;
void fib(int );
void PrintFibonacciUsingLoop(short );
int main()
{
    fib(20);
    return 0;
}
// My solution:
void fib(int num)
{
    int *ptr;
    ptr = new int [num];
    *(ptr + 0) = 0 ;
    *(ptr + 1) = 1 ;
    for (int i =  2; i <= num ; i++)
    {
        *(ptr + i) = *(ptr + i - 1 ) + *(ptr + i - 2) ;
    }
    for (int i = 0 ; i <= num ; i++)
    {
        cout << *(ptr + i) << endl ;
    }
    delete [] ptr ;
    return ;
}
// Abu-Hadhoud solution:
void PrintFibonacciUsingLoop(short Number)
{
    int FebNumber = 0;
    int Prev2 = 0, Prev1 = 1;
    cout     <<     "1   ";
    for (short i = 2; i <= Number; ++i)
        {
            FebNumber = Prev1 + Prev2;
            cout     <<     FebNumber     <<     "    ";
            Prev2     =     Prev1;
            Prev1     =     FebNumber;
        }
}

