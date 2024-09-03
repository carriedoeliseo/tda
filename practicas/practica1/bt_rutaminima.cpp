#include <iostream>
#define N 100
using namespace std;

int n;
int sol_sum;
int sol_pi[N];
int D[N][N];

int suma (int D[n][n], int pi[n]) {
    int res = D[pi[n-1]][pi[0]];
    for (int i = 0; i < n-2; i++) {
        res = res + D[pi[i]][pi[i+1]];

    }
    return res;
}

void rutaminima (int i; int pi[n], int C[n]) {
    if (i == n) {
        if (suma(D, pi) <= sol_sum) {
            sol_pi = pi;
            sol_sum = suma(D, pi);

        }
    } else {
        for (int k = 0; k < n; k++) {
            if (C[k] != -1) {
                int pii = C[k];
                pi[i] = pii; C[k] = -1;
                rutaminima(i+1, pi, C)
                C[k] = pii;

            }
        }
    }
}

int main () {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int dij; cin >> dij;
            D[i][j] =

        }

    }

}


