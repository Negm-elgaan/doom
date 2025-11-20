#ifndef ARENAALLOCATOR_H_INCLUDED
#define ARENAALLOCATOR_H_INCLUDED

#include <utility>

extern "C"
{
        #include "Arena.h"
}

class ArenaAllocater
{
    Arena* MyArena = nullptr;

    public:

        ArenaAllocater();

        ArenaAllocater(size_t Size);

        void* Alloc(size_t Size);

        template <class T , class... Args> T* ObjectAlloc(Args&&... args)
        {
            void* memory = Alloc(sizeof(T));
            T* ptr = new (memory) T(std::forward<Args>(args)...);
            return ptr;
        }

        ~ArenaAllocater();

};


#endif // ARENAALLOCATOR_H_INCLUDED
