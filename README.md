### Tower Detection System - C++ Project Description

This C++ project implements a **Tower Detection System** that allows users to manage and analyze the connectivity of towers represented as a graph. The system enables users to perform various graph-related operations, such as adding nodes and edges, finding the Minimum Spanning Tree (MST), finding the shortest path between two nodes, and checking the connectivity of the graph. The project also includes a simple user authentication system (login/registration) and the ability to save/load graph data from a file.

---

### Features:
1. **User Authentication:**
   - **Login System**: Users must log in using a registered username and password.
   - **Registration System**: New users can register by creating a username and password.

2. **Graph Management:**
   - **Add Node**: Add a new node (tower) to the graph.
   - **Add Edge**: Add an edge (connection between two towers) with a specified weight (cost).
   - **Display Graph**: View the current graph structure, including all nodes and edges.
   - **Save Graph**: Save the current graph to a file for future use.
   - **Load Graph**: Load an existing graph from a file.

3. **Graph Algorithms:**
   - **Minimum Spanning Tree (MST)**: Use **Prim's Algorithm** to find the minimum spanning tree of the graph, which connects all nodes with the minimum possible total edge weight.
   - **Shortest Path**: Use **Dijkstra's Algorithm** to find the shortest path between two specified nodes.
   - **Connectivity Check**: Use **Depth-First Search (DFS)** to check if the graph is connected, i.e., if all nodes are reachable from any other node.

4. **File Management:**
   - **Save Graph to File**: Save the graph structure (nodes and edges) to a text file for persistent storage.
   - **Load Graph from File**: Load a graph from a file and reconstruct the graph with nodes and edges.

5. **ASCII Art Display**: A welcome screen with ASCII art to greet users upon starting the program.

---

### How It Works:
- The user starts by logging in or registering. After a successful login, they are presented with a menu to manage the graph.
- The graph can be modified by adding nodes and edges, and users can view the current structure of the graph at any time.
- Various graph algorithms such as MST, Shortest Path, and Connectivity Check can be executed to analyze the graph.
- Changes to the graph are saved to a file for future sessions.

### Code Structure:
- **Graph Structure**: The `Graph` class manages nodes, edges, and various algorithms like Prim's and Dijkstra's.
- **User Authentication**: User credentials (username and password) are managed using a simple text file (`users.txt`).
- **Graph Data Persistence**: Graph data is stored in `graph.txt` to maintain the state across sessions.

---

### Prerequisites:
- C++11 or higher
- C++ Standard Library

---

### How to Use:
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/TowerDetectionSystem.git
   cd TowerDetectionSystem
   ```

2. **Compile the Code:**
   ```bash
   g++ -o tower_detection_system main.cpp
   ```

3. **Run the Program:**
   ```bash
   ./tower_detection_system
   ```

4. **Follow the On-Screen Prompts:**
   - Register or log in with your username and password.
   - Use the menu options to manage the graph and perform graph algorithms.

---

### Example:

**Welcome Screen:**
```
=== Welcome to the Tower Detection System ===
Manage and analyze tower connectivity efficiently.
```

**Menu:**
```
1. Add Node
2. Add Edge
3. Display Graph
4. Find MST
5. Find Shortest Path
6. Check Connectivity
7. Save Graph
8. Logout
Enter your choice: 
```

**Sample Graph Output:**
```
--- Tower Graph Connections ---
Node 0: (1, 5) (2, 10)
Node 1: (0, 5) (2, 2)
Node 2: (0, 10) (1, 2)
```

**MST Output (Prim’s Algorithm):**
```
--- Minimum Spanning Tree (MST) ---
0 - 1 (Weight: 5)
1 - 2 (Weight: 2)
```

---

### Files:
- `main.cpp`: The main program file with all the logic for the Tower Detection System.
- `graph.txt`: The file used to store graph data (nodes and edges).
- `users.txt`: The file used to store user credentials (username and password).

---

### Contributing:
Feel free to fork this project, make modifications, and submit pull requests for new features or bug fixes!

---

### License:
This project is open-source and available under the [MIT License](LICENSE).

---

### Acknowledgements:
- The graph algorithms used (Prim's for MST and Dijkstra's for shortest path) are standard algorithms widely used in network optimization and graph theory.
