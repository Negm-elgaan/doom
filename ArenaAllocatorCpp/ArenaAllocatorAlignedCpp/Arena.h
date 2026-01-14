#ifndef ARENA_H_INCLUDED
#define ARENA_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

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
    //size_t _Total_Bytes_Allocated;
};

struct Arena_Snap
{
    struct Region* _Region;
    size_t Bytes;
    size_t _Count;
};

void* MY_ALLOC(size_t Capacity);

void MY_FREE(void* Address, size_t Capacity);

struct Region* CreateRegion(size_t Capacity);

struct Arena* ArenaCreator(struct Arena* MyArena , size_t Capacity);

void* ArenaAlloc(struct Arena* MyArena , size_t Capacity);

void* ArenaAllocAlignedWithoutMask(struct Arena* MyArena , size_t Capacity , size_t Alignment);

void* ArenaAllocAligned(struct Arena* MyArena , size_t Capacity , size_t Alignment);

void* MonotonicArenaAllocAligned(struct Arena* MyArena , size_t Capacity , size_t Alignment);

struct Arena_Snap SnapByValue(struct Arena* MyArena);

struct Arena_Snap* Snap(struct Arena* MyArena);

struct Arena* Rewind(struct Arena* MyArena , struct Arena_Snap* _Arena_Snap);

size_t BytesUsed(struct Arena* MyArena);

size_t BytesAlloc(struct Arena* MyArena);

size_t TotalBytes(struct Arena* MyArena);

size_t FreeBytes(struct Arena* MyArena);

_Bool Isempty(struct Arena* MyArena);

void ArenaReset(struct Arena* MyArena);

struct Arena* DestroyLastRegion (struct Arena* MyArena , size_t TotalBytesAfterDeletion);

struct Arena* DestroyFirstRegion(struct Arena* MyArena , size_t TotalBytesAfterDeletion);

void ArenaDestroy(struct Arena* MyArena);

#endif // ARENA_H_INCLUDED
