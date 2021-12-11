#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <cstdlib>
#include <iostream>

#define srand(x) PRDS_seed = x, srand(x)

unsigned int PRDS_seed = 0;

class PRDS_MyOwn {
	public:
		/**
		 * @brief Construct a new PRDS_MyOwn object and predict future page accesses
		 * 
		 * @param pages number of pages available in main memory
		 */
		PRDS_MyOwn(int pages) {
			capacity = pages;
		}

		/**
		 * @brief Predicts one million random page accesses
		 * 
		 */
		void generate() {
			if (generated) {
				return;
			}

			srand(PRDS_seed);
			for (int i = 0; i < 1000000; ++i) {
				accesses[rand() % 10].emplace_back(i);
			}
			srand(PRDS_seed);
			rand();

			generated = true;
		}

		/**
		 * @brief Determine which page to swap out of main memory to accomodate next page
		 * 
		 * @param page next page to load
		 * @return int -1 if page exists in memory, -2 if fault but no swap, else the page to replace
		 */
		int load(int page) {
			accesses[page].pop_front();

			// If page is found in page set, return -1
			if (pages.count(page)) {
				return -1;
			}

			// If page set is not at capacity, add page to set and return -2
			if (pages.size() < capacity) {
				pages.emplace(page);
				return -2;
			}

			// In the event all predictions have been used, randomly replace page
			if (exhausted) {
				auto iter = pages.begin();
				for (int i = 0; i < rand() % capacity; ++i) {
					++iter;
				}
				return *iter;
			}

			// Page fault has occurred, consult predictions to determine which
			// page will not be used for the longest time
			int farthest = *pages.begin();
			for (const int& p : pages) {
				if (accesses[p].empty()) {
					exhausted = true;
					break;
				}
				if (accesses[p].front() > accesses[farthest].front()) {
					farthest = p;
				}
			}
			pages.erase(farthest);
			pages.emplace(page);
			return farthest;
		}

	private:
		// Maximum number of pages which can be stored in memory
		int capacity;

		// Flag to record whether predictions have been generated
		bool generated = false;

		// Flag to record whether predictions have been exhausted
		bool exhausted = false;

		// Pages currently in memory
		std::unordered_set<int> pages;

		// Times at which a page will be accessed
		std::unordered_map<int, std::list<int>> accesses;
};

/**
 * @brief Selects a page to replace using optimal page replacement algorithm
 * 
 * @param pages vector storing the set of pages currently in main memory
 * @param nextpage next page to be accessed
 * @param p pointer to data structure used to calculate page replacement
 * @return int index of page to replace
 */
int Page_Replacement_MyOwn(std::vector<int>& pages, int nextpage, PRDS_MyOwn* p) {
	p->generate();
	int replaced = p->load(nextpage);
	if (replaced == -1) {
		// Try to find the existing page
		for (int i = 0; i < pages.size(); ++i) {
			if (pages[i] == nextpage) return -1;
		}
	}
	if (replaced == -2) {
		// Find next empty space in memory
		for (int i = 0; i < pages.size(); ++i) {
			if (pages[i] == -1) return i;
		}
	}
	for (int i = 0; i < pages.size(); ++i) {
		if (pages[i] == replaced) return i;
	}
	return pages.size();
}