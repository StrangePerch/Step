#pragma once

#include <iomanip>

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
		TVal data;
		TKey key;
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
		TreeNode(TVal val, TKey key)
		{
			this->data = val;
			this->key = key;
		}

		void menu()
		{
			while (1)
			{
				std::system("cls");
				cout << setw(10) << data << endl;
				cout << setw(11) << "/   \\" << endl;
				if (left != nullptr)
					cout << setw(7) << left->data;
				else
					cout << setw(7) << " ";
				if (right != nullptr)
					cout << setw(6) << right->data << endl;
				else
					cout << setw(6) << " " << endl;
				int choice;
				cout << endl << "0.Back, 1.Left, 2.Right" << endl;
				cin >> choice;
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
			cout << data << " ";
			if (right != nullptr) right->echo();
		}
		
		bool push(TVal& data, TKey& key)
		{
			if (key > this->key)
			{
				if (right != nullptr)
				{
					right->push(data, key);
				}
				else
				{
					right = new TreeNode<TVal, TKey>(data, key);
				}
				return true;
			}
			else
			{
				if (left != nullptr)
				{
					left->push(data, key);
				}
				else
				{
					left = new TreeNode<TVal, TKey>(data, key);
					return true;
				}
			}
		}
	};


	template<class TVal, class TKey>
	class BinaryTree
	{
	public:
		TreeNode<TVal, TKey>* root_ = nullptr;

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
		
		void menu()
		{
			root_->menu();
		}
		
		bool push(TVal data, TKey key)
		{
			if(isEmpty())
			{
				this->root_ = new TreeNode<TVal, TKey>(data,key);
				return true;
			}
			else
			{
				return root_->push(data, key);
			}
		}
	};


}