#include <iostream>
#include <tuple>
#include <vector>
int N;
using namespace std;

bool conjuncionsubmatriz (vector<vector<int>>& M, int i0, int i1, int j0, int j1) {
    for (int i = i0; i < i1; i++) {
        for (int j = j0; j < j1; j++) {
            if (M[i][j] == 1) return true;

        }
    }
    return false;

}

tuple<int,int> cazadorfalses (vector<vector<int>>& M) {
    int i0 = 0, i1 = M.size();
    int j0 = 0, j1 = M.size();
    while (i0+1 < i1 && j0+1 < j1) {
        if ((i1-i0)%2 == 0) {
            bool exit = false;
            int imid = (i1 - i0)/2;
            int jmid = (j1 - j0)/2;
            for (int i = i0; i < i1; i += imid) {
                for (int j = j0; j < j1; j += jmid) {
                    if (conjuncionsubmatriz(M, i, i+imid, j, j+jmid)) {
                        i0 = i; i1 = i+imid;
                        j0 = j; j1 = j+jmid;
                        exit = true;
                        break;
                        
                    }
                }
                if (exit) break;

            }    
        } 
        else {
            bool exit = false;  
            int imid = (i1 - i0)/2;
            int jmid = (j1 - j0)/2;
            for (int i = i0; i < i1-1; i += imid) {
                for (int j = j0; j < j1-1; j += jmid) {
                    if (conjuncionsubmatriz(M, i, i+imid+1, j, j+jmid+1)) {
                        i0 = i; i1 = i+imid+1;
                        j0 = j; j1 = j+jmid+1;
                        exit = true;
                        break;
                        
                    }
                }
                if (exit) break;

            }    
        }
    }
    return make_tuple(i0, j0);

}

int contadorfalses (vector<vector<int>>& M) {
    int size = M.size();
    if (size == 1) return conjuncionsubmatriz(M, 0, size, 0, size);

    int ans = 0;
    if (size % 2 == 0) {
        int mid = size/2;
        for (int i = 0; i < size; i += mid) {
            for (int j = 0; j < size; j += mid) {
                if (conjuncionsubmatriz(M, i, i+mid, j, j+mid)) {
                    vector<vector<int>> S;
                    S.reserve(mid);
                    for (int k = i; k < i+mid; k++) {
                        vector<int> row (M[k].begin()+j, M[k].begin()+j+mid);
                        S.push_back(row);

                    }
                    ans += contadorfalses(S);

                }
            }
        }
    } 
    else {
        int mid = size/2;
        ans -= M[mid][mid];
        for (int i = 0; i < size-1; i += mid) {
            for (int j = 0; j < size-1; j += mid) {
                if (i == j) {
                    if (conjuncionsubmatriz(M, i, i+mid+1, j, j+mid+1)) {
                        vector<vector<int>> S;
                        S.reserve(mid+1);
                        for (int r = i; r < i+mid+1; r++) {
                            vector<int> row (M[r].begin()+j, M[r].begin()+j+mid+1);
                            S.push_back(row);

                        }
                        ans += contadorfalses(S);

                    }
                }
                else {
                    if (i == 0) {
                        if (conjuncionsubmatriz(M, i, i+mid, j+1, j+mid+1)) {
                            vector<vector<int>> S;
                            S.reserve(mid);
                            for (int r = i; r < i+mid; r++) {
                                vector<int> row (M[r].begin()+j+1, M[r].begin()+j+mid+1);
                                S.push_back(row);

                            }
                            ans += contadorfalses(S);

                        }
                    } else {
                        if (conjuncionsubmatriz(M, i+1, i+mid+1, j, j+mid)) {
                            vector<vector<int>> S;
                            S.reserve(mid);
                            for (int r = i+1; r < i+mid+1; r++) {
                                vector<int> row (M[r].begin()+j, M[r].begin()+j+mid);
                                S.push_back(row);

                            }
                            ans += contadorfalses(S);

                        }
                    }
                }
            }
        }
    }
    return ans;

}

int main () {
    cin >> N;
    vector<vector<int>> M (N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> M[i][j];

        }
    }
    tuple<int,int> ans = cazadorfalses(M);
    cout << "( " << get<0>(ans)+1 << ", " << get<1>(ans)+1 << " ), Falses: " << contadorfalses(M) << endl;
    return 0;

}