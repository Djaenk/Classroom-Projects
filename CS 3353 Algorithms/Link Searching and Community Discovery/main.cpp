#include "graph.h"
#include "graphControl.h"
#include <iostream>
#include <string>
#include <vector>

void testgraph(){
	SimpleGraph<int> graph;
	graph.addVertex(1);
	graph.addVertex(2);
	graph.addVertex(3);
	graph.addVertex(4);
	graph.addVertex(5);
	graph.addVertex(6);
	graph.addVertex(7);
	graph.addVertex(8);
	graph.addVertex(9);
	graph.addVertex(10);
	graph.addVertex(11);
	graph.addVertex(12);
	graph.addEdge(1,2);
	graph.addEdge(2,3);
	graph.addEdge(1,4);
	graph.addEdge(1,5);
	graph.addEdge(2,5);
	graph.addEdge(3,5);
	graph.addEdge(3,6);
	graph.addEdge(4,5);
	graph.addEdge(5,6);
	graph.addEdge(4,7);
	graph.addEdge(5,7);
	graph.addEdge(5,8);
	graph.addEdge(5,9);
	graph.addEdge(6,9);
	graph.addEdge(7,8);
	graph.addEdge(8,9);
	graph.addEdge(7,10);
	graph.addEdge(8,11);
	graph.addEdge(9,12);
	std::cout << graph.textFormat() << std::endl;
	for (std::pair<int, int> edge : graph.connect(3,1)){
		std::cout << '(' << edge.first << ',' << edge.second << ')' << std::endl;
	}
	auto communities = graph.discoverCommunities();
	for (uint i = 0; i < communities.size(); i++){
		std::cout << "Community " << i << ": ";
		for (const auto& vertex : communities[i]){
			std::cout << vertex << ", ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char** argv){
	if (argc > 1){
		readCommandsFromFile(argv[1]);
	}
	else{
		readCommandsFromFile("exampleinput.txt");
	}
	return 0;
}