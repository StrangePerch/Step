#pragma once

namespace av
{
	template <class T>
	class SmartPointer
	{
	public:
		T* pointer = nullptr;
		SmartPointer(T* p) : pointer(p)
		{
		}
		SmartPointer(const SmartPointer& p)
		{
			pointer = new T;
			*pointer = *p.pointer;
		}
		SmartPointer(SmartPointer&& p) noexcept
		{
			pointer = p.pointer;
			p.pointer = nullptr;
		}
		~SmartPointer()
		{
			delete pointer;
		}
			
		SmartPointer& operator=(const SmartPointer& rhs)
		{
			if (&rhs != this)
			{
				delete pointer;
				pointer = new T;
				*pointer = rhs.pointer;
			}
			return *this;
		}
		
		SmartPointer& operator=(SmartPointer&& rhs) noexcept
		{
			if (&rhs != this)
			{
				delete pointer;
				pointer = rhs.pointer;
				rhs.pointer = nullptr;
			}
			return *this;
		}
		T* operator->()
		{
			return pointer;
		}
	};
}