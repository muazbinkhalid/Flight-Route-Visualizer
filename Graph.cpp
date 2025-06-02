#include "Graph.h"
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>

void Graph::addEdge(const std::string& from, const std::string& to, float weight) {
    if (from.empty() || to.empty()) {
        std::cerr << "Warning: Attempted to add edge with empty node name\n";
        return;
    }
    adjList[from].push_back(std::make_pair(to, weight));
    adjList[to].push_back(std::make_pair(from, weight));
}

const std::map<std::string, std::vector<std::pair<std::string, float>>>& Graph::getAdjList() const {
    return adjList;
}

std::vector<std::pair<std::string, float>> Graph::findShortestPath(const std::string& start, const std::string& end) {
    if (adjList.find(start) == adjList.end() || adjList.find(end) == adjList.end()) {
        std::cerr << "Pathfinding error: Start or end node not found\n";
        return {};
    }

    std::map<std::string, float> distances;
    std::map<std::string, std::string> previous;
    std::map<std::string, bool> visited;

    auto compare = [](const std::pair<float, std::string>& a, const std::pair<float, std::string>& b) {
        return a.first > b.first;
    };

    std::priority_queue<std::pair<float, std::string>,
        std::vector<std::pair<float, std::string>>,
        decltype(compare)> pq(compare);

    for (const auto& node : adjList) {
        distances[node.first] = std::numeric_limits<float>::max();
    }
    distances[start] = 0.0f;
    pq.push({ 0.0f, start });

    while (!pq.empty()) {
        auto current = pq.top().second;
        pq.pop();

        if (current == end) break;
        if (visited[current]) continue;
        visited[current] = true;

        for (const auto& neighbor : adjList.at(current)) {
            float alt = distances[current] + neighbor.second;
            if (alt < distances[neighbor.first]) {
                distances[neighbor.first] = alt;
                previous[neighbor.first] = current;
                pq.push({ alt, neighbor.first });
            }
        }
    }

    std::vector<std::pair<std::string, float>> path;
    if (previous.find(end) == previous.end() && start != end) {
        return path;
    }

    std::string current = end;
    while (current != start) {
        path.emplace_back(current, distances[current]);
        current = previous.at(current);
    }
    path.emplace_back(start, 0.0f);
    std::reverse(path.begin(), path.end());

    return path;
}
