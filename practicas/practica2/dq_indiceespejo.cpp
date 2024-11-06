#include <iostream>
#include <vector>
#include <tuple>
int N;
using namespace std;

tuple<bool, int> indiceespejo (vector<int>& C) {
    int bottom, top, mid;
    bottom = 0;
    top = C.size()-1;
    while (bottom <= top) {
        mid = (bottom + top)/2;
        if (C[mid] == mid+1) break;
        else if (C[mid] > mid+1) top = mid;
        else if (C[mid] < mid+1) bottom = mid;

    }
    if (C[mid] == mid+1) return make_tuple(true, mid+1);
    return make_tuple(false, -1);
    

}

int main() {
    cin >> N;
    vector<int> C (N);
    for (int i = 0; i < N; i++) cin >> C[i];
    tuple<bool,int> ans = indiceespejo(C);
    cout << boolalpha << get<0>(ans) << ", " << get<1>(ans) << endl;
    return 0;

}
