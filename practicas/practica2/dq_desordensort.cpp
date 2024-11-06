#include <iostream>
#include <vector>
int N, ans;
using namespace std;

vector<int> merge (vector<int>& left, vector<int>& right) {
    vector<int> vmerge (left.size() + right.size());
    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            vmerge[k] = left[i];
            k++; i++;

        } else {
            vmerge[k] = right[j];
            ans += left.size()-i;
            k++; j++;

        }
    }
    while (i < left.size()) {
        vmerge[k] = left[i];
        k++; i++;

    }
    while (j < right.size()) {
        vmerge[k] = right[j];
        ans += left.size()-i;
        k++; j++;

    }
    return vmerge;

}

vector<int> desordensort(vector<int>& S) {
    if (S.size() <= 1) return S;
    int mid = S.size()/2;
    vector<int> left (S.begin(), S.begin()+mid);
    vector<int> right (S.begin()+mid, S.end());
    left = desordensort(left);
    right = desordensort(right);
    return merge(left, right);

}

int main () {
    cin >> N;
    ans = 0;
    vector<int> S (N);
    for (int i = 0; i < N; i++) cin >> S[i];
    desordensort(S);
    cout << ans;
    return 0;

}