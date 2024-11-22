//
// Created by carri on 21/11/2024.
//

#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int n, m, students, capacities;
vector<int> parent, status;
vector<vector<bool>> inNetwork;
vector<vector<int>> residualCapacity, residualNetwork;

#define INF 100000

#define Discovered 1
#define Discovering 0
#define notDiscovered (-1)
#define noParent (-1)

#define source 0
#define sink ((2*n)+1)
#define iLayer(x) ((x > n && x != sink) ? (x-n) : (x))
#define jLayer(x) ((x < n+1 && x != source) ? (x+n) : (x))

void bfs (vector<vector<int>>& AdjacencyList, const int root) {
    status.assign(2*n+2,notDiscovered);
    parent.assign(2*n+2, noParent);
    /*
     * Empiezo a recorrer desde la raiz.
     */
    status[root] = Discovering;
    queue<int> Q;
    Q.push(root);
    bool breakWhile = false;
    while (!Q.empty()) {
        const int u = Q.front(); Q.pop();
        for (int v : AdjacencyList[u]) {
            if (status[v] == notDiscovered) {
                if (residualCapacity[u][v] > 0) {
                    /*
                     * Discrimino caminos sin capacidad.
                     */
                    status[v] = Discovering;
                    parent[v] = u;
                    if (v == sink) {
                        breakWhile = true;
                        break;
                    }
                    Q.push(v);

                }
            }
        }
        status[u] = Discovered;
        /*
         * Si ya encontre el camino al Sink freno el BFS.
         */
        if (breakWhile) break;

    }
}

int augmentPath () {
    int node = sink;
    int minCapacity = INF;
    while (parent[node] != noParent) {
        /*
         * Busco mínimo del camino de aumento.
         */
        if (residualCapacity[parent[node]][node] < minCapacity) {
            minCapacity = residualCapacity[parent[node]][node];

        }
        node = parent[node];

    }

    node = sink;
    residualCapacity[node][parent[node]] += minCapacity;
    residualCapacity[parent[node]][node] -= minCapacity;
    node = parent[node];

    while (parent[node] != noParent) {
        /*
         * Actualizo la red residual.
         */
        if (inNetwork[iLayer(parent[node])][iLayer(node)]) {
            residualCapacity[node][parent[node]] += minCapacity;
            residualCapacity[parent[node]][node] -= minCapacity;

        } else {
            residualCapacity[parent[node]][node] += minCapacity;
            residualCapacity[node][parent[node]] -= minCapacity;

        }
        node = parent[node];

    }
    /*
     * Retorno lo que debo aumentar al flujo.
     */
    return minCapacity;

}

int FFEK (vector<vector<int>>& AdjacencyList) {
    int maxFlow = 0;
    while (true) {
        bfs(AdjacencyList, source);
        /*
         * Me fijo si hay camino de aumento.
         */
        if (parent[sink] == noParent) break;
        const int flow = augmentPath();
        /*
         * Aumento el flujo
         */
        maxFlow += flow;

    }
    return maxFlow;
}

int main () {
    cin >> n >> m;
    /*
     * Matrices inNetwork (binaria) y residualCapacity, para operar en O(1).
     */
    residualCapacity.assign(2*n+2, vector<int>(2*n+2, 0));
    inNetwork.assign(n+2, vector<bool>(n+2, false));
    /*
     * Lista de adyacencia de la red residual:
     *       Posición [0] es Source y [2n+1] es Sink.
     *       Posición [i], 1 <= i <= n corresponde primera Layer.
     *       Posición [j], n+1 <= j <= 2n corresponde a segunda Layer.
     */
    residualNetwork.assign(2*n+2, vector<int>());
    students = 0;
    for (int i = 1; i <= n; i++) {
        /*
         * Asignación original de aulas.
         */
        int a; cin >> a;
        inNetwork[source][i] = true;
        residualCapacity[source][iLayer(i)] = a;
        residualNetwork[i].push_back(source);
        residualNetwork[source].push_back(iLayer(i));
        students += a;
        /*
         * Posibilidad de que no sean cambiados de aula.
         */
        inNetwork[i][i] = true;
        residualCapacity[iLayer(i)][jLayer(i)] = a;
        residualNetwork[iLayer(i)].push_back(jLayer(i));
        residualNetwork[jLayer(i)].push_back(iLayer(i));

    }
    capacities = 0;
    for (int j = 1; j <= n; j++) {
        /*
         * Capacidad de las aulas.
         */
        int b; cin >> b;
        inNetwork[j][n+1] = true;
        residualCapacity[jLayer(j)][sink] = b;
        residualNetwork[sink].push_back(jLayer(j));
        residualNetwork[jLayer(j)].push_back(sink);
        capacities += b;

    }
    for (int k = 0; k < m; k++) {
        /*
         * Posibles cambios de aulas.
         */
        int i, j; cin >> i >> j;
        inNetwork[i][j] = true;
        inNetwork[j][i] = true;
        residualCapacity[iLayer(i)][jLayer(j)] = residualCapacity[source][iLayer(i)];
        residualCapacity[iLayer(j)][jLayer(i)] = residualCapacity[source][iLayer(j)];
        residualNetwork[iLayer(i)].push_back(jLayer(j));
        residualNetwork[iLayer(j)].push_back(jLayer(i));

    }
    if (students != capacities) {
        cout << "NO" << endl;

    } else {
        const int maxFlow = FFEK(residualNetwork);
        if (maxFlow != students) {
            cout << "NO" << endl;

        } else {
            cout << "YES" << endl;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    cout << residualCapacity[jLayer(j)][iLayer(i)] << " ";

                }
                cout << endl;
            }
        }
    }

    return 0;

}
