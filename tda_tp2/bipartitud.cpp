//
// Created by carri on 15/10/2024.
//

#include <iostream>
#include <vector>
using namespace std;

int N, even_odd[2];
vector<int> color;
vector<vector<int>> adjacency;

void dfs (const int v,const int mod2) {
    color[v] = 0;
    even_odd[mod2]++;
    for (const int u : adjacency[v]) {
        if (color[u] == -1) {
            dfs(u, 1-mod2);

        }
    }
    color[v] = 1;

}

int main () {
    cin >> N;
    color.assign(N, -1);
    adjacency.resize(N);
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        adjacency[u-1].push_back(v-1);
        adjacency[v-1].push_back(u-1);

    }
    dfs(0, 0);
    const int sol = (even_odd[0]*even_odd[1]) - (N-1);
    cout << sol << endl;
    return 0;

}

