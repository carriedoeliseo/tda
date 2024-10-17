//
// Created by carri on 16/10/2024.
//
#include <iostream>
#include <vector>
#define INF 1000000000
using namespace std;
int N;
vector<int> shortcut;
vector<vector<int>> edges, tree_edges;

class DisjointSets {

vector<int> parent;
vector<int> rank;

public:
    explicit DisjointSets(const int n) {
        parent.resize(n);
        rank.resize(n);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;

        }
    }

    int find_set (const int v) {
        if (v != parent[v]) {
            parent[v] = find_set(parent[v]);

        }
        return parent[v];

    }

    void link (const int v, const int w) {
        if (rank[v] > rank[w]) {
            parent[w] = v;

        }
        else {
            parent[v] = w;
            if (rank[v] == rank[w]) {
                rank[w]++;

            }
        }
    }

    void unite_set (const int v, const int w) {
        link(find_set(v), find_set(w));

    }
};

int weigth (const int v, const int w) {
    if (shortcut[v] == w) return 1;
    return abs(v-w);

}



int main () {
    cin >> N;
    shortcut.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> shortcut[i];

    }
    tree_edges.assign(N, vector<int>());
    return 0;
}