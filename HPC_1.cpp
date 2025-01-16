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
    vector<vector<int> > adj;

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

    #pragma omp parallel
    {
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";
            
            #pragma omp for
            for (int v : graph.adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

void parallelDFS(Graph &graph, int start) {
    vector<bool> visited(graph.V, false);
    stack<int> s;
    s.push(start);

    #pragma omp parallel
    {
        while (!s.empty()) {
            int u = s.top();
            s.pop();
            if (!visited[u]) {
                visited[u] = true;
                cout << u << " ";
                
                #pragma omp for
                for (int v : graph.adj[u]) {
                    if (!visited[v]) {
                        s.push(v);
                    }
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
