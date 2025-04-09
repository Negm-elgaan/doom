#include "clsTuple.h"
#include <tuple>

int main()
{
    clsTuple<int, char, double, string> MyTuple(42, 'O', 3.14, "Hello Tuple");
    MyTuple.Insert(10, 'A', 3.94, "Hello world");
    MyTuple.Print();
    //char c = MyTuple.Get(1);
    //cout << c << endl;
}