#include "ArenaScope.h"

ArenaScope::ArenaScope(ArenaAllocater& TheArena) : MyArena(TheArena)
{
    Snapper = TheArena.SnapShotByValue();
}

ArenaScope::~ArenaScope() noexcept
{
    MyArena.RewinderByValue(Snapper);
}
