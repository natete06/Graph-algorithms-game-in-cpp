# Graph Algorithms Visualiser (C++) — BFS Guessing Game (WIP)

An interactive C++ project that visualizes a graph using **raylib** and turns **Breadth-First Search (BFS)** into a small “guess the next node” game.

The goal is to click nodes in the correct BFS visitation order (starting from a chosen start node). Correct guesses highlight the node (and the BFS predecessor edge); wrong guesses consume tries.

> **Status:** Work in progress — features, UI, and structure are still changing.

---

## Features (current)
- Graph represented as an adjacency list
- Node rendering + labels (A, B, C, …)
- Edge rendering (with per-edge coloring support)
- BFS traversal computed once at start to generate an “answer key”
- Manual mode:
  - Click to guess the next BFS node
  - Correct guess → node turns green (+ BFS predecessor edge turns green)
  - Wrong guess → node turns red and tries decrease
- On-screen HUD: tries remaining + BFS step progress

---

## Planned / Ideas
- “Hint” / help key to reveal the next step (e.g., SPACE)
- Better feedback for wrong guesses (temporary red flash, then revert)
- Add DFS / Dijkstra modes
- Load graphs dynamically (file input) instead of hardcoded graph
- Cleaner code organization (split into headers/source files)

---

## Build / Run
This project is currently set up for a raylib + MinGW workflow (Windows).  
Exact build instructions may change while the repo is being reorganized.

If you already have your raylib toolchain configured, build from the project root using your existing make setup.

---

## Credits
This project uses the **raylib** library for graphics/input.

- raylib website: https://www.raylib.com/

raylib is an open-source C library for videogame programming.

---

## License
This repository is for learning / academic work and is currently WIP.  
(If you plan to open-source formally, add a LICENSE file and update this section.)
