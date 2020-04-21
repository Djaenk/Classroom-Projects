#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#ifndef SORTINGFUN_SORTER_H
#define SORTINGFUN_SORTER_H

template <typename T>
class Sorter {
protected:
    std::vector<T> data;

public:
    Sorter() {}
    Sorter(T& x):data(x) {}
    void setData(const std::vector<T>& x) {
        data = x;
    }
    virtual void sort() = 0;

};


template <typename T>
class MysterySorterA : public Sorter<T> {
public:
    virtual void sort() {
        bool swapp = true;
        while(swapp){
            swapp = false;
            for (size_t i = 0; i < this->data.size()-1; i++) {
                if (this->data[i] > this->data[i+1] ){
                    this->data[i] += this->data[i+1];
                    this->data[i+1] = this->data[i] - this->data[i+1];
                    this->data[i] -= this->data[i+1];
                    swapp = true;
                }
            }
        }
    }
};

template <typename T>
class MysterySorterB : public Sorter<T> {
public:
    virtual void sort() {
        int i, j, tmp;

        for (i=1; i< this->data.size(); i++)
        {
            j=i;
            tmp=this->data[i];
            while (j>0 && tmp<this->data[j-1])
            {
                this->data[j]=this->data[j-1];
                j--;
            }
            this->data[j]=tmp;
        }
    }
};

template <typename T>
class MysterySorterC : public Sorter<T> {
public:
    virtual void sort() {
        int i, j, first_element, size = this->data.size();
        for ( i = size - 1; i > 0; i-- ){
            first_element = 0;
            for ( j = 1; j <= i; j++ ){
                if ( this->data[j] < this->data[first_element] )
                first_element = j;             //Obtains smallest element
            }//end for
            std::swap(this->data[first_element], this->data[i]);    //Swaps smallest element with data[i]
        }
    }
};

template <typename T>
class MysterySorterD : public Sorter<T> {
public:
    virtual void sort() {
        quickSort(this->data, 0, this->data.size());
    }

	void quickSort(std::vector<T>& A, int p,int q)
	{
		int r;
		if(p<q)
		{
			r=partition(A, p,q);
			quickSort(A,p,r);  
			quickSort(A,r+1,q);
		}
	}
	
	int partition(std::vector<T>& A, int p,int q)
	{
		int x= A[p];
		int i=p;
		int j;
	
		for(j=p+1; j<q; j++)
		{
			if(A[j]<=x)
			{
				i=i+1;
				std::swap(A[i],A[j]);
			}
	
		}
	
		std::swap(A[i],A[p]);
		return i;
	}
};

template <typename T>
class MysterySorterE : public Sorter<T> {
public:
    virtual void sort() {
        mergeSort(this->data, 0, this->data.size() - 1);
    }
	void merge(std::vector<T> &arr, int start, int middle, int end) {

		std::vector<T> leftArray(middle - start + 1);
		std::vector<T> rightArray(end - middle);

		// fill in left array
		for (int i = 0; i < leftArray.size(); ++i)
			leftArray[i] = arr[start + i];

		// fill in right array
		for (int i = 0; i < rightArray.size(); ++i)
			rightArray[i] = arr[middle + 1 + i];

		/* Merge the temp arrays */

		// initial indexes of first and second subarrays
		int leftIndex = 0, rightIndex = 0;

		// the index we will start at when adding the subarrays back into the main array
		int currentIndex = start;

		// compare each index of the subarrays adding the lowest value to the currentIndex
		while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) {
			if (leftArray[leftIndex] <= rightArray[rightIndex]) {
				arr[currentIndex] = leftArray[leftIndex];
				leftIndex++;
			} else {
				arr[currentIndex] = rightArray[rightIndex];
				rightIndex++;
			}
			currentIndex++;
		}

		// copy remaining elements of leftArray[] if any
		while (leftIndex < leftArray.size()) arr[currentIndex++] = leftArray[leftIndex++];

		// copy remaining elements of rightArray[] if any
		while (rightIndex < rightArray.size()) arr[currentIndex++] = rightArray[rightIndex++];
	}

	// main function that sorts array[start..end] using merge()
	void mergeSort(std::vector<T> &arr, int start, int end) {
		// base case
		if (start < end) {
			// find the middle point
			int middle = (start + end) / 2;

			mergeSort(arr, start, middle); // sort first half
			mergeSort(arr, middle + 1, end);  // sort second half

			// merge the sorted halves
			merge(arr, start, middle, end);
		}
	}
};

#endif //SORTINGFUN_SORTER_H
