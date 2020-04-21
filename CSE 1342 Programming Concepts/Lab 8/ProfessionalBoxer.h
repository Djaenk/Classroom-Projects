#ifndef PROFESSIONAL_BOXER
#define PROFESSIONAL_BOXER

#include "Boxer.h"

class Professional : public Boxer{
	public:
		Professional(std::string atheltic_commission, std::string name, int wins, int losses);
		std::string toString();
	private:
		std::string athletic_commission;
};

#endif