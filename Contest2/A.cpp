#include <bits/stdc++.h>
using namespace std;
int main()
{   
    ios::sync_with_stdio(false);
    int n, m;
    cin >> m >> n;
    bool B[m][n], A[m][n], C[m][n];
    for (int i = 0; i < m; ++i)
    {
    	for (int j = 0; j < n; ++j)
    	{
    		cin >> B[i][j];
    		A[i][j] = 1;
    		C[i][j] = 0;
    	}
    }
    // Inicialización de la matriz B, A, y C.
for (int i = 0; i < m; ++i)
{
    for (int j = 0; j < n; ++j)
    {
        // Si un elemento en B es 0, entonces toda la fila y columna correspondiente en A debe ser 0.
        // Esto se debe a que un 0 en B indica que no hubo ningún 1 en esa fila y columna en A.
        if (B[i][j] == 0)
        {
            // Establecer toda la fila i en A a 0
            for (int k = 0; k < n; ++k)
            {
                A[i][k] = 0;
            }
            // Establecer toda la columna j en A a 0
            for (int k = 0; k < m; ++k)
            {
                A[k][j] = 0;
            }
        }
    }
}

// Intentar reconstruir B a partir de A y almacenar el resultado en C.
for (int i = 0; i < m; ++i)
{
    for (int j = 0; j < n; ++j)
    {
        // Si el elemento en A es 1, entonces la operación OR resultará en 1 para esa fila y columna.
        if (A[i][j])
        {
            // Establecer toda la fila i en C a 1
            for (int k = 0; k < n; ++k)
            {
                C[i][k] = 1;
            }
            // Establecer toda la columna j en C a 1
            for (int k = 0; k < m; ++k)
            {
                C[k][j] = 1;
            }
        }
    }
}

// Verificar si la matriz C reconstruida es igual a la matriz B dada.
for (int i = 0; i < m; ++i)
{
    for (int j = 0; j < n; ++j)
    {
        // Si hay una discrepancia entre C y B, entonces es imposible reconstruir A a partir de B.
        if (C[i][j] != B[i][j])
        {
            cout << "NO\n";
            return 0; // Terminar el programa si se encuentra una discrepancia.
        }
    }
}

// Si todas las comparaciones son iguales, es posible reconstruir A a partir de B.
cout << "YES\n";
// Imprimir la matriz A.
for (int i = 0; i < m; ++i)
{
    for (int j = 0; j < n; ++j)
    {
        cout << A[i][j] << " ";
    }
    cout << "\n";
}
return 0;
}