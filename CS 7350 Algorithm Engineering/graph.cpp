#include <iostream>
#include <map>
#include <list>
#include <string>
#include <cmath>
#include <chrono>
#include <deque>
#include <unordered_set>
#include <fstream>

typedef std::map<int, std::list<int>> Graph;

int
pair(int a, int b) {
    return a >= b ? (a * a + a * b) : (a + b * b);
}

std::pair<int, int>
unpair(int c) {
    //Matthew Szudzik's unpairing function (http://szudzik.com/ElegantPairing.pdf)
    int sqrtc = sqrt(c);
    int sqc = sqrtc * sqrtc;
    return c - sqc >= sqrtc ?
        std::make_pair(sqrtc, c - sqc - sqrtc) :
        std::make_pair(c - sqc, sqrtc);
}

Graph
createCompleteGraph(int vertices) {
    Graph graph;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (j != i) {
                graph[i + 1].emplace_back(j + 1);
            }
        }
    }
    return graph;
}

Graph
createCycleGraph(int vertices) {
    Graph graph;
    for (int i = 0; i < vertices; ++i) {
        graph[i + 1].emplace_back(i);
        graph[i + 1].emplace_back(i + 2);
    }
    graph[1].pop_front();
    graph[1].emplace_front(vertices);
    graph[vertices].pop_back();
    graph[vertices].emplace_back(1);
    return graph;
}

Graph
createRandomGraph(int vertices, int edges) {
    Graph graph;
    std::deque<int> available(vertices * vertices - 2);
    std::unordered_set<int> created;
    for (int i = 0; i < vertices * vertices - 2; ++i) {
        available[i] = i + 1;
    }
    int edge;
    std::pair<int, int> v;
    int edge_;
    for (int i = 0; i < edges; ++i) {
        auto iter = available.begin();
        std::advance(iter, rand() % available.size());
        edge = *iter;
        v = unpair(edge);
        edge_ = pair(v.second, v.first);
        available.erase(iter);
        if (v.first != v.second && created.count(edge_) == 0) {
            graph[v.first + 1].emplace_back(v.second + 1);
            graph[v.second + 1].emplace_back(v.first + 1);
            created.emplace(pair(v.second, v.first));
        }
        else {
            --i;
        }
    }
    return graph;
}

std::string
graphToString(Graph graph) {
    int line = graph.size();
    std::string s = std::to_string(line++) + '\n';
    for (auto const& v : graph) {
        s += std::to_string(line) + '\n';
        line += v.second.size();
    }
    for (const auto& v : graph) {
        for (const int& e : v.second) {
            s += std::to_string(e) + '\n';
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    Graph graph;
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point stop;
    std::string option(argv[1]);

    if (option == "complete") {
        start = std::chrono::high_resolution_clock::now();
        graph = createCompleteGraph(std::stoi(argv[2]));
        stop = std::chrono::high_resolution_clock::now();
    }
    else if (option == "cycle") {
        start = std::chrono::high_resolution_clock::now();
        graph = createCycleGraph(std::stoi(argv[2]));
        stop = std::chrono::high_resolution_clock::now();
    }
    else if (option == "random") {
        start = std::chrono::high_resolution_clock::now();
        graph = createRandomGraph(std::stoi(argv[2]), std::stoi(argv[3]));
        stop = std::chrono::high_resolution_clock::now();
    }

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << duration.count() << " nanoseconds" << std::endl;

    std::ofstream file;
    file.open("graph.txt");
    file << graphToString(graph);
    file.close();
}