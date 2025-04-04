#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

class Graph
{
public:
    int V;
    vector<vector<int>> adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

void parallelBFS(Graph &graph, int start) {
    vector<bool> visited(graph.V, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph.adj[u].size(); i++)
        {
            int v = graph.adj[u][i];
            if (!visited[v]) {
                #pragma omp critical
                {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
}

void parallelDFS(Graph &graph, int start) {
    vector<bool> visited(graph.V, false);
    stack<int> s;
    s.push(start);

    while (!s.empty())
    {
        int u = s.top();
        s.pop();
        if (!visited[u]) {
            visited[u] = true;
            cout << u << " ";

            #pragma omp parallel for
            for (int i = 0; i < graph.adj[u].size(); i++) {
                int v = graph.adj[u][i];
                if (!visited[v]) {
                    #pragma omp critical
                    s.push(v);
                }
            }
        }
    }
}

int main() {
    Graph graph(4);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);

    cout << "Parallel BFS: ";
    parallelBFS(graph, 0);
    cout << endl;

    cout << "Parallel DFS: ";
    parallelDFS(graph, 0);
    cout << endl;

    return 0;
}

