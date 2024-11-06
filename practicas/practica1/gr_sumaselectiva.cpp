#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
int N, k;

using namespace std;

tuple <int, vector<int>> sumaselectiva (vector<int> X) {
    int sum = 0;
    vector<int> S (k); 
    sort(X.begin(), X.end(), greater<int>()); 
    for (int i = 0; i < k; i++) { 
        sum = sum + X[i];
        S[i] = X[i];

    } 
    return make_tuple(sum, S); 

} // Complejidad: O(nlogn + 2k) ≡ O(nlogn)

tuple <int, vector<int>> sumaselectiva_heap (vector<int> X) {
    int sum = 0;
    vector<int> S (k); 
    for (int i = 0; i < k; i++) {
        sum = sum + X[i];
        S[i] = X[i];

    }
    make_heap(S.begin(), S.end(), greater<int>()); 
    for (int i = k; i < N; i++) {
        if (S.front() < X[i]) {
            sum = sum - S.front() + X[i];
            pop_heap(S.begin(), S.end(), greater<int>());
            S[k-1] = X[i];
            push_heap(S.begin(), S.end(), greater<int>());

        }
    }
    return make_tuple(sum, S);

}

int main() {
    cin >> N >> k;
    vector<int> X (N);
    for (int i = 0; i < N; i++) cin >> X[i];
    tuple <int, vector<int>> ans = sumaselectiva_heap(X);
    cout << get<0>(ans) << endl;
    vector<int> S = get<1>(ans);
    cout << "{ ";
    for (int i = 0; i < k; i++) cout << S[i] << " ";
    cout << "}" << endl;
    return 0;

}


