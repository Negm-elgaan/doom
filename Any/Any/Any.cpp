#include "Any.h"
#include <iostream>
#include <string>

int main()
{
    Any any;
    any = 10;
    int X = any.Get<int>();
    std::cout << X << std::endl;
    any = 'O';
    char O = any.Get<char>();
    std::cout << O << std::endl;
    any = 22.5;
    double D = any.Get<double>();
    std::cout << D << std::endl;
    any = std::string("Negm");
    std::string S = any.Get<std::string>();
    std::cout << S << std::endl;
    std::cout << "Hello World!\n";

    std::cout << "=== Default Constructor Test ===\n";
    Any a1;
    std::cout << "a1.Has_Value(): " << a1.Has_Value() << "\n\n";

    std::cout << "=== Template Constructor Test ===\n";
    Any a2(42);
    std::cout << "a2.Has_Value(): " << a2.Has_Value() << "\n";
    std::cout << "a2.Get<int>(): " << a2.Get<int>() << "\n\n";

    std::cout << "=== Copy Constructor Test ===\n";
    Any a3(a2);
    std::cout << "a3.Get<int>(): " << a3.Get<int>() << "\n";
    std::cout << "a2.Get<int>(): " << a2.Get<int>() << "\n\n";

    std::cout << "=== Move Constructor Test ===\n";
    Any a4(std::move(a3));
    std::cout << "a4.Get<int>(): " << a4.Get<int>() << "\n";
    std::cout << "a3.IsEmpty(): " << a3.IsEmpty() << "\n\n";

    std::cout << "=== Copy Assignment Test ===\n";
    Any a5;
    a5 = a4;
    std::cout << "a5.Get<int>(): " << a5.Get<int>() << "\n\n";

    std::cout << "=== Move Assignment Test ===\n";
    Any a6;
    a6 = std::move(a5);
    std::cout << "a6.Get<int>(): " << a6.Get<int>() << "\n";
    std::cout << "a5.IsEmpty(): " << a5.IsEmpty() << "\n\n";

    std::cout << "=== Template Assignment Test ===\n";
    a6 = std::string("Negm");
    std::cout << "a6.Get<std::string>(): " << a6.Get<std::string>() << "\n\n";

    std::cout << "=== Swap() Test ===\n";
    Any a7(99.99);
    std::cout << "Before swap: a6=" << a6.Get<std::string>() << ", a7=" << a7.Get<double>() << "\n";
    a6.Swap(a7);
    std::cout << "After swap:  a6=" << a6.Get<double>() << ", a7=" << a7.Get<std::string>() << "\n\n";

    std::cout << "=== Has_Numeric() Test ===\n";
    std::cout << "a6.Has_Numeric(): " << a6.Has_Numeric() << "\n";
    std::cout << "a7.Has_Numeric(): " << a7.Has_Numeric() << "\n\n";

    std::cout << "=== Reset() Test ===\n";
    a7.Reset();
    std::cout << "a7.IsEmpty(): " << a7.IsEmpty() << "\n\n";

    std::cout << "=== IsOneOf() Test ===\n";
    Any a8(3.14f);
    std::cout << "a8.IsOneOf<int, float, std::string>(): " << a8.IsOneOf<int, float, std::string>() << "\n";
    std::cout << "a8.IsOneOf<char, std::string>(): " << a8.IsOneOf<char, std::string>() << "\n\n";

    std::cout << "=== All Tests Completed ===\n";
}
