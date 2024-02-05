## <h1 align="center">"Catch The Cat"</h1>
[![Watch the video](https://img.youtube.com/vi/GTk5aNsfXJE/maxresdefault.jpg)](https://youtu.be/GTk5aNsfXJE)

## Overview:
The "Catch The Cat" game is a C++ project built using the SFML library,
creating a game where the player aims to prevent a cat from reaching the end of a board.
The game utilizes a graph-based approach, treating each square on the board as a vertex.
The cat movementis based on the BFS (Breadth-First Search) algorithm to find the fastest way to the end. 
the player is blocking the cat by narking the squares and "removing" them from the graph.

## Technologies Used:
- **SFML** Simple and Fast Multimedia Library - for graphics and sounds.

## Project Structure - main classes:
- **Game**: Responsible on the game loop handling and the gameplay flow.
- **Table**: Represent the Graph and holds the Vertices (squares) and the cat, performs the BFS algorithm.
- **Vertex**: Represent a Vertex on the graph (square). holds all the the vertex data needed for the BFS algorythm.
- **Utilities**: Holds needed global variables such as enum classes and define variables.

## Key Features:
1. Graph Representation:
   - Utilizes a graph-based model to represent the game board, treating each square as a vertex.
   - Implements BFS algorithm to calculate the cat's movement on the graph.
2. Game Logic:
   - Cat moves one step towards the board's edge each turn.
   - Player blocks squares by marking them, preventing the cat from stepping on marked squares.
   - Removal of marked squares corresponds to removing nodes from the graph.
3. Random Movement:
   - After the player successfully blocks all possible paths, the cat moves randomly on the remaining unblocked squares.

## Getting Started:
1. Clone the repository to your local machine.
   ```bash
   git clone <https://github.com/Daniel959595/Catch-The-Cat.git>
2. Install SFML library: <a href="https://www.sfml-dev.org/download.php">Download from here</a>.
3. Extract the library and make sure its in the exact path as follow: "C:/SFML/SFML-2.5.1".

## Licence:
Free for personal use.
