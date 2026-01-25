#ifndef ARENASCOPE_H_INCLUDED
#define ARENASCOPE_H_INCLUDED

#include "ArenaAllocator.h"

class ArenaScope
{
    ArenaSnap Snapper;
    ArenaAllocater& MyArena;

    public:

        ArenaScope(ArenaAllocater& TheArena);

        ArenaScope(const ArenaScope& other) = delete;

        ArenaScope& operator=(const ArenaScope& other) = delete;

        ArenaScope(ArenaScope&& other) = delete;

        ArenaScope& operator=(ArenaScope&& other) = delete;

        ~ArenaScope() noexcept;
};

#endif // ARENASCOPE_H_INCLUDED
