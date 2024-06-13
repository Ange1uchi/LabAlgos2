#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Función para verificar si un carácter es un paréntesis de apertura
bool op(char ch) {
    return ch == '(' || ch == '{' || ch == '[' || ch == '<';
}

// Función para verificar si un carácter es un paréntesis de cierre
bool cls(char ch) {
    return ch == ')' || ch == '}' || ch == ']' || ch == '>';
}

// Función para obtener el paréntesis de apertura correspondiente a un paréntesis de cierre
char check(char ch) {
    if (ch == ')') return '(';
    if (ch == '}') return '{';
    if (ch == ']') return '[';
    if (ch == '>') return '<';
    return '\0';
}

// Función para calcular el número mínimo de reemplazos necesarios para equilibrar los paréntesis
int reemplazos(string s) {
    vector<char> st;  // Usamos un vector como pila para almacenar los paréntesis de apertura
    int replacements = 0;  // Contador de reemplazos

    // Iteramos sobre cada carácter en la cadena
    for (char ch : s) {
        if (op(ch)) {
            // Si el carácter es un paréntesis de apertura, lo agregamos a la pila
            st.push_back(ch);
        } else if (cls(ch)) {
            // Si el carácter es un paréntesis de cierre, verificamos si la pila está vacía
            if (st.empty()) {
                // Si la pila está vacía, no podemos equilibrar los paréntesis, por lo que retornamos -1
                return -1;
            }
            // Obtenemos el paréntesis de apertura en la cima de la pila
            char top = st.back();
            st.pop_back();
            // Si el paréntesis de apertura en la cima de la pila no corresponde al paréntesis de cierre actual, incrementamos el contador de reemplazos
            if (check(ch) != top) {
                replacements++;
            }
        }
    }

    // Si la pila no está vacía después de iterar sobre todos los caracteres, no podemos equilibrar los paréntesis, por lo que retornamos -1
    if (!st.empty()) {
        return -1;
    }

    // Retornamos el número mínimo de reemplazos necesarios para equilibrar los paréntesis
    return replacements;
}
int main() {
    string s;
    cin >> s;

    int result = reemplazos(s);
    if (result == -1) {
        cout << "Impossible" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}