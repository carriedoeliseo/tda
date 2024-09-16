#include <iostream>
#define INF 1000000000
using namespace std;

int l;
int cs;
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

int main() {
    cin >> l >> cs;
    C[0] = 0; 
    C[cs+1] = l;
    for (int k = 1; k <= cs; k++) {
        cin >> C[k];

    }
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            for (int h = 0; h < 101; h++) {
                M[i][j][h] = INF;

            }
        }
    }
    cout << ce_top(0, cs+1, 1) << endl;
    return 0;

}