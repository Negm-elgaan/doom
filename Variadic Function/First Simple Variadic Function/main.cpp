#include <iostream>
#include <cstdarg>
using namespace std;

void Tester(const char* ptr...)
{
    va_list Arguments;
    va_start(Arguments,ptr);

    while(*ptr != '\0')
    {
        if (*ptr == 'a' || *ptr == 'b' || *ptr == 'c')
        {
            int i = va_arg(Arguments,int);
            cout << i << endl;
        }
        ptr++;
    }
    va_end(Arguments);
}

int Multiply1(const int* ptr...)
{
    va_list Arguments;
    va_start(Arguments,ptr);
    int Mult = 1;
    while(*ptr != '\0')
    {
        int i = va_arg(Arguments,int);
        Mult *= i;
        ptr++;
    }
    va_end(Arguments);
    return Mult;
}

int Multiply(int counter, ...)  // First argument specifies the count of numbers
{
    va_list Arguments;
    va_start(Arguments, counter);  // Initialize va_list with the number of arguments

    int Mult = 1;
    for (int i = 0; i < counter; ++i) {
        int num = va_arg(Arguments, int);  // Get the next integer
        Mult *= num;  // Multiply the result
    }

    va_end(Arguments);  // Clean up the va_list
    return Mult;
}

int Sum(int* ptr...)
{
    va_list Arguments;
    va_start(Arguments, *ptr);

    int Sum = 0;
    for (int i = 0; i < *ptr ; i++)
    {
        int num = va_arg(Arguments, int);
        Sum += num;
    }

    va_end(Arguments);
    return Sum;
}
int main()
{
    cout << Multiply(5,1,2,3,4,5) << endl;
    int x = 5;
    int *ptr = &x;
    cout << Sum(ptr,1,2,3,4,5);
    return 0;
}
