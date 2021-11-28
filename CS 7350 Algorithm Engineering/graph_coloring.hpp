#include <vector>
#include <list>
#include <unordered_set>
#include <queue>
#include <stack>

typedef std::vector<std::list<int>> Graph;
typedef std::list<int> Ordering;
typedef std::vector<int> Coloring;

Coloring greedy_coloring(const Graph& graph_, const Ordering& order);

Ordering smallest_last_vertex_ordering(const Graph& graph_);
Ordering smallest_original_degree_ordering(const Graph& graph_);
Ordering uniform_random_ordering(const Graph& graph_);
Ordering largest_original_degree_ordering(const Graph& graph_);
Ordering breadth_first_search_ordering(const Graph& graph_);
Ordering depth_first_search_ordering(const Graph& graph_);