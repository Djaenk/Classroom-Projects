#include <vector>
#include <unordered_set>
#include <list>
#include <string>
#include <cmath>
#include <random>
#include <unordered_set>
#include <sstream>

typedef std::vector<std::list<int>> Graph;

int pair(int a_, int b_);
std::pair<int, int> unpair(int c_);

Graph create_complete_graph(int vertices_);
Graph create_cycle_graph(int vertices_);
Graph create_uniform_random_graph(int vertices_, int edges_);
Graph create_skewed_random_graph(int vertices_, int edges_);
Graph create_normal_random_graph(int vertices_, int edges_);

std::string graph_to_string(Graph graph);
Graph string_to_graph(std::string string_);