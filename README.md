# ✈️ FlightRouteVisualizer

An interactive C++ application that visualizes the **shortest flight path** between countries using **Dijkstra's Algorithm** and renders it over a world map using **SFML**.

## 🗺️ Project Description

This project implements a **graph-based flight network** and visually animates the **shortest route** between two locations. The application supports:
- **Zooming & Panning**
- **Interactive Plane Animation**
- **Dynamic Distance Labels**
- **Shortest Path Visualization**

Developed using:
- **C++ STL** for Graph and Pathfinding
- **SFML (Simple and Fast Multimedia Library)** for GUI rendering

## 📌 Features

- ✅ Graph data structure for countries and distances
- ✅ Dijkstra’s algorithm for finding the shortest path
- ✅ Smooth plane animation across map
- ✅ Real-time zoom and pan for better exploration
- ✅ City markers and edge weights shown
- ✅ Clean and modular code structure

## 🛠️ Technologies Used

| Component | Technology |
|----------|------------|
| Programming Language | C++ |
| Graphics Library | SFML |
| Algorithms | Dijkstra's Shortest Path |
| Data Structures | STL `map`, `vector`, `priority_queue` |

## 🧠 How it Works

1. **Graph Creation**: Countries are represented as nodes; distances between them are edge weights.
2. **Path Calculation**: When a path is needed, Dijkstra’s algorithm finds the shortest route.
3. **GUI Rendering**:
    - The world map is displayed.
    - Cities are marked.
    - The computed shortest path is drawn and animated.
4. **User Interaction**:
    - Mouse scroll zooms in/out
    - Left-click drag to pan
    - Path animation runs smoothly across countries

## 📂 Project Structure


## 🚀 How to Run

1. Install **SFML** on your system.
2. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/FlightRouteVisualizer.git
   cd FlightRouteVisualizer
Authors
Muaz Bin Khalid
Ihtisham Sheraz

BSCS - Semester 3, Bahria University
