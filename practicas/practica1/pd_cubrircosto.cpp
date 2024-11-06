#include <iostream>
#include <algorithm>
#include <tuple>

#define MAXN 100
#define MAXC 1000
#define INF 1000000000 // 1e9
using namespace std;

tuple<int, int> M[MAXN][MAXC];
int B[MAXN];
int N, c;

tuple<int, int> tup_sum (tuple<int, int> t1, tuple<int, int> t2) {
    int c0 = get<0>(t1) + get<0>(t2);
    int c1 = get<1>(t1) + get<1>(t2);
    return make_tuple(c0, c1);

}

tuple<int, int> cc (int i, int j) {
    if (M[i][j] != make_tuple(-1, -1)) {
        return M[i][j];

    } else if (i == N) {
        tuple<int, int> t = make_tuple(INF, INF);
        return M[i][j] = t;

    } else if ( j-B[i] <= 0) {
        tuple<int, int> t = make_tuple(B[i], 1);
        return M[i][j] = min(cc(i+1, j), t);

    } else {
        tuple<int, int> t = make_tuple(B[i], 1);
        return M[i][j] = min(cc(i+1, j), tup_sum(cc(i+1, j-B[i]), t));

    }
}

 int main () {
    cin >> c >> N;
    for (int k = 0; k < N; k++) {
        int bk; cin >> B[k];
        
    }
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j <= c; j++) {
            M[i][j] = make_tuple(-1,-1);

        }
    }
    tuple<int, int> sol = cc(0, c);
    cout << "(" << get<0>(sol) << "," << get<1>(sol) << ")" << endl;
    return 0;
}


