#include <vector>
#include <array>
#include <stdlib.h>
#include <time.h>

class PRDS_MyOwn {
	public:
		/**
		 * @brief Construct a new PRDS_MyOwn object and seed shuffle table
		 * 
		 * @param pages number of pages available in main memory
		 */
		PRDS_MyOwn(int pages) {
			srand(time(NULL));
			shuffle_table[0] = rand();
			shuffle_table[1] = rand();
			shuffle_table[2] = rand();
			shuffle_table[3] = rand();
		}

		// Shuffle table for generating random numbers
		std::array<uint64_t, 4> shuffle_table;
};

/**
 * @brief Selects a page to replace using xoshiro256+ pseudorandom number generator
 * 
 * @param pages vector storing the set of pages currently in main memory
 * @param nextpage next page to be accessed
 * @param p pointer to data structure used to calculate page replacement
 * @return int index of page to replace
 */
int Page_Replacement_MyOwn(std::vector<int>& pages, int nextpage, PRDS_MyOwn* p) {
	// Try to find nextpage or an empty page
	for (int i = 0; i < pages.size(); ++i) {
		if (pages[i] == nextpage) return -1;
		if (pages[i] == -1) return i;
	}

	// Else randomly select page
	const uint64_t result = p->shuffle_table[0] + p->shuffle_table[3];

	const uint64_t t = p->shuffle_table[2] << 17;

	p->shuffle_table[2] ^= p->shuffle_table[0];
	p->shuffle_table[3] ^= p->shuffle_table[1];
	p->shuffle_table[1] ^= p->shuffle_table[2];
	p->shuffle_table[0] ^= p->shuffle_table[3];

	p->shuffle_table[2] ^= t;
	
	p->shuffle_table[3] = (p->shuffle_table[3] << 45) | (p->shuffle_table[3] >> 19);

	return result % pages.size();
}