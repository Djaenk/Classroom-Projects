#ifndef TIMER
#define TIMER

#include <utility>
#include <type_traits>
#include <chrono>
#include <string>

template <typename Func, typename ... Args>
std::pair<unsigned int, std::result_of<Func(Args...)>> 
timeFunction(std::string unit, Func function, Args ... args){
	using namespace std::chrono;

	auto start = high_resolution_clock::now();
	auto result = function(args...);
	auto stop = high_resolution_clock::now();

	if (unit == "ns"){
		auto ns = duration_cast<nanoseconds>(stop - start);
		return std::make_pair(ns.count(), result);
	}
	else if (unit == "us"){
		auto us = duration_cast<microseconds>(stop - start);
		return std::make_pair(us.count(), result);
	}
	else if (unit == "ms"){
		auto ms = duration_cast<milliseconds>(stop - start);
		return std::make_pair(ms.count(), result);
	}
	else if (unit == "s"){
		auto s = duration_cast<seconds>(stop - start);
		return std::make_pair(s.count(), result);
	}
	else{
		auto duration = stop - start;
		return std::make_pair(duration.count(), result);
	}
}

#endif