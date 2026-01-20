#include <iostream>

using namespace std;

template <class T> class Unique_Ptr
{
    T* ptr;
    public: //Some functions will be added

        Unique_Ptr()
        {
            ptr = nullptr;
        }

        explicit Unique_Ptr(T* Data)
        {
            ptr = Data;
        }

        Unique_Ptr(Unique_Ptr&& other) noexcept
        {
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }

        Unique_Ptr& operator=(Unique_Ptr&& other) noexcept
        {
            if(this != &other)
            {
                delete this->ptr;
                this->ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        T& operator*() const //returns a reference  which is an alias for the original variable
        {
            return *ptr;
        }

        T* operator->() const noexcept //returns a pointer which holds the memory address
        {
            return ptr;
        }

        explicit operator bool() const noexcept
        {
            return ptr != nullptr;
        }
        
        T* Release() noexcept
        {
            T* Releaser = ptr;
            ptr = nullptr;
            return Releaser;
        }
        
        T* Get() const noexcept
        {
            return ptr;
        }

        void Reset(T* newptr = nullptr)
        {
            delete ptr;
            ptr = newptr;
        }

        Unique_Ptr(const Unique_Ptr& other) = delete;

        Unique_Ptr& operator=(const Unique_Ptr& other) = delete;

        ~Unique_Ptr() { delete ptr; }
};

template <class T> class Unique_Ptr<T[]>
{
    T* ptr;

    public:

        Unique_Ptr()
        {
            ptr = nullptr;
        }

        explicit Unique_Ptr(T* Data)
        {
            ptr = Data;
        }

        Unique_Ptr(Unique_Ptr&& other) noexcept
        {
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }

        Unique_Ptr& operator=(Unique_Ptr&& other) noexcept
        {
            if(this != &other)
            {
                delete[] this->ptr;
                this->ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        T& operator[](int index) const
        {
            return ptr[index];
        }

        explicit operator bool() const noexcept
        {
            return ptr != nullptr;
        }

        T* Release()
        {
            T* Releaser = ptr;
            ptr = nullptr;
            return Releaser;
        }
        
        T* Get() const noexcept
        {
            return ptr;
        }

        void Reset(T* newptr = nullptr)
        {
            delete[] ptr;
            ptr = newptr;
        }

        Unique_Ptr(const Unique_Ptr& other) = delete;

        Unique_Ptr& operator=(const Unique_Ptr& other) = delete;

        ~Unique_Ptr() { delete[] ptr; }
};
