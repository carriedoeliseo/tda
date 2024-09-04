#include <iostream>
#include <vector>
#include <algorithm>

#define MAXT 10
#define MAXN 100000

using namespace std;

int T;
int N;


bool ends_first (vector<int>& a1, vector<int>& a2) {
    return a1[1] < a2[1];

}

int busyman (vector<vector<int>> actv) {
    sort(actv.begin(), actv.end(), ends_first);
    int finish = -1;
    int sol = 0;
    for (int i = 0; i < N; i++) {
        if (actv[i][0] >= finish) {
            finish = actv[i][1];
            sol++;

        }
    }
    return sol;
}

int main () {
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        vector<vector<int>> A (N, vector<int>(2));
        for (int i = 0; i < N; i++) {
            int n, m; cin >> n >> m;
            A[i][0] = n;
            A[i][1] = m;

        }
        cout << busyman(A) << endl;

    }
    return 0;

}





