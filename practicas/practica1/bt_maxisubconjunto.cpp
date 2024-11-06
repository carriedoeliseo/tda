#include <iostream>
#include <vector>

using namespace std;

void maxisubconjunto_recursivo (vector<vector<int>> M, vector<int>& conj, int k, vector<int>& sol, int& max_sum, int n) {
    if (conj.size() == k) {
        int suma = 0;
        for (int fil = 0; fil < k; fil++) {
            for (int col = 0; col < k; col++) {
                suma = suma + M[conj[fil]][conj[col]];

            }
        }
        if (suma >= max_sum) {
            sol = conj;
            max_sum = suma;

        }

    } else if (M.size()-n > k-conj.size()) {
        maxisubconjunto_recursivo(M, conj, k, sol, max_sum, n+1);
        conj.push_back(n);
        maxisubconjunto_recursivo(M, conj, k, sol, max_sum, n+1);
        conj.pop_back();

    } else {
        conj.push_back(n);
        maxisubconjunto_recursivo(M, conj, k, sol, max_sum, n+1);
        conj.pop_back();

    }
}

vector<int> maxisubconjunto (vector<vector<int>> M, int k) {
    vector<int> max_conj = {};
    vector<int> conj = {};
    int max_sum = 0;
    maxisubconjunto_recursivo(M, conj, k, max_conj, max_sum, 0);
    return max_conj;

}

int main () {
    int n;
    cout << "n: " ; cin >> n ;
    vector<vector<int>> M (n, vector<int>(n));
    cout << "M:" << endl ;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> M[i][j];
        }
        cout << endl ;
    }
    int k;
    cout << "k: " ; cin >> k ;
    vector<int> res = maxisubconjunto(M, k);
    cout << "{ " ;
    for (int val : res) {
        cout << val << " ";

    }
    cout << "}" ;
    return 0;
}