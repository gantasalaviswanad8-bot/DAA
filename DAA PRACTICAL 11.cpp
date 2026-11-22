
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

#define INF 99999

void floydWarshall(vector<vector<int>>& graph, int n)
{
    vector<vector<int>> dist = graph;

    // Floyd-Warshall Algorithm
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] =
                        dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Display shortest distance matrix
    cout << "\n====================================\n";
    cout << "       SHORTEST DISTANCE MATRIX      \n";
    cout << "====================================\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
                cout << setw(8) << "INF";
            else
                cout << setw(8) << dist[i][j];
        }

        cout << endl;
    }

    // Negative cycle detection
    bool negativeCycle = false;

    for (int i = 0; i < n; i++)
    {
        if (dist[i][i] < 0)
        {
            negativeCycle = true;
            break;
        }
    }

    cout << "\nNegative Cycle: ";

    if (negativeCycle)
        cout << "Detected\n";
    else
        cout << "Not Detected\n";
}

int main()
{
    int n;

    cout << "====================================\n";
    cout << "       FLOYD WARSHALL ALGORITHM      \n";
    cout << "====================================\n";

    // Input number of vertices
    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid number of vertices!\n";
        return 1;
    }

    vector<vector<int>> graph(n, vector<int>(n));

    // Input adjacency matrix
    cout << "\nEnter adjacency matrix:\n";
    cout << "(Enter " << INF << " for no direct edge)\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];

            if (cin.fail())
            {
                cout << "Invalid matrix input!\n";
                return 1;
            }
        }
    }

    // Display original matrix
    cout << "\nOriginal Cost Matrix:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                cout << setw(8) << "INF";
            else
                cout << setw(8) << graph[i][j];
        }

        cout << endl;
    }

    // Apply Floyd-Warshall
    floydWarshall(graph, n);

    // Complexity
    cout << "\n====================================\n";
    cout << "          COMPLEXITY ANALYSIS       \n";
    cout << "====================================\n";

    cout << "Time Complexity  : O(V^3)\n";
    cout << "Space Complexity : O(V^2)\n";

    cout << "\n====================================\n";
    cout << "             PROGRAM ENDED          \n";
    cout << "====================================\n";

    return 0;
}
