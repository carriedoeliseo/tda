#include <iostream>
#include <vector>

#define MAXN 200
#define MAXXi 1e6
#define INF 1e9

using namespace std;

int N;
int s[MAXN];

int borw (int i, int lastb, int lastw) {
    if (i == N) {
        return 0;

    } else if (lastw <= s[i] && s[i] <= lastb) {
        return (borw(i+1, lastb, lastw) + 1);

    } else if (lastw > s[i] && s[i] <= lastb) {
        return (min(borw(i+1, lastb, s[i]), borw(i+1, lastb, lastw) + 1));

    } else if (lastw <= s[i] && s[i] > lastb) {
        return (min(borw(i+1, s[i], lastw), borw(i+1, lastb, lastw) + 1));

    } else {
        return (min(min(borw(i+1, s[i], lastw), borw(i+1, lastb, s[i])), borw(i+1, lastb, lastw) + 1));

    }
}

int main () {
    vector<int> outputs;
    cin >> N;
    while (N != -1) {
        for (int i = 0; i < N; i++) {
            int xi; cin >> xi;
            s[i] = xi;

        }
        outputs.push_back(borw(0, -1, INF));
        cin >> N;
    }
    for (int i = 0; i < outputs.size(); i++) {
        cout << outputs[i] << endl;

    }
    return 0;
    
}