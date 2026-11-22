
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Prim's Algorithm
int Prim(int start, vector<vector<pair<int, int>>>& graph,
         vector<pair<int, int>>& mstEdges)
{
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    vector<bool> visited(graph.size(), false);

    pq.push({0, start});

    int totalWeight = 0;
    int visitedCount = 0;

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        visitedCount++;
        totalWeight += weight;

        // Store selected MST edge
        if (weight != 0)
            mstEdges.push_back({u, weight});

        // Check adjacent vertices
        for (auto edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (!visited[v])
                pq.push({w, v});
        }
    }

    if (visitedCount != (int)graph.size())
        return -1;

    return totalWeight;
}

int main()
{
    int n, e;

    cout << "\n========================================\n";
    cout << "       PRIM'S MST ALGORITHM             \n";
    cout << "========================================\n";

    // Input vertices
    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid number of vertices!\n";
        return 1;
    }

    vector<vector<pair<int, int>>> graph(n);

    // Input edges
    cout << "\nEnter number of edges: ";
    cin >> e;

    if (cin.fail() || e < 0)
    {
        cout << "Invalid number of edges!\n";
        return 1;
    }

    cout << "\nEnter edges (source destination weight):\n";

    for (int i = 0; i < e; i++)
    {
        int u, v, w;

        cin >> u >> v >> w;

        if (cin.fail() || u < 0 || u >= n ||
            v < 0 || v >= n || u == v)
        {
            cout << "Invalid edge input!\n";
            return 1;
        }

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    // Display graph
    cout << "\n========================================\n";
    cout << "             GRAPH EDGES                \n";
    cout << "========================================\n";

    cout << left << setw(15) << "Source"
         << setw(15) << "Destination"
         << "Weight\n";

    cout << "----------------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        for (auto edge : graph[i])
        {
            if (i < edge.first)
            {
                cout << left << setw(15) << i
                     << setw(15) << edge.first
                     << edge.second << endl;
            }
        }
    }

    // Starting vertex
    int start;

    cout << "\nEnter starting vertex (0 to "
         << n - 1 << "): ";

    cin >> start;

    if (cin.fail() || start < 0 || start >= n)
    {
        cout << "Invalid starting vertex!\n";
        return 1;
    }

    // Run Prim's Algorithm
    vector<pair<int, int>> mstEdges;

    auto startTime = high_resolution_clock::now();

    int totalWeight = Prim(start, graph, mstEdges);

    auto endTime = high_resolution_clock::now();

    auto executionTime =
        duration_cast<nanoseconds>(
            endTime - startTime
        ).count();

    // Display MST
    cout << "\n========================================\n";
    cout << "       MINIMUM SPANNING TREE             \n";
    cout << "========================================\n";

    if (totalWeight == -1)
    {
        cout << "MST cannot be formed!\n";
        cout << "The graph is disconnected.\n";
    }
    else
    {
        cout << left << setw(15) << "Vertex"
             << "Edge Weight\n";

        cout << "----------------------------------------\n";

        for (auto edge : mstEdges)
        {
            cout << left << setw(15) << edge.first
                 << edge.second << endl;
        }

        cout << "\nTotal MST Weight: "
             << totalWeight << endl;

        cout << "Number of MST Edges: "
             << mstEdges.size() << endl;
    }

    // Execution time
    cout << "\n========================================\n";
    cout << "          PERFORMANCE RESULT            \n";
    cout << "========================================\n";

    cout << "Execution Time: "
         << executionTime << " ns\n";

    // Complexity
    cout << "\n========================================\n";
    cout << "          COMPLEXITY ANALYSIS           \n";
    cout << "========================================\n";

    cout << "Time Complexity  : O(E log V)\n";
    cout << "Space Complexity : O(V + E)\n";

    cout << "\n========================================\n";
    cout << "              PROGRAM ENDED             \n";
    cout << "========================================\n";

    return 0;
}
