#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "CycleBreaking.h"

using namespace std;

/*
DisjointSet::DisjointSet(int size): parent(size), rank(size, 0) {
    for (int i = 0; i < size; ++i) {
        parent[i] = i;
    }
}*/

int DisjointSet::Find(int u) {
    if (parent[u] != u) {
        parent[u] = Find(parent[u]); // Path compression
    }
    return parent[u];
}

void DisjointSet::Union(int u, int v) {
    int rootU = Find(u);
    int rootV = Find(v);

    if (rootU != rootV) {
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

//-------------------------------------------------------------------------------------------------

void Graph::AddEdge(int u, int v, int w) {
    edges.push_back(Edge(u, v, w));
}

void Graph::SortEdges() {
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.weight > b.weight; //descending order
    });
}

void Graph::PrintEdges() {
    for (const Edge &edge : edges) {
        cout << "Edge: " << edge.u << " - " << edge.v << " Weight: " << edge.weight << endl;
    }
}

void Graph::PrintAdjList() {
    for (int i = 0; i < num_vertices; i++) {
        for (const auto &edge : adjList[i]) {
            cout << "(" << edge.first << ", " << edge.second << ") "; // Print adjacent vertex and weight
        }
        cout << endl;
    }
}

void Graph::MakeAdjList() {
    for (int i = 0; i < num_edges; i++) {
        if (!edge_removed1[i]) {
            adjList[edges[i].u].push_back(make_pair(edges[i].v, edges[i].weight));
        }
    }
}

int Graph::Kruskal() {
    DisjointSet s(num_vertices);
    int removed_weight = 0;
    for (int i = 0; i < num_edges; i++) {
        if (s.Find(edges[i].u) != s.Find(edges[i].v)) {
            s.Union(edges[i].u, edges[i].v);
        } else {
            edge_removed1[i] = true;
            removed_weight += edges[i].weight;
        }
    }
    return removed_weight;
}

void Graph::WriteFile(ofstream& OutputFile) {
    int test = 0;
    for (int i = 0; i < num_edges; i++) {
        if (edge_removed1[i]) {
            OutputFile << edges[i].u << " " << edges[i].v << " " << edges[i].weight << endl;
            test += edges[i].weight;
        }
    }
    //OutputFile << "test: " << test;
}

bool Graph::HasCycleUtil(int v, vector<bool>& visited, vector<bool>& recStack) {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        for (auto& neighbor : tempadjList[v]) {
            int u = neighbor.first;
            if (!visited[u] && HasCycleUtil(u, visited, recStack))
                return true;
            else if (recStack[u])
                return true;
        }
    }

    recStack[v] = false;
    return false;
}

bool Graph::HasCycle() {
    vector<bool> visited(num_vertices, false);
    vector<bool> recStack(num_vertices, false);

    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i] && HasCycleUtil(i, visited, recStack))
            return true;
    }
    return false;
}

int Graph::AddEdgesBack() {
    int added_weight = 0;
    for (int i = 0; i < num_edges; i++) {
        if (edges[i].weight >= 0 and edge_removed1[i]) {
            tempadjList = adjList;
            tempadjList[edges[i].u].push_back(make_pair(edges[i].v, edges[i].weight));
            if (!HasCycle()) {
                adjList[edges[i].u].push_back(make_pair(edges[i].v, edges[i].weight));
                edge_removed1[i] = false;
                added_weight += edges[i].weight;
            } else {
                //cout << "Has Cycle at: " << i << endl;
                tempadjList = adjList;
            }
        }
        else if (edges[i].weight < 0) break;
    }
    return added_weight;
}