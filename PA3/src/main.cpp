#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "CycleBreaking.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    if(argc != 3) {
        cerr << "Invalid Usage!" << endl;
        cerr << "usage: ./cb <input_file> <output_file>" << endl;
        return 0;
    }

    int num_vertices, num_edges;
    bool is_directed;
    char graph_type;

    // read input ---------------------------------------------------
    ifstream InputFile(argv[1]);
    InputFile >> graph_type >> num_vertices >> num_edges;
    is_directed = (graph_type == 'd');

    Graph G(num_vertices, num_edges, is_directed);
    int from, to, weight;
    for (int i = 0; i < num_edges; i++) {
        InputFile >> from >> to >> weight;
        G.AddEdge(from, to, weight);
        
    }
    int zero;
    InputFile >> zero;
    InputFile.close();

    // solve --------------------------------------------------------
    if (!is_directed) {
        G.SortEdges();
        //G.PrintEdges();
        ofstream OutputFile(argv[2]);
        OutputFile << G.Kruskal() << endl;
        G.WriteFile(OutputFile);
        OutputFile.close();
    } else {
        
        G.SortEdges();
        //  Kruskal and then add edges back?
        int rm_weight = G.Kruskal();
        G.MakeAdjList();    //adjlist after Kruskal
        //G.PrintAdjList();
        //cout << G.HasCycle() << endl;
        rm_weight -= G.AddEdgesBack();
        ofstream OutputFile(argv[2]);
        OutputFile << rm_weight << endl;
        G.WriteFile(OutputFile);
        OutputFile.close();
    }
    return 0;
}