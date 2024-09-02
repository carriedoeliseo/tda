#include <iostream>
#include <vector>

using namespace std;

// 1 ====================================================================================================

void sumaSubconjuntos_recursivo (int i, int rest, vector<int>& conj, vector<vector<int>>& sol, vector<int> C) {
    if (rest == 0) {
        sol.push_back(conj);

    } else if (rest < 0) {
        return;

    } else if (i == -1) {
        return;

    } else {
        conj[i] = 1;
        sumaSubconjuntos_recursivo(i-1, rest-C[i], conj, sol, C);
        conj[i] = 0;
        sumaSubconjuntos_recursivo(i-1, rest, conj, sol, C);

    }
}

vector<vector<int>> sumaSubconjuntos (vector<int> C, int k) {
    vector<int> conj (C.size());
    for (int i = 0; i < conj.size(); i++) {
        conj[i] = 0;

    }
    vector<vector<int>> sol = {};
    sumaSubconjuntos_recursivo(C.size()-1, k, conj, sol, C);
    return sol;

}

// 2 ====================================================================================================

int esValido (vector<vector<int>> matriz) {
    int magic_number = 0;
    bool val = true;
    for (int i = 0; i < matriz.size(); i++){
        magic_number = magic_number + matriz[0][i];

    }
    int sum_diag = 0;
    int sum_cdiag = 0;
    for (int i = 0; i < matriz.size(); i++){
        int sum_fil = 0;
        int sum_col = 0;
        for (int j = 0; j < matriz.size(); j++){
            sum_fil = sum_fil + matriz[i][j];
            sum_col = sum_col + matriz[j][i];

        }
        val = val && (sum_col == magic_number) && (sum_fil == magic_number);
        if (val == false) return false;
        sum_diag = sum_diag + matriz[i][i];
        sum_cdiag = sum_cdiag + matriz[i][matriz.size()-1-i];
        
    }
    val = val && (sum_diag == magic_number) && (sum_cdiag == magic_number);
    return val;

}

void magicuadrado_recursivo (vector<vector<int>>& M, int fila, int columna, vector<int>& usados, int& sol) {
    int n = M.size();

    if (fila == n) {
        if (esValido(M)) sol++;

    } else if (columna == n-1) {
        for (int k = 0; k < n*n; k++) {
            if (usados[k] == 0) {
                M[fila][columna] = k+1;
                usados[k] = 1;
                magicuadrado_recursivo(M, fila+1, 0, usados, sol);
                usados[k] = 0;

            }
        }

    } else {
        for (int k = 0; k < n*n; k++) {
            if (usados[k] == 0) {
                M[fila][columna] = k+1;
                usados[k] = 1;
                magicuadrado_recursivo(M, fila, columna+1, usados, sol);
                usados[k] = 0;

            }
        }
    }
}

int magicuadrado (int n) {
    int res = 0;
    int fil = 0;
    int col = 0;
    vector<vector<int>> M (n, vector<int>(n));
    vector<int> usd (n*n);
    for (int k = 0; k < usd.size(); k++) {
        usd[k] = 0;
    }
    
    magicuadrado_recursivo(M, fil, col, usd, res);

    return res;
}

void magicuadrado_recursivo_podado (vector<vector<int>>& M, int fila, int columna, vector<int>& usados, int& sol) {
    int n = M.size();
    int magic_num = (n*n*n + n)/2;

    if (fila == n) {
        if (esValido(M)) sol++;

    } else if (columna == n-1) {
        for (int k = 0; k < n*n; k++) {
            int sum_fil = 0;
            int sum_col = 0;
            for (int j = 0; j < columna; j++) {
                sum_fil = sum_fil + M[fila][j];
            }
            for (int i = 0; i < fila; i++) {
                sum_col = sum_col + M[i][columna];
            }
            if (usados[k] == 0 && (sum_fil + k+1) <= magic_num && (sum_col + k+1) <= magic_num) {
                vector<vector<int>> M_prima = M;
                M[fila][columna] = k+1;
                usados[k] = 1;
                magicuadrado_recursivo(M, fila+1, 0, usados, sol);
                usados[k] = 0;

            }
        }

    } else {
        for (int k = 0; k < n*n; k++) {
            int sum_fil = 0;
            int sum_col = 0;
            for (int j = 0; j < columna; j++) {
                sum_fil = sum_fil + M[fila][j];
            }
            for (int i = 0; i < fila; i++) {
                sum_col = sum_col + M[i][columna];
            }
            if (usados[k] == 0 && (sum_fil + k+1) <= magic_num && (sum_col + k+1) <= magic_num) {
                vector<vector<int>> M_prima = M;
                M[fila][columna] = k+1;
                usados[k] = 1;
                magicuadrado_recursivo(M, fila, columna+1, usados, sol);
                usados[k] = 0;

            }
        }
    }
}

int magicuadrado_podado (int n) {
    int res = 0;
    int fil = 0;
    int col = 0;
    vector<vector<int>> M (n, vector<int>(n));
    vector<int> usd (n*n);
    for (int k = 0; k < usd.size(); k++) {
        usd[k] = 0;
    }
    magicuadrado_recursivo_podado(M, fil, col, usd, res);
    return res;

}

// 3 ====================================================================================================

void maxisubconjunto_recursivo (vector<vector<int>> M, vector<int>& conj, int k, vector<int>& sol, int& max_sum, int n) {
    if (conj.size() == k) {
        int suma = 0;
        for (int fil = 0; fil < k; fil++) {
            for (int col = 0; col < k; col++) {
                suma = suma + M[conj[fil]][conj[col]];

            }
        }
        if (suma >= max_sum) {
            sol = conj;
            max_sum = suma;

        }

    } else if (M.size()-n > k-conj.size()) {
        maxisubconjunto_recursivo(M, conj, k, sol, max_sum, n+1);
        conj.push_back(n);
        maxisubconjunto_recursivo(M, conj, k, sol, max_sum, n+1);
        conj.pop_back();

    } else {
        conj.push_back(n);
        maxisubconjunto_recursivo(M, conj, k, sol, max_sum, n+1);
        conj.pop_back();

    }
}

vector<int> maxisubconjunto (vector<vector<int>> M, int k) {
    vector<int> max_conj = {};
    vector<int> conj = {};
    int max_sum = 0;
    maxisubconjunto_recursivo(M, conj, k, max_conj, max_sum, 0);
    return max_conj;

}

// main ====================================================================================================

int main() {
    cout << "(1- sumaSubconjuntos)" << "(2- magicuadrado)" << "(3- maxisubconjunto)" << endl;
    int opt;
    cin >> opt;

    if (opt == 1) {
        int n;
        cout << "n: "; cin >> n ;
        vector<int> C (n);
        cout << "C: " ;
        for (int i = 0; i < n; i++) {
            cin >> C[i];

        }
        int k;
        cout << "k: " ; cin >> k ;
        vector<vector<int>> res = sumaSubconjuntos(C, k);
        for (int i = 0; i < res.size(); i ++) {
            cout << "{ " ;
            for (int j = 0; j < res[i].size(); j++) {
                cout << res[i][j] << " " ;

            }
            cout << "};" << endl ;
        }

    } else if (opt == 2) {
        cout << "(1- magicuadrado)" << " " << "(2- magicuadrado podado)" << endl;
        int opt_mc;
        cin >> opt_mc;

        if (opt_mc == 1) {
            int n;
            cout << "n: " ; cin >> n;
            int res = magicuadrado (n);
            cout << res;

        } else if (opt_mc == 2) {
            int n;
            cout << "n: " ; cin >> n;
            int res = magicuadrado_podado (n);
            cout << res;

        }
        
    } else if (opt == 3) {
        int n;
        cout << "n: " ; cin >> n ;
        vector<vector<int>> M (n, vector<int>(n));
        cout << "M:" << endl ;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> M[i][j];
            }
            cout << endl ;
        }
        int k;
        cout << "k: " ; cin >> k ;
        vector<int> res = maxisubconjunto(M, k);
        cout << "{ " ;
        for (int val : res) {
            cout << val << " ";

        }
        cout << "}" ;
    }

    return 0;
}

