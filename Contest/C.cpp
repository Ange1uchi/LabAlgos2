#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Leer el número de piezas de sushi
    int n;
    cin >> n;

    // Crear un vector para almacenar los tipos de sushi
    vector<int> t(n);

    // Leer los tipos de sushi
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    // Inicializar las variables
    // last: el último tipo de sushi
    // cur: la longitud del segmento actual de sushi del mismo tipo
    // next: la longitud del siguiente segmento de sushi del mismo tipo
    // max_len: la longitud máxima de un segmento válido de sushi
    int last = -1, cur = 0, next = 0, max_len = 0;

    // Recorrer los tipos de sushi
    for (int i = 0; i < n; i++) {
        // Si el sushi actual es del mismo tipo que el último
        if (t[i] == last) {
            // Incrementar la longitud del segmento actual
            cur++;
        } else {
            // Si el sushi actual es de un tipo diferente
            // Actualizar la longitud máxima con el mínimo de cur y next multiplicado por 2
            max_len = max(max_len, min(cur, next) * 2);
            // Actualizar next con cur
            next = cur;
            // Reiniciar cur
            cur = 1;
            // Actualizar last con el tipo de sushi actual
            last = t[i];
        }
    }

    // Después del bucle, actualizar max_len una vez más
    max_len = max(max_len, min(cur, next) * 2);

    // Imprimir la longitud máxima de un segmento válido de sushi
    cout << max_len << endl;

    return 0;
}