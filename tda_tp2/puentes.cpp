//
// Created by carri on 30/10/2024.
//
#include <vector>
#include <iostream>
using namespace std;
int V;
vector<int> parent, cover, status;
vector<vector<int>> adjacency;

void dfs (const int v, const int p) {
    status[v] = 0; cover[v] = 0;
    for (const int u : adjacency[v]) {
        if (status[u] == -1) {
            parent[u] = v;
            dfs(u, v);

        } else if (u != p) {
            if (status[u] == 0) {
                cover[u]--;
                cover[v]++;

            }
        }
    }
    status[v] = 1; cover[p] += cover[v];

}

int main() {
    cin >> V; adjacency.assign(V, vector<int>());
    for (int i = 0; i < V; i++) {
        adjacency[i].reserve(V-1);
        int vi;
        while (true) {
            cin >> vi; if (vi == -1) break;
            adjacency[i].push_back(vi-1);

        }
    }
    parent.assign(V, -1);
    cover.assign(V, -1);
    status.assign(V, -1);
    dfs(0, -1);
    for (int i = 0; i < V; i++) {
        cout << cover[i] << endl;

    }

}