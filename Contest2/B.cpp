#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n; // Lee el tamaño del array
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i]; // Lee los elementos del array
    }
    sort(a.begin(), a.end()); // Ordena el array
    // Elimina los elementos duplicados
    a.resize(unique(a.begin(), a.end()) - a.begin());
    int pnt = 0, ans = 0;
    for (int i = 0; i < a.size(); i++) {
        // Avanza el puntero pnt mientras la diferencia entre a[i] y a[pnt] es al menos n
        while(a[i] - a[pnt] >= n) {
            pnt++;
        }
        // Actualiza ans con el tamaño máximo del rango encontrado
        ans = max(ans, i - pnt + 1);
    }
    cout << ans << endl; // Imprime el resultado
}

signed main() {
    int t = 1;
    cin >> t; // Lee el número de casos de prueba
    for (int i = 0; i < t; ++i) {
        solve(); // Resuelve cada caso de prueba
    }
    return 0;
}