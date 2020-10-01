#pragma once

//---------------------------------------------|
//											   |
//	Vect.h 								       |
//											   |
//	Not std Vector library					   |
//											   |
//	Created by:								   |
//											   |
//	Vavilov Aleksandr Aleksandrovich		   |
//											   |
//	© 2020 NONAME corp. All rights reserved	   |
//											   |
//---------------------------------------------|

namespace av
{

	template <class T>
	class Vect
	{
	private:

		T* array = nullptr;
		unsigned short size_ = 0;
	public:
		Vect<T>() = default;

		Vect<T>(int size)
		{
			try
			{
				array = new T[size];
				size_ = size;
			}
			catch (std::bad_alloc & error)
			{
				std::cerr << "Constructor bad_alloc caught: " << error.what() << std::endl;
				throw error;
			}
		}

		Vect<T>(Vect<T>& obj)
		{
			try
			{
				array = new T[obj.size()];
				size_ = obj.size();
				for (size_t i = 0; i < obj.size(); i++)
				{
					array[i] = obj[i];
				}
			}
			catch (std::bad_alloc & error)
			{
				std::cerr << "Constructor bad_alloc caught: " << error.what() << std::endl;
				throw error;
			}
		}


		void push_back(const T a)
		{
			try
			{
				T* temp = new T[size_ + 1];
				for (size_t i = 0; i < size_; i++)
				{
					temp[i] = array[i];
				}
				temp[size_] = a;
				delete[] array;
				array = temp;
				size_++;
			}
			catch (std::bad_alloc & error)
			{
				std::cerr << "Push_back bad_alloc caught: " << error.what() << std::endl;
				throw error;
			}
		}

		void erase(const int start)
		{
			erase(start, start);
		}

		void erase(int start, int finish)
		{
			if (start > size_) throw std::exception("Erase start > size");
			if (finish > size_) throw std::exception("Erase finish > size");
			if (start > finish) throw std::exception("Erase start > finish");
			T* temp = new T[size_ - ((finish - start) + 1)];
			int a = 0;
			for (auto i = 0; i < start; i++)
			{
				temp[i] = array[i];
				a++;
			}
			for (auto i = finish + 1; i < size_; i++)
			{
				temp[a] = array[i];
				a++;
			}
			delete array;
			array = temp;
			size_ -= ((finish - start) + 1);
		}


		void pop_back(int value = 1)
		{
			if (value > size_) throw std::exception("pop_back out_of_range");
			T* temp = new T[size_ - value];
			for (auto i = 0; i < size_ - value; i++)
			{
				temp[i] = array[i];
			}
			delete array;
			array = temp;
			size_ -= value;
		}


		void insert(int index, const T value)
		{
			if (index > size_) throw std::exception("Insert index > size");
			if (index < 0) throw std::exception("Insert index < 0");
			T* temp = new T[size_ + 1];

			for (auto i = 0; i < index; i++)
			{
				temp[i] = array[i];
			}
			temp[index] = value;
			for (auto i = index + 1; i < size_ + 1; i++)
			{
				temp[i] = array[i - 1];
			}
			delete array;
			array = temp;
			size_++;
		}


		Vect& operator=(Vect<T>& vec)
		{
			size_ = vec.size();
			delete array;
			array = new T[size()];
			for (size_t i = 0; i < size(); i++)
			{
				array[i] = vec[i];
			}
			return *this;
		}

		T& operator[](int key) const
		{
			if (key > size_) throw std::exception("operator[] key > size");
			if (key < 0) throw std::exception("operator[] key < 0");
			T val = array[key];
			return val;
		}

		int size() const
		{
			return size_;
		}

		Vect& operator+=(const T a)
		{
			push_back(a);
			return *this;
		}

		Vect& operator-=(const int a)
		{
			pop_back(a);
			return *this;
		}

		~Vect()
		{
			delete[] array;
		}
	};

	template<class T, class U>
	T& operator<<(T& os, const Vect<U>& vect)
	{
		for (size_t i = 0; i < vect.size(); i++)
			os << vect[i] << " ";
		os << '\n';
		return os;
	}



	template<class T>
	void operator--(const Vect<T>& vect)
	{
		vect.pop_back();
	}

	template <class U>
	inline bool operator<(const Vect<U>& lhs, const Vect<U>& rhs)
	{
		return rhs.size() < lhs.size();
	}

	template <class U>
	inline bool operator>(const Vect<U>& lhs, const Vect<U>& rhs)
	{
		return rhs.size_() > lhs.size_();
	}

	template <class U>
	inline bool operator==(const Vect<U>& lhs, const Vect<U>& rhs)
	{
		if (rhs.size_() == lhs.size_())
		{
			for (int i = 0; i < rhs.size_(); i++)
			{
				if (lhs[i] != rhs[i]) return false;
			}
			return true;
		}
		return false;
	}
}