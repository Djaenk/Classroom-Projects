#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>

#include "graph_generation.hpp"
#include "graph_coloring.hpp"

int main(int argc, char* argv[]) {
	if (argc >= 4) {
		Graph graph;
		int V = atoi(argv[1]);
		int E = atol(argv[2]);
		auto start = std::chrono::high_resolution_clock::now();
		if (strcmp(argv[3], "COMPLETE") == 0) {
			graph = create_complete_graph(V);
		}
		else if (strcmp(argv[3], "CYCLE") == 0) {
			graph = create_cycle_graph(V);
		}
		else if (strcmp(argv[3], "RANDOM") == 0) {
			if (strcmp(argv[4], "UNIFORM") == 0) {
				graph = create_uniform_random_graph(V, E);
			}
			else if (strcmp(argv[4], "SKEWED") == 0) {
				graph = create_skewed_random_graph(V, E);
			}
			else {
				graph = create_normal_random_graph(V, E);
			}
		}

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Runtime: " << duration.count() << " microseconds" << std::endl;

		std::ofstream output("graph.txt");
		output << graph_to_string(graph);
		output.close();

		std::ofstream conflicts("conflicts.csv");
		for (const auto& list : graph) {
			conflicts << list.size() << "\n";
		}
		conflicts.close();
	}
	else {
		std::string input;
		std::getline(std::ifstream(argv[1]), input, '\0');
		Graph graph = string_to_graph(input);
		auto start = std::chrono::high_resolution_clock::now();
		Ordering order;
		if (argv[2][0] == '1') {
			order = smallest_last_vertex_ordering(graph);
		}
		else if (argv[2][0] == '2') {
			order = smallest_original_degree_ordering(graph);
		}
		else if (argv[2][0] == '3') {
			order = uniform_random_ordering(graph);
		}
		else if (argv[2][0] == '4') {
			order = largest_original_degree_ordering(graph);
		}
		else if (argv[2][0] == '5') {
			order = breadth_first_search_ordering(graph);
		}
		else if (argv[2][0] == '6') {
			order = depth_first_search_ordering(graph);
		}

		Coloring coloring = greedy_coloring(graph, order);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		std::ofstream output("coloring.txt");
		output << coloring_to_string(coloring);
		output.close();

		std::ofstream removal;
		std::cout << std::setw(8) << "Vertex";
		std::cout << std::setw(8) << "Color";
		std::cout << std::setw(8) << "Degree";
		if (argv[2][0] == '1') {
			std::cout << " Degree when removed";
			removal.open("degree_at_removal.csv");
		}
		std::cout << std::endl;
		for (const auto& i : order) {
			std::cout << std::setw(8) << std::to_string(i);
			std::cout << std::setw(8) << coloring[i];
			std::cout << std::setw(8) << std::to_string(graph[i].size());
			if (argv[2][0] == '1') {
				std::cout << std::setw(8) << std::to_string(degree_at_removal[i]);
				removal << std::to_string(degree_at_removal[i]) << '\n';
			}
			std::cout << std::endl;
		}
		if (argv[2][0] == '1') {
			removal.close();
		}

		std::cout << "Number of colors used: " << *std::max_element(coloring.begin(), coloring.end()) + 1 << std::endl;
		std::cout << "Average original degree: ";
		double edges = 0;
		for (const auto& v : graph) edges += v.size();
		std::cout << edges / graph.size() << std::endl;
		if (argv[2][0] == '1') {
			std::cout << "Maximum degree when deleted: " << *std::max_element(degree_at_removal.begin(), degree_at_removal.end()) << std::endl;
			int terminal_clique_size = 0;
			auto iter = order.end();
			while (iter != order.begin()) {
				if (degree_at_removal[*--iter] != terminal_clique_size) {
					break;
				}
				++terminal_clique_size;
			}
			std::cout << "Terminal clique size: " << terminal_clique_size << std::endl;
		}
		std::cout << "Runtime: " << duration.count() << " microseconds" << std::endl;
	}
}