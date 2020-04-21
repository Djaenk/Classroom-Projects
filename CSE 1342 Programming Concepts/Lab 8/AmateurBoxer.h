#ifndef	AMATEUR_BOXER
#define AMATEUR_BOXER

#include "Boxer.h"

class Amateur : public Boxer{
	public:
		Amateur(std::string golden_gloves, std::string name, int wins, int losses);
		std::string toString();
	private:
		std::string golden_gloves;
};

#endif