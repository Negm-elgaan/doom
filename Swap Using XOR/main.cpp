#include <iostream>

using namespace std;

void Swap(int &x , int &y)
{
    x = x ^ y ;
    y = x ^ y ;
    x = x ^ y ;
    return ;
}
int main()
{
    int  x = 5 , y = 4 ;
    Swap(x,y);
    cout << x << " " << y;
    return 0;
}
