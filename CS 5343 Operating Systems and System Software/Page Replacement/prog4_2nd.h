#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

class PRDS_2nd {
	public:
		/**
		 * @brief Construct a new PRDS_2nd object
		 * 
		 * @param pages number of pages available in main memory
		 */
		PRDS_2nd(int pages) {
			capacity = pages;
			references.reserve(pages);
		}

		/**
		 * @brief Chooses page to swap using modified second chance algorithm if necessary
		 * 
		 * @param page page to load
		 * @return int -1 if page exists in memory, -2 if fault but no swap, else the page to replace
		 */
		int push(int page) {
			// If the page is already queued, increment its reference count, up to three
			if (references.count(page)) {
				references[page] = std::min(++references[page], 3);
				return -1;
			}

			// If the page is not queued, and there is space available, enqueue it
			if (queue.size() < capacity) {
				queue.emplace_back(page);
				references[page] = 0;
				return -1;
			}

			// Other decrement reference counts until a victim with 0 reference is found
			while (references[queue.front()]) {
				--references[queue.front()];
				queue.emplace_back(queue.front());
				queue.pop_front();
			}

			// Page at front of queue is victim for page replacement; perform page swap
			int replaced = queue.front();
			references.erase(replaced);
			queue.pop_front();
			queue.emplace_back(page);
			references[page] = 0;
			return replaced;
		}
	
	private:
		// Maximum number of pages which can be stored in memory
		int capacity;

		// FIFO Queue of pages in memory
		std::list<int> queue;


		// Associative array counting the number of references to pages in memory
		std::unordered_map<int, int> references;
};

/**
 * @brief Uses a modified second chance replacmenet algorithm to select an index
 * 
 * @param pages vector storing the set of pages currently in main memory
 * @param nextpage next page to be accessed
 * @param p pointer to data structure used to calculate page replacement
 * @return int -1 if no replacement is needed, else the index to replace
 */
int Page_Replacement_2nd(std::vector<int>& pages, int nextpage, PRDS_2nd* p) {
	int replaced = p->push(nextpage);
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