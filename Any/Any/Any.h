#pragma once

#include <typeinfo>

class IHolder
{
	virtual const type_info& info() const = 0;

	virtual IHolder* clone() const = 0;

	friend class Any;

	public:

		virtual ~IHolder() = 0;
};


IHolder::~IHolder() {}

template <class T> class Holder : public IHolder
{

	const type_info& info() const override
	{
		return typeid(T);
	}

	IHolder* clone() const override
	{
		Holder <T>* Hold = new Holder<T>();
		Hold->Data = Data;
		return Hold;
	}

	public:

		T Data;

	friend class Any;
};

class Any
{
	IHolder* ptr;

	public :

		Any()
		{
			ptr = nullptr;
		}

		Any(Any& any)
		{	
			this->ptr = any.ptr ? any.ptr->clone() : nullptr;
		}

		Any(Any&& any)
		{
			this->ptr = any.ptr;
			any.ptr = nullptr;
		}

		Any& operator= (Any& any)
		{
			Reset();
			this->ptr = any.ptr ? any.ptr->clone() : nullptr;
			return *this;
		}

		Any& operator= (Any&& any)
		{
			Reset();
			this->ptr = any.ptr;
			any.ptr = nullptr;
			return *this;
		}

		template <class T> void operator= (T data)
		{
			Reset();
			Holder <T>* Hold = new Holder<T>();
			Hold->Data = data;
			ptr = Hold;
		}

		template <class T> T Get()
		{
			if (ptr->info() == typeid(T))
			{
				Holder <T>* Hold = dynamic_cast<Holder<T>*>(ptr);
				return Hold->Data;
			}

			throw std::bad_cast();
		}

		bool Has_Value()
		{
			if (ptr)
			{
				return true;
			}

			return false;
		}

		void Reset()
		{
			if (ptr)
			{
				delete ptr;
				ptr = nullptr;
			}
		}

		~Any()
		{
			delete ptr;
		}
};

