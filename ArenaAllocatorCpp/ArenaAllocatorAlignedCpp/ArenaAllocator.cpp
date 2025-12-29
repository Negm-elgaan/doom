#include "ArenaAllocator.h"

void* ArenaAllocater::DestructorAlloc(size_t Size)
{
    return ArenaAlloc(MyDestructorListArena , Size);
}

void* ArenaAllocater::DestructorAllocAligned(size_t Size , size_t Alignment)
{
    return ArenaAllocAligned(MyDestructorListArena , Size , Alignment);
}

ArenaAllocater::ArenaAllocater()
{
    MyArena = ArenaCreator(MyArena , 1024);
    MyDestructorListArena = ArenaCreator(MyDestructorListArena , 1024);
}

ArenaAllocater::ArenaAllocater(size_t Size)
{
    MyArena = ArenaCreator(MyArena , Size);
    MyDestructorListArena = ArenaCreator(MyDestructorListArena , Size);
}

void* ArenaAllocater::Alloc(size_t Size)
{
    return ArenaAlloc(MyArena , Size);
}

void* ArenaAllocater::Alloc(size_t Size , size_t Alignment)
{
    return ArenaAllocAligned(MyArena , Size , Alignment);
}

size_t ArenaAllocater::ByteUse()
{
    return BytesUsed(MyArena);
}

void ArenaAllocater::ArenaAllocaterReset()
{
    while (CurrentNode != nullptr)
    {
        CurrentNode->DestructorPtr(CurrentNode->Objectptr);
        CurrentNode = CurrentNode->Prev;
    }

    ArenaReset(MyDestructorListArena);
    ArenaReset(MyArena);
}

ArenaAllocater::~ArenaAllocater()
{
    while (CurrentNode != nullptr)
    {
        CurrentNode->DestructorPtr(CurrentNode->Objectptr);
        CurrentNode = CurrentNode->Prev;
    }

    ArenaDestroy(MyDestructorListArena);

    ArenaDestroy(MyArena);
}
