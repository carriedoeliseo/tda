#include <iostream>
#include <algorithm>

#define MAXN 100000

int t, N, C;
int stall[MAXN];

using namespace std;

bool check_distance (int d) {
    int last = 0;
    int cont = 1;
    for (int i = 1; i < N; i++) {
        if (stall[i] >= stall[last] + d) {
            cont++;
            last = i;
            
        }
        if (cont == C) return true;

    }
    return false;

}

int aggrcow () {
    int first = 1;
    int last = stall[N-1] - stall[0];
    while (first < last-1) {
        int mid = (last + first)/2;
        if (check_distance(mid)) first = mid;
        else last = mid-1;
 
    }
    if (check_distance(last)) return last;
    else return first;
 
}


int main () {
    cin >> t;
    for (int k = 0; k < t; k++) {
        cin >> N >> C;
        for (int i = 0; i < N; i++) {
            cin >> stall[i];

        }
        sort(stall, stall+N);
        cout << aggrcow() << endl;

    }
    return 0;

}