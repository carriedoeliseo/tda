//
// Created by carri on 16/10/2024.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#define all(x) x.begin(), x.end()
int V, E;
std::vector<std::tuple<int,int,int>> edges;

int main () {
    std::cin >> V >> E;
    edges.reserve(E);
    for (int i = 0; i < E; i++) {
        int a, b, w; std::cin >> a >> b >> w;
        edges.emplace_back(a, b, w);
    }

}