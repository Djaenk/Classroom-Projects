#include "graph_coloring.hpp"

std::vector<int> degree_at_removal;

Coloring
greedy_coloring(const Graph& graph_, const Ordering& order) {
	Coloring coloring(graph_.size(), -1);
	bool valid;
	for (const int& v : order) {
		for (int color = 0;; ++color) {
			valid = true;
			for (const int& neighbor : graph_[v]) {
				if (coloring[neighbor] == color) {
					valid = false;
					break;
				}
			}
			if (valid) {
				coloring[v] = color;
				break;
			}
		}
	}
	return coloring;
}

Ordering
smallest_last_vertex_ordering(const Graph& graph_) {
	degree_at_removal.assign(graph_.size(), 0);
	std::vector<int> degree(graph_.size());
	std::vector<std::list<int>> degrees(graph_.size());
	std::vector<std::list<int>::iterator> pointers(graph_.size());
	for (int i = 0; i < graph_.size(); ++i) {
		degree[i] = graph_[i].size();
		degrees[degree[i]].emplace_back(i);
		pointers[i] = --degrees[degree[i]].end();
	}
	
	Ordering ordering;
	std::vector<bool> removed(graph_.size(), false);
	bool removing = true;
	while (removing) {
		removing = false;
		for (int d = 0; d < degrees.size(); ++d) {
			for (const int& v : degrees[d]) {
				degree_at_removal[v] = d;
				ordering.emplace_back(v);
				degrees[d].erase(pointers[v]);
				removed[v] = true;
				for(const int& neighbor : graph_[v]) {
					if (!removed[neighbor]) {
						degrees[degree[neighbor]].erase(pointers[neighbor]);
						--degree[neighbor];
						degrees[degree[neighbor]].emplace_back(neighbor);
						pointers[neighbor] = --degrees[degree[neighbor]].end();
					}
				}
				removing = true;
				break;
			}
			if (removing) break;
		}
	}
	return ordering;
}

Ordering
smallest_original_degree_ordering(const Graph& graph_) {
	std::vector<std::list<int>> degrees(graph_.size());
	for (int i = 0; i < graph_.size(); ++i) {
		degrees[graph_[i].size()].emplace_back(i);
	}

	Ordering ordering;
	for (auto& d : degrees) {
		while (!d.empty()) {
			ordering.emplace_back(d.front());
			d.pop_front();
		}
	}
	return ordering;
}

Ordering
uniform_random_ordering(const Graph& graph_) {
	std::unordered_set<int> unselected(2 * graph_.size());
	for (int i = 0; i < graph_.size(); ++i) {
		unselected.emplace(i);
	}

	Ordering ordering;
	while (!unselected.empty()) {
		ordering.emplace_back(*unselected.begin());
		unselected.erase(unselected.begin());
	}
	return ordering;
}

Ordering
largest_original_degree_ordering(const Graph& graph_) {
	std::vector<std::list<int>> degrees(graph_.size());
	for (int i = 0; i < graph_.size(); ++i) {
		degrees[graph_[i].size()].emplace_back(i);
	}

	Ordering ordering;
	for (int d = degrees.size() - 1; d >= 0; --d) {
		while (!degrees[d].empty()) {
			ordering.emplace_back(degrees[d].front());
			degrees[d].pop_front();
		}
	}
	return ordering;
}

Ordering
breadth_first_search_ordering(const Graph& graph_) {
	Ordering ordering;
	std::queue<int> queue;
	std::vector<bool> explored(graph_.size(), false);
	ordering.emplace_back(0);
	queue.emplace(0);
	explored[0] = true;
	int vertex;
	while (!queue.empty()) {
		vertex = queue.front();
		queue.pop();
		for (const auto& neighbor : graph_[vertex]) {
			if (!explored[neighbor]) {
				ordering.emplace_back(neighbor);
				queue.emplace(neighbor);
				explored[neighbor] = true;
			}
		}
	}
	return ordering;
}

Ordering
depth_first_search_ordering(const Graph& graph_) {
	Ordering ordering;
	std::stack<int> stack;
	std::vector<bool> discovered(graph_.size(), false);
	stack.emplace(0);
	int vertex;
	while (!stack.empty()) {
		vertex = stack.top();
		stack.pop();
		if (!discovered[vertex]) {
			ordering.emplace_back(vertex);
			discovered[vertex] = true;
			for (const auto& neighbor : graph_[vertex]) {
				stack.emplace(neighbor);
			}
		}
	}
	return ordering;
}

std::string
coloring_to_string(Coloring coloring_) {
	std::string s = "";
	for (int i = 0; i < coloring_.size(); ++i) {
		s += std::to_string(i);
		s += ", ";
		s += std::to_string(coloring_[i]);
		s += "\n";
	}
	return s;
}