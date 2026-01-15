template <class T> class Unique_Ptr 
{ 
T* ptr; 
public: //Some functions will be added
Unique_Ptr()
{
ptr = nullptr;
}
Unique_Ptr(T* Data)
{
ptr = Data;
}
Unique_Ptr(Unique_Ptr&& other)
{
this->ptr = other.ptr;
other.ptr = nullptr;
}
Unique_Ptr& operator=(Unique_Ptr&& other)
{
if(this != &other)
{
delete this->ptr;
this->ptr = other.ptr;
other.ptr = nullptr;
}
return *this;
}
Unique_Ptr(const Unique_Ptr& other) = delete;

Unique_Ptr& operator=(Unique_Ptr& other) = delete;

~Unique_Ptr() { delete ptr; } 
};