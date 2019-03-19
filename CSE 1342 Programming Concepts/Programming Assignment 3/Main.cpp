#include <cstdlib>
#include <ctime>
#include <fstream>
#include "SortFunctions.h"

int main(){
	srand(time(NULL));
	
	for(int i = 0; i < 10000; i++){
		for(int n = 2; n <= 100; n++){
			int array_selectionsort[n];
			int array_mergesort[n];
			for(int k = 0; k < n; k++){
				int random = rand() % 1000;
				array_selectionsort[k] = random;
				array_mergesort[k] = random;
			}
			
		}
	}
}