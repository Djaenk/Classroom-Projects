#include <iostream>
using namespace std;

int SelectionSort(int (&numbers)[], int numbersSize) {
	int operations = 0;
	int i;
	int j;
	int indexSmallest;
	int temp;      // Temporary variable for swap

	for (++operations,i = 0; ++operations,i < numbersSize - 1; ++operations,++i) {
		// Find index of smallest remaining element
		++operations,indexSmallest = i;
		for (++operations,j = i + 1; ++operations, j < numbersSize; ++operations,++j) {
			if ( ++operations,numbers[j] < numbers[indexSmallest] ) {
				++operations,indexSmallest = j;
			}
		}
		// Swap numbers[i] and numbers[indexSmallest]
		++operations,temp = numbers[i];
		++operations,numbers[i] = numbers[indexSmallest];
		++operations,numbers[indexSmallest] = temp;
	}
	return operations;
}

void Merge(int (&numbers)[], int i, int j, int k, int &operations) {
	int mergedSize;                            // Size of merged partition
	int mergePos;                              // Position to insert merged number
	int leftPos;                               // Position of elements in left partition
	int rightPos;                              // Position of elements in right partition
	int* mergedNumbers = nullptr;

	mergePos = 0;
	mergedSize = k - i + 1;
	leftPos = i;                               // Initialize left partition position
	rightPos = j + 1;                          // Initialize right partition position
	mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
                                               // for merged numbers
   
	// Add smallest element from left or right partition to merged numbers
	while (++operations,leftPos <= j && rightPos <= k) {
		if (++operations,numbers[leftPos] < numbers[rightPos]) {
			++operations,mergedNumbers[mergePos] = numbers[leftPos];
			++operations,++leftPos;
		}
		else {
			++operations,mergedNumbers[mergePos] = numbers[rightPos];
			++operations,++rightPos;
		}
		++mergePos;
	}
   
	// If left partition is not empty, add remaining elements to merged numbers
	while (++operations,leftPos <= j) {
		++operations,mergedNumbers[mergePos] = numbers[leftPos];
		++operations,++leftPos;
		++operations,++mergePos;
	}
   
	// If right partition is not empty, add remaining elements to merged numbers
	while (++operations,rightPos <= k) {
		++operations,mergedNumbers[mergePos] = numbers[rightPos];
		++operations,++rightPos;
		++operations,++mergePos;
	}
   
	// Copy merge number back to numbers
	for (++operations,mergePos = 0; ++operations,mergePos < mergedSize; ++operations,++mergePos) {
		++operations,numbers[i + mergePos] = mergedNumbers[mergePos];
	}
}

int MergeSort(int (&numbers)[], int i, int k, int &operations) {
	int j;
   
	if (++operations,i < k) {
		++operations,j = (i + k) / 2;  // Find the midpoint in the partition
		// Recursively sort left and right partitions
		MergeSort(numbers, i, j, operations);
		MergeSort(numbers, j + 1, k, operations);
		// Merge left and right partition in sorted order
		Merge(numbers, i, j, k, operations);
	}
	return operations;
}