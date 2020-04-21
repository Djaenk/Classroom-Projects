#include "disjoint_set.hpp"
#include "weighted_graph.hpp"
#include "mst_algorithm.hpp"
//#include "timer.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

std::string readFileToString(std::string filename){
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open()){
		throw std::runtime_error("Cannot open file");
	}
	std::ifstream::pos_type fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<char> bytes(fileSize);
	file.read(bytes.data(), fileSize);
	return std::string(bytes.data(), fileSize);
}

template <typename vertex>
std::vector<std::tuple<double, vertex, vertex>>
benchmarkKruskals(const WeightedGraph<vertex>& graph){
	using namespace std::chrono;

	auto start = high_resolution_clock::now();
	auto MST = MSTKruskal(graph, false);
	auto stop = high_resolution_clock::now();
	auto runtime = duration_cast<microseconds>(stop - start);
	std::cout << "trivial runtime: " << runtime.count() << " microseconds" << std::endl;

	start = high_resolution_clock::now();
	MST = MSTKruskal(graph, true);
	stop = high_resolution_clock::now();
	runtime = duration_cast<microseconds>(stop - start);
	std::cout << "optimized runtime: " << runtime.count() << " microseconds" << std::endl;
	return MST;
}

template <typename vertex>
void
writeMSTToFile(std::string graphname, const std::vector<std::tuple<double, vertex, vertex>>& edges){
	double totalWeight = 0.0;
	for (const auto& edge : edges){
		totalWeight += std::get<0>(edge);
	}
	std::ofstream output(graphname + "_MST.txt");
	output << "Minimum Spanning Tree of " << graphname << " has a total weight of " << totalWeight << "." << std::endl;
	output << "Edges are listed in order of weight:" << std::endl;
	output << "[undirected]" << std::endl;
	for (const auto& edge : edges){
		output << std::get<0>(edge) << " - " << std::get<1>(edge) << " - " << std::get<2>(edge) << std::endl;
	}
}

int main(){
	for (uint i = 0; i < 15; i++){
		WeightedGraph<std::string> graph;
		std::string graphname = "graph" + std::to_string(i);
		std::string graphTextFormat = readFileToString(graphname + ".txt");
		graph.readtextFormat(graphTextFormat);
		std::cout << graphname << std::endl;
		writeMSTToFile(graphname, benchmarkKruskals(graph));
		std::cout << std::endl;
	}
}