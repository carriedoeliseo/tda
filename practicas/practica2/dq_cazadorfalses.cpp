#include <iostream>
#include <tuple>
#include <vector>
int N, f, ans;
using namespace std;

bool conjuncionsubmatriz (vector<vector<int>>& M, int i0, int i1, int j0, int j1) {
    for (int i = i0; i < i1; i++) {
        for (int j = j0; j < j1; j++) {
            if (S[i][j] == 1) return true;

        }
    }
    return false;

}

bool cazadorfalses (vector<vector<int>>& M) {
    int s = M.size();
    if (s == 1)


}

int main () {
    cin >> N >> f;
    vector<vector<0>> M (N, vector<0>(N, 0));
    for (int k = 0; k < f; k++) {
        int i, j; 
        cin >> i >> j;
        M[i][j] = 1;

    }
    cout << boolalpha << cazadorfalses(M) << endl;
    return 0;

}