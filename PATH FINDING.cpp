#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <stdexcept>
#include <stack> 

using namespace std;

// Function to display ASCII art
void displayAsciiArt() {
    cout << R"(
    __                        _      __      _    
   |_   _|                       \ \    / /     | |   
     | | _  _ _ __  _ _      \ \  / / _ _| |  
     | |/ _ \| '/ _ \| '_ \      \ \/ / ` | '| _|
     | | () | | | () | | | |      \  / (| | |  | | 
     \/\/||  \/|| ||       \/ \,||   \|
    )" << endl;
}

// Function to display the welcome screen
void displayWelcomeScreen() {
    displayAsciiArt();
    cout << "\n=== Welcome to the Tower Detection System ===\n";
    cout << "Manage and analyze tower connectivity efficiently.\n\n";
}

// Function to display the menu header
void displayMenuHeader() {
    cout << R"(
  ==========================================
            Tower Detection System
  ==========================================
    )" << endl;
}

// Data structure for the Tower Detection System
struct Graph {
    int numNodes;
    vector<vector<pair<int, int>>> adjList;

    Graph(int nodes = 0) : numNodes(nodes) {
        adjList.resize(nodes);
    }

    void addEdge(int src, int dest, int weight) {
        if (src >= numNodes || dest >= numNodes || src < 0 || dest < 0) {
            cout << "Invalid node. Please ensure the nodes exist.\n";
            return;
        }
        adjList[src].emplace_back(dest, weight);
        adjList[dest].emplace_back(src, weight); // Undirected graph
    }

    void addNode() {
        numNodes++;
        adjList.resize(numNodes);
        cout << "Node " << numNodes - 1 << " added successfully.\n";
    }

    void displayGraph() {
        cout << "\n--- Tower Graph Connections ---\n";
        for (int i = 0; i < numNodes; i++) {
            cout << "Node " << i << ": ";
            for (auto& [neighbor, weight] : adjList[i]) {
                cout << "(" << neighbor << ", " << weight << ") ";
            }
            cout << endl;
        }
    }

    // Minimum Spanning Tree using Prim's Algorithm
    void findMST() {
        if (numNodes == 0) {
            cout << "No nodes in the graph.\n";
            return;
        }

        cout << "\n--- Minimum Spanning Tree (MST) ---\n";
        vector<int> key(numNodes, INT_MAX);
        vector<bool> inMST(numNodes, false);
        vector<int> parent(numNodes, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        key[0] = 0;
        pq.push({ 0, 0 });

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (auto& [v, weight] : adjList[u]) {
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({ key[v], v });
                }
            }
        }

        for (int i = 1; i < numNodes; ++i) {
            if (parent[i] != -1) {
                cout << parent[i] << " - " << i << " (Weight: " << key[i] << ")\n";
            }
        }
    }

    // Shortest Path using Dijkstra's Algorithm
    void findShortestPath(int start, int end) {
        if (start >= numNodes || end >= numNodes || start < 0 || end < 0) {
            cout << "Invalid nodes.\n";
            return;
        }

        cout << "\n--- Shortest Path ---\n";
        vector<int> dist(numNodes, INT_MAX);
        vector<int> parent(numNodes, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[start] = 0;
        pq.push({ 0, start });

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& [v, weight] : adjList[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                    parent[v] = u;
                }
            }
        }

        if (dist[end] == INT_MAX) {
            cout << "No path exists.\n";
            return;
        }

        vector<int> path;
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << "\nTotal Cost: " << dist[end] << endl;
    }

    // Improved Connectivity Check using DFS
    bool isConnected() {
        if (numNodes == 0) {
            cout << "Graph is empty.\n";
            return false;
        }

        vector<bool> visited(numNodes, false);  // Keep track of visited nodes
        stack<int> s;
        s.push(0);  // Start DFS from node 0
        visited[0] = true;

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            for (auto& [neighbor, _] : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }

        // Check if all nodes were visited
        for (bool visit : visited) {
            if (!visit) {
                cout << "The graph is not connected. There are unreachable nodes.\n";
                return false;
            }
        }

        cout << "The graph is connected.\n";
        return true;
    }

    // Load graph from file
    void loadGraphFromFile() {
        ifstream file("graph.txt");
        if (!file) {
            cout << "No graph data file found, creating a new graph.\n";
            return;
        }

        int nodeCount, edgeCount;
        file >> nodeCount >> edgeCount;
        numNodes = nodeCount;
        adjList.resize(numNodes);

        for (int i = 0; i < edgeCount; i++) {
            int src, dest, weight;
            file >> src >> dest >> weight;
            addEdge(src, dest, weight);
        }
        file.close();
    }

    // Save graph to file
    void saveGraphToFile() {
        ofstream file("graph.txt");
        file << numNodes << " " << adjList.size() << "\n";
        for (int i = 0; i < numNodes; i++) {
            for (auto& [neighbor, weight] : adjList[i]) {
                if (i < neighbor) { // Avoid duplicating edges
                    file << i << " " << neighbor << " " << weight << "\n";
                }
            }
        }
        file.close();
    }
};

// Login system
unordered_map<string, string> users;

string getPasswordInput() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void loadUsers() {
    ifstream file("users.txt");
    if (file.is_open()) {
        string username, password;
        while (file >> username >> password) {
            users[username] = password;
        }
        file.close();
    }
}

void saveUsers() {
    ofstream file("users.txt");
    for (auto& [username, password] : users) {
        file << username << " " << password << endl;
    }
}

void registerUser() {
    string username, password;
    cout << "\n--- New User Registration ---\n";
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, username);
    if (users.find(username) != users.end()) {
        cout << "Username already exists. Please try again.\n";
        return;
    }
    cout << "Enter password: ";
    password = getPasswordInput();
    users[username] = password;
    saveUsers();
    cout << "Registration successful!\n";
}

bool loginUser() {
    string username, password;
    cout << "\n--- User Login ---\n";
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, username);
    if (users.find(username) == users.end()) {
        cout << "Username not found. Please register as a new user.\n";
        return false;
    }
    cout << "Enter password: ";
    password = getPasswordInput();
    if (users[username] == password) {
        cout << "Login successful!\n";
        return true;
    }
    else {
        cout << "Incorrect password. Please try again.\n";
        return false;
    }
}

// Menu
void menuPage() {
    Graph graph;
    graph.loadGraphFromFile(); // Load graph from file on startup
    int choice;

    do {
        displayMenuHeader();
        cout << "1. Add Node\n";
        cout << "2. Add Edge\n";
        cout << "3. Display Graph\n";
        cout << "4. Find MST\n";
        cout << "5. Find Shortest Path\n";
        cout << "6. Check Connectivity\n";
        cout << "7. Save Graph\n";
        cout << "8. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            graph.addNode();
            break;
        case 2: {
            int src, dest, weight;
            cout << "Enter source, destination, and weight: ";
            cin >> src >> dest >> weight;
            graph.addEdge(src, dest, weight);
            break;
        }
        case 3:
            graph.displayGraph();
            break;
        case 4:
            graph.findMST();
            break;
        case 5: {
            int start, end;
            cout << "Enter start and end nodes: ";
            cin >> start >> end;
            graph.findShortestPath(start, end);
            break;
        }
        case 6:
            if (graph.isConnected()) {
                cout << "The graph is connected.\n";
            }
            else {
                cout << "The graph is not connected.\n";
            }
            break;
        case 7:
            graph.saveGraphToFile();
            cout << "Graph saved successfully!\n";
            break;
        case 8:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

int main() {
    loadUsers();
    displayWelcomeScreen();

    int choice;
    do {
        cout << "\n1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            if (loginUser()) {
                menuPage();
            }
            break;
        case 3:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}