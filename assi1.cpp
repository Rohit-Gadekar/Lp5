#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

class Graph
{
    int V;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V) : V(V), adj(V) {}

    // Add an edge to the graph
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Parallel Depth-First Search
    void parallelDFS(int startVertex)
    {
        vector<bool> visited(V, false);
        parallelDFSUtil(startVertex, visited);
    }

    // Parallel DFS utility function
    void parallelDFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

#pragma omp parallel for
        for (int i = 0; i < adj[v].size(); i++)
        {
            int curr = adj[v][i];
            if (!visited[curr])
                parallelDFSUtil(curr, visited);
        }
    }

    void sequentialDFS(int startVertex)
    {
        vector<bool>visited(V, false);
        sequentialDFSUtil(startVertex, visited);
    }

    void sequentialDFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < adj[v].size(); i++)
        {
            int curr = adj[v][i];
            if (!visited[curr])
                parallelDFSUtil(curr, visited);
        }
    }

    // Parallel Breadth-First Search
    void parallelBFS(int startVertex)
    {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";

#pragma omp parallel for
            for (int i = 0; i < adj[v].size(); ++i)
            {
                int curr = adj[v][i];
                if (!visited[curr])
                {
                    visited[curr] = true;
                    q.push(curr);
                }
            }
        }
    }

    void sequentialBFS(int startVertex)
    {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int i = 0; i < adj[v].size(); ++i)
            {
                int curr = adj[v][i];
                if (!visited[curr])
                {
                    visited[curr] = true;
                    q.push(curr);
                }
            }
        }
    }
};

int main()
{
    int choice;
    int V, E;
    int startVertex;
    double start_time, end_time;

    Graph g(0); // Initialize with 0 vertices initially

    while (true)
    {
        cout << "Menu:\n";
        cout << "1. Create graph\n";
        cout << "2. Perform Breadth-First Search (BFS)\n";
        cout << "3. Perform Depth-First Search (DFS)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the number of vertices: ";
            cin >> V;
            g = Graph(V);
            cout << "Enter the number of edges: ";
            cin >> E;
            cout << "Enter the edges (source and destination vertices):\n";
            for (int i = 0; i < E; ++i)
            {
                int src, dest;
                cin >> src >> dest;
                g.addEdge(src, dest);
            }
            break;
        case 2:
            cout << "Enter the start vertex for BFS: ";
            cin >> startVertex;

            start_time = omp_get_wtime();
            cout << "Parallel Breadth-First Search (BFS): ";
            g.parallelBFS(startVertex);
            end_time = omp_get_wtime();
            cout<<"Parallel duration: "<< end_time-start_time<<endl;
            cout << endl;

            start_time = omp_get_wtime();
            cout << "Sequential Breadth-First Search (BFS): ";
            g.sequentialBFS(startVertex);
            end_time = omp_get_wtime();
            cout<<"Sequential duration: "<< end_time-start_time<<endl;
            cout << endl;

            break;
        case 3:
            cout << "Enter the start vertex for DFS: ";
            cin >> startVertex;

            start_time = omp_get_wtime();
            cout << "Parallel Depth-First Search (DFS): ";
            g.parallelDFS(startVertex);
            end_time = omp_get_wtime();
            cout<<"Parallel Duration DFS: "<<end_time-start_time<<endl;
            cout << endl;

            start_time = omp_get_wtime();
            cout << "Sequential Depth-First Search (DFS): ";
            g.sequentialDFS(startVertex);
            end_time = omp_get_wtime();
            cout<<"Sequential Duration DFS: "<<end_time-start_time<<endl;
            cout << endl;
            break;
        case 4:
            cout << "Exiting\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


/*

Here's what the #pragma omp parallel for directive does:

#pragma omp: This is a pragma directive that indicates to the compiler that what follows is an OpenMP 
directive.

parallel: This keyword starts a parallel region, which means that the code enclosed by this 
pragma will be executed by multiple threads in parallel. Each thread will execute the code 
within the parallel region.

for: This keyword indicates that the following loop should be executed in parallel. 
OpenMP will automatically distribute the iterations of the loop among the available threads.

*/  