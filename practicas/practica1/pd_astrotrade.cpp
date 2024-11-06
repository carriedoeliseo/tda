#include <iostream>

#define INF 1000000000
using namespace std;

int N;
int p[100];
int M[100][100];
int S[101];

int at_top (int i, int c) { 
    if (i < 0 && c != 0) {
        return -INF;

    } else if (i < 0 && c == 0) {
        return 0;

    } else if (M[i][c] != INF) {
        return M[i][c];

    } else if (i >= 0 && c == 0) {
        return M[i][c] = max(at_top(i-1, c+1) + p[i], at_top(i-1, c));

    } else {
        M[i][c] = max(max(at_top(i-1, c-1) - p[i], at_top(i-1, c+1) + p[i]), at_top(i-1, c));

    }
}

int at_bottom () {
    S[0] = 0;
    for (int i = 1; i <= N; i++) {
        S[i] = -INF;
    }     
    for (int i = 0; i < N; i++) {
        for (int c = 0; c <= i; c++) {
            S[c] = max(S[c], S[c+1] + p[i]);

        }
        S[i+1] = S[i] - p[i];

    }
    return S[0];

}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> p[i];

    }
    cout << at_bottom();
    return 0;

}
