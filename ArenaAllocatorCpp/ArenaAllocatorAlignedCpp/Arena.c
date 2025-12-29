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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdalign.h>
#include <windows.h>
#include "Arena.h"

const size_t _Default_Capacity = 4 * 1024 * 1024;

struct Region* CreateRegion(size_t Capacity)
{
    struct Region* NewRegion = (struct Region *)VirtualAlloc(NULL , (sizeof(struct Region) + Capacity) , MEM_RESERVE | MEM_COMMIT , PAGE_READWRITE);

    /*if (NewRegion == NULL) {
        return NULL; // Out of Memory!
    }*/

    NewRegion->_Capacity = Capacity;
    NewRegion->_Count = 0;
    NewRegion->_Next = NULL;
    NewRegion->_Prev = NULL;
    return NewRegion;
}

struct Arena* ArenaCreator(struct Arena* MyArena , size_t Capacity)
{
    MyArena = (struct Arena *)VirtualAlloc(NULL , sizeof(struct Arena) , MEM_RESERVE | MEM_COMMIT , PAGE_READWRITE);
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
    /*if (NewRegion == NULL) {
        return NULL; // Crash prevention: Return NULL instead of segfaulting
    }*/
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
    /*if (NewRegion == NULL) {
        return NULL; // Crash prevention: Return NULL instead of segfaulting
    }*/
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
        VirtualFree(Temp1 , 0 , MEM_RELEASE);
        Temp1 = Temp2;
    }

    VirtualFree(MyArena , 0 , MEM_RELEASE);

    return;
}

