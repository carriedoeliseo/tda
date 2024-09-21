#include <iostream>
#define INF 1e9
using namespace std;

int m, n;
int A[100][100];
int M[100][100];
int S[100];

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
        S[n-1] = 1 - A[m-1][n-1];
        for (int j = n-2; j >= 0; j--) {
            S[j] = max(1, S[j+1] - A[m-1][j]);

        }
        for (int i = m-2; i >= 0; i--) {
            S[n-1] = max(1, S[n-1] - A[i][n-1]);
            for (int j = n-2; j >= 0; j--) {
                S[j] = max(1, min(S[j], S[j+1]) - A[i][j]);
                
            }
        }
    } else {
        S[m-1] = 1 - A[m-1][n-1];
        for (int i = m-2; i >= 0; i--) {
            S[i] = max(1, S[i+1] - A[n-1][i]);

        }
        for (int j = n-2; j >= 0; j--) {
            S[m-1] = max(1, S[m-1] - A[m-1][j]);
            for (int i = m-2; i >= 0; i--) {
                S[i] = max(1, min(S[i], S[i+1]) - A[i][j]);
                
            }
        }
    }
    return S[0];

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