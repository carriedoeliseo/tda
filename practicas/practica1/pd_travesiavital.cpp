#include <iostream>
#define INF 1e9
using namespace std;

int m, n;
int A[100][100];
int M[100][100];

int tv (int i, int j) {
    if (M[i][j] != -1) {
        return M[i][j];

    } else if (i == m-1 && j == n-1) {
        return M[i][j] = max(1, 1 - A[i][j]);

    } else if (i == m-1 && j < n-1) {
        return M[i][j] = max(1, tv(i, j+1) - A[i][j]);

    } else if (i < m-1 && j == n-1) {
        return M[i][j] = max(1, tv(i+1, j) - A[i][j]);
        
    } else {
        return M[i][j] = max(1, min(tv(i, j+1), tv(i+1, j)) - A[i][j]);

    }
}

int main () {
    cin >> m >> n ;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
            M[i][j] = -1;
            
        }
    }
    cout << tv(0,0) << endl;
    return 0;

}