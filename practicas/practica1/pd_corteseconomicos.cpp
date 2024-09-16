#include <iostream>
#include <vector>
#define INF 1000000000 //1e9
using namespace std;

int l; // long inicial de la vara.
int n; // # cortes.
int ans;
int C[101];
int M[101][101][101];

int ce_top (int i, int j, int c) {
    if (M[i][j][c] != INF) {
        return M[i][j][c];

    } else if (i+1 == j) {
        return 0;

    } else if (c+1 == j) {
        return M[i][j][c] = C[j]-C[i] + ce_top(i, c, i+1);

    } else {
        return M[i][j][c] = min(ce_top(i, j, c+1), C[j]-C[i] + ce_top(i, c, i+1) + ce_top(c, j, c+1));

    }
}

int ce_bottom (vector<int> V) {
    for (int i = n; i > 0; i--) {
        int min = INF;
        int c;
        for (int k = 1; k <= i; k++) {
            if (V[k+1]-V[k-1] < min) {
                min = V[k+1]-V[k-1];
                c = k;

            }
        }
        ans = ans + min;
        V.erase(V.begin() + c);
    }
    return ans;

}

int main() {
    cin >> l >> n;
    vector<int> V (n+2);
    V[0] = 0; V[n+1] = l;
    for (int k = 1; k <= n; k++) {
        int v; cin >> v;
        V[k] = v;

    }
    cout << ce_bottom(V) << endl;
    return 0;

}

/*
int main() {
    cin >> l >> n;
    C[0] = 0; 
    C[n+1] = l;
    for (int k = 1; k <= n; k++) {
        cin >> C[k];

    }
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            for (int h = 0; h < 101; h++) {
                M[i][j][h] = INF;

            }
        }
    }
    cout << ce_top(0, n+1, 1) << endl;
    return 0;

}
*/