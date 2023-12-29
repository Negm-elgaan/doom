#include <iostream>

using namespace std;

long long binary(int num)
{
    long long bin = 0,reverser = 0;
    int remiander = num ,zero = 0;
    while (num % 2 == 0)
    {
        zero++ ;
        num /= 2 ;
    }
    while (remiander > 0)
    {
        bin = (bin * 10) + remiander % 2 ;
        remiander /= 2 ;
    }
    while (bin > 0)
    {
        reverser = reverser * 10 + bin % 10 ;
        bin /= 10 ;
    }
    while (zero > 0)
    {
        reverser *= 10 ;
        zero --;
    }
    return reverser;
}

int main()
{
    int n = 0 ;
    cin >> n ;
    cout << binary(n);
    return 0;
}

