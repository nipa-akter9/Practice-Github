#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int v) : vertices(v) {
        adjList.resize(v);
    }
    
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // For undirected graph, remove this line for directed
    }
    
    // Recursive DFS
    void dfsRecursive(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << start << " ";
        
        for (int neighbor : adjList[start]) {
            if (!visited[neighbor]) {
                dfsRecursive(neighbor, visited);
            }
        }
    }
    
    // Iterative DFS using stack
    void dfsIterative(int start) {
        vector<bool> visited(vertices, false);
        stack<int> s;
        
        s.push(start);
        
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            
            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";
                
                // Add neighbors to stack (in reverse order to maintain left-to-right traversal)
                for (int i = adjList[current].size() - 1; i >= 0; i--) {
                    int neighbor = adjList[current][i];
                    if (!visited[neighbor]) {
                        s.push(neighbor);
                    }
                }
            }
        }
    }
    
    // Wrapper function for recursive DFS
    void dfs(int start) {
        vector<bool> visited(vertices, false);
        cout << "DFS Traversal (Recursive): ";
        dfsRecursive(start, visited);
        cout << endl;
    }
    
    // Function to perform DFS and find path between two nodes
    bool dfsPath(int start, int target, vector<int>& path, vector<bool>& visited) {
        visited[start] = true;
        path.push_back(start);
        
        if (start == target) {
            return true;
        }
        
        for (int neighbor : adjList[start]) {
            if (!visited[neighbor]) {
                if (dfsPath(neighbor, target, path, visited)) {
                    return true;
                }
            }
        }
        
        path.pop_back(); // Backtrack
        return false;
    }
    
    // Find path between two nodes using DFS
    void findPath(int start, int target) {
        vector<bool> visited(vertices, false);
        vector<int> path;
        
        cout << "Finding path from " << start << " to " << target << ": ";
        if (dfsPath(start, target, path, visited)) {
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << endl;
        } else {
            cout << "No path found!" << endl;
        }
    }
    
    void printGraph() {
        cout << "\nGraph Adjacency List:" << endl;
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    // Create a graph with 6 vertices
    Graph g(6);
    
    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    
    // Print the graph
    g.printGraph();
    
    // Perform DFS traversal
    g.dfs(0);
    
    cout << "DFS Traversal (Iterative): ";
    g.dfsIterative(0);
    cout << endl;
    
    // Find path between nodes
    g.findPath(0, 5);
    g.findPath(3, 5);
    
    return 0;
}