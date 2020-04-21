#ifndef PLANNER
#define PLANNER

#include "adjacencylist.h"
#include "stack.h"
#include <fstream>
#include <iostream>

class FlightPlanner{
	private:
		AdjacencyList airports;
		LinkedList<Stack<Flight>> backtrack(const DSString, const DSString);
		LinkedList<Stack<Flight>> filter(LinkedList<Stack<Flight>>, DSString);

	public:
		void flight_data(std::istream&);
		void flight_requests(std::istream&, std::ostream&);
};

LinkedList<Stack<Flight>> FlightPlanner::backtrack(const DSString origin, const DSString destination){
	LinkedList<Stack<Flight>> flight_plans;
	Stack<Flight> plan;
	Stack<City*> path;
	path.push(airports[origin]);
	Flight iter = airports[origin]->flights.first();
	while(!plan.empty() || !iter.null()){
		if(iter.null()){ //if the iterator has reached the end of a city's possible connections, pop the stack and continue iterating from the previous level
			path.pop();
			iter = plan.pop();
			if(path.empty()) break; //if the algo has iterated through the last connection of the origin city, break out of the loop
			path.top()->iterate(iter);
		}
		else if(path.top()->name == destination){ //if the iterator reached the destination, store the current stack and end iteration at the current level
			path.pop();
			if(path.empty() || plan.empty()) break; //if the source and destination cities are the same, immediately break out and don't produce any paths
			flight_plans.append(plan);
			iter = plan.pop();
			path.top()->iterate(iter);
		}
		else if(path.contains(iter.destination)){ //if the iterator is at a city which is already in the path, iterate to the next connection
			path.top()->iterate(iter);
		}
		else{
			path.push(iter.destination); //otherwise, push the city onto the path and begin interation on that city
			plan.push(iter);
			iter = iter.destination->flights.first();
		}
	}
	return flight_plans;
}

LinkedList<Stack<Flight>> FlightPlanner::filter(LinkedList<Stack<Flight>> possible_plans, DSString priority){
	LinkedList<Stack<Flight>> best_plans;

	if(priority[0] == 'T'){
		int lowest_times [3] = {0};
		for(int i = 0; i < possible_plans.size(); i++){
			int plan_time = -43; //negates the layover time penalty of the first flight
			Stack<Flight> reversed_flights;
			while(!possible_plans[i].empty()){
				if(!reversed_flights.empty() && !possible_plans[i].empty()){ //if there are still elements in both flight stacks..
					if(reversed_flights.top().airline != possible_plans[i].top().airline){ //compare the airlines of the flights on top of each stack..
						plan_time += 22; //and incur the time penalty if the airlines are different for the layover
					}
				}
				reversed_flights.push(possible_plans[i].pop());
				plan_time += reversed_flights.top().time;
				plan_time += 43;
			}

			if(i < 3){ //first three possible flight plans are accepted as the best
				best_plans.append(reversed_flights);
				lowest_times[i] = plan_time;
			}
			if(i >= 3){ //additional flight plans replace the initial three if they are found to have a lower time penalty
				for(int j = 0; j < 3; j++){
					if(plan_time < lowest_times[j]){
						best_plans[j] = reversed_flights;
						lowest_times[j] = plan_time;
						break;
					}
				}
			}
		}
	}

	if(priority[0] == 'C'){
		double lowest_costs [3] = {0.0};
		for(int i = 0; i < possible_plans.size(); i++){
			double plan_cost = -19.0; //negates the layover cost penalty of the first flight
			Stack<Flight> reversed_flights;
			while(!possible_plans[i].empty()){
				reversed_flights.push(possible_plans[i].pop());
				plan_cost += reversed_flights.top().cost;
				plan_cost += 19;
			}
			
			if(i < 3){ //first three possible flight plans are accepted as the best
				best_plans.append(reversed_flights);
				lowest_costs[i] = plan_cost;
			}
			if(i >=3 ){ //additional flight plans replace the initial three if they are found to have a lower cost penalty
				for(int j = 0; j < 3; j++){
					if(plan_cost < lowest_costs[j]){
						best_plans[j] = reversed_flights;
						lowest_costs[j] = plan_cost;
					}
				}
			}
		}
	}

	return best_plans;
}

void FlightPlanner::flight_data(std::istream& data){
	int rows;
	DSString origin;
	DSString destination;
	double cost;
	int time;
	DSString airline;
	data >> rows;
	data.ignore(1, '\n');
	for(int i = 0; i < rows; i++){
		getline(data, origin, '|');
		getline(data, destination, '|');
		data >> cost;
		data.ignore(10, '|');
		data >> time;
		data.ignore(10, '|');
		getline(data, airline);
		airports.add_flight(origin, destination, cost, time, airline);
	}
}

void FlightPlanner::flight_requests(std::istream& requests, std::ostream& output){
	int rows;
	DSString origin;
	DSString destination;
	DSString priority;
	requests >> rows;
	requests.ignore(1, '\n');
	for(int i = 0; i < rows; i++){
		getline(requests, origin, '|');
		getline(requests, destination, '|');
		getline(requests, priority);
		LinkedList<Stack<Flight>> possible_plans = backtrack(origin, destination);
		LinkedList<Stack<Flight>> best_plans_reversed = filter(possible_plans, priority);

		output << DSString("Flight ") << i + 1 << DSString(": ") << origin << DSString(", ") << destination;
		if(priority[0] == 'T') output << DSString(" (Time)") << std::endl;
		if(priority[0] == 'C') output << DSString(" (Cost)") << std::endl;
		for(int j = 0; j < best_plans_reversed.size(); j++){
			int plan_time = -43;
			double plan_cost = -19.0;
			Flight flight;
			output << DSString("Path ") << j + 1 << DSString(": ") << origin;
			while(true){
				flight = best_plans_reversed[j].pop();
				plan_time += flight.time;
				plan_time += 43;
				plan_cost += flight.cost;
				plan_cost += 19.0;
				output << DSString(" -> ") << flight.destination->name;
				if(!best_plans_reversed[j].empty()){
					if(flight.airline != best_plans_reversed[j].top().airline){
						plan_time += 22;
					}
				}
				else{
					break;
				}
			}
			output << DSString(". Time: ") << plan_time;
			output.precision(2);
			output << std::fixed << DSString(" Cost: ") << plan_cost << std::endl;
		}
		if(best_plans_reversed.size() == 0){
			output << DSString("No flight paths exist.") << std::endl;
		}
		output << std::endl;
	}
}

#endif