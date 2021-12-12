#include <vector>
#include <list>
#include <unordered_map>

class PRDS_MyOwn{
	
	public:
		/**
		 * @brief Construct a new PRDS_MyOwn object
		 * 
		 * @param pages number of pages available in main memory
		 */
		PRDS_MyOwn(int pages) {
			Km = pages * 3 / 4;
			Kin = pages - Km;
			Kout = pages / 2;
		}

		/**
		 * @brief Loads page into memory, swapping using the 2Q algorithm
		 * 
		 * @param page page to load
		 * @return int -1 if page exists in memory, -2 if fault but no swap, else the page to replace
		 */
		int push(int page) {
			// If page is found in Am queue, bring it to the front
			if (Am_iter.count(page)) {
				Am.erase(Am_iter[page]);
				Am.emplace_front(page);
				Am_iter[page] = Am.begin();
				return -1;
			}

			// If page reference is found in A1out queue, push it to Am queue
			if (A1out_iter.count(page)) {
				A1out.erase(A1out_iter[page]);
				A1out_iter.erase(page);
				Am.emplace_front(page);
				Am_iter[page] = Am.begin();
				// If Am queue was full, remove last page
				if (Am.size() > Km) {
					int replaced = Am.back();
					Am.pop_back();
					Am_iter.erase(replaced);
					return replaced;
				}
				// If Am queue was not full, return -2
				return -2;
			}

			// If page is found in A1in queue, do nothing
			if (A1in_iter.count(page)){
				return -1;
			}

			// Else page has no recorded encounter, push to A1in queue
			A1in.emplace_front(page);
			A1in_iter[page] = A1in.begin();
			// If A1in queue was full, move last page to A1out
			if (A1in.size() > Kin) {
				int replaced = A1in.back();
				A1in.pop_back();
				A1in_iter.erase(replaced);
				A1out.emplace_front(replaced);
				A1out_iter[replaced] = A1out.begin();
				// If A1out queue was full, remove last page of A1out
				if (A1out.size() > Kout) {
					A1out_iter.erase(A1out.back());
					A1out.pop_back();
				}
				return replaced;
			}
			return -2;
		}
	
	private:
		// Pages in memory are organized into a main LRU queue and secondary FIFO queue
		std::list<int> Am;
		std::list<int> A1in;

		// FIFO queue of references to recently removed pages
		std::list<int> A1out;

		// Maximum number of pages which can be stored in each buffer
		int Km;
		int Kin;
		int Kout;

		// Associates pages with a pointer to their location in the buffer
		std::unordered_map<int, std::list<int>::iterator> Am_iter;
		std::unordered_map<int, std::list<int>::iterator> A1in_iter;
		std::unordered_map<int, std::list<int>::iterator> A1out_iter;
};

/**
 * @brief Uses the least recently used replacement algorithm to select an index
 * 
 * @param pages vector storing the set of pages currently in main memory
 * @param nextpage next page to be accessed
 * @param p pointer to data structure used for page replacement
 * @return int -1 if no replacement is needed, else the index to replace
 */
int Page_Replacement_MyOwn(std::vector<int>& pages, int nextpage, PRDS_MyOwn* p) {
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