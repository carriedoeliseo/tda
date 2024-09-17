#include <iostream>
#define INF 1e9
using namespace std;

int m, n;
int A[100][100];

int tv (int i, int j, int v) {
    if (i == m-1 && j == n-1 && v > 0) {
        return v -(A[i][j]);

    } else if (i == m-1 && j == n-1 && v <= 0) {
        return INF;

    } else if (i == m-1 && j < n-1) {
        return tv(i, j+1, v-(A[i][j]));

    } else if (i < m-1 && j == n-1) {
        return tv(i+1, j, v-(A[i][j]));
        
    } else {
        return min(tv(i, j+1, v-(A[i][j])), tv(i+1, j, v-(A[i][j])));

    }
}

int main () {
    cin >> m >> n ;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];

        }
    }
    cout << tv(0,0,1) << endl;
    return 0;

}