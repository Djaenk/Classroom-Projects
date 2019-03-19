#include <cstdlib>
#include <ctime>
#include <fstream>
#include "SortFunctions.h"

int main(){
	srand(time(NULL));
	std::ofstream operations;
	operations.open("operations.csv");
	operations << "array size,selection sort operations,merge sort operations" << std::endl;
	for(int n = 2; n <= 100; n++){
		for(int i = 0; i < 10000; i++){
			int array_selectionsort[n];
			int array_mergesort[n];
			for(int j = 0; j < n; j++){
				int random = rand() % 1000;
				array_selectionsort[j] = random;
				array_mergesort[j] = random;
			}
			int operations_selectionsort = SelectionSort(array_selectionsort, n);
			int operations_mergesort = MergeSort(array_mergesort, 0, n);
			operations << n << "," << operations_selectionsort << "," << operations_mergesort << std::endl;
		}
	}
	operations.close();
}