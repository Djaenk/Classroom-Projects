#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>
#include <exception>

template <class T>
struct Node;

template <class T>
class LinkedList{
	private:
		Node<T>* head = nullptr;
		Node<T>* tail = nullptr;
		int len = 0;

	public:
		LinkedList() = default;
		LinkedList(const LinkedList&);
		LinkedList& operator=(const LinkedList&);
		~LinkedList();

		T& operator[](const int);
		T& operator[](const int) const;
		T& first();
		T& last();
		int size();
		void clear();
		void insert(T, const int);	//add element to arbitrary location in list
		void erase(const int);		//remove element from arbitrary location in list
		void append(T);				//add element to end of list
		void truncate();			//remove element from end of list
		void prepend(T);			//add element to beginning of list
		void remove();				//remove element from beginning of list
};

template <class T>
struct Node{
	T data;
	Node<T>* prev = nullptr;
	Node<T>* next = nullptr;

	Node(T data){
		this->data = data;
	}
	Node(T data, Node* p, Node* n){ //inserts self into list upon initialization
		this->data = data;
		if(p){prev = p; p->next = this;}
		if(n){next = n; n->prev = this;}
	}
	~Node(){ //points preceding and proceeding nodes to each other
		Node<T>* p = prev;
		Node<T>* n = next;
		if(prev) prev->next = n;
		if(next) next->prev = p;
	}
};



template <class T>
LinkedList<T>::LinkedList(const LinkedList& source){
	for(int i = 0; i < source.len; i++){
		append(source[i]);
	}
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& source){
	clear();
	for(int i = 0; i < source.len; i++){
		append(source[i]);
	}
	return *this;
}

template <class T>
LinkedList<T>::~LinkedList(){
	clear();
}

template <class T>
T& LinkedList<T>::operator[](const int index){
	Node<T>* iter;
	if(index >= len || index < 0) throw std::out_of_range ("Index out of linked list range.");
	iter = head;
	for(int i = 0; i < index; i++){
		iter = iter->next;
	}
	return iter->data;
}

template <class T>
T& LinkedList<T>::operator[](const int index) const{
	Node<T>* iter;
	if(index >= len || index < 0) throw std::out_of_range ("Index out of linked list range.");
	iter = head;
	for(int i = 0; i < index; i++){
		iter = iter->next;
	}
	return iter->data;
}

template <class T>
T& LinkedList<T>::first(){
	if(len == 0) throw std::out_of_range ("No elements in linked list.");
	return head->data;
}

template <class T>
T& LinkedList<T>::last(){
	if(len == 0) throw std::out_of_range ("No elements in linked list.");
	return tail->data;
}

template <class T>
int LinkedList<T>::size(){
	return len;
}

template <class T>
void LinkedList<T>::clear(){
	Node<T>* iter = head;
	while(iter){
		head = head->next;
		delete iter;
		iter = head;
	}
	len = 0;
}

template <class T>
void LinkedList<T>::insert(T data, const int index){
	if(index > len || index < 0) throw std::out_of_range ("Index out of linked list range.");
	else if(index == 0){
		head = new Node<T>(data, nullptr, head);
	}
	else if(index == len){
		tail = new Node<T>(data, tail, nullptr);
	}
	else{
		Node<T>* iter = head;
		for(int i = 0; i < index; i++){
			iter = iter->next;
		}
		new Node<T>(data, iter->prev, iter);
	}
	len++;
}

template <class T>
void LinkedList<T>::erase(const int index){
	if(index > len || index < 0) throw std::out_of_range ("Index out of linked list range.");
	else if(index == 0){
		head = head->next;
		delete head->prev;
	}
	else if(index == len){
		tail = tail->prev;
		delete tail->next;
	}
	else{
		Node<T>* iter = head;
		for(int i = 0; i < index; i++){
			iter = iter->next;
		}
		delete iter;
	}
	len--;
}

template <class T>
void LinkedList<T>::append(T data){
	if(tail){
		tail = new Node<T>(data, tail, nullptr);
	}
	else{
		head = tail = new Node<T>(data);
	}
	len++;
}

template <class T>
void LinkedList<T>::truncate(){
	if(len == 0){
		//do nothing
	}
	if(len == 1){
		delete tail;
		head = tail = nullptr;
		len--;
	}
	else{
		tail = tail->prev;
		delete tail->next;
		len--;
	}		
}

template <class T>
void LinkedList<T>::prepend(T data){
	if(head){
		head = new Node<T>(data, nullptr, head);
	}
	else{
		head = tail = new Node<T>(data);
	}
	len++;
}

template <class T>
void LinkedList<T>::remove(){
	if(len == 0){
		//do nothing
	}
	if(len == 1){
		delete head;
		head = tail = nullptr;
		len--;
	}
	else{
		head = head->next;
		delete head->prev;
		len--;
	}
}

#endif