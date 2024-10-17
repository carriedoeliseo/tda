//
// Created by carri on 15/10/2024.
//

#include <iostream>
#include <vector>
#define white (-1)
#define gray 0
#define black 1
using namespace std;

long long N, even_odd[2];
vector<int> color;
vector<vector<int>> adjacency;

void dfs (const int v,const int mod2) {
    color[v] = gray;
    even_odd[mod2]++;
    for (const int u : adjacency[v]) {
        if (color[u] == white) {
            dfs(u, 1-mod2);

        }
    }
    color[v] = black;

}

int main () {
    cin >> N;
    color.assign(N, white);
    adjacency.resize(N);
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        adjacency[u-1].push_back(v-1);
        adjacency[v-1].push_back(u-1);

    }
    dfs(0, 0);
    const long long sol = (even_odd[0]*even_odd[1]) - (N-1);
    cout << sol << endl;
    return 0;

}

