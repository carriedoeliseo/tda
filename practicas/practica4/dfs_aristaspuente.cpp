#include <iostream>
#include <vector>

using namespace std;

vector<int> estado, memo, backEdgeSup, backEdgeInf;
vector<int> aristas [100], treeEdges [100];

void dfs (int v, int p = -1) {
    estado[v] = 0;
    for (int u : aristas[v]) {
        if (estado[u] == -1) {
            treeEdges[v].push_back(u);
            dfs(u, v);

        } else if (estado[u] == 1) {
            backEdgeSup[v]++;
            backEdgeInf[u]++;

        }
    }
    estado[v] = 1;

}

int cubren (int v) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    res += backEdgeInf[v];
    res -= backEdgeSup[v];
    for (int hijo : treeEdges[v]) {
        res += cubren(hijo);

    }
    memo[v] = res;
    return res;

}

int main () {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        vector<int> ady; ady.reserve(n);
        int nh;
        while (cin >> nh && nh != -1) {
            ady.push_back(nh-1);

        }
        aristas[i] = ady;

    }
    for (int i = 0; i < n; i++) {
        vector<int> treeAdy; treeAdy.reserve(n);
        treeEdges[i] = treeAdy;

    }
    memo.assign(n, -1);
    estado.assign(n, -1); 
    backEdgeInf.assign(n, 0); 
    backEdgeSup.assign(n, 0);
    dfs(0);
    int puentes = 0;
    for (int i = 0; i < n; i++) {
        if (cubren(i) == 0) {
            puentes++;

        }
    }
    cout << puentes-1 << endl;
    return 0;

}

