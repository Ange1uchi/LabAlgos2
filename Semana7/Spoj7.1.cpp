#include <iostream>
using namespace std;

// Definición de la estructura de un nodo de la lista enlazada
struct Node {
    int data; // Dato almacenado en el nodo
    Node* next; // Puntero al siguiente nodo en la lista
};

// Definición de la clase Stack que implementa una pila usando una lista enlazada
class Stack {
private:
    Node* top; // Puntero al nodo superior de la pila
public:
    // Inicializa el puntero superior a nullptr indicando que la pila está vacía
    Stack() { top = nullptr; }
    
    // Método para agregar un elemento a la pila
    void push(int x) {
        Node* newNode = new Node(); // Crea un nuevo nodo
        newNode->data = x; // Asigna el dato al nodo
        newNode->next = top; // El siguiente nodo del nuevo nodo es el actual top
        top = newNode; // El nuevo nodo se convierte en el top de la pila
    }
    
    // Método para verificar si la pila está vacía
    bool isEmpty() {
        return top == nullptr; // Retorna true si top es nullptr, lo que indica que la pila está vacía
    }
    
    // Método para eliminar el elemento superior de la pila
    void pop() {
        if (isEmpty()) { // Verifica si la pila está vacía
            cout << "Stack is empty" << endl;
            return;
        }
        Node* temp = top; // Guarda el nodo superior actual en temp
        top = top->next; // Mueve el top al siguiente nodo
        delete temp; // Elimina el nodo superior anterior
    }
    
    // Método para obtener el elemento superior de la pila sin eliminarlo
    int peek() {
        if (isEmpty()) { // Verifica si la pila está vacía
            cout << "Stack is empty" << endl;
            return -1; // Retorna -1 si la pila está vacía
        }
        return top->data; // Retorna el dato del nodo superior
    }
};

int main() {
    int t; scanf("%d", &t); // Lee el número de operaciones a realizar
    Stack s; // Crea una instancia de la pila
    while (t--) {
        // El código para manejar las operaciones de la pila se agregará aquí
    }
}