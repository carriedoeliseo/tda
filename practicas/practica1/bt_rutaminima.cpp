#include <iostream>
#include <vector>
#define N 100
#define INF 1e9
using namespace std;

int n;
int sol_sum;
int sol_pi[N];
int act_pi[N];
int C[N];
int D[N][N];

int suma () {
    int res = D[act_pi[n-1]][act_pi[0]];
    for (int i = 0; i < n-1; i++) {
        res = res + D[act_pi[i]][act_pi[i+1]];

    }
    return res;

}

void rutaminima (int i) {
    if (i == n) {
        if (suma() <= sol_sum) {
            for (int j = 0; j < n; j++) {
                sol_pi[j] = act_pi[j];

            }
            sol_sum = suma();

        }
    } else {
        for (int k = 0; k < n; k++) {
            if (C[k] != -1) {
                act_pi[i] = C[k]; 
                C[k] = -1;
                rutaminima(i+1);
                C[k] = act_pi[i];

            }
        }
    }
}

int main () {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int dij; cin >> dij;
            D[i][j] = dij;
            

        }
        C[i] = i;

    }
    sol_sum = INF;
    rutaminima (0);
    cout << "{ ";
    for (int i = 0; i < n; i++) {
        cout << sol_pi[i]+1 << " ";

    }
    cout << "}" << endl;
    cout << sol_sum ; 
    return 0;

}


