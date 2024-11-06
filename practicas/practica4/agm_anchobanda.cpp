//
// Created by carri on 6/11/2024.
//
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 1000000000
#define all(x) (x).begin(), (x).end()
using namespace std;

int N, M, k;
struct Edge {int u; int v; int w;};
vector<Edge> edges;

class DisjointSet {
    vector<int> parent;
    vector<int> rank;

public:
    explicit DisjointSet(const int n) {
        parent.reserve(n);
        rank.reserve(n);
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
            rank.push_back(0);

        }
    }

    int FindSet(const int x) {
        if (parent[x] != x) parent[x] = FindSet(parent[x]);
        return parent[x];

    }

    void Link (const int x, const int y) {
        if (rank[x] > rank[y]) {
            parent[y] = x;

        } else {
            parent[x] = y;
            if (rank[x] == rank[y]) rank[y]++;

        }
    }

    void Union (const int x, const int y) {
        Link(FindSet(x), FindSet(y));

    }
};

bool compareByWeight(const Edge& a, const Edge& b) { return a.w > b.w; }
void Kruskal (vector<Edge>& edges) {
    /*
     * Algoritmo de Kruskal para AGMáx
     */
    sort(all(edges), compareByWeight);
    DisjointSet DS (N);
    for (const Edge& edge : edges) {
        if (DS.FindSet(edge.u) != DS.FindSet(edge.v)) {
            DS.Union(edge.u, edge.v);
            if (edge.w < k) k = edge.w;

        }
    }
}

int main () {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        Edge edge{};
        cin >> edge.u >> edge.v >> edge.w;
        edge.u--; edge.v--;
        edges.push_back(edge);

    }
    k = INF;
    Kruskal(edges);
    cout << k << endl;
    return 0;

}
