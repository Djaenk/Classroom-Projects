#include <iostream>
#include "tabletop.h"

using namespace std;

int main(){
	
	TableTop tableTop;
	
	bool someoneRanOutOfCards = false;
	int round = 1;
	while(!someoneRanOutOfCards){
		cout << "======== Round " << round++ << " ========" << endl;
		someoneRanOutOfCards = tableTop.DoBattle();
	}
	
	return 0;
}