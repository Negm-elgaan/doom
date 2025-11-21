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
    Arena* MyDestructorListArena = nullptr;

    struct DestructorNode
    {
        void* Objectptr;
        void (*DestructorPtr)(void* objptr);
        DestructorNode* Next;
        DestructorNode* Prev;
    };

    DestructorNode* CurrentNode = nullptr;

    void* DestructorAlloc(size_t Size);

    public:

        ArenaAllocater();

        ArenaAllocater(size_t Size);

        void* Alloc(size_t Size);

        template <class T , class... Args> T* ObjectAlloc(Args&&... args)
        {
            void* memory = Alloc(sizeof(T));
            T* ptr = new (memory) T(std::forward<Args>(args)...);

            if (!CurrentNode)
            {
                CurrentNode = (DestructorNode*)DestructorAlloc(sizeof(DestructorNode));
                CurrentNode->Objectptr = ptr;
                CurrentNode->DestructorPtr = [](void* objptr){static_cast<T*>(objptr)->~T();};
                CurrentNode->Prev = nullptr;
                CurrentNode->Next = nullptr;
            }
            else
            {
                DestructorNode* NewNode = (DestructorNode*)DestructorAlloc(sizeof(DestructorNode));
                NewNode->Objectptr = ptr;
                NewNode->DestructorPtr = [](void* objptr){static_cast<T*>(objptr)->~T();};
                NewNode->Prev = CurrentNode;
                NewNode->Next = nullptr;
                CurrentNode->Next = NewNode;
                CurrentNode = NewNode;
            }

            return ptr;
        }

        ~ArenaAllocater();

};


#endif // ARENAALLOCATOR_H_INCLUDED
