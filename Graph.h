#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <string>
#include <utility>

class Graph {
public:
    void addEdge(const std::string& from, const std::string& to, float weight);
    std::vector<std::pair<std::string, float>> findShortestPath(const std::string& start, const std::string& end);
    const std::map<std::string, std::vector<std::pair<std::string, float>>>& getAdjList() const;

private:
    std::map<std::string, std::vector<std::pair<std::string, float>>> adjList;
};

#endif // GRAPH_H
