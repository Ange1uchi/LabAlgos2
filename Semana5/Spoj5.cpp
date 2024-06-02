#include <iostream>
#include <vector>

using namespace std;
// Quicksort no funcionó, así que vamos a usar HeapSort:

// Función para ajustar el subárbol con raíz en i en un heap:
void heapify(vector<vector<int>>& Freq, int n, int i) {
    // Inicializamos el más grande como nodo raíz:
    int bigg = i; 
    // hijo izquierdo
    int izq = 2 * i + 1;
    // hijo derecho
    int dcha = 2 * i + 2; 

    // Si el hijo izquierdo es más grande que el nodo raíz (o padre)
    if (izq < n && (Freq[izq][1] > Freq[bigg][1] || 
        (Freq[izq][1] == Freq[bigg][1] && Freq[izq][2] < Freq[bigg][2]))) {
        bigg = izq;
    }

    // Si el hijo derecho es más grande que el más grande hasta ahora
    if (dcha < n && (Freq[dcha][1] > Freq[bigg][1] || 
        (Freq[dcha][1] == Freq[bigg][1] && Freq[dcha][2] < Freq[bigg][2]))) {
        bigg = dcha;
    }

    // Si el más grande no es el nodo raíz (o padre) intercambiar
    if (bigg != i) {
        swap(Freq[i], Freq[bigg]);

        // Hacemos este proceso recursiva para no afectar el resto del subarbol
        heapify(Freq, n, bigg);
    }
}

void HeapSort(vector<vector<int>>& Freq) {
    int n = Freq.size();

    // Reordenamos el vector Freq para que sea un heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(Freq, n, i);
    }

    // Extraemos uno por uno los elementos del heap
    for (int i = n - 1; i > 0; i--) {
        // Movemos la raíz actual al final (intercambio con una hoja)
        swap(Freq[0], Freq[i]);

        // Llamamos a heapify en el heap reducido
        heapify(Freq, i, 0);
    }
}

// Invertimos el orden del vector, el output es el vector invertido
void invertir_vector(vector<vector<int>>& V) {
    int n = V.size();
    for (int i = 0; i < n / 2; i++) {
        swap(V[i], V[n - 1 - i]);
    }
}

int main() {
    // n es el número de elementos a leer.
    // c es el máximo valor posible de un número.
    int n, c;
    cin >> n >> c;

    // Vector que contiene el número, su frecuencia y su primera posición de aparición:
    vector<vector<int>> Freq;

    // se lee cada número
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        bool num_registrado = false;

        // Verifica si el número ya existe y de ser así aumenta su frecuencia en 1 
        for (auto& item : Freq) {
            if (item[0] == num) {
                item[1]++;
                num_registrado = true;
                break;
            }
        }

        // Si el número no estaba registrado, añadirlo a Freq
        if (!num_registrado) {
            Freq.push_back({num, 1, i});
        }
    }

    // Ordenar el vector
    HeapSort(Freq);

    // Revertimos el vector para obtener el orden correcto
    invertir_vector(Freq);

    // Imprimimos los números ordenados por frecuencia y orden de aparición
    for (const auto& item : Freq) {
        for (int count = 0; count < item[1]; count++) {
            cout << item[0] << " ";
        }
    }
    cout << endl;

    return 0;
}