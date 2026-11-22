
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

class Graph
{
private:
    int vertices;
    vector<vector<int>> adj;

public:

    // Constructor
    Graph(int v)
    {
        vertices = v;
        adj.resize(v);
    }

    // Add edge
    void addEdge(int u, int v, bool directed)
    {
        adj[u].push_back(v);

        if (!directed)
            adj[v].push_back(u);
    }

    // Display graph
    void displayGraph()
    {
        cout << "\n========== ADJACENCY LIST ==========\n";

        for (int i = 0; i < vertices; i++)
        {
            cout << "Vertex " << i << " -> ";

            for (int x : adj[i])
                cout << x << " ";

            cout << endl;
        }
    }

    // DFS Helper
    void DFSHelper(int current, vector<bool>& visited,
                   vector<int>& result)
    {
        visited[current] = true;
        result.push_back(current);

        for (int neighbor : adj[current])
        {
            if (!visited[neighbor])
                DFSHelper(neighbor, visited, result);
        }
    }

    // DFS Traversal
    vector<int> DFS(int start)
    {
        vector<bool> visited(vertices, false);
        vector<int> result;

        DFSHelper(start, visited, result);

        return result;
    }

    // BFS Traversal
    vector<int> BFS(int start)
    {
        vector<bool> visited(vertices, false);
        vector<int> result;

        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            result.push_back(current);

            for (int neighbor : adj[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return result;
    }

    // Display traversal
    void displayTraversal(const vector<int>& result)
    {
        for (int vertex : result)
            cout << vertex << " ";

        cout << endl;
    }

    // Get number of vertices visited
    int countVisited(const vector<int>& result)
    {
        return result.size();
    }
};

int main()
{
    int vertices, edges;
    int choice, graphType;

    cout << "\n========================================\n";
    cout << "          GRAPH TRAVERSAL               \n";
    cout << "========================================\n";

    // Input vertices
    cout << "\nEnter number of vertices: ";
    cin >> vertices;

    if (cin.fail() || vertices <= 0)
    {
        cout << "Invalid number of vertices!\n";
        return 1;
    }

    Graph graph(vertices);

    // Graph type
    cout << "\nSelect Graph Type:\n";
    cout << "1. Undirected Graph\n";
    cout << "2. Directed Graph\n";
    cout << "Enter choice: ";

    cin >> graphType;

    if (cin.fail() || (graphType != 1 && graphType != 2))
    {
        cout << "Invalid graph type!\n";
        return 1;
    }

    bool directed = (graphType == 2);

    // Input edges
    cout << "\nEnter number of edges: ";
    cin >> edges;

    if (cin.fail() || edges < 0)
    {
        cout << "Invalid number of edges!\n";
        return 1;
    }

    cout << "\nEnter edges (source destination):\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v;

        cin >> u >> v;

        if (cin.fail() || u < 0 || u >= vertices ||
            v < 0 || v >= vertices)
        {
            cout << "Invalid edge! Try again.\n";
            return 1;
        }

        graph.addEdge(u, v, directed);
    }

    // Display graph
    graph.displayGraph();

    // Starting vertex
    int start;

    cout << "\nEnter starting vertex: ";
    cin >> start;

    if (cin.fail() || start < 0 || start >= vertices)
    {
        cout << "Invalid starting vertex!\n";
        return 1;
    }

    // Menu
    cout << "\n========== TRAVERSAL MENU ==========\n";
    cout << "1. Depth First Search (DFS)\n";
    cout << "2. Breadth First Search (BFS)\n";
    cout << "3. Perform Both Traversals\n";
    cout << "Enter your choice: ";

    cin >> choice;

    if (cin.fail() || choice < 1 || choice > 3)
    {
        cout << "Invalid choice!\n";
        return 1;
    }

    vector<int> dfsResult, bfsResult;

    long long dfsTime = 0;
    long long bfsTime = 0;

    // DFS
    if (choice == 1 || choice == 3)
    {
        auto startTime = high_resolution_clock::now();

        dfsResult = graph.DFS(start);

        auto endTime = high_resolution_clock::now();

        dfsTime =
            duration_cast<nanoseconds>(
                endTime - startTime
            ).count();

        cout << "\n========== DFS RESULT ==========\n";

        cout << "DFS Traversal: ";
        graph.displayTraversal(dfsResult);

        cout << "Visited Vertices: "
             << graph.countVisited(dfsResult) << endl;

        cout << "Unvisited Vertices: "
             << vertices - graph.countVisited(dfsResult)
             << endl;

        cout << "Execution Time: "
             << dfsTime << " ns\n";
    }

    // BFS
    if (choice == 2 || choice == 3)
    {
        auto startTime = high_resolution_clock::now();

        bfsResult = graph.BFS(start);

        auto endTime = high_resolution_clock::now();

        bfsTime =
            duration_cast<nanoseconds>(
                endTime - startTime
            ).count();

        cout << "\n========== BFS RESULT ==========\n";

        cout << "BFS Traversal: ";
        graph.displayTraversal(bfsResult);

        cout << "Visited Vertices: "
             << graph.countVisited(bfsResult) << endl;

        cout << "Unvisited Vertices: "
             << vertices - graph.countVisited(bfsResult)
             << endl;

        cout << "Execution Time: "
             << bfsTime << " ns\n";
    }

    // Comparison
    if (choice == 3)
    {
        cout << "\n========================================\n";
        cout << "             COMPARISON                 \n";
        cout << "========================================\n";

        cout << left << setw(20) << "Algorithm"
             << setw(20) << "Visited Nodes"
             << "Time (ns)\n";

        cout << "----------------------------------------\n";

        cout << left << setw(20) << "DFS"
             << setw(20) << dfsResult.size()
             << dfsTime << endl;

        cout << left << setw(20) << "BFS"
             << setw(20) << bfsResult.size()
             << bfsTime << endl;

        cout << "\nPerformance Result:\n";

        if (dfsTime < bfsTime)
            cout << "DFS was faster in this test.\n";
        else if (bfsTime < dfsTime)
            cout << "BFS was faster in this test.\n";
        else
            cout << "Both took the same time.\n";
    }

    // Complexity
    cout << "\n========================================\n";
    cout << "           COMPLEXITY ANALYSIS          \n";
    cout << "========================================\n";

    cout << "DFS Time Complexity : O(V + E)\n";
    cout << "BFS Time Complexity : O(V + E)\n";

    cout << "DFS Space Complexity: O(V)\n";
    cout << "BFS Space Complexity: O(V)\n";

    cout << "\n========================================\n";
    cout << "             PROGRAM ENDED              \n";
    cout << "========================================\n";

    return 0;
}
