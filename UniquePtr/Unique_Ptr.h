template <class T> class Unique_Ptr 
{ 
T* ptr; 
public: //Some functions and will add move constructor and move assignment operator
Unique_Ptr()
{
ptr = nullptr;
}
Unique_Ptr(const Unique_Ptr& other) = delete;

Unique_Ptr& operator=(Unique_Ptr& other) = delete;

~Unique_Ptr() { delete ptr; } 
};