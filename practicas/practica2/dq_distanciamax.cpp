#include <iostream>
#include <vector>
#include <tuple>
int V;
using namespace std;

tuple<int, int> distanciamax (vector<vector<int>>& E, int root) {
    if (E[root][0] == E[root][1]) return make_tuple(0, 0);
    int hijos [2][3];
    for (int s = 0; s < 2; s++) {
        int hijo = E[root][s];
        if (hijo != 0) {
            tuple<int, int> hijo_ans = distanciamax(E, hijo);
            hijos[s][0] = get<0>(hijo_ans);
            hijos[s][1] = get<1>(hijo_ans);
            hijos[s][2] = 1;

        } else {
            hijos[s][0] = 0;
            hijos[s][1] = 0;
            hijos[s][2] = 0;

        }
    }
    int dmax = 0; int high = 0;
    if (hijos[0][2] + hijos[1][2] == 2) {
        for (int s = 0; s < 2; s++) {
            if (dmax < hijos[s][0]) dmax = hijos[s][0];
            if (high < hijos[s][1]) high = hijos[s][1];

        }
        dmax = max(dmax, hijos[0][1]+hijos[1][1]+2);
        high++;

    } else {
        for (int s = 0; s < 2; s++) {
            if (hijos[s][2] == 1) {
                dmax = max(hijos[s][0], hijos[s][1]+1);
                high = hijos[s][1]+1;

            }
        }
    }
    return make_tuple(dmax, high);

}

int main () {
    cin >> V;
    vector<vector<int>> E (V+1, vector<int>(2));
    for (int i = 1; i < V+1; i++) cin >> E[i][0] >> E[i][1];
    tuple<int, int> ans = distanciamax (E, 1);
    cout << get<0>(ans) << endl;
    return 0;
    
}