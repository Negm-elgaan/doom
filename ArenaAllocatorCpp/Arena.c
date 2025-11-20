#include "Arena.h"
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
}
