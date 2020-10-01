#pragma once

#include <iomanip>
#include "../Vector/Vect.h"

//+-------------------------------------------------------------------+
//| AVLTree  													      |
//+-------------------------------------------------------------------+
//|																	  |
//|	@author	Vavilov Alexandr Alexndrovich <sasha.aav.sv@gmail.com>    |
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
			height = 1;
		}

		TVal* get(TKey& key)
		{
			if (key == this->key) return &this->data;
			if (key < this->key && this->left != nullptr) return this->left->get(key);
			if (key > this->key && this->right != nullptr) return this->right->get(key);
			return nullptr;
		}

		TreeNode<TVal, TKey>* find(TKey& key)
		{
			if (key > this->key)
				if (right != nullptr)
					return right->find(key);
				else return nullptr;
			else if (key < this->key)
				if (left != nullptr)
					return left->find(key);
				else return nullptr;
			else
				return this;
		}

		TreeNode<TVal, TKey>* push(TVal& val, TKey& key)
		{
			TreeNode<TVal, TKey>* temp;
			if (key > this->key)
			{
				if (right == nullptr)
				{
					height++;
					return right = new TreeNode<TVal, TKey>(val, key);
				}
				temp = right->push(val, key);
			}
			else if(key < this->key)
			{
				if (left == nullptr)
				{
					height++;
					return left = new TreeNode<TVal, TKey>(val, key);
				}
				temp = left->push(val, key);
			}
			else
			{
				return nullptr;
			}
			balance();
			return temp;
		}

		void balance()
		{
			balance(left);
			balance(right);
		}

		void balance(TreeNode<TVal, TKey>*& node)
		{
			adjustHeight();
			if (getBalance(node) > 1)
			{
				if (getBalance(node->right) >= 0)
					node = node->rightTurn();
				else if (getBalance(node->left) < -1)
				{
					node->left = node->left->leftTurn();
					node = node->rightTurn();
				}
			}
			if (getBalance(node) < -1)
			{
				if (getBalance(node->left) <= 0)
					node = node->leftTurn();
				else if (getBalance(node->right) > 1)
				{
					node->right = node->right->rightTurn();
					node = node->leftTurn();
				}
			}
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
				case 1: if (left != nullptr) left->menu(); break;
				case 2: if (right != nullptr) right->menu(); break;
				}
			}
		}

		void echo(std::ostream& os)
		{
			if (left != nullptr) left->echo(os);
			os << data << " ";
			if (right != nullptr) right->echo(os);
		}

		void echo_h()
		{
			if (left != nullptr) left->echo_h();
			std::cout << data << " - " << height << std::endl;
			if (right != nullptr) right->echo_h();
		}

		void size(int& n)
		{
			n++;
			if (left != nullptr) left->size(n);
			if (right != nullptr) right->size(n);
		}

		//                      Left rotation
		//             x					      y
		//            / \					     / \
		//           a   y           --->	    x   b   
		//              / \					   / \
		//             z   b				  a   z 
		TreeNode < TVal, TKey> *leftTurn()
		{
			TreeNode<TVal, TKey>* x = this;
			TreeNode <TVal, TKey> *y = x->right;
			TreeNode <TVal, TKey> *z = y->left;


			//Rotation
			y->left = x;
			x->right = z;

			//Adjust height
			x->adjustHeight();
			y->adjustHeight();

			return y;
		}

		//                      Right rotation
		//             x				      y
		//            / \				     / \
		//           y   a          --->    b   x  
		//          / \					       / \
		//         b   z				      z   a
		TreeNode <TVal, TKey> *rightTurn()
		{
			TreeNode<TVal, TKey>* x = this;
			TreeNode <TVal, TKey> *y = x->left;
			TreeNode <TVal, TKey> *z = y->right;

			//Rotation
			y->right = x;
			x->left = z;

			//Adjust height
			x->adjustHeight();
			y->adjustHeight();

			return y;
		}

		void adjustHeight()
		{
			if (left == nullptr && right == nullptr) height = 1;
			else if (left == nullptr) height = right->height + 1;
			else if (right == nullptr) height = left->height + 1;
			else height = std::max(left->height, right->height) + 1;
		}
	};











	
	template <class V, class K>
	int getHeight(TreeNode<V, K>*& node)
	{
		if (node == nullptr) return 0;
		else
		{
			node->adjustHeight();
			return node->height;
		}

	}

	template <class V, class K>
	int getBalance(TreeNode<V,K>* node)
	{
		if (node == nullptr) return 0;
		return getHeight(node->left) - getHeight(node->right);
	}



	template <class T>
	int max(T a, T b)
	{
		return (a > b) ? a : b;
	}



	








	
	template<class TVal, class TKey>
	class AVLTree
	{
		
	TreeNode<TVal, TKey>* root_ = nullptr;
		
	public:

		AVLTree() = default;

		TreeNode<TVal, TKey>* begin()
		{
			return root_;
		}
		
		bool isEmpty()
		{
			if (this->root_ == nullptr) return true;
			return false;
		}

		void echo(std::ostream& os)
		{
			root_->echo(os);
		}

		void echo_h()
		{
			root_->echo_h();
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
			TreeNode<TVal, TKey>* temp = root_->push(data, key);
			root_->adjustHeight();
			if (getBalance(root_) < -1)
			{
				root_ = root_->leftTurn();
			}
			if (getBalance(root_) > 1)
			{
				root_ = root_->rightTurn();
			}
			return temp;
		}

		TreeNode<TVal, TKey>* find(TKey& key)
		{
			if (root_ == nullptr) return nullptr;
			return root_->find(key);
		}

		TVal* get(TKey& key)
		{
			if (this->root_ != nullptr)
				return this->root_->get(key);
			return nullptr;
		}

		int size()
		{
			int size = 0;
			root_->size(size);
			return size;
		}

		friend std::ostream& operator<< (std::ostream& os, AVLTree<TVal,TKey> tree)
		{
			echo(os);
			return os;
		}

	};


}