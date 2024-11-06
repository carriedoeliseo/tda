#include <iostream>
#include <vector>

using namespace std;

void sumaSubconjuntos_recursivo (int i, int rest, vector<int>& conj, vector<vector<int>>& sol, vector<int> C) {
    if (rest == 0) {
        sol.push_back(conj);

    } else if (rest < 0) {
        return;

    } else if (i == -1) {
        return;

    } else {
        conj[i] = 1;
        sumaSubconjuntos_recursivo(i-1, rest-C[i], conj, sol, C);
        conj[i] = 0;
        sumaSubconjuntos_recursivo(i-1, rest, conj, sol, C);

    }
}

vector<vector<int>> sumaSubconjuntos (vector<int> C, int k) {
    vector<int> conj (C.size());
    for (int i = 0; i < conj.size(); i++) {
        conj[i] = 0;

    }
    vector<vector<int>> sol = {};
    sumaSubconjuntos_recursivo(C.size()-1, k, conj, sol, C);
    return sol;

}

int main () {
    int n;
    cout << "n: "; cin >> n ;
    vector<int> C (n);
    cout << "C: " ;
    for (int i = 0; i < n; i++) {
        cin >> C[i];

    }
    int k;
    cout << "k: " ; cin >> k ;
    vector<vector<int>> res = sumaSubconjuntos(C, k);
    for (int i = 0; i < res.size(); i ++) {
        cout << "{ " ;
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " " ;

        }
        cout << "};" << endl ;
    }
    return 0;
}