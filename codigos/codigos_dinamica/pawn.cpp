#include <iostream>

#define MAXN 105
#define MAXM 105
#define MAXK 12
#define INF 1e9

using namespace std;

int n, m, k;
int M[MAXN][MAXM];
int dp[MAXN][MAXM][MAXK];

int f(int i, int j, int l) {
    if (i == -1) {
        if (l % (k+1) == 0) return 0; 
        else return -INF;
    }
    
    if (j < 0 || j >= m) return -INF;

    if (dp[i][j][l] != -1) return dp[i][j][l];

    return dp[i][j][l] = M[i][j] + 
                max(f(i-1, j-1, (l+M[i][j]) % (k+1)), f(i-1, j+1, (l+M[i][j]) % (k+1)));
}

int main() {
    cin >> n >> m >> k;

    for (int i=0; i<=n; i++)
        for (int j=0; j<=m; j++)
            for (int l=0; l<=k; l++)
                dp[i][j][l] = -1;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            char c; cin >> c;
            M[i][j] = c-'0';
        }
    }

    int best_index = 0;
    for (int j=0; j<m; j++)
        if (f(n-1, j, 0) > f(n-1, best_index, 0))
            best_index = j;

    if (f(n-1, best_index, 0) < 0) cout << -1 << endl;
    else {
        cout << f(n-1, best_index, 0) << endl;
        cout << best_index + 1 << endl;

        int row = n-1; int column = best_index; int cur_mod = 0;
        while (row > 0) {
            cur_mod = (cur_mod + M[row][column]) % (k+1); 
            
            if (f(row-1, column-1, cur_mod) > f(row-1, column+1, cur_mod)) {
                cout << "L"; 
                column--;
            } else {
                cout << "R"; 
                column++;
            }
            
            row--;
        }

        cout << endl;
    }

    return 0;
}
