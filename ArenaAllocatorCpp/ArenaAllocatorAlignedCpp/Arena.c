#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdalign.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/mman.h>
#endif

//#include <cuda_runtime.h>
#include "Arena.h"

void* MY_ALLOC(size_t Capacity)
{
void* ptr;
//if (cudaMallocManaged(&ptr , Capacity) == cudaSuccess)
   // return ptr;
#if defined(_WIN32) || defined(_WIN64)
    ptr = VirtualAlloc(NULL, Capacity, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    return ptr;
#else
    ptr = mmap(NULL, Capacity, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    return ptr;
#endif
}

void MY_FREE(void* Address, size_t Capacity)
{
//if (cudaFree(Address) == cudaSuccess)
  //  return;
#if defined(_WIN32) || defined(_WIN64)
    VirtualFree(Address, 0, MEM_RELEASE);
#else
    munmap(Address, Capacity);
#endif
}

const size_t _Default_Capacity = 4 * 1024 * 1024;
//const size_t _Default_Capacity = 4;

struct Region* CreateRegion(size_t Capacity)
{
    struct Region* NewRegion =
        (struct Region*)MY_ALLOC(sizeof(struct Region) + Capacity);

    NewRegion->_Capacity = Capacity;
    NewRegion->_Count = 0;
    NewRegion->_Next = NULL;
    NewRegion->_Prev = NULL;
    return NewRegion;
}

struct Arena* ArenaCreator(size_t Capacity)
{
    struct Arena* MyArena = (struct Arena*)MY_ALLOC(sizeof(struct Arena));
    MyArena->_Start = CreateRegion(Capacity);
    MyArena->_End = MyArena->_Start;
    MyArena->_Current = MyArena->_Start;
    MyArena->_Total_Bytes_Used = 0;
    return MyArena;
}

void* ArenaAlloc(struct Arena* MyArena, size_t Capacity)
{
    if (MyArena->_Current->_Capacity - MyArena->_Current->_Count >= Capacity)
    {
        void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count;
        MyArena->_Current->_Count += Capacity;
        MyArena->_Total_Bytes_Used += Capacity;
        return vptr;
    }

    while (MyArena->_Current->_Next)
    {
        MyArena->_Current = MyArena->_Current->_Next;
        if (MyArena->_Current->_Capacity - MyArena->_Current->_Count >= Capacity)
        {
            void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count;
            MyArena->_Current->_Count += Capacity;
            MyArena->_Total_Bytes_Used += Capacity;
            return vptr;
        }
    }

    struct Region* NewRegion =
        CreateRegion(Capacity < _Default_Capacity ? _Default_Capacity : Capacity);

    MyArena->_End->_Next = NewRegion;
    NewRegion->_Prev = MyArena->_End;
    MyArena->_End = NewRegion;
    MyArena->_Current = NewRegion;

    void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count;
    MyArena->_Current->_Count += Capacity;
    MyArena->_Total_Bytes_Used += Capacity;
    return vptr;
}

void* ArenaAllocAlignedWithoutMask(struct Arena* MyArena, size_t Capacity, size_t Alignment)
{
    uintptr_t Address =
        (uintptr_t)MyArena->_Current->_Data +
        (uintptr_t)MyArena->_Current->_Count;

    uintptr_t Drift = Address % Alignment;
    uintptr_t padding = (Alignment - Drift) % Alignment;

    if (MyArena->_Current->_Capacity - MyArena->_Current->_Count >= Capacity + padding)
    {
        void* vptr;
        if ((Address % Alignment) != 0)
        {
            vptr = (void*)(Address + (Alignment - (Address % Alignment)));
            MyArena->_Current->_Count += Capacity + (Alignment - (Address % Alignment));
            MyArena->_Total_Bytes_Used += Capacity + (Alignment - (Address % Alignment));
        }
        else
        {
            vptr = (void*)Address;
            MyArena->_Current->_Count += Capacity;
            MyArena->_Total_Bytes_Used += Capacity;
        }
        return vptr;
    }

    while (MyArena->_Current->_Next)
    {
        MyArena->_Current = MyArena->_Current->_Next;

        Address =
            (uintptr_t)MyArena->_Current->_Data +
            (uintptr_t)MyArena->_Current->_Count;

        Drift = Address % Alignment;
        padding = (Alignment - Drift) % Alignment;

        if (MyArena->_Current->_Capacity - MyArena->_Current->_Count >= Capacity + padding)
        {
            void* vptr;
            if ((Address % Alignment) != 0)
            {
                vptr = (void*)(Address + (Alignment - (Address % Alignment)));
                MyArena->_Current->_Count += Capacity + (Alignment - (Address % Alignment));
                MyArena->_Total_Bytes_Used += Capacity + (Alignment - (Address % Alignment));
            }
            else
            {
                vptr = (void*)Address;
                MyArena->_Current->_Count += Capacity;
                MyArena->_Total_Bytes_Used += Capacity;
            }
            return vptr;
        }
    }

    struct Region* NewRegion =
        CreateRegion(Capacity < _Default_Capacity
            ? _Default_Capacity + (Alignment - 1)
            : Capacity + (Alignment - 1));

    MyArena->_End->_Next = NewRegion;
    NewRegion->_Prev = MyArena->_End;
    MyArena->_End = NewRegion;
    MyArena->_Current = NewRegion;

    Address =
        (uintptr_t)MyArena->_Current->_Data +
        (uintptr_t)MyArena->_Current->_Count;

    void* vptr;
    if ((Address % Alignment) != 0)
    {
        vptr = (void*)(Address + (Alignment - (Address % Alignment)));
        MyArena->_Current->_Count += Capacity + (Alignment - (Address % Alignment));
        MyArena->_Total_Bytes_Used += Capacity + (Alignment - (Address % Alignment));
    }
    else
    {
        vptr = (void*)Address;
        MyArena->_Current->_Count += Capacity;
        MyArena->_Total_Bytes_Used += Capacity;
    }

    return vptr;
}

void* ArenaAllocAligned(struct Arena* MyArena, size_t Capacity, size_t Alignment)
{
    uintptr_t mask = (Alignment - 1);
    uintptr_t Address =
        (uintptr_t)MyArena->_Current->_Data +
        (uintptr_t)MyArena->_Current->_Count;

    uintptr_t Drift = Address & mask;
    uintptr_t padding = (Alignment - Drift) & mask;

    if (MyArena->_Current->_Capacity - MyArena->_Current->_Count >= Capacity + padding)
    {
        void* vptr;
        if ((Address & mask) != 0)
        {
            vptr = (void*)(Address + (Alignment - (Address & mask)));
            MyArena->_Current->_Count += Capacity + (Alignment - (Address & mask));
            MyArena->_Total_Bytes_Used += Capacity + (Alignment - (Address & mask));
        }
        else
        {
            vptr = (void*)Address;
            MyArena->_Current->_Count += Capacity;
            MyArena->_Total_Bytes_Used += Capacity;
        }
        return vptr;
    }

    while (MyArena->_Current->_Next)
    {
        MyArena->_Current = MyArena->_Current->_Next;

        Address =
            (uintptr_t)MyArena->_Current->_Data +
            (uintptr_t)MyArena->_Current->_Count;

        Drift = Address & mask;
        padding = (Alignment - Drift) & mask;

        if (MyArena->_Current->_Capacity - MyArena->_Current->_Count >= Capacity + padding)
        {
            void* vptr;
            if ((Address & mask) != 0)
            {
                vptr = (void*)(Address + (Alignment - (Address & mask)));
                MyArena->_Current->_Count += Capacity + (Alignment - (Address & mask));
                MyArena->_Total_Bytes_Used += Capacity + (Alignment - (Address & mask));
            }
            else
            {
                vptr = (void*)Address;
                MyArena->_Current->_Count += Capacity;
                MyArena->_Total_Bytes_Used += Capacity;
            }
            return vptr;
        }
    }

    struct Region* NewRegion =
        CreateRegion(Capacity < _Default_Capacity
            ? _Default_Capacity + (Alignment - 1)
            : Capacity + (Alignment - 1));

    MyArena->_End->_Next = NewRegion;
    NewRegion->_Prev = MyArena->_End;
    MyArena->_End = NewRegion;
    MyArena->_Current = NewRegion;

    Address =
        (uintptr_t)MyArena->_Current->_Data +
        (uintptr_t)MyArena->_Current->_Count;

    void* vptr;
    if ((Address & mask) != 0)
    {
        vptr = (void*)(Address + (Alignment - (Address & mask)));
        MyArena->_Current->_Count += Capacity + (Alignment - (Address & mask));
        MyArena->_Total_Bytes_Used += Capacity + (Alignment - (Address & mask));
    }
    else
    {
        vptr = (void*)Address;
        MyArena->_Current->_Count += Capacity;
        MyArena->_Total_Bytes_Used += Capacity;
    }

    return vptr;
}

void* MonotonicArenaAllocAligned(struct Arena* MyArena , size_t Capacity , size_t Alignment)
{
    uintptr_t mask = (Alignment - 1);
    uintptr_t Address =
        (uintptr_t)MyArena->_Current->_Data +
        (uintptr_t)MyArena->_Current->_Count;

    uintptr_t Drift = Address & mask;
    uintptr_t padding = (Alignment - Drift) & mask;

    if (MyArena->_Current->_Capacity - MyArena->_Current->_Count >= Capacity + padding)
    {
        void* vptr;
        if ((Address & mask) != 0)
        {
            vptr = (void*)(Address + (Alignment - (Address & mask)));
            MyArena->_Current->_Count += Capacity + (Alignment - (Address & mask));
            MyArena->_Total_Bytes_Used += Capacity + (Alignment - (Address & mask));
        }
        else
        {
            vptr = (void*)Address;
            MyArena->_Current->_Count += Capacity;
            MyArena->_Total_Bytes_Used += Capacity;
        }
        return vptr;
    }

    struct Region* NewRegion =
        CreateRegion(Capacity < _Default_Capacity
            ? _Default_Capacity + (Alignment - 1)
            : Capacity + (Alignment - 1));

    MyArena->_End->_Next = NewRegion;
    NewRegion->_Prev = MyArena->_End;
    MyArena->_End = NewRegion;
    MyArena->_Current = NewRegion;

    Address =
        (uintptr_t)MyArena->_Current->_Data +
        (uintptr_t)MyArena->_Current->_Count;

    void* vptr;
    if ((Address & mask) != 0)
    {
        vptr = (void*)(Address + (Alignment - (Address & mask)));
        MyArena->_Current->_Count += Capacity + (Alignment - (Address & mask));
        MyArena->_Total_Bytes_Used += Capacity + (Alignment - (Address & mask));
    }
    else
    {
        vptr = (void*)Address;
        MyArena->_Current->_Count += Capacity;
        MyArena->_Total_Bytes_Used += Capacity;
    }

    return vptr;
}

struct Arena_Snap SnapByValue(struct Arena* MyArena)
{
    struct Arena_Snap _Arena_Snap;
    _Arena_Snap._Region = MyArena->_Current;
    _Arena_Snap._Count = MyArena->_Current->_Count;
    _Arena_Snap.Bytes = MyArena->_Total_Bytes_Used;
    return _Arena_Snap;
};

struct Arena_Snap* Snap(struct Arena* MyArena) //Allocates a pointer struct of type Arena_Snap and returns it to user it's user responsibility to FREE IT
{
    struct Arena_Snap* _Arena_Snap = (struct Arena_Snap*)MY_ALLOC(sizeof(struct Arena_Snap));
    _Arena_Snap->_Region = MyArena->_Current;
    _Arena_Snap->_Count = MyArena->_Current->_Count;
    _Arena_Snap->Bytes = MyArena->_Total_Bytes_Used;
    return _Arena_Snap;
};

struct Arena* Rewind(struct Arena* MyArena , struct Arena_Snap* _Arena_Snap)
{
    struct Region* Temp1 = MyArena->_Current;

    while (Temp1 != _Arena_Snap->_Region)
    {
        struct Region* Temp2 = Temp1->_Prev;
        MY_FREE(Temp1, Temp1->_Capacity + sizeof(struct Region));
        Temp1 = Temp2;
    }

    MyArena->_Current = _Arena_Snap->_Region;
    MyArena->_Current->_Count = _Arena_Snap->_Count;
    MyArena->_End = MyArena->_Current;
    MyArena->_Total_Bytes_Used = _Arena_Snap->Bytes;
    MyArena->_Current->_Next = NULL;
    return MyArena;
};

struct Arena* RewindByValue(struct Arena* MyArena , struct Arena_Snap _Arena_Snap)
{
    struct Region* Temp1 = MyArena->_Current;

    while (Temp1 != _Arena_Snap._Region)
    {
        struct Region* Temp2 = Temp1->_Prev;
        MY_FREE(Temp1, Temp1->_Capacity + sizeof(struct Region));
        Temp1 = Temp2;
    }

    MyArena->_Current = _Arena_Snap._Region;
    MyArena->_Current->_Count = _Arena_Snap._Count;
    MyArena->_End = MyArena->_Current;
    MyArena->_Total_Bytes_Used = _Arena_Snap.Bytes;
    MyArena->_Current->_Next = NULL;
    return MyArena;
};

size_t BytesUsed(struct Arena* MyArena)
{
    return MyArena->_Total_Bytes_Used;
}

size_t BytesAlloc(struct Arena* MyArena)
{
    size_t Bytes = 0;
    struct Region* Temp = MyArena->_Start;
    while (Temp != MyArena->_End)
    {
        Bytes += Temp->_Capacity;
        Temp = Temp->_Next;
    }
    Bytes += Temp->_Capacity;
    return Bytes;
}

size_t TotalBytes(struct Arena* MyArena)
{
    size_t Bytes = 0;
    struct Region* Temp = MyArena->_Start;
    while (Temp != MyArena->_End)
    {
        Bytes += Temp->_Capacity + sizeof(struct Region);
        Temp = Temp->_Next;
    }
    Bytes += Temp->_Capacity + sizeof(struct Region) + sizeof(struct Arena);
    return Bytes;
}

size_t FreeBytes(struct Arena* MyArena)
{
    return BytesAlloc(MyArena) - MyArena->_Total_Bytes_Used;
}

_Bool Isempty(struct Arena* MyArena)
{
    return MyArena->_Total_Bytes_Used == 0;
}

_Bool Isfull(struct Arena* MyArena) //No free Bytes in Arena
{
    return BytesAlloc(MyArena) - MyArena->_Total_Bytes_Used == 0;
}

_Bool Canallocwithoutaligncheck(struct Arena* MyArena , size_t Capacity) // Note doesn't check if there is enough with alignment padding
{
    return BytesAlloc(MyArena) - MyArena->_Total_Bytes_Used >= Capacity ;
}

void ArenaReset(struct Arena* MyArena)
{
    struct Region* Temp = MyArena->_Start;
    while (Temp != MyArena->_Current)
    {
        Temp->_Count = 0;
        Temp = Temp->_Next;
    }
    MyArena->_Current->_Count = 0;
    MyArena->_Current = MyArena->_Start;
    MyArena->_Total_Bytes_Used = 0;
}

struct Arena* DestroyLastRegion(struct Arena* MyArena , size_t TotalBytesAfterDeletion) // Doesn't track total bytes
{
    if (MyArena->_End == MyArena->_Start)
    {
        return NULL;
    }

    struct Region* Temp = MyArena->_End;

    if (MyArena->_Current == MyArena->_End)
    {
        MyArena->_Current = MyArena->_End->_Prev;
    }

    MyArena->_End = MyArena->_End->_Prev;
    MyArena->_End->_Next = NULL;
    MY_FREE(Temp , Temp->_Capacity + sizeof(struct Region));
    MyArena->_Total_Bytes_Used = TotalBytesAfterDeletion;
    return MyArena;
}

struct Arena* DestroyFirstRegion(struct Arena* MyArena , size_t TotalBytesAfterDeletion)
{
    if (MyArena->_Start == NULL)
    {
        return NULL;
    }

    struct Region* Temp = MyArena->_Start;

    if (MyArena->_Start->_Next == NULL)
    {
        return NULL;
    }

    if (MyArena->_Current == MyArena->_Start)
    {
        MyArena->_Current = MyArena->_Start->_Next;
    }

    MyArena->_Start = MyArena->_Start->_Next;

    MyArena->_Start->_Prev = NULL;

    MY_FREE(Temp , Temp->_Capacity + sizeof(struct Region));
    MyArena->_Total_Bytes_Used = TotalBytesAfterDeletion;

    return MyArena;
}

void ArenaDestroy(struct Arena* MyArena)
{
    struct Region* Temp1 = MyArena->_Start;

    while (Temp1 != NULL)
    {
        struct Region* Temp2 = Temp1->_Next;
        MY_FREE(Temp1, Temp1->_Capacity + sizeof(struct Region));
        Temp1 = Temp2;
    }

    MY_FREE(MyArena, sizeof(struct Arena));
}
