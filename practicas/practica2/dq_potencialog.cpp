#include <iostream>
#include <vector>
int a, b;
using namespace std;

int potencialog(int p) {
    if (p == 0) return 1;
    if (p == 1) return a;
    if (p % 2 == 0) {
        int mid = potencialog(p/2);
        return mid * mid;

    }
    int mid = potencialog((p-1)/2);
    return mid * mid * a;
}

int main () {
    cin >> a >> b;
    cout << potencialog(b) << endl;
    return 0;

}