#include "ArenaAllocator.h"

void* ArenaAllocater::DestructorAlloc(size_t Size)
{
    return ArenaAlloc(MyDestructorListArena , Size);
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
