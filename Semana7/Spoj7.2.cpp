#include <iostream>
using namespace std;

struct Node {
    int data; // Almacena el dato del nodo
    Node* next; // Puntero al siguiente nodo en la cola
    
    // Constructor para inicializar un nodo con datos y establecer el siguiente como nullptr
    Node(int data) : data(data), next(nullptr) {}
};

class Queue {
private:
    Node* front; // Puntero al primer nodo de la cola
    Node* rear; // Puntero al último nodo de la cola
public:
    // Constructor para inicializar una cola vacía
    Queue() : front(nullptr), rear(nullptr) {}
    
    // Función para agregar un nuevo elemento al final de la cola
    void enqueue(int data) {
        Node* newNode = new Node(data); // Crea un nuevo nodo con el dato dado
        if (rear == nullptr) {
            // Si la cola está vacía, tanto front como rear apuntan al nuevo nodo
            front = rear = newNode;
            return;
        }
        // De lo contrario, agrega el nuevo nodo al final de la cola y actualiza rear
        rear->next = newNode;
        rear = newNode;
    }
    
    // Función para eliminar el elemento del frente de la cola
    void dequeue() {
        if (front == nullptr) return; // Si la cola está vacía, no hace nada
        Node* temp = front; // Puntero temporal al primer nodo
        front = front->next; // Mueve front al siguiente nodo
        if (front == nullptr) rear = nullptr; // Si la cola queda vacía, actualiza rear a nullptr
        delete temp; // Elimina el antiguo nodo del frente
    }
    
    // Función para obtener el dato del elemento al frente de la cola
    int getFront() {
        if (front == nullptr) return -1; // Si la cola está vacía, retorna -1
        return front->data; // Retorna el dato del nodo del frente
    }
    
    // Función para verificar si la cola está vacía
    bool isEmpty() {
        return front == nullptr; // Retorna true si front es nullptr, indicando que la cola está vacía
    }
};

int main() {
    int t; scanf("%d", &t); // Lee el número de operaciones
    Queue q; // Crea una instancia de Queue
    while (t--) {
        int operation; scanf("%d", &operation); // Lee el tipo de operación
        if (operation == 1) {
            int x; scanf("%d", &x); // Para la operación enqueue, lee el dato a agregar
            q.enqueue(x); // Agrega el dato a la cola
        } else if (operation == 2) {
            q.dequeue(); // Para la operación dequeue, elimina el elemento del frente de la cola
        } else if (operation == 3) {
            // Para la operación de obtener el elemento del frente, verifica si la cola está vacía
            if (q.isEmpty()) printf("Empty!\n"); // Si está vacía, imprime "Empty!"
            else printf("%d\n", q.getFront()); // De lo contrario, imprime el dato del elemento del frente
        }
    }
    return 0;
}