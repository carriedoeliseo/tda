#include <iostream>
#include <vector>

using namespace std;

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

int main () {
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
    return 0;
}