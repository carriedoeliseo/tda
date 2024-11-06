#include <iostream>
#include <vector>

#define MAXN 202
#define INF 1e9

using namespace std;

int N;
int s[MAXN];
int M[MAXN][MAXN][MAXN];

int borw (int i, int lastb, int lastw) {
    if (M[i][lastb][lastw] != -1) {
        return M[i][lastb][lastw];

    } else if (i == N) {
        return 0;

    } else if (s[lastw] <= s[i] && s[i] <= s[lastb]) {
        return M[i][lastb][lastw] = borw(i+1, lastb, lastw) + 1;

    } else if (s[lastw] > s[i] && s[i] <= s[lastb]) {
        return M[i][lastb][lastw] =  min(borw(i+1, lastb, i), borw(i+1, lastb, lastw) + 1);

    } else if (s[lastw] <= s[i] && s[i] > s[lastb]) {
        return M[i][lastb][lastw] =  min(borw(i+1, i, lastw), borw(i+1, lastb, lastw) + 1);

    } else {
        return M[i][lastb][lastw] = min(min(borw(i+1, i, lastw), borw(i+1, lastb, i)), borw(i+1, lastb, lastw) + 1);

    }
}

int main () {
    s[200] = -1; s[201] = INF;
    cin >> N;
    while (N != -1) {
        for (int i = 0; i < MAXN; i++){
            for (int j = 0; j < MAXN; j++){
                for (int k = 0; k < MAXN; k++){
                    M[i][j][k] = -1;

                }
            }
        }
        for (int i = 0; i < N; i++) {
            int xi; cin >> xi;
            s[i] = xi;

        }
        cout << borw(0, 200, 201) << endl;
        cin >> N;
    }
    return 0;
    
}