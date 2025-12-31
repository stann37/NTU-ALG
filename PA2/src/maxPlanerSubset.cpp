#include "maxPlanerSubset.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void outOfMemHandler()
{
    std::cerr << "Unable to satisfy request for memory\n";
    std::abort();
}

void BackTrack(vector<vector<int>>& idx, int* ch, char** s, int i, int j) {
    if (i >= j) return;
    else if (s[i][j] == -1) {
        BackTrack(idx, ch, s, i, j - 1);
        //cout << "-1\n";
    } else if (s[i][j] == 1) {
        vector<int> vec = {ch[j], j};
        BackTrack(idx, ch, s, ch[j] + 1, j - 1);
        idx.push_back(vec);
        BackTrack(idx, ch, s, i, ch[j] - 1);
        //cout << "1\n";
    } else if (s[i][j] == 2) {
        vector<int> vec = {ch[j], j};
        idx.push_back(vec);
        BackTrack(idx, ch, s, i + 1, j - 1);
        //cout << "2\n";
    }
}

vector<vector<int>> maxPlanerSubset(int n, vector<vector<int>> chords){

    int ch[n];
    for (int i = 0; i < n / 2; i++) {
        ch[chords[i][0]] = chords[i][1];
        ch[chords[i][1]] = chords[i][0];
    }
    std::set_new_handler(outOfMemHandler);
    unsigned short** m = new unsigned short*[n];
    char** s = new char*[n];
    //vector<vector<unsigned short>> m(n, vector<unsigned short>(n, 0));
    //vector<vector<char>> s(n, vector<char>(n, -1));
    for (int i = 0; i < n; i++) {
        m[i] = new unsigned short[n];
        s[i] = new char[n];
        for (int j = 0; j < n; j++) {
            m[i][j] = 0;
            s[i][j] = -1;
        }
    }
    for (int l = 1; l < n; l++) {   //length
        for (int i = 0; i < n - l; i++) {
            int j = i + l;
            int k = ch[j];
            if (k < i or k > j) {
                m[i][j] = m[i][j - 1];
                //s[i][j] = s[i][j - 1];
            } else if (k > i and k < j) {
                if (m[i][j - 1] >= m[i][k - 1] + 1 + m[k + 1][j - 1]) { // > or >=
                    m[i][j] = m[i][j - 1];
                    //s[i][j] = s[i][j - 1];
                } else {
                    m[i][j] = m[i][k - 1] + 1 + m[k + 1][j - 1];
                    s[i][j] = 1;
                }
            } else if (k == i) {
                m[i][j] = m[i][j - 1] + 1;
                s[i][j] = 2;
            }
        }
    }
    //cout << m[0][n - 1];
    //backtracking
    vector<vector<int>> idx;
    BackTrack(idx, ch, s, 0, n - 1);
    
    for (int i = 0; i < n; i++) {
        delete[] m[i];
        delete[] s[i];
    }
    delete[] m;
    delete[] s;

    return idx;
}
