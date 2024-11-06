#include <iostream>
#include <vector>
#include <numeric>
int N;
using namespace std;

bool masizquierda (vector<int>& S, int i, int j) {
    if (i+2 == j) return S[i] >= S[i+1];
    int left = accumulate(S.begin()+i, S.begin()+(j+i)/2, 0);
    int right = accumulate(S.begin()+(j+i)/2, S.begin()+j, 0);
    return (left >= right) && masizquierda(S, i, (j+i)/2) && masizquierda(S, (j+i)/2, j);
}

int main () {
    cin >> N;
    vector<int> S (N);
    for (int i = 0; i < N; i++) cin >> S[i];
    cout << boolalpha << masizquierda(S,0,N) << endl;
    return 0;

}