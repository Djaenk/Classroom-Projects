#include <vector>
#include <list>
#include <unordered_map>

class PRDS_LRU{
	
	public:
		/**
		 * @brief Construct a new PRDS_LRU object
		 * 
		 * @param pages number of pages available in main memory
		 */
		PRDS_LRU(int pages) {
			capacity = pages;
			page_map.reserve(pages);
		}

		/**
		 * @brief Loads page into memory, swapping using LRU algorithm if necessary
		 * 
		 * @param page page to load
		 * @return int -1 if page exists in memory, -2 if fault but no swap, else the page to replace
		 */
		int push(int page) {
			// If page is found in page list, refresh it to be most recently used
			if (page_map.count(page)) {
				page_list.erase(page_map[page]);
				page_list.emplace_front(page);
				page_map[page] = page_list.begin();
				return -1;
			}

			// Else if page list has space for another page, add it
			if (page_list.size() < capacity) {
				page_list.emplace_front(page);
				page_map[page] = page_list.begin();
				return -2;
			}

			// If conditions fail, page fault has occurred and swap is necessary
			int replaced = page_list.back();
			page_map.erase(replaced);
			page_list.pop_back();
			page_list.emplace_front(page);
			page_map[page] = page_list.begin();
			return replaced;
		}
	
	private:
		// Maximum number of pages which can be stored in memory
		int capacity;

		// Linked list of pages in memory, in order of most to least recently used
		std::list<int> page_list;

		// Associates pages with a pointer to a location in page_list
		std::unordered_map<int, std::list<int>::iterator> page_map;
};

/**
 * @brief Uses the least recently used replacement algorithm to select an index
 * 
 * @param pages vector storing the set of pages currently in main memory
 * @param nextpage next page to be accessed
 * @param p pointer to data structure used for page replacement
 * @return int -1 if no replacement is needed, else the index to replace
 */
int Page_Replacement_LRU(std::vector<int>& pages, int nextpage, PRDS_LRU* p) {
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