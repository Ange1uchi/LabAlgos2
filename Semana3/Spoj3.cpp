#include <bits/stdc++.h>
using namespace std;
// Este codigo tiene un approach algo greedy, pues lo que hace es intentar ubicar las vacas lo mas lejos posible entre ellas
// y luego se va acercando a la respuesta correcta, es decir, se va acercando a la respuesta correcta de forma agresiva.
// La idea es que si se puede ubicar las vacas con una distancia dada, entonces se puede ubicar las vacas con una distancia mayor.
// Por lo tanto, se puede realizar una busqueda binaria para encontrar la distancia maxima posible.

// Función para fusionar dos subarreglos ordenados
void merge(vector<int>& v, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(n1);
    vector<int> right(n2);

    for (int i = 0; i < n1; i++) {
        left[i] = v[low + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = v[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            v[k] = left[i];
            i++;
        } else {
            v[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        v[k] = left[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = right[j];
        j++;
        k++;
    }
}

// Función para ordenar el arreglo usando el algoritmo merge sort
void merge_sort(vector<int>& v, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge_sort(v, low, mid);
        merge_sort(v, mid + 1, high);
        merge(v, low, mid, high);
    }
}

// Función para verificar si es posible colocar las vacas de forma agresiva
bool ok(vector<int>& v, int x, int c) {
    int n = v.size();
    int count = 1;
    int d = v[0];
    // Recorrer el arreglo y contar las vacas colocadas
    for (int i = 1; i < n; i++) {
        if (v[i] - d >= x) {
            d = v[i];
            count++;
        }
        // Si se han colocado todas las vacas, retornar verdadero
        if (count == c) {
            return true;
        }
    }
    // Si no se han colocado todas las vacas, retornar falso
    return false;
}

// Función principal
int agresivacas(vector<int>& v, int n, int k) {
    // Ordenar el arreglo
    merge_sort(v, 0, n - 1);
    int low = 0, high = v[n - 1] - v[0];
    int ans = 0;
    // Realizar una búsqueda binaria para encontrar la distancia máxima
    while (low <= high) {
        int mid = low + (high - low) / 2;
        // Verificar si es posible colocar las vacas con la distancia dada
        if (ok(v, mid, k)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    // Retornar la distancia máxima encontrada
    return ans;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int N, K;
        cin >> N >> K;
        vector<int> arr(N);
        // Leer los elementos del arreglo
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }
        // Calcular y mostrar la distancia máxima
        int ans = agresivacas(arr, N, K);
        cout << ans << endl;
    }
    return 0;
}
