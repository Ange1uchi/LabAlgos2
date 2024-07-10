#include<bits/stdc++.h>
using namespace std;

long long n;
stack <int> st;
char s[100005];
int m= 0;

int mind[100005];

main(){
    scanf("%s",s);
    n= strlen(s);

    char mini= s[n-1];
    mind[n-1]= n-1;

    // Este bucle inicializa el arreglo mind con los índices de los elementos mínimos hacia la derecha.
for(int i=n-2;i>=0;i--){
        mind[i]= mind[i+1];
        if(s[i]<=mini){
            mini= s[i];
            mind[i]= i;
        }
    }

    // Este bucle procesa los elementos del arreglo s utilizando una pila para mantener un orden.
    while(m<n){
        // Si la pila está vacía, se agrega el índice actual a la pila y se incrementa m.
        if(st.empty()){
            st.push(m++);
            continue;
        }

        // Mientras el elemento en la cima de la pila tenga un índice menor en mind, se agrega m a la pila y se incrementa m.
        while(m<n && st.top()< mind[st.top()])
            st.push(m++);

        // Si el elemento en la cima de la pila es el mínimo hacia la derecha, se imprime y se elimina de la pila.
        if(st.top()==mind[ st.top() ]){
            printf("%c",s[st.top()]);
            st.pop();

            // Si la pila no está vacía, se actualiza el índice del mínimo hacia la derecha para el nuevo elemento en la cima.
            if(st.empty())  continue;

            if(s[mind[m]] < s[st.top()])
                mind[st.top()]= mind[m];
            else
                mind[st.top()]= st.top();
        }
    }

    // Este bucle vacía la pila imprimiendo los elementos restantes.
    while(!st.empty()){
        printf("%c",s[st.top()]);
        st.pop();
    }
}