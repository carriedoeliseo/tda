//
// Created by carri on 21/11/2024.
//

#include <queue>
#include <vector>
#include <iostream>

int n, m;
long long students, capacities;
std::vector<int> parent, status;
std::vector<std::vector<bool>> inNetwork;
std::vector<std::vector<int>> residualCapacity, residualNetwork;

#define infinity 100000

#define Discovered 1
#define Discovering 0
#define notDiscovered (-1)
#define noParent (-1)

#define source 0
#define sink ((2*n)+1)
#define iLayer(x) ((x > n && x != sink) ? (x-n) : (x))
#define jLayer(x) ((x < n+1 && x != source) ? (x+n) : (x))

void bfs (std::vector<std::vector<int>>& AdjacencyList, const int root) {
    status.assign(2*n+2,notDiscovered);
    parent.assign(2*n+2, noParent);
    /*
     * Empiezo a recorrer desde la raiz.
     */
    status[root] = Discovering;
    std::queue<int> Q;
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

long long augmentPath () {
    int node = sink;
    long long minCapacity = infinity;
    while (parent[node] != noParent) {
        /*
         * Busco mínimo del camino de aumento.
         */
        if (residualCapacity[parent[node]][node] < minCapacity) {
            minCapacity = residualCapacity[parent[node]][node];

        }
        node = parent[node];

    }
    /*
     * Actualizo red residual en el sumidero.
     */
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

long long FFEK (std::vector<std::vector<int>>& AdjacencyList) {
    long long maxFlow = 0;
    while (true) {
        bfs(AdjacencyList, source);
        /*
         * Me fijo si hay camino de aumento.
         */
        if (parent[sink] == noParent) break;
        const long long flow = augmentPath();
        /*
         * Aumento el flujo
         */
        maxFlow += flow;

    }
    return maxFlow;

}

int main () {
    std::cin >> n >> m;
    /*
     * Matrices inNetwork (binaria) y residualCapacity.
     */
    residualCapacity.assign(2*n+2, std::vector<int>(2*n+2, 0));
    inNetwork.assign(n+2, std::vector<bool>(n+2, false));
    /*
     * Lista de adyacencia de la red residual:
     *       Posición [0] es Source y [2n+1] es Sink.
     *       Posición [i], 1 <= i <= n corresponde primera Layer.
     *       Posición [j], n+1 <= j <= 2n corresponde a segunda Layer.
     */
    residualNetwork.assign(2*n+2, std::vector<int>());
    students = 0;
    for (int i = 1; i <= n; i++) {
        /*
         * Asignación original de aulas.
         */
        int a; std::cin >> a;
        inNetwork[source][i] = true;
        residualCapacity[source][iLayer(i)] = a;
        residualNetwork[i].push_back(source);
        residualNetwork[source].push_back(iLayer(i));
        students += a;
        /*
         * Posibilidad de que no sean cambiados de aula.
         */
        inNetwork[i][i] = true;
        residualCapacity[iLayer(i)][jLayer(i)] = infinity;
        residualNetwork[iLayer(i)].push_back(jLayer(i));
        residualNetwork[jLayer(i)].push_back(iLayer(i));

    }
    capacities = 0;
    for (int j = 1; j <= n; j++) {
        /*
         * Capacidad de las aulas.
         */
        int b; std::cin >> b;
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
        int i, j; std::cin >> i >> j;
        inNetwork[i][j] = true;
        inNetwork[j][i] = true;
        residualCapacity[iLayer(i)][jLayer(j)] = infinity;
        residualCapacity[iLayer(j)][jLayer(i)] = infinity;
        residualNetwork[iLayer(i)].push_back(jLayer(j));
        residualNetwork[iLayer(j)].push_back(jLayer(i));
        residualNetwork[jLayer(i)].push_back(iLayer(j));
        residualNetwork[jLayer(j)].push_back(iLayer(i));

    }
    if (students != capacities) {
        std::cout << "NO" << std::endl;

    } else {
        const long long maxFlow = FFEK(residualNetwork);
        if (maxFlow != students) {
            std::cout << "NO" << std::endl;

        } else {
            std::cout << "YES" << std::endl;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    std::cout << residualCapacity[jLayer(j)][iLayer(i)] << " ";

                }
                std::cout << std::endl;

            }
        }
    }

    return 0;

}