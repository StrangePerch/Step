#pragma once

#include <iostream>

using namespace std;

template <class T>
class Node
{
public:
	T data;
	Node* next = nullptr;
	Node(T data)
	{
		this->data = data;
	}

	void echo(int step)
	{
		cout << "(#" << step << ") = " << data << "\n";
		if (next != nullptr)
			next->echo(++step);
	}

	void remove()
	{
		if (next != nullptr)
		{
			next->remove();
			delete next;
		}
	}

};

template <class T>
class ForwardList
{
private:
	Node<T>* root_;
	Node<T>* iterator_;
	
public:
	ForwardList()
	{
		root_ = nullptr;
		iterator_ = nullptr;
	}

	void push_back(T data)
	{
		Node<T>* new_root = new Node<T>(data);
		new_root->next = this->root_;
		this->root_ = new_root;
	}	
	
	void echo()
	{
		if (root_ == nullptr) cout << "List empty" << endl;
		else
		{
			cout << "List:" << endl;
			root_->echo(1);
		}
	}

	T get()
	{
		return root_->data;
	}
	
	T pop_back()
	{
		if (isEmpty() == false)
		{
			Node<T>* old_root = this->root_;
			T data = old_root->data;
			this->root_ = old_root->next;
			delete old_root;
			return data;
		}
	}

	bool isEmpty()
	{
		if (this->root_ == nullptr) return true;
		return false;
	}

	operator T()
	{
		return iterator_.data;
	}

	Node<T>* operator++()
	{
		iterator_ = iterator_->next;
		return iterator_;
	}
	
	~ForwardList()
	{
		root_->remove();
	}
	
};
