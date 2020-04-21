#ifndef MST_ALGORITHM
#define MST_ALGORITHM

#include "weighted_graph.hpp"
#include "disjoint_set.hpp"
#include <vector>
#include <tuple>
#include <map>
#include <iostream>
#include <memory>

template <typename vertex>
std::vector<std::tuple<double, vertex, vertex>>
MSTKruskal(const WeightedGraph<vertex>& graph, bool optimized = true){
	std::vector<std::tuple<double, vertex, vertex>> MST;
	std::unique_ptr<DisjointSet<vertex>> vertexSet;
	std::multimap<double, std::pair<vertex, vertex>> edgePriorityQueue;

	//initialize selected implementation of disjoint set interface
	if (optimized){
		vertexSet = std::make_unique<DisjointSetOptimized<vertex>>();
	}
	else{
		vertexSet = std::make_unique<DisjointSetTrivial<vertex>>();
	}

	//create a subset for every vertex in the graph
	for (const auto& target : graph.vertices){
		vertexSet->makeSet(target.first);
	}

	//create priority queue of edges in order of increasing weight
	for (const auto& edge_weight : graph.weights){
		edgePriorityQueue.emplace(edge_weight.second, edge_weight.first);
	}

	//
	for (const auto& weight_edge : edgePriorityQueue){
		const double& weight = weight_edge.first;
		const std::pair<vertex, vertex>& edge = weight_edge.second;
		if (vertexSet->findSet(edge.first) != vertexSet->findSet(edge.second)){
			MST.emplace_back(std::make_tuple(weight, edge.first, edge.second));
			vertexSet->setUnion(edge.first, edge.second);
		}
	}
	return MST;
}

#endif