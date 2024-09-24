#include <iostream>
#include <vector>
#include <algorithm>

int N;

using namespace std;

int sumagolosa (vector<int> G) {
    int ans = 0;
    sort(G.begin(), G.end());
    for (int i = 0; i < N-1; i++) {
        ans = ans + G[i] + G[i+1];
        G[i+1] = G[i] + G[i+1];

    }
    return ans;

}

int main () {
    cin >> N;
    vector<int> G (N);
    for (int i = 0; i < N; i++) cin >> G[i];
    cout << sumagolosa(G);
    return 0;

}