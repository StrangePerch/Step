#pragma once

#include <iostream>

namespace av
{

	template <class T>
	class Node
	{
	public:
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
		Node(T& data)
		{
			this->data = data;
		}

		T get()
		{
			return data;
		}

		void echo(int step)
		{
			std::cout << "(#" << step << ") = " << data << "\n";
			if (next != nullptr)
				next->echo(++step);
		}

		int length()
		{
			if (next == nullptr) return 1;
			else return next->length() + 1;
		}
		void remove()
		{
			if (next != nullptr)
			{
				next->remove();
				delete next;
			}
		}

		Node<T>* find(const T& obj)
		{
			if (this->data == obj) return this;
			if (next == nullptr) return nullptr;
			return next->find(obj);
		}

		Node<T>& at(int& index)
		{
			if (index == 0) return *this;
			if (next == nullptr) throw std::exception("Out or range");
			return next->at(--index);
		}

		Node<T>* operator++()
		{
			return next;
		}

		Node<T>* operator--()
		{
			return prev;
		}

		friend std::ostream& operator<< (std::ostream& os, Node<T>& a)
		{
			os << a.data;
			return os;
		}

		operator T()
		{
			return data;
		}

	};

	template <class T>
	class List
	{
	public:

		class iterator
		{
		public:
			Node<T>* pointer;
		public:
			iterator()
			{
				pointer = nullptr;
			}
			iterator(iterator& other)
			{
				pointer = other.pointer;
			}
			iterator(Node<T>* other)
			{
				pointer = other;
			}
			iterator& operator++(int)
			{
				if (!pointer) throw std::exception("Iterator is nullptr");
				pointer = pointer->next;
				return *this;
			}

			iterator& operator--(int)
			{
				if (!pointer) throw std::exception("Iterator is nullptr");
				pointer = pointer->prev;
				return *this;
			}

			iterator& operator++()
			{
				if (!pointer) throw std::exception("Iterator is nullptr");
				pointer = pointer->next;
				return *this;
			}

			iterator& operator--()
			{
				if (!pointer) throw std::exception("Iterator is nullptr");
				pointer = pointer->prev;
				return *this;
			}

			iterator& operator=(Node<T>* p)
			{
				pointer = p;
				return *this;
			}

			iterator& operator=(T data)
			{
				pointer->data = data;
				return *this;
			}

			Node<T>* operator->()
			{
				return pointer;
			}

			operator T()
			{
				if (!pointer) throw std::exception("Iterator is nullptr");
				return pointer->data;
			}

			T& operator*()
			{
				return pointer->data;
			}

			operator Node<T>* ()
			{
				return pointer;
			}

			friend std::ostream& operator<<(std::ostream& os, iterator& i)
			{
				if (!i.pointer) throw std::exception("Iterator is nullptr");
				os << i.pointer->data;
				return os;
			}

			friend bool operator==(iterator& lhs, iterator& rhs)
			{
				if (lhs.pointer == rhs.pointer) return true;
				return false;
			}

			friend bool operator!=(iterator& lhs, iterator& rhs)
			{
				if (lhs.pointer == rhs.pointer) return false;
				return true;
			}

			~iterator()
			{
				pointer = nullptr;
			}
		};

		Node<T>* front_;
		Node<T>* back_;

		List()
		{
			front_ = nullptr;
			back_ = nullptr;
		}

		List(List<T>& list)
		{
			try
			{
				iterator iterator_;
				iterator_ = list.begin();
				while (iterator_.pointer)
				{
					push_back(iterator_->data);
					++iterator_;
				}
			}
			catch (std::bad_alloc & error)
			{
				std::cerr << "bad_alloc caught, not enough memory: " << error.what() << std::endl;
				throw;
			}
		}

		Node<T>* find(const T& obj)
		{
			if (isEmpty()) return nullptr;
			return front_->find(obj);
		}

		Node<T>& at(int index)
		{
			if (index < 0) throw std::exception("Out of range, index < 0");
			if (index == 0) return *front_;
			return front_->at(index);
		}

		Node<T>& push_back(T& data)
		{
			try
			{
				if (back_ != nullptr)
				{
					auto* new_back = new Node<T>(data);
					new_back->prev = this->back_;
					new_back->prev->next = new_back;
					back_ = new_back;
				}
				else
				{
					this->front_ = new Node<T>(data);
					this->front_->next = nullptr;
					this->front_->prev = nullptr;
					this->back_ = this->front_;
				}
			}
			catch (std::bad_alloc & error)
			{
				std::cerr << "Push_back bad_alloc caught: " << error.what() << std::endl;
				throw error;
			}
			return *back_;
		}

		int length()
		{
			if (isEmpty()) return 0;
			return front_->length();
		}

		void push_front(T data)
		{
			try
			{
				if (front_ != nullptr)
				{
					auto* new_front = new Node<T>(data);
					new_front->next = this->front_;
					new_front->prev = nullptr;;
					front_->prev = new_front;
					front_ = new_front;
				}
				else
				{
					front_ = new Node<T>(data);
					back_ = front_;
					front_->next = nullptr;
					front_->prev = nullptr;
				}
			}
			catch (std::bad_alloc & error)
			{
			std::cerr << "Push_front bad_alloc caught: " << error.what() << std::endl;
			throw error;
			}
		
		}

		void echo()
		{
			if (front_ == nullptr) std::cout << "List empty" << std::endl;
			else
			{
				std::cout << "List:" << std::endl;
				front_->echo(1);
			}
		}

		T pop_back()
		{
			if (!begin()) throw std::exception("List is empty");
			T data = back_->data;
			Node<T>* old_back = this->back_;
			this->back_ = old_back->prev;
			if (back_ != nullptr)
				back_->next = nullptr;
			if (this->back_ == nullptr)
			{
				this->front_ = nullptr;
			}
			delete old_back;
			old_back = nullptr;
			return data;
		}

		T pop_front()
		{
			if(!begin()) throw std::exception("List is empty");
			T data = front_->data;
			Node<T>* old_front = this->front_;
			this->front_ = old_front->next;
			if (front_ != nullptr)
				front_->prev = nullptr;
			if (this->front_ == nullptr)
			{
				this->back_ = nullptr;
			}
			delete old_front;
			old_front = nullptr;
			return data;

		}

		void discard_back()
		{
			if (!front_) throw std::exception("List is empty");
			Node<T>* old_back = this->back_;
			this->back_ = old_back->prev;
			if (back_ != nullptr)
				back_->next = nullptr;
			if (this->back_ == nullptr)
			{
				this->front_ = nullptr;
			}
			delete old_back;
			old_back = nullptr;
		}

		void discard_front()
		{
			if (!front_) throw std::exception("List is empty");
			Node<T>* old_front = this->front_;
			this->front_ = old_front->next;
			if (front_ != nullptr)
				front_->prev = nullptr;
			if (this->front_ == nullptr)
			{
				this->back_ = nullptr;
			}
			delete old_front;
			old_front = nullptr;
		}

		Node<T>* min()
		{
			Node<T>* min = begin();
			iterator iterator_ = begin()->next;
			while (iterator_ != nullptr)
			{
				if (iterator_ < min->data) min = iterator_;
				++iterator_;
			}
			return min;
		}

		Node<T>* max()
		{
			Node<T>* max = begin();
			iterator iterator_ = begin()->next;
			while (iterator_ != nullptr)
			{
				if (iterator_ > max->data) max = iterator_;
				++iterator_;
			}
			return max;
		}

		void pop_pointer(Node<T>* pointer)
		{
			if(!pointer) throw std::exception("Pop nullptr");
			if (pointer == front_)
			{
				discard_front();
				return;
			}
			if (pointer == back_)
			{
				discard_back();
				return;
			}
			pointer->prev->next = pointer->next;
			pointer->next->prev = pointer->prev;
			//T data = pointer->data;
			delete pointer;
			return;// data;
		}

		void push(Node<T>* pointer, T data, bool next = true)
		{
			if (!pointer) throw std::exception("Push to nullptr");
			try
			{
				Node<T>* temp;
				if (next)
				{
					temp = new Node<T>;
					temp->data = data;
					temp->prev = pointer;
					temp->next = pointer->next;
					pointer->next->prev = temp;
					pointer->next = temp;
				}
				else
				{
					temp = new Node<T>;
					temp->data = data;
					temp->next = pointer;
					temp->prev = pointer->prev;
					pointer->prev->next = temp;
					pointer->prev = temp;
				}
			}
			catch (std::bad_alloc & error)
			{
				std::cerr << "Push bad_alloc caught: " << error.what() << std::endl;
				throw error;
			}
		}

		bool isEmpty()
		{
			if (front_ == nullptr || back_ == nullptr) return true;
			return false;
		}

		List<T>& operator=(const List<T>& list)
		{
			iterator iterator_ = list.front_;
			while (iterator_.pointer)
			{
				push_back(iterator_->data);
				iterator_ = iterator_->next;
			}
			return *this;
		}

		friend bool operator==(List<T>& lhs, T& rhs)
		{
			iterator iterator_ = lhs.front_;
			while (iterator_.pointer)
			{
				if (iterator_->data != rhs) return false;
				iterator_++;
			}
			return true;
		}

		iterator& end()
		{
			return *new iterator(back_);
		}

		iterator& back()
		{
			return *new iterator(back_);
		}

		iterator& begin()
		{
			return *new iterator(front_);
		}

		iterator& front()
		{
			return *new iterator(front_);
		}

		~List()
		{
			if (!isEmpty())
				front_->remove();
		}

	};
}