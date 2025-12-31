#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "maxPlanerSubset.h"

using namespace std;

void help_message() {
    cout << "usage: mps <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
       help_message();
       return 0;
    }
    ////read inputs--------------------------------------------------------------------------
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }
    int n;
    inputFile >> n;
    vector<vector<int>> chords(n/2, vector<int>(2));
    for (int i = 0; i < n/2; ++i) {
        inputFile >> chords[i][0] >> chords[i][1];
    }
    inputFile.close();

    ////maxPlanerSubset----------------------------------------------------------------------
    vector<vector<int>> idx;    //pairs of chords selected
    idx = maxPlanerSubset(n, chords);

    ////output-------------------------------------------------------------------------------
    ofstream outputFile(argv[2]);

    if (!outputFile.is_open()) {    //check output file is open
        cerr << "Error opening output file." << endl;
        return 1;
    }
    outputFile << idx.size() << endl;
    sort(idx.begin(), idx.end());
    for (std::vector<std::vector<int>>::size_type i = 0; i < idx.size(); i++) {
        outputFile << idx[i][0] << " " << idx[i][1] << endl;
    }
    
    outputFile.close();
    return 0;
}