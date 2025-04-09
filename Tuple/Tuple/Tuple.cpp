#include "clsTuple.h"
#include <tuple>

int main()
{
    clsTuple<int, char, double, string> MyTuple(42, 'O', 3.14, "Hello Tuple");
    MyTuple.Insert(10, 'A', 3.94, "Hello world");
    MyTuple.Print();
    //char c = MyTuple.Get(1);
    //cout << c << endl;

    clsTupleArray <int, char, double, string> MyTupleArr(5);
    MyTupleArr.SetItem(0, 21, 'O', 3.14, "Negm");
    MyTupleArr.SetItem(1, 271, 'K', 83.28, "Mike");
    MyTupleArr.SetItem(2, 90, 'L', 9.4, "Sara");
    MyTupleArr.SetItem(3, 12, 'Q', 0.9, "Israa");
    MyTupleArr.SetItem(4, 46, 'A', 11.27, "Mohamed");
    MyTupleArr.print();
}