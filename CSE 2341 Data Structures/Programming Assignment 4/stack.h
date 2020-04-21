#ifndef LLSTACK
#define LLSTACK

#include "linkedlist.h"
#include <iostream>

template <class T>
class Stack{
	private:
		LinkedList<T> list;

	public:
		bool empty();
		int height();
		void push(const T);
		T pop();
		T top();
		bool contains(const T);
};

template <class T>
bool Stack<T>::empty(){
	if(list.size() == 0){
		return true;
	}
	else{
		return false;
	}
}

template <class T>
int Stack<T>::height(){
	return list.size();
}

template <class T>
void Stack<T>::push(const T element){
	list.append(element);
}

template <class T>
T Stack<T>::pop(){
	T element = list.last();
	list.truncate();
	return element;
}

template <class T>
T Stack<T>::top(){
	return list.last();
}

template <class T>
bool Stack<T>::contains(const T element){ //iterates through private list to see if one of its elements matches what is passed
	for(int i = 0; i < list.size(); i++){
		if(list[i] == element) return true;
	}
	return false;
}

#endif