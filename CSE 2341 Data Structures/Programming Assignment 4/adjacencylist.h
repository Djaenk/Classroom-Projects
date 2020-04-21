#ifndef ADJACENCYLIST
#define ADJACENCYLIST

#include "linkedlist.h"
#include "DSString.hpp"

struct Flight;
struct City;

class AdjacencyList{
	private:
		LinkedList<City> cities;
		City* add_city(const DSString);

	public:
		City* operator[](const int);
		City* operator[](const DSString);
		int size();
		void add_flight(const DSString, const DSString, const double, const int, const DSString);
};

struct Flight{
	City* origin = nullptr;
	City* destination = nullptr;
	double cost = 0.0;
	int time = 0;
	DSString airline = "";

	Flight() = default;
	Flight(City* const origin, City* const destination, const double cost, const int time, const DSString airline){
		this->origin = origin;
		this->destination = destination;
		this->cost = cost;
		this->time = time;
		this->airline = airline;
	}
	bool operator==(const Flight& comparand){
		return (origin == comparand.origin
			&& destination == comparand.destination
			&& cost == comparand.cost
			&& time == comparand.time
			&& airline == comparand.airline);
	}
	bool null(){ //designate the following data members to be that of a pseudo-null flight
		return (origin == nullptr
			&& destination == nullptr
			&& cost == 0
			&& time == 0
			&& airline == "");
	}
};

struct City{ //The adjacency list contains a series of cities, each of which contains a series of flights
	DSString name;
	LinkedList<Flight> flights;

	City() = default;
	City(const DSString name){
		this->name = name;
	}
	bool operator==(const City& comparand){return name == comparand.name;}
	void iterate(Flight& fliterator){
		for(int i = 0; i < flights.size() - 1; i++){
			if(flights[i] == fliterator){
				fliterator = flights[i + 1];
				return;
			}		
		}
		fliterator = Flight();
	};
};



City* AdjacencyList::add_city(const DSString name){
	cities.append(City(name));
	return &cities.last();
}

City* AdjacencyList::operator[](const int index){
	return &cities[index];
}

City* AdjacencyList::operator[](const DSString name){
	for(int i = 0; i < cities.size(); i++){
		if(cities[i].name == name) return &cities[i];
	}
	return nullptr;
}

int AdjacencyList::size(){
	return cities.size();
}

void AdjacencyList::add_flight(const DSString origin, const DSString destination, const double cost, const int time, const DSString airline){
	//adds a flight to the flight lists of the appropriate cities
	City *vertex1 = nullptr;
	City *vertex2 = nullptr;	
	for(int i = 0; i < cities.size(); i++){
		if(cities[i].name == origin) 		vertex1 = &cities[i];
		if(cities[i].name == destination)	vertex2 = &cities[i];
	}
	//if the appropriate cities, don't yet exist, create them
	if(vertex1 == nullptr) vertex1 = add_city(origin);
	if(vertex2 == nullptr) vertex2 = add_city(destination);

	vertex1->flights.append(Flight(vertex1, vertex2, cost, time, airline));
	if(origin != destination){
		vertex2->flights.append(Flight(vertex2, vertex1, cost, time, airline));
	}
}

#endif