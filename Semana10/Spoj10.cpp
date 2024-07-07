#include <iostream>
using namespace std;
// El codigo no está tan profundamente explicado pues es una implementación básica de un árbol rojo negro,
// por esto, las funciones de rotacion izq y derecha no estan detalladas a fondo.

// Enumeración para definir los colores de los nodos
enum Color { ROJO, NEGRO };

// Clase Nodo para representar los nodos del árbol rojo-negro
class Nodo {
public:
    int dato; // Valor del nodo
    int pos; // Posición del nodo en el array original
    bool color; // Color del nodo
    Nodo *izquierdo, *derecho, *padre; // Punteros a los hijos izquierdo, derecho y al padre

    Nodo(int dato, int pos) : dato(dato), pos(pos) {
        padre = izquierdo = derecho = nullptr;
        color = ROJO; // Nuevo nodo siempre se inserta como rojo
    }
};

// Clase ArbolRojoNegro para manejar el árbol rojo-negro
class ArbolRojoNegro {
private:
    Nodo *raiz; // Puntero a la raíz del árbol

protected:
    // Funciones para rotaciones y arreglos de inserción
    void rotarIzquierda(Nodo *&, Nodo *&);
    void rotarDerecha(Nodo *&, Nodo *&);
    void arreglarInsercion(Nodo *&);
    Nodo* insertarBST(Nodo* raiz, Nodo *pt);
    Nodo* buscarAyudante(Nodo* raiz, int dato);

public:
    ArbolRojoNegro() { raiz = nullptr; } // Constructor inicializando la raíz como nula
    void insertar(int dato, int pos); // Función para insertar un nuevo nodo
    int buscar(int dato); // Función para buscar un nodo y devolver su posición
};

// Rotación a la izquierda
void ArbolRojoNegro::rotarIzquierda(Nodo *&raiz, Nodo *&pt) {
    Nodo *pt_derecho = pt->derecho;

    pt->derecho = pt_derecho->izquierdo;
    if (pt->derecho != nullptr) pt->derecho->padre = pt;

    pt_derecho->padre = pt->padre;
    if (pt->padre == nullptr)
        raiz = pt_derecho;
    else if (pt == pt->padre->izquierdo)
        pt->padre->izquierdo = pt_derecho;
    else
        pt->padre->derecho = pt_derecho;

    pt_derecho->izquierdo = pt;
    pt->padre = pt_derecho;
}

// Rotación a la derecha
void ArbolRojoNegro::rotarDerecha(Nodo *&raiz, Nodo *&pt) {
    Nodo *pt_izquierdo = pt->izquierdo;

    pt->izquierdo = pt_izquierdo->derecho;
    if (pt->izquierdo != nullptr) pt->izquierdo->padre = pt;

    pt_izquierdo->padre = pt->padre;
    if (pt->padre == nullptr)
        raiz = pt_izquierdo;
    else if (pt == pt->padre->izquierdo)
        pt->padre->izquierdo = pt_izquierdo;
    else
        pt->padre->derecho = pt_izquierdo;

    pt_izquierdo->derecho = pt;
    pt->padre = pt_izquierdo;
}

// Función para arreglar la inserción y mantener las propiedades del árbol rojo-negro
void ArbolRojoNegro::arreglarInsercion(Nodo *&pt) {
    Nodo *padre_pt = nullptr;
    Nodo *abuelo_pt = nullptr;

    while ((pt != raiz) && (pt->color != NEGRO) &&
           (pt->padre != nullptr && pt->padre->color == ROJO)) {
        padre_pt = pt->padre;
        abuelo_pt = pt->padre->padre;

        if (padre_pt == abuelo_pt->izquierdo) {
            Nodo *tio_pt = abuelo_pt->derecho;

            if (tio_pt != nullptr && tio_pt->color == ROJO) {
                abuelo_pt->color = ROJO;
                padre_pt->color = NEGRO;
                tio_pt->color = NEGRO;
                pt = abuelo_pt;
            } else {
                if (pt == padre_pt->derecho) {
                    rotarIzquierda(raiz, padre_pt);
                    pt = padre_pt;
                    padre_pt = pt->padre;
                }
                rotarDerecha(raiz, abuelo_pt);
                swap(padre_pt->color, abuelo_pt->color);
                pt = padre_pt;
            }
        } else {
            Nodo *tio_pt = abuelo_pt->izquierdo;

            if (tio_pt != nullptr && tio_pt->color == ROJO) {
                abuelo_pt->color = ROJO;
                padre_pt->color = NEGRO;
                tio_pt->color = NEGRO;
                pt = abuelo_pt;
            } else {
                if (pt == padre_pt->izquierdo) {
                    rotarDerecha(raiz, padre_pt);
                    pt = padre_pt;
                    padre_pt = pt->padre;
                }
                rotarIzquierda(raiz, abuelo_pt);
                swap(padre_pt->color, abuelo_pt->color);
                pt = padre_pt;
            }
        }
    }
    raiz->color = NEGRO; // La raíz siempre debe ser negra
}

// Función auxiliar para insertar un nodo en el árbol binario de búsqueda
Nodo* ArbolRojoNegro::insertarBST(Nodo* raiz, Nodo *pt) {
    if (raiz == nullptr) return pt;

    if (pt->dato < raiz->dato) {
        raiz->izquierdo = insertarBST(raiz->izquierdo, pt);
        raiz->izquierdo->padre = raiz;
    } else if (pt->dato > raiz->dato) {
        raiz->derecho = insertarBST(raiz->derecho, pt);
        raiz->derecho->padre = raiz;
    }

    return raiz;
}

// Función para insertar un nuevo nodo y arreglar el árbol rojo-negro
void ArbolRojoNegro::insertar(int dato, int pos) {
    Nodo *pt = new Nodo(dato, pos);
    raiz = insertarBST(raiz, pt);
    arreglarInsercion(pt);
}

// Función auxiliar para buscar un nodo en el árbol
Nodo* ArbolRojoNegro::buscarAyudante(Nodo* raiz, int dato) {
    if (raiz == nullptr || raiz->dato == dato) return raiz;
    if (dato < raiz->dato) return buscarAyudante(raiz->izquierdo, dato);
    return buscarAyudante(raiz->derecho, dato);
}

// Función para buscar un nodo y devolver su posición
int ArbolRojoNegro::buscar(int dato) {
    Nodo* resultado = buscarAyudante(raiz, dato);
    return (resultado != nullptr) ? resultado->pos : -1;
}

int main() {
    ios_base::sync_with_stdio(false); // Optimización de entrada/salida
    cin.tie(nullptr); // Desacopla cin de cout

    int N, Q;
    cin >> N >> Q;

    ArbolRojoNegro arbol;
    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;
        arbol.insertar(num, i);
    }

    for (int i = 0; i < Q; ++i) {
        int consulta;
        cin >> consulta;
        cout << arbol.buscar(consulta) << '\n';
    }

    return 0;
}
