#ifndef _CYCLEBREAKING_H_
#define _CYCLEBREAKING_H_

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>

using namespace std;

struct Edge {
    int u, v, weight;
    Edge(){};
    Edge(int from, int to, int w): u(from), v(to), weight(w){};
    ~Edge(){};
};

class DisjointSet {
    public:
        DisjointSet(int size): parent(size), rank(size, 0) {
            for (int i = 0; i < size; ++i) {
                parent[i] = i;
            }
        }
        ~DisjointSet(){};
        int Find(int u);
        void Union(int u, int v);
    private:
        vector<int> parent;
        vector<int> rank;
};

class Graph {
    public:
        Graph(){};
        Graph(int n_v, int n_e, bool i_d): num_vertices(n_v), num_edges(n_e), is_directed(i_d), edge_removed1(n_e, false), adjList(n_v), tempadjList(n_v){};
        ~Graph(){};
        void AddEdge(int u, int v, int w);
        void SortEdges();
        void PrintEdges();
        void MakeAdjList(); //adjlist that contains edges that are not removed
        void PrintAdjList();
        int Kruskal();   //returns removed weight
        void WriteFile(ofstream& OutputFile);  //for undirected graphs
        bool HasCycleUtil(int v, vector<bool>& visited, vector<bool>& recStack);
        bool HasCycle();
        int AddEdgesBack(); // returns weight of edges that are added back


    private:
        int num_vertices, num_edges;
        bool is_directed;

        vector<Edge> edges;
        vector<bool> edge_removed1;
        vector<vector<pair<int, int>>> adjList;    // u: (v1, w1), (v2, w2); after Kruskal
        vector<vector<pair<int, int>>> tempadjList;
};

#endif