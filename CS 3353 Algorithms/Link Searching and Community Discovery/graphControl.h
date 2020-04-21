#ifndef GRAPHCONTROL
#define GRAPHCONTROL

#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>

std::string readFileToString(std::string filename){
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open()){
		throw std::runtime_error("Cannot open file");
	}
	std::ifstream::pos_type fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<char> bytes(fileSize);
	file.read(bytes.data(), fileSize);
	return std::string(bytes.data(), fileSize);
}

void readCommandsFromFile(std::string filename){
	SimpleGraph<std::string> graph;
	std::string arg;
	std::string commands = readFileToString(filename);
	std::istringstream commandStream(commands);
	std::ofstream output;
	while(commandStream >> arg){
		if (arg == "or"){
			commandStream >> arg;
			std::string graphInput = readFileToString(arg);
			graph.readtextFormat(graphInput);
		}
		else if (arg == "ow"){
			commandStream >> arg;
			output.close();
			output.open(arg);
			if (!output.is_open()){
				throw std::runtime_error("Cannot open file");
			}
			else{
				output << "Opened " << arg << " for output." << std::endl;
			}
		}
		else if (arg == "dfs"){
			commandStream >> arg;
			output << "Edges traversed during depth first search, starting from " << arg << ':' << std::endl;
			for (const auto& edge : graph.depthFirstSearch(arg)){
				output << '(' << edge.first << " - " << edge.second << ')' << std::endl;
			}
			output << std::endl;
		}
		else if (arg == "bfs"){
			commandStream >> arg;
			output << "Edges traversed during breadth first search, starting from " << arg << ':' << std::endl;
			for (const auto& edge : graph.breadthFirstSearch(arg)){
				output << '(' << edge.first << " - " << edge.second << ')' << std::endl;
			}
			output << std::endl;
		}
		else if (arg == "mc"){
			std::string start;
			std::string destination;
			commandStream >> start >> destination;
			output << "Introductions necessary to connect " << start << " and " << destination << ':' << std::endl;
			output << '{';
			for (const auto& edge : graph.connect(start, destination)){
				output << '(' << edge.first << " - " << edge.second << "),";
			}
			output << '}' << std::endl;
		}
		else if (arg == "dc"){
			auto communities = graph.discoverCommunities();
			for (uint i = 0; i < communities.size(); ++i){
				output << "Community " << i + 1 << ": ";
				for (const auto& vertex : communities[i]){
					output << vertex << ", ";
				}
				output << std::endl;
			}
			output << std::endl;
		}
		else{
			output << "Unrecognized argument or command: " << arg << std::endl;
			std::cerr << "Unrecognized argument or command: " << arg << std::endl;
		}
		output << std::endl;
	}
} 

#endif