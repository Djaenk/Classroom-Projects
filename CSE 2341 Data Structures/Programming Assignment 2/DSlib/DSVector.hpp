#ifndef DSVECTOR
#define DSVECTOR

template <class T>
class DSVector{
	private:
		T* vector = nullptr;
		int size = 0;

	public:
		DSVector();
		DSVector(const int);
		DSVector(const DSVector<T>&);
		~DSVector();
		DSVector& operator=(const DSVector<T>&);

		int len();
		T& back();
		T& operator[](const int i);
		void assign(const T[], int);
		void push_back(const T&);
		void pop_back();
		void insert(int, const T&);
		void erase(int);
		void swap(DSVector<T>&); //exchanges the contents of two DSVectors
		void clear(); //removes all elements of a DSVector;
		
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
DSVector<T>::DSVector(){
	vector = new T[0];
}

template<class T>
DSVector<T>::DSVector(const DSVector<T>& source){
	this->size = source.size;
	vector = new T[size];
	for(int i = 0; i < size; i++){
		vector[i] = source.vector[i];
	}
}

template<class T>
DSVector<T>::DSVector(const int size){
	vector = new T[size];
	this->size = size;
}

template <class T>
DSVector<T>::~DSVector(){
	delete[] vector;
}

template <class T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T>& source){
	delete[] vector;
	vector = new T[source.size];
	size = source.size;
	for(int i = 0; i < size; i++){
		vector[i] = source.vector[i];
	}
	return *this;
}

template <class T>
int DSVector<T>::len(){
	return size;
}

template <class T>
T& DSVector<T>::back(){
	return vector[size - 1];
}

template <class T>
T& DSVector<T>::operator[](const int i){
	return vector[i];
}

template <class T>
void DSVector<T>::assign(const T array[], int size){
	delete[] vector;
	vector = new T[size];
	this->size = size;
	for(int i = 0; i < size; i++){
		vector[i] = array[i];
	}
}

template <class T>
void DSVector<T>::push_back(const T& val){
	T* temp = vector;
	vector = new T[size + 1];
	for(int i = 0; i < size; i++){
		vector[i] = temp[i];
	}
	vector[size] = val;
	size++;
	delete[] temp;
}

template <class T>
void DSVector<T>::pop_back(){
	T* temp = vector;
	vector = new T[--size];
	for(int i = 0; i < size - 1; i++){
		vector[i] = temp[i];
	}
	delete[] temp;
}

template <class T>
void DSVector<T>::insert(int position, const T& val){
	T* temp = vector;
	vector = new T[size + 1];
	for(int i = 0; i < position; i++){
		vector[i] = temp[i];
	}
	vector[position] = val;
	for(int i = position; i < size; i++){
		vector[i + 1] = temp[i];
	}
	size++;
	delete[] temp;
}

template <class T>
void DSVector<T>::erase(int position){
	T* temp = vector;
	vector = new T[size - 1];
	for(int i = 0; i < position; i++){
		vector[i] = temp[i];
	}
	for(int i = position + 1; i < size; i++){
		vector[i - 1] = temp[i];
	}
	size--;
	delete[] temp;
}

template <class T>
void DSVector<T>::swap(DSVector<T>& alternate){
	T* temp_vector = this->vector;
	int temp_size = this->size;
	this->vector = alternate.vector;
	this->size = alternate.size;
	alternate.vector = temp_vector;
	alternate.size = temp_size;			
}

template <class T>
void DSVector<T>::clear(){
	delete[] vector;
	vector = new T[0];
	size = 0;
}

#endif