#ifndef SIMPLE_GRAPH
#define SIMPLE_GRAPH

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <tuple>
#include <queue>
#include <stack>
#include <vector>
#include <exception>
#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>

template<typename vertex> class WeightedGraph;

template <typename vertex>
class Graph{
	//Forward declaration
	protected:
		struct hash_pair;

	private:
		//Interally, a graph is defined by a map. Keys are vertices, values are
		//the set of neighbors.
		std::unordered_map<vertex, std::unordered_set<vertex>> vertices;
		size_t edgeCount = 0;

		struct DAGNode{ //defines node in BFS when calculating betweenness
			uint level;
			uint label;
			double credit;
			std::unordered_set<vertex> children;
			std::unordered_map<vertex, double> parentEdgeCredit;

			DAGNode(uint level, uint label, double credit) : level(level), label(label), credit(credit){}
		};

		//In the context of this Graph class, a component is a subgraph that is
		//not connected to any vertices outside of the subgraph. Communities are
		//found by removing high-betweenness edges and finding what components
		//remain.

		//Given a set of edges to ignore (i.e. edges that have removed),
		//defineComponents() traverses the graph to group vertices into
		//components.
		std::vector<std::unordered_set<vertex>> defineComponents(
			const std::unordered_set<std::pair<vertex, vertex>, hash_pair>& //edges to ignore
		);

		//updateBetweenness() performs the Newman-Girvan algorithm on a
		//component to update betweenness of edges.
		void updateBetweenness(
			std::unordered_map<std::pair<vertex, vertex>, double, hash_pair>&, //map of edges and their betweenness
			const std::unordered_set<vertex>&, //component
			const std::unordered_set<std::pair<vertex, vertex>, hash_pair>& //edges to ignore during computation
		);

		//Utility function to find the highest betweenness edge
		std::pair<vertex, vertex> highestBetweenness(
			std::unordered_map<std::pair<vertex, vertex>, double, hash_pair>&
		);

		//Kruskal's algorithm requires access to graph vertices
		template <typename externVertex>
		friend std::vector<std::tuple<double, externVertex, externVertex>>
		MSTKruskal(const WeightedGraph<externVertex>&, bool);

	protected:
		struct hash_pair {                //provide function to hash std::pair so
			template <class T1, class T2> //it can be used as a key in stl hashmaps
			size_t operator()(const std::pair<T1, T2>& p) const{ 
				return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
			} 
		};

	public:
		//graph construction functions
		void addVertex(const vertex&);
		void removeVertex(const vertex&);
		void addEdge(const vertex&, const vertex&);
		void removeEdge(const vertex&, const vertex&);
		void clear();

		//graph analysis functions
		std::vector<std::pair<vertex, vertex>> breadthFirstSearch(const vertex&, std::unordered_set<vertex>&);
		std::vector<std::pair<vertex, vertex>> breadthFirstSearch(const vertex&);
		std::vector<std::pair<vertex, vertex>> depthFirstSearch(const vertex&, std::unordered_set<vertex>&);
		std::vector<std::pair<vertex, vertex>> depthFirstSearch(const vertex&);
		std::vector<std::pair<vertex, vertex>> connect(const vertex&, const vertex&);
		std::vector<std::vector<vertex>> discoverCommunities();

		//graph input/output utility functions
		std::string textFormat();
		void readtextFormat(std::string);
};



template <typename vertex>
void
Graph<vertex>::addVertex(const vertex& target){
	if (vertices.find(target) != vertices.end()){
		throw std::invalid_argument("Vertex to be added already exists in Graph.");
	}
	vertices.emplace(target, std::unordered_set<vertex>());
}

template <typename vertex>
void
Graph<vertex>::removeVertex(const vertex& target){
	if (vertices.find(target) == vertices.end()){
		throw std::out_of_range("Vertex to be removed does not exist in Graph.");
	}
	for (vertex edge : vertices.at(target)){
		removeEdge(target, edge);
	}
	vertices.erase(target);
}

template <typename vertex>
void
Graph<vertex>::addEdge(const vertex& target1, const vertex& target2){
	if (vertices.find(target1) == vertices.end()
	|| vertices.find(target2) == vertices.end()){
		throw std::out_of_range("Edge to be added requires nonexistent vertex or vertices in Graph.");
	}
	else if (vertices.at(target1).find(target2) != vertices.at(target1).end()
	|| vertices.at(target2).find(target1) != vertices.at(target2).end()){
		throw std::invalid_argument("Edge to be added already exists in Graph.");
	}
	else{
		vertices.at(target1).emplace(target2);
		vertices.at(target2).emplace(target1);
		edgeCount++;
	}
}

template <typename vertex>
void
Graph<vertex>::removeEdge(const vertex& target1, const vertex& target2){
	if (vertices.find(target1) == vertices.end()
	|| vertices.find(target2) == vertices.end()){
		throw std::out_of_range("Edge to by removed requires nonexistent vertex or vertices in Graph.");
	}
	else if (vertices.at(target1).find(target2) == vertices.at(target1).end()
	|| vertices.at(target2).find(target1) == vertices.at(target2).end()){
		throw std::invalid_argument("Edge to be removed does not exist in Graph.");
	}
	else{
		vertices.at(target1).erase(target2);
		vertices.at(target2).erase(target1);
		edgeCount--;
	}
}

template <typename vertex>
void
Graph<vertex>::clear(){
	vertices.clear();
	edgeCount = 0;
}



template <typename vertex>
std::vector<std::pair<vertex, vertex>>
Graph<vertex>::breadthFirstSearch(const vertex& start, std::unordered_set<vertex>& discovered){
	std::vector<std::pair<vertex, vertex>> traversedEdges;
	traversedEdges.reserve(vertices.size());

	std::queue<vertex> toSearch;
	discovered.emplace(start);
	toSearch.emplace(start);
	while(!toSearch.empty()){
		const vertex& currentVertex = toSearch.front();
		for (const vertex& neighbor : vertices[currentVertex]){
			if (discovered.find(neighbor) == discovered.end()){
				discovered.emplace(neighbor);
				toSearch.emplace(neighbor);
				traversedEdges.push_back(std::make_pair(currentVertex, neighbor));
			}
		}
		toSearch.pop();
	}

	return traversedEdges;
}

template <typename vertex>
std::vector<std::pair<vertex, vertex>>
Graph<vertex>::breadthFirstSearch(const vertex& start){
	std::unordered_set<vertex> discovered;
	discovered.reserve(vertices.size());
	return breadthFirstSearch(start, discovered);
}

template <typename vertex>
std::vector<std::pair<vertex, vertex>>
Graph<vertex>::depthFirstSearch(const vertex& start, std::unordered_set<vertex>& discovered){
	std::vector<std::pair<vertex, vertex>> traversedEdges;
	if(discovered.size() < vertices.size() / 2){
		traversedEdges.reserve(vertices.size() - 1);
	}
	
	discovered.emplace(start);
	for (const vertex& neighbor : vertices[start]){
		if (discovered.find(neighbor) == discovered.end()){
			traversedEdges.push_back(std::make_pair(start, neighbor));
			discovered.emplace(neighbor);
			std::vector<std::pair<vertex, vertex>> toTraverse = depthFirstSearch(neighbor, discovered); //recurse
			traversedEdges.insert(traversedEdges.end(), toTraverse.begin(), toTraverse.end());
		}
	}

	return traversedEdges;
}

template <typename vertex>
std::vector<std::pair<vertex, vertex>>
Graph<vertex>::depthFirstSearch(const vertex& start){
	std::unordered_set<vertex> discovered;
	discovered.reserve(vertices.size());
	return depthFirstSearch(start, discovered);
}

template <typename vertex>
std::vector<std::pair<vertex, vertex>>
Graph<vertex>::connect(const vertex& start, const vertex& destination){
	std::unordered_map<vertex, vertex> discoveryTree;
	discoveryTree.reserve(vertices.size());
	std::vector<std::pair<vertex, vertex>> path;
	path.reserve(vertices.size());

	std::queue<vertex> toSearch;
	discoveryTree.emplace(start, start);
	toSearch.emplace(start);
	while(!toSearch.empty()){
		const vertex& currentVertex = toSearch.front();
		for (const vertex& neighbor : vertices[currentVertex]){
			if (discoveryTree.find(neighbor) == discoveryTree.end()){
				discoveryTree.emplace(neighbor, currentVertex);
				if (neighbor == destination){ //if the destination has been found,
					goto constructPath;       //exit the bfs entirely
				}
				toSearch.emplace(neighbor);
			}
		}
		toSearch.pop();
	}

	constructPath:
	vertex backtrack = destination;
	while(backtrack != discoveryTree.at(backtrack)){
		path.emplace(path.begin(), std::make_pair(discoveryTree.at(backtrack), backtrack));
		backtrack = discoveryTree.at(backtrack);
	}
	return path;
}

template <typename vertex>
std::vector<std::unordered_set<vertex>>
Graph<vertex>::defineComponents(
	const std::unordered_set<std::pair<vertex, vertex>, hash_pair>& ignoredEdges
){
	std::unordered_set<vertex> accounted; //set of *all* encountered vertices while defining components
	accounted.reserve(edgeCount);
	std::vector<std::unordered_set<vertex>> components; //sets of vertices belonging to a single component

	for (const auto& v : vertices){
		const vertex& target = v.first;
		if (accounted.find(target) == accounted.end()){
			std::unordered_set<vertex> discovered; //set of vertices belonging to component being searched
			discovered.reserve(vertices.size());
			std::queue<vertex> toSearch;
			discovered.emplace(target);
			accounted.emplace(target);
			toSearch.emplace(target);
			while(!toSearch.empty()){
				const vertex& currentVertex = toSearch.front();
				for (const vertex& neighbor : vertices[currentVertex]){
					if (discovered.find(neighbor) == discovered.end()){
						if (ignoredEdges.find(std::make_pair(currentVertex, neighbor)) != ignoredEdges.end()
						|| ignoredEdges.find(std::make_pair(neighbor, currentVertex)) != ignoredEdges.end()){
							continue; //do nothing upon encoutering an ignored edge
						}
						discovered.emplace(neighbor);
						accounted.emplace(neighbor);
						toSearch.emplace(neighbor);
					}
				}
				toSearch.pop();
			}
			components.push_back(discovered);
			//after finishing searching a component, add it to the vector of components
		}
	}
	
	return components;
}

template <typename vertex>
void
Graph<vertex>::updateBetweenness(
	std::unordered_map<std::pair<vertex, vertex>, double, hash_pair>& betweenness,
	const std::unordered_set<vertex>& component,
	const std::unordered_set<std::pair<vertex, vertex>, hash_pair>& ignoredEdges
){
	//temporarily store the betweenness of edges in the given component
	std::unordered_map<std::pair<vertex, vertex>, double, hash_pair> tempEdgeBetweenness;
	tempEdgeBetweenness.reserve(edgeCount);

	for(const vertex& target : component){
		std::unordered_map<vertex, DAGNode> DAG;
		DAG.reserve(component.size());

		//perform BFS on graph to generate DAG
		std::queue<std::pair<vertex, uint>> toSearch;
		DAG.emplace(std::piecewise_construct, std::forward_as_tuple(target), std::forward_as_tuple(0, 0, 0));
		toSearch.emplace(std::make_pair(target, 0));
		while (!toSearch.empty()){
			const vertex& currentVertex = toSearch.front().first;
			const uint& currentLevel = toSearch.front().second;
			for (const vertex& neighbor : vertices[currentVertex]){
				if (DAG.find(neighbor) == DAG.end()){
					if (ignoredEdges.find(std::make_pair(currentVertex, neighbor)) != ignoredEdges.end()
					|| ignoredEdges.find(std::make_pair(neighbor, currentVertex)) != ignoredEdges.end()){
						continue; //do nothing upon encountering a removed edge
					}
					DAG.at(currentVertex).children.emplace(neighbor);
					DAG.emplace(std::piecewise_construct, std::forward_as_tuple(neighbor), std::forward_as_tuple(currentLevel + 1, 0, 0));
					DAG.at(neighbor).parentEdgeCredit.emplace(currentVertex, 0);
					toSearch.emplace(std::make_pair(neighbor, currentLevel + 1));
				}
				else if (DAG.at(neighbor).level == currentLevel + 1){
					if (ignoredEdges.find(std::make_pair(currentVertex, neighbor)) != ignoredEdges.end()
					|| ignoredEdges.find(std::make_pair(neighbor, currentVertex)) != ignoredEdges.end()){
						continue;
					}
					DAG.at(currentVertex).children.emplace(neighbor);
					DAG.at(neighbor).parentEdgeCredit.emplace(currentVertex, 0);
				}
			}
			toSearch.pop();
		}

		//perform BFS on DAG to generate labels
		std::queue<vertex> toLabel;
		DAG.at(target).label = 1;
		toLabel.emplace(target);
		while (!toLabel.empty()){
			const vertex& currentVertex = toLabel.front();
			for (const vertex& child : DAG.at(currentVertex).children){
				if (DAG.at(child).label == 0){
					for (const auto& parent : DAG.at(child).parentEdgeCredit){
						DAG.at(child).label += DAG.at(parent.first).label;
					}
					toLabel.emplace(child);
				}
			}
			toLabel.pop();
		}

		//perform DFS on DAG to calculate credit
		std::stack<vertex> toCredit;
		toCredit.emplace(target);
		while (!toCredit.empty()){
			const vertex& currentVertex = toCredit.top();
			if (std::all_of(DAG.at(currentVertex).children.begin(), DAG.at(currentVertex).children.end(),
			[&DAG](const vertex& child){return DAG.at(child).credit != 0;})){
				DAG.at(currentVertex).credit = 1;
				for (const vertex& child : DAG.at(currentVertex).children){
					DAG.at(currentVertex).credit += DAG.at(child).parentEdgeCredit.at(currentVertex);
				}
				for (auto& edge : DAG.at(currentVertex).parentEdgeCredit){
					edge.second = DAG.at(currentVertex).credit * DAG.at(edge.first).label / DAG.at(currentVertex).label;
				}
				toCredit.pop();
			}
			else{
				for (const vertex& child : DAG.at(currentVertex).children){
					if (DAG.at(child).credit == 0){
						toCredit.emplace(child);
					}
				}
			}
		}

		//add calculated edge betweenness for starting vertex of this iteration
		for (const auto& node : DAG){
			const vertex& target = node.first;
			const auto& parentEdges = node.second.parentEdgeCredit;
			for (const auto& edge : parentEdges){
				const vertex& parent = edge.first;
				const double& credit = edge.second;
				if (target < parent){
					tempEdgeBetweenness[std::make_pair(target, parent)] += credit;
				}
				else{
					tempEdgeBetweenness[std::make_pair(parent, target)] += credit;
				}
			}
		}
	}

	//update betweenness using recalculated values in tempEdgeBetweenness
	for (const auto& temp : tempEdgeBetweenness){
		betweenness[temp.first] = temp.second;
	}
}

template <typename vertex>
std::pair<vertex, vertex>
Graph<vertex>::highestBetweenness(
	std::unordered_map<std::pair<vertex, vertex>, double, hash_pair>& betweenness
){
	auto edge = betweenness.begin();
	auto highestBetweennessEdge = edge;
	while (edge != betweenness.end()){
		if (edge->second > highestBetweennessEdge->second){
			highestBetweennessEdge = edge;
		}
		edge++;
	}
	return highestBetweennessEdge->first;
}

template <typename vertex>
std::vector<std::vector<vertex>>
Graph<vertex>::discoverCommunities(){
	std::unordered_map<std::pair<vertex, vertex>, double, hash_pair> betweenness; //associate each edge with its betweenness
	std::unordered_set<std::pair<vertex, vertex>, hash_pair> ignoredEdges;
	std::vector<std::vector<vertex>> communities;

	//initialize betweenness value to zero for each edge of the graph
	betweenness.reserve(edgeCount);
	for (const auto& vertexNeighborsPair : vertices){
		const vertex& target1 = vertexNeighborsPair.first;
		const std::unordered_set<vertex>& neighbors = vertexNeighborsPair.second;
		for (const vertex& target2 : neighbors){
			if (target1 < target2){
				betweenness[std::make_pair(target1, target2)] = 0.0;
			}
			else{
				betweenness[std::make_pair(target2, target1)] = 0.0;
			}
		}
	}

	//populate betweenness values of edges before any are removed
	auto components = defineComponents(ignoredEdges);
	for (const auto& component : components){
		updateBetweenness(betweenness, component, ignoredEdges);
	}

	//remove edges until a threshold has been crossed
	std::pair<vertex, vertex> recentlyIgnored;
	while (ignoredEdges.size() < 1.8 * (pow(edgeCount, 3) / pow(vertices.size(), 3) - pow(edgeCount, 2) / pow(vertices.size(), 2))){
	//1.8 * ((# of edges / # of vertices)^3 - (# of edges / # of vertices)^2)
		recentlyIgnored = highestBetweenness(betweenness);
		ignoredEdges.emplace(recentlyIgnored);
		betweenness[recentlyIgnored] = 0;
		components = defineComponents(ignoredEdges);
		for (const auto& component : components){
			if (component.find(recentlyIgnored.first) != component.end()){
				updateBetweenness(betweenness, component, ignoredEdges);
			}
			else if (component.find(recentlyIgnored.second) != component.end()){
				updateBetweenness(betweenness, component, ignoredEdges);
			}
			else{
				//if this component did not contain the most recently removed
				//edge, then there is no need to update its edge betweenness
				;
			}
		}
		if (ignoredEdges.size() == edgeCount){
			break; //in the event every vertex is orphaned before hitting the limit
		}
	}

	//after edge removal limit is reached, the remaining components are returned
	//as the original graph's communities
	for(const auto& component : defineComponents(ignoredEdges)){
		communities.emplace_back(component.begin(), component.end());
	}
	return communities;
}



template <typename vertex>
std::string
Graph<vertex>::textFormat(){
	std::ostringstream output;
	output << '[' << vertices.size() << ']' << std::endl;
	for (std::pair<vertex, std::unordered_set<vertex>> target : vertices){
		output << target.first << std::endl;
	}
	std::unordered_set<vertex> printed;
	output << "[undirected]" << std::endl;
	for (std::pair<vertex, std::unordered_set<vertex>> target1 : vertices){
		printed.emplace(target1.first);
		for (vertex target2 : target1.second){
			if (printed.find(target2) == printed.end()){
				output << target1.first << " - " << target2 << std::endl;
			}
		}
	}
	return output.str();
}

template <typename vertex>
void
Graph<vertex>::readtextFormat(std::string graph){
	std::istringstream input(graph);
	std::string line;
	uint vertexCount = 0;
	bool readingEdges = false;
	clear();
	while(std::getline(input, line)){
		if (line.front() == '[' && line.back() == ']'){
			line.erase(0,1);
			line.pop_back();
			if (std::all_of(line.begin(), line.end(), ::isdigit)){
				vertexCount = std::atoi(line.c_str());
				readingEdges = false;
			}
			if (line == "undirected"){
				readingEdges = true;
			}
		}
		else if (readingEdges){
			vertex target1;
			vertex target2;
			std::string target1String = line.substr(0, line.find(" - "));
			std::string target2String = line.substr(line.find(" - ") + 3);
			std::istringstream target1SS(target1String);
			std::istringstream target2SS(target2String);
			target1SS >> std::noskipws >> target1;
			target2SS >> std::noskipws >> target2;
			addEdge(target1, target2);
		}
		else if (vertexCount > 0){
			vertex target;
			std::string targetString = line;
			std::istringstream targetSS(targetString);
			targetSS >> std::noskipws >> target;
			addVertex(target);
			vertexCount--;
		}
	}
}

#endif