#include <chrono>
#include <iostream>
#include "Sorter.h"
#include "identifier.h"

int main(){
	SorterIdentifier id;
	MysterySorterA<long double> A;
	MysterySorterB<long double> B;
	MysterySorterC<long double> C;
	MysterySorterD<long double> D;
	MysterySorterE<long double> E;
	id.identify(A, 'A');
	id.identify(B, 'B');
	id.identify(C, 'C');
	id.identify(D, 'D');
	id.identify(E, 'E');
}
