//
// Created by carri on 4/11/2024.
//

#include <algorithm>
#include <iostream>
#include <vector>
#define INF 1000000000
#define all(x) (x).begin(), (x).end()
using namespace std;
struct Coord {int x; int y;};
struct Edge {int u; int v; int w;};
int N, k;
int KruskalMSTWeight, KnMSTWeight;
vector<Edge> Edges;
vector<vector<int>> Sequences, AdjacencyList, AdjacencyMatrix;

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

int matrixWeight (const int i, const int j) {
    return AdjacencyMatrix[i][j];

}

int distance (const int i, const int j) {
    /*
     * Calcula distancia entre dos nodos
     */
    int sum = 0;
    for (int m = 0; m < k; m++) {
        sum += abs(Sequences[i][m] - Sequences[j][m]);

    }
    return sum;

}

void Kn (vector<vector<int>> AdjMatrix) {
    for (int j = 0; j < N-1; j++) {
        /*
         * Inicializo referencias a minimos
         */
        int minimum = INF;
        Coord minimumTuple{}; minimumTuple.x = -1; minimumTuple.y = -1;
        //
        for (int i = j+1; i < N; i++) {
            if (AdjMatrix[i][j] < minimum) {
                minimum = AdjMatrix[i][j];
                minimumTuple.x = i;
                minimumTuple.y = j;

            }
        }
        /*
         * Sumo peso al AGM
         */
        KnMSTWeight += matrixWeight(minimumTuple.x, minimumTuple.y);
        /*
         * Dejo de tener en cuenta la arista que usé
         */
        AdjMatrix[minimumTuple.x][minimumTuple.y] = INF;
        AdjMatrix[minimumTuple.y][minimumTuple.x] = INF;
    }
}
bool compareByWeight(const Edge& a, const Edge& b) { return a.w < b.w; }
void Kruskal (vector<Edge>& edges) {
    /*
     * Algoritmo de Kruskal
     */
    sort(all(edges), compareByWeight);
    DisjointSet DS (N);
    for (const Edge& edge : edges) {
        if (DS.FindSet(edge.u) != DS.FindSet(edge.v)) {
            KruskalMSTWeight += edge.w;
            DS.Union(edge.u, edge.v);

        }
    }
}

int main() {
    cin >> N >> k;
    //
    Edges.reserve(N*(N-1)/2);
    Sequences.assign(N, vector<int>());
    AdjacencyList.assign(N, vector<int>());
    AdjacencyMatrix.assign(N, vector<int>(N, 0));
    /*
     * Inicio contadores de pesos
     */
    KnMSTWeight = 0;
    KruskalMSTWeight = 0;
    //
    for (int i = 0; i < N; i++) {
        Sequences[i].reserve(k);
        AdjacencyList[i].reserve(N-1);
        /*
         * Armo secuencias Xi
         */
        for (int j = 0; j < k; j++) {
            int Sik; cin >> Sik;
            Sequences[i].push_back(Sik);

        }
        /*
         * Armo lista de adyacencia completa
         */
        for (int j = 0; j < N; j++) {
            if (j != i) {AdjacencyList[i].push_back(j);}

        }
    }
    //
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            /*
             * Armo matriz de adyacencia pesada
             */
            const int weight = distance(i, j);
            AdjacencyMatrix[i][j] = weight;
            AdjacencyMatrix[j][i] = weight;
            Edge edge{}; edge.u = i; edge.v = j; edge.w = weight;
            Edges.push_back(edge);

        }
    }
    /*
     * Corro algoritmos
     */
    Kn (AdjacencyMatrix);
    Kruskal (Edges);
    /*
     * Imprimo matriz de adyacencia pesada
     */
    for (int i = 0; i < N; i++) {
        cout << "[";
        for (int j = 0; j < N; j++) {
            cout << " " << AdjacencyMatrix[i][j];
        }
        cout << " ]" << endl;
    }
    /*
     * Verifico que sean iguales
     */
    cout << "Kn: " << KnMSTWeight << endl;
    cout << "Kruskal: " << KruskalMSTWeight << endl;
    return 0;

}