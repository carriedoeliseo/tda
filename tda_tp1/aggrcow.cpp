#include <iostream>
#include <vector>
#include <algorithm>

#define MAXX 1000000001
#define MAXN 100000

int t, N, C;
int s[MAXN];
int d[MAXN];

using namespace std;



int aggrcow (int i) {
    for (int j = i+1; j < N-1; j++) {
        int distance = s[j] - s[i];
        for (int c = 0; c < C-1; c++) {
            if (distance > d[c]) {
                int temp = d[c];
                d[c] = distance;
                distance = temp;

            }
        }
    }
    if (i < N-1) aggrcow(i+1);

}

int main () {
    cin >> t;
    for (int k = 0; k < t; k++) {
        cin >> N >> C;
        for (int n = 0; n < N; n++) {
            int xi; cin >> xi;
            s[n] = xi;

        }
        sort(s, s+N);
        for (int c = 0; c < C-1; c++) {
            d[c] = -1;

        }
        aggrcow(0);
        cout << d[C-2] << endl;

    }
    return 0;

}
