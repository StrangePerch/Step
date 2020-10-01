#pragma once

#include <iomanip>
#include <iostream>

#include "../Vector/Vect.h"

//+-------------------------------------------------------------------+
//| BinaryTree													      |
//+-------------------------------------------------------------------+
//|																	  |
//|	@author	Vavilov Alexandr Alexndrovich <sasha.aav.sv@gmail.com>     |
//|																	  |
//| Data must have overloaded operators >, <, ==, !=				  |
//|																	  |
//+-------------------------------------------------------------------+

namespace av
{

	template<class TVal, class TKey>
	class TreeNode
	{
	public:
		int height = 1;
		TVal data;
		TKey key;
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
		TreeNode(TVal val, TKey key)
		{
			this->data = val;
			this->key = key;
		}

		TVal* get(TKey& key)
		{
			if (key == this->key) return &this->data;
			if (key < this->key && this->left != nullptr) return this->left->get(key);
			if (key > this->key && this->right != nullptr) return this->right->get(key);
			return nullptr;
		}
		
		void menu()
		{
			while (true)
			{
				std::system("cls");
				std::cout << std::setw(10) << data << std::endl;
				std::cout << std::setw(11) << "/   \\" << std::endl;
				if (left != nullptr)
					std::cout << std::setw(7) << left->data;
				else
					std::cout << std::setw(7) << " ";
				if (right != nullptr)
					std::cout << std::setw(6) << right->data << std::endl;
				else
					std::cout << std::setw(6) << " " << std::endl;
				int choice;
				std::cout << std::endl << "0.Back, 1.Left, 2.Right" << std::endl;
				std::cin >> choice;
				switch (choice)
				{
				default: return;
				case 1: if(left != nullptr) left->menu(); break;
				case 2: if(right != nullptr) right->menu(); break;
				}
			}
		}

		void echo()
		{
			if (left != nullptr) left->echo();
			std::cout << data << " ";
			if (right != nullptr) right->echo();
		}

		TreeNode<TVal, TKey>* push(TVal& data, TKey& key)
		{
			if (key > this->key)
			{
				if (right != nullptr)
				{
					return right->push(data, key);
				}
				else
				{
					right = new TreeNode<TVal, TKey>(data, key);
					return right;
				}
			}
			else
			{
				if (left != nullptr)
				{
					return left->push(data, key);
				}
				else
				{
					left = new TreeNode<TVal, TKey>(data, key);
					return left;
				}
			}
		}

		Vect<TVal> createArray(Vect<TVal>& array)
		{
			if (left != nullptr) left->createArray(array);
			array.push_back(data);
			if (right != nullptr) right->createArray(array);
			return array;
		}

	};
	
	
	
	template <class T>
	int max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	
	template<class TVal, class TKey>
	class BinaryTree
	{
		TreeNode<TVal, TKey>* root_ = nullptr;
	public:

		BinaryTree(){}

		bool isEmpty()
		{
			if (this->root_ == nullptr) return true;
			return false;
		}

		void echo()
		{
			root_->echo();
		}

		Vect<TVal> createArray()
		{
			Vect<TVal> a;
			return root_->createArray(a);
		}
		
		void menu()
		{
			root_->menu();
		}


		TreeNode<TVal, TKey>* push(TVal data)
		{
			return push(data, data);
		}

		TreeNode<TVal, TKey>* push(TVal data, TKey key)
		{
			if (root_ == nullptr) return root_ = new TreeNode<TVal, TKey>(data, key);

			return root_->push(data, key);
		}

		TVal* get(TKey& key)
		{
			if (this->root_ != nullptr)
				return this->root_->get(key);
			return nullptr;
		}
	};


}