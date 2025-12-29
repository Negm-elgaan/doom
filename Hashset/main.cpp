#include <iostream>
#include "HashSet.h"

int main()
{
    HashSet <int> Set;
    Set.Insert(1);
    Set.Insert(1);
    Set.Insert(1);
    Set.Insert(1);
    Set.Insert(1);
    Set.Insert(1);
    Set.Insert(2);
    Set.Insert(2);
    Set.Insert(2);
    Set.Insert(3);
    Set.Print();
    std::cout << "Hello World!\n";
}
