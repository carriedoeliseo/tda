//
// Created by carri on 16/10/2024.
//
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int N;
vector<int> state, d;
vector<vector<int>> adjacency;

void bfs (vector<vector<int>>& G, const int s) {
    state[s] = 0;
    d[s] = 0;
    queue<int> queue;
    queue.push(s);
    while (queue.empty() == false) {
        const int u = queue.front(); queue.pop();
        for (int v : G[u]) {
            if (v != -1 && state[v] == -1) {
                state[v] = 0;
                d[v] = d[u] + 1;
                queue.push(v);

            }
        }
        state[s] = 1;

    }
}

int main() {
    cin >> N;
    d.assign(N, -1);
    state.assign(N, -1);
    adjacency.assign(N, vector<int>(3, -1));
    for (int i = 0; i < N; i++) {
        int shortcut; cin >> shortcut;
        adjacency[i][0] = shortcut-1;
        adjacency[i][1] = i+1;
        if (i != 0) adjacency[i][2] = i-1;

    }
    bfs(adjacency, 0);
    for (int i = 0; i < N; i++) {
        cout << d[i] << " ";

    }
    return 0;

}