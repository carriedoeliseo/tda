//
// Created by carri on 16/10/2024.
//
#include <vector>
#include <iostream>
#include <algorithm>
#define all(x) x.begin(), x.end()
using namespace std;
int V, E;
struct Edge {int u = -1; int v = -1; int weight = -1; int index = -1;};
vector<Edge> edges;
vector<string> MST;
vector<int> status, parent, cover;
vector<vector<int>> MSTAdjacency;

// DISJOINT SET ========================================================================================================

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

// BRIDGES =============================================================================================================

void dfs (const int v, const int p) {
    status[v] = 0;
    for (const int u : MSTAdjacency[v]) {
        if (parent[u] != v) {
            if (status[u] == -1) {
                parent[u] = v;
                dfs(u, v);

            } else if (u != p) {
                if (status[u] == 0) {
                    cover[u]--;
                    cover[v]++;

                }
            }
        } else {
            cover[u]++;

        }
    }
    if (p != -1) cover[p] += cover[v];
    status[v] = 1;

}

void bridges(vector<int>& references) {
    cover.assign(V, 0);
    parent.assign(V, -1);
    status.assign(V, -1);
    for (const int& ref : references) {
        if (status[ref] == -1) {
            dfs(ref, -1);

        }
    }
}

// KRUSKAL =============================================================================================================

bool compareByWeight(const Edge& a, const Edge& b) { return a.weight < b.weight; }
bool compareByIndex(const Edge& a, const Edge& b) { return a.index < b.index; }

void kruskal (DisjointSet& DS, vector<Edge>& edges) {
    sort(all(edges), compareByWeight);
    MSTAdjacency.assign(V, vector<int>());
    int MSTEdges = 0;
    for (int i = 0; i < E; i++) {
        if (edges[i].weight == edges[i+1].weight) {

            const int first = i;
            while (edges[i].weight == edges[i+1].weight) i++;
            const int last = i;

            vector<int> uRefs; uRefs.reserve(last-first+1);
            vector<int> vRefs; vRefs.reserve(last-first+1);

            for (int j = first; j <= last; j++) {
                const int uRef = DS.FindSet(edges[j].u);
                const int vRef = DS.FindSet(edges[j].v);
                if (uRef != vRef) {
                    MST[edges[j].index] = "at least one";
                    MSTAdjacency[uRef].push_back(vRef);
                    MSTAdjacency[vRef].push_back(uRef);

                }
                uRefs.push_back(uRef);
                vRefs.push_back(vRef);

            }

            bridges(uRefs);

            for (int j = first; j <= last; j++) {
                if (uRefs[j-first] != vRefs[j-first]) {
                    DS.Union(edges[j].u, edges[j].v);
                    MSTAdjacency[edges[j].u].clear();
                    MSTAdjacency[edges[j].v].clear();
                    if (parent[uRefs[j-first]] == vRefs[j-first]) {
                        if (cover[uRefs[j-first]] == 0) {
                            MST[edges[j].index] = "any";

                        }
                    }
                    else if (parent[vRefs[j-first]] == uRefs[j-first]) {
                        if (cover[vRefs[j-first]] == 0) {
                            MST[edges[j].index] = "any";

                        }
                    }
                }
            }
        }
        else if (DS.FindSet(edges[i].u) != DS.FindSet(edges[i].v)) {
            MST[edges[i].index] = "any";
            DS.Union(edges[i].u, edges[i].v);

        }
        MSTEdges++;
        if (MSTEdges == V-1) break;

    }
}

// MAIN ================================================================================================================

int main () {
    cin >> V >> E;
    edges.reserve(E);
    MST.assign(E, "none");
    DisjointSet DS (V);
    for (int i = 0; i < E; i++) {
        Edge edge;
        cin >> edge.u >> edge.v >> edge.weight;
        edge.u--; edge.v--; edge.index = i;
        edges.push_back(edge);

    }
    kruskal (DS, edges);
    for (string& mst : MST) {
        cout << mst << endl;

    }

    return 0;

}
