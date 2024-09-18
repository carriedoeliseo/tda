#include <iostream>
#define INF 1e9
using namespace std;

int m, n;
int A[100][100];
int M[100][100];
int S[2][100];

int tv_top (int i, int j) {
    if (M[i][j] != -1) {
        return M[i][j];

    } else if (i == m-1 && j == n-1) {
        return M[i][j] = max(1, 1 - A[i][j]);

    } else if (i == m-1 && j < n-1) {
        return M[i][j] = max(1, tv_top(i, j+1) - A[i][j]);

    } else if (i < m-1 && j == n-1) {
        return M[i][j] = max(1, tv_top(i+1, j) - A[i][j]);
        
    } else {
        return M[i][j] = max(1, min(tv_top(i, j+1), tv_top(i+1, j)) - A[i][j]);

    }
}

int tv_bottom () {
    if (m >= n) {
        for (int j = 0; j < n-1; j++) {
            S[1][j] = A[m-1][j];

        }
        S[1][n-1] = 1 - A[m-1][n-1];
        for (int i = m-2; i >= 0; i--) {
            S[0][n-1] = A[i][n-1];
            S[1][n-1] = max(1, S[1][n-1] - S[0][n-1]);
            for (int j = n-2; j > 0; j--) {
                S[0][j] = A[i][j];
                S[1][j-1] = max(1, S[1][j] - S[1][j-1]);
                S[1][j] = max(1, min(S[1][j], S[1][j+1]) - S[0][j]);
                

            }
            S[0][0] = A[i][0];
            S[1][0] = max(1, min(S[1][0], S[1][1]) - S[0][0]);

        }
    } else {
        for (int i = 0; i < m-1; i++) {
            S[1][i] = A[i][n-1];

        }
        S[1][m-1] = 1 - A[m-1][n-1];
        for (int j = n-2; j >= 0; j--) {
            S[0][m-1] = A[m-1][j];
            S[1][m-2] = max(1, S[1][m-1] - S[1][m-2]);
            S[1][m-1] = max(1, S[1][m-1] - S[0][m-1]);
            for (int i = m-2; i > 0; i--) {
                S[0][i] = A[i][j];
                S[1][i-1] = max(1, S[1][i] - S[1][i-1]);
                S[1][i] = max(1, min(S[1][i], S[1][i+1]) - S[0][i]);

            }
            S[0][0] = A[0][j];
            S[1][0] = max(1, min(S[1][0], S[1][1]) - S[0][0]);

        }
    }
    return S[1][0];

}



int main () {
    cin >> m >> n ;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
            M[i][j] = -1;

        }
    }
    cout << tv_bottom() << endl;
    return 0;

}