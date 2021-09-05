#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>

std::default_random_engine generator;

void func1(int n, int array[]) {
	for (int i = 0; i < n; i++) {
		std::cout << "Hello, World\n";
	}
	std::cout << std::endl;
}

void func2(int n, int array[]) {
	std::uniform_int_distribution<int> uniform(1, n);
	array[0] = uniform(generator);
	for (int i = 1; i < n; i++) {
		int number = uniform(generator);
		int j = 0;
		while (j < i && array[j] < number) {
			j++;
		}
		for (int k = i; k > j; k--) {
			array[k] = array[k - 1];
		}
		array[j] = number;
	}
}

void func3(int n, int array[]) {
	std::uniform_int_distribution<int> uniform(1,3);
	int count[3] = {0, 0, 0};
	for (int i = 0; i < n; i++) {
		int number = uniform(generator);
		array[i] = number;
		count[number]++;
	}
}

void func4(int n, int array[]) {
	int left = 0;
	int right = n - 1;
	for (int i = 0; i < n && left != right; i++) {
		if (array[i] == 1) {
			array[i] = array[left];
			array[left] = 1;
			left++;
		}
		else if (array[i] == 3) {
			array[i] = array[right];
			array[right] = 3;
			right--;
		}
	}
}

int main(int argc, char* argv[]) {
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point stop;
	int func = atoi(argv[1]);
	int n = atoi(argv[2]);

	int array[n] = {0};
	switch (func) {
		case 1:
			start = std::chrono::high_resolution_clock::now();
			func1(n, array);
			stop = std::chrono::high_resolution_clock::now();
			break;
		case 2:
			start = std::chrono::high_resolution_clock::now();
			func2(n, array);
			stop = std::chrono::high_resolution_clock::now();	
			break;
		case 3:
			start = std::chrono::high_resolution_clock::now();
			func3(n, array);
			stop = std::chrono::high_resolution_clock::now();	
			break;
		case 4:
			func3(n, array);
			start = std::chrono::high_resolution_clock::now();
			func4(n, array);
			stop = std::chrono::high_resolution_clock::now();	
			break;
	}
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	std::cout << duration.count() << " nanoseconds" << std::endl;
}