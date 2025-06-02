#include "Graph.h"
#include "gui.h"
#include <SFML/Graphics.hpp>
#include <map>

int main() {
    Graph graph;

    graph.addEdge("Pakistan", "India", 10);
    graph.addEdge("Pakistan", "UAE", 13);
    graph.addEdge("Pakistan", "China", 20);
    graph.addEdge("India", "UAE", 15);
    graph.addEdge("India", "China", 5);
    graph.addEdge("China", "UAE", 8);
    graph.addEdge("UAE", "Turkey", 25);
    graph.addEdge("Turkey", "Germany", 30);
    graph.addEdge("Germany", "USA", 50);

    auto shortestPath = graph.findShortestPath("Pakistan", "USA");

    std::map<std::string, sf::Vector2f> locations = {
        {"Pakistan", {700, 350}},
        {"India", {750, 400}},
        {"UAE", {680, 420}},
        {"China", {800, 300}},
        {"Turkey", {600, 300}},
        {"Germany", {550, 250}},
        {"USA", {150, 250}},
    };

    std::vector<std::tuple<std::string, std::string, float, sf::Color>> paths;
    for (const auto& [from, adj] : graph.getAdjList()) {
        for (const auto& [to, weight] : adj) {
            if (from < to) {
                paths.emplace_back(from, to, weight, sf::Color::Black);
            }
        }
    }

    for (size_t i = 0; i + 1 < shortestPath.size(); ++i) {
        for (auto& path : paths) {
            if ((std::get<0>(path) == shortestPath[i].first && std::get<1>(path) == shortestPath[i + 1].first) ||
                (std::get<1>(path) == shortestPath[i].first && std::get<0>(path) == shortestPath[i + 1].first)) {
                std::get<3>(path) = sf::Color::Blue;
            }
        }
    }

    drawGraph(locations, paths, shortestPath);
    return 0;
}
