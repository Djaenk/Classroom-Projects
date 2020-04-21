#ifndef BOXER
#define BOXER

#include <string>

class Boxer{
	public:
		Boxer(std::string name, int wins, int losses);
		virtual std::string toString();
	protected:
		std::string name;
		int wins;
		int losses;
};

#endif