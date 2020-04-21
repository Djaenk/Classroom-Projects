#include <fstream>
#include "planner.h"
#include "tests.hpp"
#include <iostream>

int main(int argc, char* argv[]){
	if(argc == 1){
		int result = Catch::Session().run();
	}
	FlightPlanner planner;
	std::ifstream flight_data(argv[1]);
	std::ifstream flight_requests(argv[2]);
	std::ofstream flight_plans(argv[3]);
	planner.flight_data(flight_data);
	planner.flight_requests(flight_requests, flight_plans);
}