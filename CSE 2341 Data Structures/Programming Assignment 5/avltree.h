#pragma once
#include <algorithm>
#include <cmath>
#include <stdexcept>

template <class data>
class AVLNode{
	private:
		data element = {};
		AVLNode* left = nullptr;
		AVLNode* right = nullptr;
		int height = -1;

		void rotateRight();
		void rotateLeft();
		bool isImbalanced();
		void updateHeight();

	public:
		AVLNode(){}
		AVLNode(const data value) : element(value) {height = 0;}
		~AVLNode(){clear();}

		int size();
		bool isEmpty();
		void clear();
		int getHeight();
		data& operator[](data&);
		void insert(const data);
		bool contains(const data);
};



template <class data>
int AVLNode<data>::size(){
	if(left && right)
		return left->size() + right->size() + (element != data{});
	else if(left)
		return left->size() + (element != data{});
	else if(right)
		return right->size() + (element != data{});
	else
		return (element != data{});
}

template <class data>
bool AVLNode<data>::isEmpty(){
	return element == data{} && left == nullptr && right == nullptr;
}

template <class data>
void AVLNode<data>::clear(){
	element = {};
	delete left;
	left = nullptr;
	delete right;
	right = nullptr;
	height = -1;
}

template <class data>
int AVLNode<data>::getHeight(){
	if(height >= 0)
		return height;
	else
		throw std::underflow_error ("Cannot return height of an empty tree.");
}

template <class data>
data& AVLNode<data>::operator[](data& value){
	if(value == element){
		return element;
	}
	else if(value < element){
		if(left){
			return left->operator[](value);
		}
		else{
			left = new AVLNode(value);
			return left->element;
		}
	}
	else if(value > element){
		if(right){
			return right->operator[](value);
		}
		else{
			right = new AVLNode(value);
			return right->element;
		}
	}
	else{
		element = value;
		return element;
	}
}

template <class data>
void AVLNode<data>::insert(const data value){
	if(element == data()){
		element = value;
	}
	else if(value < element){
		if(left){
			left->insert(value);
			if(isImbalanced()){
				if(value < left->element){
					rotateRight();
				}
				else{
					left->rotateLeft();
					rotateRight();
				}
			}
		}
		else{
			left = new AVLNode<data>(value);
		}
	}
	else if(value > element){
		if(right){
			right->insert(value);
			if(isImbalanced()){
				if(value > right->element){
					rotateLeft();
				}
				else{
					right->rotateRight();
					rotateLeft();
				}
			}
		}
		else{
			right = new AVLNode<data>(value);
		}
	}
	updateHeight();
}

template <class data>
bool AVLNode<data>::contains(const data value){
	if(element == value)
		return true;
	else if(element < value && left)
		return left->contains(value);
	else if(element > value && right)
		return right->contains(value);
	else
		return false;
}

template <class data>
void AVLNode<data>::rotateRight(){
	AVLNode* temp = left;
	left = temp->right;
	temp->right = this;
	updateHeight();
	temp->updateHeight();
}

template <class data>
void AVLNode<data>::rotateLeft(){
	AVLNode* temp = right;
	right = temp->left;
	temp->left = this;
	updateHeight();
	temp->updateHeight();
}

template <class data>
bool AVLNode<data>::isImbalanced(){
	if(left && right)
		return abs(left->height - right->height) > 1;
	else if(left)
		return left->height > 0;
	else if(right)
		return right->height > 0;
	else
		return false;
}

template <class data>
void AVLNode<data>::updateHeight(){
	if(left && right)
		height = std::max(left->height, right->height) + 1;
	else if(left)
		height = left->height + 1;
	else if(right)
		height = right->height + 1;
	else
		height = 0;
}