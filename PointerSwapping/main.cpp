#include <iostream>

class A
{
    int a;
    public:
        void Set(int x)
        {
            a = x;
        }
        void Print()
        {
            std::cout << a << std::endl;
        }
};

template <class T> void PointerSwap(T* &P1 , T* &P2)
{
    T* Temp = P1;
    P1 = P2;
    P2 = Temp;
}

int main()
{
    int x = 10, y = 20;
    int* P1 = &x;
    int* P2 = &y;
    std::cout << "after swap: " << *P1 << " " << *P2 << std::endl;
    PointerSwap(P1, P2);
    std::cout << "after swap: " << *P1 << " " << *P2 << std::endl;

    A* P3 = new A;
    A* P4 = new A;
    P3->Set(100);
    P4->Set(200);
    std::cout << "Before swap: ";
    P3->Print();
    std::cout << " ";
    P4->Print();
    std::cout << std::endl;
    PointerSwap(P3, P4);
    std::cout << "AFter swap: ";
    P3->Print();
    std::cout << " ";
    P4->Print();
    std::cout << std::endl;
}
