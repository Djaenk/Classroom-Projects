#ifndef WEIGHTED_GRAPH
#define WEIGHTED_GRAPH

#include "simple_graph.hpp"

template <typename vertex>
class WeightedGraph : public Graph<vertex>{
	private:
		//inherit pair hashing function from base graph class
		struct hash_pair : public Graph<vertex>::hash_pair{};

		std::unordered_map<std::pair<vertex, vertex>, double, hash_pair> weights;

		//prevent public use of inherited addEdge function, which does not
		//require a weight to be provided
		using Graph<vertex>::addEdge;

		//Kruskal's algorithm requires access to graph weights
		template <typename externVertex>
		friend std::vector<std::tuple<double, externVertex, externVertex>>
		MSTKruskal(const WeightedGraph<externVertex>&, bool);

	public:
		void addEdge(const vertex&, const vertex&, const double);
		void removeEdge(const vertex&, const vertex&);
		void clear();

		void readtextFormat(std::string);
};

template <typename vertex>
void
WeightedGraph<vertex>::addEdge(const vertex& target1, const vertex& target2, const double weight){
	Graph<vertex>::addEdge(target1, target2);
	if (target1 < target2){
		weights.emplace(std::make_pair(target1, target2), weight);
	}
	else{
		weights.emplace(std::make_pair(target2, target1), weight);
	}
}

template <typename vertex>
void
WeightedGraph<vertex>::removeEdge(const vertex& target1, const vertex& target2){
	Graph<vertex>::removeEdge(target1, target2);
	if (target1 < target2){
		weights.erase(std::make_pair(target1, target2));
	}
	else{
		weights.erase(std::make_pair(target2, target1));
	}
}

template <typename vertex>
void
WeightedGraph<vertex>::clear(){
	Graph<vertex>::clear();
	weights.clear();
}

template <typename vertex>
void
WeightedGraph<vertex>::readtextFormat(std::string graph){
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
			double weight;
			uint delimiterPos1 = line.find(" - ");
			uint delimiterPos2 = line.find(" - ", delimiterPos1 + 1);
			std::string weightString = line.substr(0, delimiterPos1);
			std::string target1String = line.substr(delimiterPos1 + 3, delimiterPos2 - delimiterPos1 - 3);
			std::string target2String = line.substr(delimiterPos2 + 3);
			std::istringstream weightSS(weightString);
			std::istringstream target1SS(target1String);
			std::istringstream target2SS(target2String);
			target1SS >> std::noskipws >> target1;
			target2SS >> std::noskipws >> target2;
			weightSS >> weight;
			addEdge(target1, target2, weight);
		}
		else if (vertexCount > 0){
			vertex target;
			std::string targetString = line;
			std::istringstream targetSS(targetString);
			targetSS >> std::noskipws >> target;
			Graph<vertex>::addVertex(target);
			vertexCount--;
		}
	}
}

#endif