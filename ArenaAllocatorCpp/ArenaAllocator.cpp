#include "ArenaAllocator.h"

ArenaAllocater::ArenaAllocater()
{
    MyArena = ArenaCreator(MyArena , 1024);
}

ArenaAllocater::ArenaAllocater(size_t Size)
{
    MyArena = ArenaCreator(MyArena , Size);
}

void* ArenaAllocater::Alloc(size_t Size)
{
    return ArenaAlloc(MyArena , Size);
}

ArenaAllocater::~ArenaAllocater()
{
    ArenaDestroy(MyArena);
}
