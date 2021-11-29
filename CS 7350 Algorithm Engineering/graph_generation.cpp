#include "graph_generation.hpp"
#include <iostream>

std::default_random_engine rng;

int
pair(int a_, int b_) {
	//Matthew Szudzik's pairing function (http://szudzik.com/ElegantPairing.pdf)
	return a_ >= b_ ? (a_ * a_ + a_ + b_) : (a_ + b_ * b_);
}

std::pair<int, int>
unpair(int c_) {
	//Matthew Szudzik's unpairing function (http://szudzik.com/ElegantPairing.pdf)
	int sqrtc = sqrt(c_);
	int sqc = sqrtc * sqrtc;
	return c_ - sqc >= sqrtc ?
		std::make_pair(sqrtc, c_ - sqc - sqrtc) :
		std::make_pair(c_ - sqc, sqrtc);
}

Graph
create_complete_graph(int vertices_) {
	Graph graph(vertices_);
	for (int i = 0; i < vertices_; ++i) {
		for (int j = 0; j < vertices_; ++j) {
			if (j != i) {
				graph[i].emplace_back(j);
			}
		}
	}
	return graph;
}

Graph
create_cycle_graph(int vertices_) {
	Graph graph(vertices_);
	for (int i = 0; i < vertices_; ++i) {
		graph[i].emplace_back(i - 1);
		graph[i].emplace_back(i + 1);
	}
	graph[0].pop_front();
	graph[0].emplace_front(vertices_ - 1);
	graph[vertices_ - 1].pop_back();
	graph[vertices_ - 1].emplace_back(0);
	return graph;
}

Graph
create_uniform_random_graph(int vertices_, int edges_) {
	Graph graph(vertices_);
	std::uniform_int_distribution<int> distribution(1, vertices_ * vertices_ - 2);
	std::unordered_set<int> created(4 * edges_);
	int edge;
	std::pair<int, int> v_pair;
	for (int i = 0; i < edges_; ++i) {
		edge = distribution(rng);
		v_pair = unpair(edge);
		if (v_pair.first != v_pair.second && created.find(edge) == created.end()) {
			graph[v_pair.first].emplace_back(v_pair.second);
			graph[v_pair.second].emplace_back(v_pair.first);
		}
		else {
			--i;
		}
		created.emplace(edge);
		created.emplace(pair(v_pair.second, v_pair.first));
	}
	return graph;
}

Graph
create_skewed_random_graph(int vertices_, int edges_) {
	Graph graph(vertices_);
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	std::unordered_set<int> created(4 * edges_);
	double edge;
	std::pair<int, int> v_pair;
	for (int i = 0; i < edges_; ++i) {
		edge = distribution(rng);
		edge = pow(edge, 1.25);
		edge *= vertices_ * vertices_;
		v_pair = unpair(edge);
		if (v_pair.first != v_pair.second && created.find(edge) == created.end()) {
			graph[v_pair.first].emplace_back(v_pair.second);
			graph[v_pair.second].emplace_back(v_pair.first);
		}
		else {
			--i;
		}
		created.emplace(edge);
		created.emplace(pair(v_pair.second, v_pair.first));
	}
	return graph;
}

Graph
create_normal_random_graph(int vertices_, int edges_) {
	Graph graph(vertices_);
	std::lognormal_distribution<double> distribution(0.0, 1.0);
	std::unordered_set<int> created(4 * edges_);
	int edge;
	std::pair<int, int> v_pair;
	for (int i = 0; i < edges_; ++i) {
		edge = distribution(rng) * vertices_ * vertices_;
		v_pair = unpair(edge);
		if (edge > 0 && edge < vertices_ * vertices_ - 1 && v_pair.first != v_pair.second && created.find(edge) == created.end()) {
			graph[v_pair.first].emplace_back(v_pair.second);
			graph[v_pair.second].emplace_back(v_pair.first);
		}
		else {
			--i;
		}
		created.emplace(edge);
		created.emplace(pair(v_pair.second, v_pair.first));
	}
	return graph;
}

std::string
graph_to_string(Graph graph_) {
	int line = graph_.size();
	std::string s = std::to_string(line++) + '\n';
	for (auto const& vertex : graph_) {
		s += std::to_string(line) + '\n';
		line += vertex.size();
	}
	for (const auto& vertex : graph_) {
		for (const int& edge : vertex) {
			s += std::to_string(edge) + '\n';
		}
	}
	return s;
}

Graph
string_to_graph(std::string string_) {
	int vertex, size;
	std::stringstream stream(string_);
	stream >> size;
	Graph graph(size);
	std::vector<int> pointers(size);
	for (auto& pointer : pointers) {
		stream >> pointer;
	}
	for (int i = size + 1, j = 0; stream >> vertex; ++i) {
		if (i == pointers[j + 1]) {
			++j;
		}
		graph[j].emplace_back(vertex);
	}
	return graph;
}