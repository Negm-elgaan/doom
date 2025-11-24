#include <iostream>
#include <iomanip>

using namespace std;

template <class T> unsigned char* CastByte(T &Data)
{
    return reinterpret_cast<unsigned char*>(&Data);
}

template <class T> T& RecastByte(unsigned char *Data)
{
    T* ptr =  reinterpret_cast<T*>(Data);
    return *ptr;
}

int main()
{
    cout << "sizeof(int) = " << sizeof(int) << endl;
    int x = 1337;
    unsigned char* p = CastByte(x);
    for (size_t i = 0; i < sizeof(x); i++)
    {
        cout /*<< hex*/ << setw(2) << setfill('0') << (int)p[i] << " ";
    }
    int y = RecastByte<int>(p);
    cout << endl /*<< dec*/ << y << endl;
    return 0;
}
