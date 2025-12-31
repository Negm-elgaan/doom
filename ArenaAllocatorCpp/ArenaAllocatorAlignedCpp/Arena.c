/*#include "Arena.h"
#include <stddef.h>
#include <stdlib.h>

const size_t _Default_Capacity = 1024;


struct Region* CreateRegion(size_t Capacity)
{
    struct Region* NewRegion = (struct Region *)malloc(sizeof(struct Region) + Capacity);
    NewRegion->_Capacity = Capacity;
    NewRegion->_Count = 0;
    NewRegion->_Next = NULL;
    NewRegion->_Prev = NULL;
    return NewRegion;
}

struct Arena* ArenaCreator(struct Arena* MyArena , size_t Capacity)
{
    MyArena = (struct Arena *)malloc(sizeof(struct Arena));
    MyArena->_Start = CreateRegion(Capacity);
    MyArena->_End = MyArena->_Start;
    MyArena->_Current = MyArena->_Start;
    return MyArena;
};

void* ArenaAlloc(struct Arena* MyArena , size_t Capacity)
{
    if (MyArena->_Current->_Capacity - MyArena->_Current->_Count >= Capacity)
    {
        void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count;
        MyArena->_Current->_Count += Capacity;
        return vptr;
    }

    struct Region* NewRegion = CreateRegion(Capacity < _Default_Capacity ? _Default_Capacity : Capacity);
    MyArena->_End->_Next = NewRegion;
    NewRegion->_Prev = MyArena->_End;
    MyArena->_End = NewRegion;
    MyArena->_Current = NewRegion;
    void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count;
    MyArena->_Current->_Count += Capacity;
    return vptr;
};

void ArenaDestroy(struct Arena* MyArena)
{
    struct Region* Temp1 = MyArena->_Start;

    while(Temp1 != NULL)
    {
        struct Region* Temp2 = Temp1->_Next;
        free(Temp1);
        Temp1 = Temp2;
    }

    return;
}*/

/*#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdalign.h>
//#include <windows.h>
#if defined(_WIN32) || defined(_WIN64)
        #include <windows.h>
    #else
        #include <unistd.h>
        #include <sys/mman.h>
    #endif
#include "Arena.h"

void* MY_ALLOC(size_t Capacity)
{
    #if defined(_WIN32) || defined(_WIN64)
        void* ptr = VirtualAlloc(NULL ,  Capacity , MEM_RESERVE | MEM_COMMIT , PAGE_READWRITE);
        return ptr;
    #else
        void* ptr = mmap(NULL , Capacity , PROT_READ | PROT_WRITE , MAP_PRIVATE | MAP_ANONYMOUS , -1 , 0);
        return ptr;
    #endif // defined
}

void MY_FREE(void* Address , size_t Capacity)
{
    #if defined(_WIN32) || defined(_WIN64)
        VirtualFree(Address , 0 , MEM_RELEASE);
        return;
    #else
        munmap(Address , Capacity);
        return;
    #endif // defined
}

const size_t _Default_Capacity = 4 * 1024 * 1024;

struct Region* CreateRegion(size_t Capacity)
{
    struct Region* NewRegion = (struct Region *)MY_ALLOC(sizeof(struct Region) + Capacity);

    if (NewRegion == NULL) {
        return NULL; // Out of Memory!
    }

    NewRegion->_Capacity = Capacity;
    NewRegion->_Count = 0;
    NewRegion->_Next = NULL;
    NewRegion->_Prev = NULL;
    return NewRegion;
}

struct Arena* ArenaCreator(struct Arena* MyArena , size_t Capacity)
{
    MyArena = (struct Arena *)MY_ALLOC(sizeof(struct Arena));
    MyArena->_Start = CreateRegion(Capacity);
    MyArena->_End = MyArena->_Start;
    MyArena->_Current = MyArena->_Start;
    MyArena->_Total_Bytes_Used = 0;
    return MyArena;
};

void* ArenaAlloc(struct Arena* MyArena , size_t Capacity)
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

    struct Region* NewRegion = CreateRegion(Capacity < _Default_Capacity ? _Default_Capacity : Capacity);
    //if (NewRegion == NULL) {
    //    return NULL; // Crash prevention: Return NULL instead of segfaulting
    //}
    MyArena->_End->_Next = NewRegion;
    NewRegion->_Prev = MyArena->_End;
    MyArena->_End = NewRegion;
    MyArena->_Current = NewRegion;
    void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count;
    MyArena->_Current->_Count += Capacity;
    MyArena->_Total_Bytes_Used += Capacity;
    return vptr;
};

void* ArenaAllocAligned(struct Arena* MyArena , size_t Capacity , size_t Alignment)
{
    uintptr_t Address = (uintptr_t)MyArena->_Current->_Data + (uintptr_t)MyArena->_Current->_Count;
    //uintptr_t Alignment = Capacity;
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
        //void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count; //Address

        vptr = (void*)vptr;
        return vptr;
    }

    while (MyArena->_Current->_Next)
    {
        MyArena->_Current = MyArena->_Current->_Next;
        Address = (uintptr_t)MyArena->_Current->_Data + (uintptr_t)MyArena->_Current->_Count;
        //uintptr_t Alignment = Capacity;
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
            //void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count; //Address

            vptr = (void*)vptr;
            return vptr;
        }
    }

    struct Region* NewRegion = CreateRegion(Capacity < _Default_Capacity ? _Default_Capacity  + (Alignment - 1 ) : Capacity + (Alignment - 1 ));
    //if (NewRegion == NULL) {
      //  return NULL; // Crash prevention: Return NULL instead of segfaulting
    //}
    MyArena->_End->_Next = NewRegion;
    NewRegion->_Prev = MyArena->_End;
    MyArena->_End = NewRegion;
    MyArena->_Current = NewRegion;
    Address = MyArena->_Current->_Data + MyArena->_Current->_Count;

    void* vptr;
    if ((Address % Alignment) != 0)
    {
        vptr = Address + (Alignment - (Address % Alignment));
        MyArena->_Current->_Count += Capacity + (Alignment - (Address % Alignment));
        MyArena->_Total_Bytes_Used += Capacity + (Alignment - (Address % Alignment));
    }

    else
    {
        vptr = (void*)Address;
        MyArena->_Current->_Count += Capacity;
        MyArena->_Total_Bytes_Used += Capacity;
    }
        //void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count; //Address
    return vptr;
    //void* vptr = MyArena->_Current->_Data + MyArena->_Current->_Count;
    //MyArena->_Current->_Count += Capacity;
    //return vptr;
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

void ArenaDestroy(struct Arena* MyArena)
{
    struct Region* Temp1 = MyArena->_Start;

    while(Temp1 != NULL)
    {
        struct Region* Temp2 = Temp1->_Next;
        MY_FREE(Temp1 , Temp1->_Capacity + sizeof(struct Region));
        Temp1 = Temp2;
    }

    MY_FREE(MyArena , sizeof(struct Arena));
    //VirtualFree(MyArena , 0 , MEM_RELEASE);

    return;
}
*/

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

#include "Arena.h"

void* MY_ALLOC(size_t Capacity)
{
#if defined(_WIN32) || defined(_WIN64)
    void* ptr = VirtualAlloc(NULL, Capacity, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    return ptr;
#else
    void* ptr = mmap(NULL, Capacity, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    return ptr;
#endif
}

void MY_FREE(void* Address, size_t Capacity)
{
#if defined(_WIN32) || defined(_WIN64)
    VirtualFree(Address, 0, MEM_RELEASE);
#else
    munmap(Address, Capacity);
#endif
}

const size_t _Default_Capacity = 4 * 1024 * 1024;

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

struct Arena* ArenaCreator(struct Arena* MyArena, size_t Capacity)
{
    MyArena = (struct Arena*)MY_ALLOC(sizeof(struct Arena));
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

void* ArenaAllocAligned(struct Arena* MyArena, size_t Capacity, size_t Alignment)
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
