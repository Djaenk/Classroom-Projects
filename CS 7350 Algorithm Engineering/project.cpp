#include <iostream>

#include "graph_generation.hpp"
#include "graph_coloring.hpp"

int main() {
	Graph graph = create_uniform_random_graph(6, 8);
	std::cout << graph_to_string(graph) << std::endl;
	Ordering order = depth_first_search_ordering(graph);
	for (auto& vertex : order) {
		std::cout << vertex << std::endl;
	}
	std::cout << std::endl;
	Coloring coloring = greedy_coloring(graph, order);
	for (auto& color : coloring) {
		std::cout << color << std::endl;
	}
}