#ifndef ARENAALLOCATOR_H_INCLUDED
#define ARENAALLOCATOR_H_INCLUDED

#include <utility>
#include <type_traits>

extern "C"
{
        #include "Arena.h"
}

struct DestructorNode
{
    void* Objectptr;
    void (*DestructorPtr)(void* objptr);
    DestructorNode* Next;
    DestructorNode* Prev;
};

struct ArenaSnap
{
    Arena_Snap* Snappy = nullptr;
    Arena_Snap* DestructorArenaSnappy = nullptr;
    DestructorNode* SnapDestructorNode = nullptr;
};

class ArenaAllocater
{
    Arena* MyArena = nullptr;
    Arena* MyDestructorListArena = nullptr;

    DestructorNode* SnapNode = nullptr;
    DestructorNode* CurrentNode = nullptr;

    void* DestructorAlloc(size_t Size);

    void* DestructorAllocAligned(size_t Size , size_t Alignment);

    public:

        ArenaAllocater();

        ArenaAllocater(size_t Size);

        void* Alloc(size_t Size);

        void* Alloc(size_t Size , size_t Alignment);

        void* MonoAlloc(size_t Size , size_t Alignment);

        template <class T , class... Args> T* ObjectAllocDestructorTrackingNoAlign(Args&&... args)
        {
            void* memory = Alloc(sizeof(T));
            T* ptr = new (memory) T(std::forward<Args>(args)...);
            if constexpr (std::is_trivially_destructible_v<T>)
            {
                return ptr;
            }

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

        template <class T , class... Args> T* ObjectAllocDestructorTracking(size_t Alignment , Args&&... args)
        {
            void* memory = Alloc(sizeof(T) , Alignment);
            T* ptr = new (memory) T(std::forward<Args>(args)...);
            if constexpr (std::is_trivially_destructible_v<T>)
            {
                return ptr;
            }

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

        template <class T , class... Args> T* ObjectAlloc(Args&&... args)
        {
            void* memory = Alloc(sizeof(T));
            T* ptr = new (memory) T(std::forward<Args>(args)...);
            return ptr;
        }

        template <class T , class... Args> T* ObjectAllocAligned(size_t Alignment , Args&&... args)
        {
            void* memory = Alloc(sizeof(T) , Alignment);
            T* ptr = new (memory) T(std::forward<Args>(args)...);
            return ptr;
        }


        template <class T , class... Args> T* MonotonicObjectAllocAlignedDestructorTracking(size_t Capacity , size_t Alignment , Args&&... args)
        {
            void* memory = MonoAlloc(sizeof(T) , Alignment);
            T* ptr = new (memory) T(std::forward<Args>(args)...);
            if constexpr (std::is_trivially_destructible_v<T>)
            {
                return ptr;
            }

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

        template <class T , class... Args> T* MonotonicObjectAllocAligned(size_t Capacity , size_t Alignment , Args&&... args)
        {
            void* memory = MonoAlloc(sizeof(T) , Alignment);
            T* ptr = new (memory) T(std::forward<Args>(args)...);
            return ptr;
        }

        ArenaSnap* SnapShot();

        ArenaSnap SnapShotByValue();

        void Rewinder(ArenaSnap* Snap);

        void RewinderByValue(ArenaSnap Snap);

        size_t ByteUse();

        size_t BytesAllocated();

        size_t TotalBytesAllocated();

        size_t FreeSpace();

        bool IsEmpty();

        bool IsFull();

        bool CanAllocWithoutAlignCheck(size_t Capacity);

        void ArenaAllocaterReset();

        ~ArenaAllocater();

};
//extern thread_local ArenaAllocater ThreadArena;

thread_local inline ArenaAllocater* ThreadArenaPtr;

#endif // ARENAALLOCATOR_H_INCLUDED
