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

void* ArenaAllocater::MonoAlloc(size_t Size , size_t Alignment)
{
    return MonotonicArenaAllocAligned(MyArena , Size , Alignment);
}

Arena_Snap* ArenaAllocater::SnapShot()
{
    Arena_Snap* ArenaSnap = Snap(MyArena);
    SnapNode = CurrentNode;
    return ArenaSnap;
}

void ArenaAllocater::Rewinder(Arena_Snap* Snap) // Only One snap at a time before rewinding
{
    while (CurrentNode != SnapNode)
    {
        CurrentNode->DestructorPtr(CurrentNode->Objectptr);
        CurrentNode = CurrentNode->Prev;
    }
    MyArena = Rewind(MyArena , Snap);
}

size_t ArenaAllocater::ByteUse()
{
    return BytesUsed(MyArena);
}

size_t ArenaAllocater::BytesAllocated()
{
    return BytesAlloc(MyArena);
}

size_t ArenaAllocater::TotalBytesAllocated()
{
    return TotalBytes(MyArena);
}

size_t ArenaAllocater::FreeSpace()
{
    return FreeBytes(MyArena);
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
