#ifndef IDENTIFIER
#define IDENTIFIER

#include <vector>
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include "Sorter.h"
#include "regression.h"

class SorterIdentifier{
    private:
        std::vector<long double> sorted[300];
        std::vector<long double> reverse[300];
        std::vector<long double> random[300];
        std::vector<long double> presorted_indices;
        std::vector<long double> presorted_runtimes;
        std::vector<long double> reversed_indices;
        std::vector<long double> reversed_runtimes;
        std::vector<long double> randomized_indices;
        std::vector<long double> randomized_runtimes;


        void fill(std::vector<long double>&, const int, const char);


    public:
        SorterIdentifier();
        void identify(Sorter<long double>&, char);
};

SorterIdentifier::SorterIdentifier(){
    for(int i = 0; i < 300; i++){
        presorted_indices.push_back( (i + 1) * 25);
        fill(sorted[i], 			 (i + 1) * 25, 's');
        reversed_indices.push_back(  (i + 1) * 25);
        fill(reverse[i], 			 (i + 1) * 25, 'r');
        randomized_indices.push_back((i + 1) * 25);
        fill(random[i], 			 (i + 1) * 25, '?');
    }
}

void SorterIdentifier::fill(std::vector<long double>& data, const int size, const char order){
    data.clear();
    data = std::vector<long double>(size, 0);
    switch(order){
        case 's':
            for(int i = 0; i < size; i++){
                data[i] = i + 1;
            }
            break;
        case 'r':
            for(int i = 0; i < size; i++){
                data[i] = size - i;
            }
            break;
        case '?':
            srand(69420);
            for(int i = 0; i < size; i++){
                data[i] = rand() % size + 1;
            }
            break;
    }
}

void SorterIdentifier::identify(Sorter<long double>& mystery, char letter){
    presorted_runtimes.clear();
    reversed_runtimes.clear();
    randomized_runtimes.clear();
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 300; i++){
        //measure runtime when sorting presorted data
        mystery.setData(sorted[i]);
        start = std::chrono::high_resolution_clock::now();
        mystery.sort();
        end = std::chrono::high_resolution_clock::now();
        presorted_runtimes.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

        //measure runtime when sorting data in reverse order
        mystery.setData(reverse[i]);
        start = std::chrono::high_resolution_clock::now();
        mystery.sort();
        end = std::chrono::high_resolution_clock::now();
        reversed_runtimes.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

        //measure runtime when sorting random data
        mystery.setData(random[i]);
        start = std::chrono::high_resolution_clock::now();
        mystery.sort();
        end = std::chrono::high_resolution_clock::now();
        randomized_runtimes.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
    }

    int sorted_case_order, reversed_case_order, randomized_case_order;
    sorted_case_order = fit_curve(presorted_indices, presorted_runtimes);
    reversed_case_order = fit_curve(reversed_indices, reversed_runtimes);
    randomized_case_order = fit_curve(randomized_indices, randomized_runtimes);
	// std::cout << sorted_case_order << std::endl << reversed_case_order << std::endl << randomized_case_order << std::endl;

    if((sorted_case_order == 1 || sorted_case_order == 2) && 
	   (reversed_case_order == 1 || reversed_case_order == 2) && 
	   (randomized_case_order == 1 || randomized_case_order == 2)){
        std::cout << "Mystery Sort " << letter << " is MergeSort." << std::endl;
    }
	else if(sorted_case_order == 3 &&
			reversed_case_order == 3 &&
			(randomized_case_order == 1 || randomized_case_order == 2)){
		std::cout << "Mystery Sort " << letter << " is QuickSort." << std::endl;
	}
	else if(sorted_case_order == 3 && reversed_case_order == 3 && randomized_case_order == 3){
		std::cout << "Mystery Sort " << letter << " is SelectionSort." << std::endl;
	}
	else if(sorted_case_order == 1 && reversed_case_order == 3 && randomized_case_order == 3){
		long double slope, intercept, error;
		std::vector<long double> quad_adjusted_runtimes;
		for(int i = 0; i < randomized_runtimes.size(); i++){
			quad_adjusted_runtimes.push_back(randomized_runtimes[i] / randomized_indices[i] * randomized_runtimes.size());
		}
		least_squares_regression(randomized_indices, quad_adjusted_runtimes, slope, intercept, error);
		if(slope > .5){
			std::cout << "Mystery Sort " << letter << " is BubbleSort." << std::endl;
		}
		else{
			std::cout << "Mystery Sort " << letter << " is InsertionSort." << std::endl;
		}
	}
}

#endif
