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
    MyArena = ArenaCreator(1024);
    MyDestructorListArena = ArenaCreator(1024);
}

ArenaAllocater::ArenaAllocater(size_t Size)
{
    MyArena = ArenaCreator(Size);
    MyDestructorListArena = ArenaCreator(Size);
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

ArenaSnap* ArenaAllocater::SnapShot()
{
    ArenaSnap* ArenaSnapper = new ArenaSnap{};
    ArenaSnapper->Snappy = Snap(MyArena);
    ArenaSnapper->DestructorArenaSnappy = Snap(MyDestructorListArena);
    ArenaSnapper->SnapDestructorNode = CurrentNode;
    return ArenaSnapper;
}

ArenaSnap ArenaAllocater::SnapShotByValue()
{
    ArenaSnap ArenaSnapper;
    ArenaSnapper.Snappy = Snap(MyArena);
    ArenaSnapper.DestructorArenaSnappy = Snap(MyDestructorListArena);
    ArenaSnapper.SnapDestructorNode = CurrentNode;
    return ArenaSnapper;
}

void ArenaAllocater::Rewinder(ArenaSnap* Snap)
{
    while (CurrentNode != Snap->SnapDestructorNode)
    {
        CurrentNode->DestructorPtr(CurrentNode->Objectptr);
        CurrentNode = CurrentNode->Prev;
    }
    MyArena = Rewind(MyArena , Snap->Snappy);
    MyDestructorListArena = Rewind(MyDestructorListArena , Snap->DestructorArenaSnappy);
    MY_FREE(Snap->Snappy, sizeof(Arena_Snap));
    MY_FREE(Snap->DestructorArenaSnappy, sizeof(Arena_Snap));
    delete Snap;
}

void ArenaAllocater::RewinderByValue(ArenaSnap Snap)
{
    while (CurrentNode != Snap.SnapDestructorNode)
    {
        CurrentNode->DestructorPtr(CurrentNode->Objectptr);
        CurrentNode = CurrentNode->Prev;
    }
    MyArena = Rewind(MyArena , Snap.Snappy);
    MyDestructorListArena = Rewind(MyDestructorListArena , Snap.DestructorArenaSnappy);
    MY_FREE(Snap.Snappy, sizeof(Arena_Snap));
    MY_FREE(Snap.DestructorArenaSnappy, sizeof(Arena_Snap));
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

bool ArenaAllocater::IsEmpty()
{
    return Isempty(MyArena);
}

bool ArenaAllocater::IsFull()
{
    return Isfull(MyArena);
}

bool ArenaAllocater::CanAllocWithoutAlignCheck(size_t Capacity)
{
    return Canallocwithoutaligncheck(MyArena , Capacity);
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

//thread_local ArenaAllocater ThreadArena(4 * 1024 * 1024);
