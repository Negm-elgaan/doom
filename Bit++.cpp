#include <iostream>

using namespace std;

int main()
{
    short num = 0 , x = 0;
    cin >> num ;
    string op ;
    for (short i = 0 ; i < num ; i++)
    {
        cin >> op ;
        if (op == "++X" || op == "X++")
            x++;
        else
            x--;
    }
    cout << x << endl;
    return 0;
}

