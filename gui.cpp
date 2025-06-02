#include "gui.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void drawGraph(const std::map<std::string, sf::Vector2f>& locations,
    const std::vector<std::tuple<std::string, std::string, float, sf::Color>>& paths,
    const std::vector<std::pair<std::string, float>>& fullPath) {

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Flight Route Visualization");
    sf::Texture mapTexture;
    mapTexture.loadFromFile("world_map.png");
    sf::Sprite mapSprite(mapTexture);

    sf::View view(sf::FloatRect(0, 0, 1000, 600));
    float zoomLevel = 1.0f;
    bool isDragging = false;
    sf::Vector2f lastMousePos;

    sf::CircleShape plane(7);
    plane.setFillColor(sf::Color::White);
    float speed = 100.0f;

    size_t pathIndex = 0;
    sf::Vector2f planePos;
    float progress = 0.0f;

    if (!fullPath.empty()) {
        planePos = locations.at(fullPath[0].first);
        plane.setPosition(planePos);
    }

    sf::Font font;
    font.loadFromFile("arial.ttf");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handleZoom(window, event, view, zoomLevel);
            handlePan(window, event, view, isDragging, lastMousePos);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (pathIndex + 1 < fullPath.size()) {
            sf::Vector2f start = locations.at(fullPath[pathIndex].first);
            sf::Vector2f end = locations.at(fullPath[pathIndex + 1].first);
            sf::Vector2f direction = end - start;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= distance;

            float moveStep = speed * 0.01f;
            progress += moveStep;

            if (progress >= distance) {
                pathIndex++;
                progress = 0.0f;
                if (pathIndex + 1 < fullPath.size()) {
                    planePos = locations.at(fullPath[pathIndex].first);
                    plane.setPosition(planePos);
                }
            }
            else {
                planePos = start + direction * progress;
                plane.setPosition(planePos);
            }
        }

        window.clear();
        window.setView(view);
        window.draw(mapSprite);

        for (const auto& [from, to, dist, color] : paths) {
            sf::Vertex line[] = {
                sf::Vertex(locations.at(from), color),
                sf::Vertex(locations.at(to), color)
            };
            window.draw(line, 2, sf::Lines);

            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::Black);
            text.setString(std::to_string((int)dist));
            sf::Vector2f mid = (locations.at(from) + locations.at(to)) / 2.0f;
            text.setPosition(mid);
            window.draw(text);
        }

        for (const auto& [name, pos] : locations) {
            sf::CircleShape city(5);
            city.setFillColor(sf::Color::Red);
            city.setPosition(pos);
            window.draw(city);

            sf::Text label;
            label.setFont(font);
            label.setCharacterSize(12);
            label.setFillColor(sf::Color::Blue);
            label.setString(name);
            label.setPosition(pos.x + 6, pos.y - 6);
            window.draw(label);
        }

        window.draw(plane);
        window.display();
    }
}

void handleZoom(sf::RenderWindow& window, sf::Event& event, sf::View& view, float& zoomLevel) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        float delta = event.mouseWheelScroll.delta;
        if (delta > 0) {
            zoomLevel *= 0.9f;
        }
        else if (delta < 0) {
            zoomLevel *= 1.1f;
        }
        view.setSize(window.getDefaultView().getSize());
        view.zoom(zoomLevel);
        window.setView(view);
    }
}

void handlePan(sf::RenderWindow& window, sf::Event& event, sf::View& view,
    bool& isDragging, sf::Vector2f& lastMousePos) {

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        isDragging = true;
        lastMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }
    else if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left) {
        isDragging = false;
    }
    else if (event.type == sf::Event::MouseMoved && isDragging) {
        sf::Vector2f newMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f delta = lastMousePos - newMousePos;
        view.move(delta);
        window.setView(view);
        lastMousePos = newMousePos;
    }
}
