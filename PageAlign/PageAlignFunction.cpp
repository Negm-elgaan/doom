#include <iostream>

using namespace std;

void* PageAlign(uintptr_t Address)
{
    if ((Address & 4095) == 0)
    {
        return reinterpret_cast<void*>(Address);
    }

    Address = Address + (4096 - (Address & 4095));
    
    //Faster version : uintptr_t address = (address + 4096 - 1) & ~(4096 - 1);

    return reinterpret_cast<void*>(Address);
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
