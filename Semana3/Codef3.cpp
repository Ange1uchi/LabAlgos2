#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

vector<pair<long long,int > > v;
vector<int> ans;

void merge(vector<pair<long long,int>>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; 
    int n2 = right - mid; 

    vector<pair<long long,int>> L(n1);
    vector<pair<long long,int>> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i]; 
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j]; 

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].first <= R[j].first) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<pair<long long,int>>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Calcular el punto medio

        mergeSort(arr, left, mid); // Ordenar el subarreglo izquierdo
        mergeSort(arr, mid + 1, right); // Ordenar el subarreglo derecho

        merge(arr, left, mid, right); // Combinar los subarreglos ordenados
    }
}

int main() {
    int t, n;
    cin >> t; // Casos de prueba

    for(int i = 0; i < t; i++) {
        cin >> n; // Leer el tamaño del arreglo
        v.resize(n); // Redimensionar el vector v
        ans.resize(n); // Redimensionar el vector ans

        for(int j = 0; j < n; j++) {
            cin >> v[j].first; // Leer los valores del arreglo
            v[j].second = j; // Asignar el índice correspondiente a cada valor
        }

        mergeSort(v, 0, n - 1); // Ordenar el arreglo v

        long long ac = 0; // Variable para almacenar la suma acumulada
        int k = 0; // Variable para almacenar el índice límite

        for(int i = 0; i < n; i++) {
            if (i == k) {
                ac += v[i].first; // Sumar el valor actual a la suma acumulada
                k++;
            }
            while (k < n && ac >= v[k].first) {
                ac += v[k].first; // Sumar el valor actual a la suma acumulada
                k++;
            }

            ans[v[i].second] = k - 1; // Asignar el índice límite al elemento correspondiente en ans
        }

        for(int j = 0; j < n; j++) {
            cout << ans[j] << " "; // Imprimir las respuestas
        }
        cout << endl;
    }

    return 0;
}