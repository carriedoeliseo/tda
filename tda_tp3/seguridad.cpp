//
// Created by carri on 22/11/2024.
//

#include <vector>
#include <iostream>
#include <algorithm>

#define all(x) (x).begin(), (x).end()
#define noParent (-1)
#define infinity (1000000000)
struct Vertex { int value;
                int queueIndex;
                int distance = infinity; };
int n, m;
std::vector<Vertex> vertexList;
std::vector<int> sDistance, tDistance;
std::vector<std::vector<std::pair<Vertex&, int>>> adjacencyList;

#define getVertex(x) x.first
#define getWeight(x) x.second

void siftUp(std::vector<Vertex*>& Queue, int  index) {
    while (index > 0) {
        const int parent = (index-1)/2;
        if (Queue[index]->distance < Queue[parent]->distance) {
            std::swap(Queue[index], Queue[parent]);
            const int tempIndex = Queue[index]->queueIndex;
            Queue[index]->queueIndex = Queue[parent]->queueIndex;
            Queue[parent]->queueIndex = tempIndex;
            index = parent;

        } else {
            break;

        }
    }
}

void siftDown(std::vector<Vertex*>& Queue, int index, const int size) {
    while (index < size) {
        const long long leftChild = 2*index+1;
        const long long rightChild = 2*index+2;
        long long smallest = index;

        if (leftChild < size && Queue[leftChild]->distance < Queue[smallest]->distance) {
            smallest = leftChild;

        }
        if (rightChild < size && Queue[rightChild]->distance < Queue[smallest]->distance) {
            smallest = rightChild;

        }
        if (smallest != index) {
            std::swap(Queue[index], Queue[smallest]);
            const int tempIndex = Queue[index]->queueIndex;
            Queue[index]->queueIndex = Queue[smallest]->queueIndex;
            Queue[smallest]->queueIndex = tempIndex;
            index = smallest;

        } else {
            break;

        }
    }
}

void extractMin(std::vector<Vertex*>& Queue) {
    Queue[0] = Queue[Queue.size()-1];
    Queue[0]->queueIndex = 0;
    Queue.pop_back();
    siftDown(Queue, 0, Queue.size());

}

void heapify (std::vector<Vertex*>& Queue) {
    const int size = Queue.size();
    for (int  i = size/2-1; i >= 0; i--) {
        siftDown(Queue, i, size);

    }
}

void restartDistances (std::vector<Vertex>& vertexList) {
    for (Vertex& vertex : vertexList) {
        vertex.distance = infinity;

    }
}

bool relax (const Vertex* u, Vertex& v, const int weight) {
    if (v.distance > u->distance + weight) {
        v.distance = u->distance + weight;
        return true;

    }
    return false;

}

auto compareByDistance = [](const Vertex* v1, const Vertex* v2) {
    return v1->distance > v2->distance;

};

void dijkstra(std::vector<std::vector<std::pair<Vertex&, int>>>& adjacencyList, const int source, std::vector<int>& distances) {
    /*
     * Inicializo fuente.
     */
    distances[source] = 0;
    vertexList[source].distance = 0;
    /*
     * Inicializo cola de prioridad.
     */
    int index = 0;
    std::vector<Vertex*> Queue; Queue.reserve(n);
    for (Vertex& vertex : vertexList) {
        /*
         * Agrego vértices a cola de prioridad.
         */
        vertex.queueIndex = index;
        Queue.push_back(&vertex);
        index++;

    }
    heapify(Queue);
    while (!Queue.empty()) {
        const Vertex* min = Queue[0];
        extractMin(Queue);
        /*
         * Veo adyacentes al minimo.
         */
        for (auto& adj : adjacencyList[min->value]) {
            Vertex& vertex = getVertex(adj);
            const int weight = getWeight(adj);
            /*
             * Relajo los vertices adyacentes.
             */
            const bool decrease = relax(min, vertex, weight);
            if (decrease) {
                /*
                 * Si mejora distancia decremento la key en la cola.
                 */
                distances[vertex.value] = vertex.distance;
                siftUp(Queue, vertex.queueIndex);

            }
        }
    }
}

int main() {
    std::cin >> n >> m;
    /*
     * Inicializo listas.
     */
    vertexList.assign(n, Vertex{});
    adjacencyList.assign(n, std::vector<std::pair<Vertex&, int>>());

    for (int i = 0; i < m; i++) {
        int v, u, weight; std::cin >> v >> u >> weight;
        vertexList[v].value = v;
        vertexList[u].value = u;
        /*
         * Tomo referencias.
         */
        Vertex& vVertex = vertexList[v];
        Vertex& uVertex = vertexList[u];
        /*
         * Agrego referencias a la lista de adyacencia junto con el peso de la arista.
         */
        adjacencyList[v].emplace_back(uVertex, weight);
        adjacencyList[u].emplace_back(vVertex, weight);

    }
    /*
     * Distancias a vertice [0].
     */
    sDistance.assign(n, infinity);
    dijkstra(adjacencyList, 0, sDistance); // O(n2*m)
    /*
     * Distancias a vertice [n-1]
     */
    restartDistances(vertexList);
    tDistance.assign(n, infinity);
    dijkstra(adjacencyList, n-1, tDistance);

    long long cost = 0;
    for (int i = 0; i < n; i++) {
        for (const auto& adj : adjacencyList[i]) {
            if (sDistance[i] + getWeight(adj) + tDistance[getVertex(adj).value] == sDistance[n-1]) {
                cost += getWeight(adj);

            }
        }
    }
    std::cout << 2*cost << std::endl;
    return 0;

}