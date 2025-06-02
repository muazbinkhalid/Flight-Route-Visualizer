#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>

void drawGraph(const std::map<std::string, sf::Vector2f>& locations,
    const std::vector<std::tuple<std::string, std::string, float, sf::Color>>& paths,
    const std::vector<std::pair<std::string, float>>& fullPath);

void handleZoom(sf::RenderWindow& window, sf::Event& event, sf::View& view, float& zoomLevel);
void handlePan(sf::RenderWindow& window, sf::Event& event, sf::View& view,
    bool& isDragging, sf::Vector2f& lastMousePos);

#endif
