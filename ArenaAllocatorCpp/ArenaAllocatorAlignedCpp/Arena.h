#ifndef ARENA_H_INCLUDED
#define ARENA_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>


struct Region
{
    struct Region* _Next;
    struct Region* _Prev;
    size_t _Count;
    size_t _Capacity;

    //uintptr_t _Data[];
    unsigned char _Data[];
};

struct Arena
{
    struct Region* _Start;
    struct Region* _End;
    struct Region* _Current;
    size_t _Total_Bytes_Used;
};

struct Region* CreateRegion(size_t Capacity);

struct Arena* ArenaCreator(struct Arena* MyArena , size_t Capacity);

void* ArenaAlloc(struct Arena* MyArena , size_t Capacity);

void* ArenaAllocAligned(struct Arena* MyArena , size_t Capacity , size_t Alignment);

size_t BytesUsed(struct Arena* MyArena);

void ArenaReset(struct Arena* MyArena);

void ArenaDestroy(struct Arena* MyArena);

#endif // ARENA_H_INCLUDED
