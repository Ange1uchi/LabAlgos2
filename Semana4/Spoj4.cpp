#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

using namespace std;

/* Ajustar las dimensiones de las matrices para que sean potencias
   de 2, lo cual es necesario para el algoritmo de Strassen.*/
int nextpow2(int k){
    return pow(2, int(ceil(log2(k))));
}


// Opera la suma de Matrices A y B y almacena el resultado en C.
void sumarMatrices(const vector<vector<uint64_t>> &A, const vector<vector<uint64_t>> &B, vector<vector<uint64_t>> &C, int Dims){
    for (int i = 0; i < Dims; i++){
        for (int j = 0; j < Dims; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
// Opera la resta de Matrices A y B y almacena el resultado en C.
void restarMatrices(const vector<vector<uint64_t>> &A, const vector<vector<uint64_t>> &B, vector<vector<uint64_t>> &C, int Dims){
    for (int i = 0; i < Dims; i++){
        for (int j = 0; j < Dims; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Opera el producto estándar de dos matrices y almacena el resultado en C.
void MultiBasic(const vector<vector<uint64_t>> &A, const vector<vector<uint64_t>> &B, vector<vector<uint64_t>> &C, int Dims) {
    for (int i = 0; i < Dims; ++i) {
        for (int j = 0; j < Dims; ++j) {
            // Inicializamos C en 0.
            C[i][j] = 0;
            for (int k = 0; k < Dims; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Algoritmo de Strassen para multiplicar dos matrices.
void Strassen(const vector<vector<uint64_t>> &A, const vector<vector<uint64_t>> &B, vector<vector<uint64_t>> &C, int Dims, int lim_estandar)
{
     // Si la dimensión de las matrices es menor o igual al límite establecido, se realiza la multiplicación estándar:
    if (Dims <= lim_estandar)
    {
        MultiBasic(A, B, C, Dims);
        return;
    }

     // Calculamos la dimensión de las submatrices:
    int dim_nueva = Dims / 2;
    

    /* Inicializamos vectores temporales para las submatrices A, B y C, así como para los
       productos parciales p_1 a p_7. También un nuevo vector z de tamaño dim_nueva lleno de ceros:*/
    vector<uint64_t> z(dim_nueva);
    vector<vector<uint64_t>>
        a_11(dim_nueva, z), a_12(dim_nueva, z), a_21(dim_nueva, z), a_22(dim_nueva, z),
        b_11(dim_nueva, z), b_12(dim_nueva, z), b_21(dim_nueva, z), b_22(dim_nueva, z),
        c_11(dim_nueva, z), c_12(dim_nueva, z), c_21(dim_nueva, z), c_22(dim_nueva, z),
        p_1(dim_nueva, z), p_2(dim_nueva, z), p_3(dim_nueva, z), p_4(dim_nueva, z),
        p_5(dim_nueva, z), p_6(dim_nueva, z), p_7(dim_nueva, z),
        Result_a(dim_nueva, z), Result_b(dim_nueva, z);

    // Dividimos las matrices A y B en 4 submatrices cada una:
    // filas (i) columnas (j)
    int i, j;
    for (i = 0; i < dim_nueva; i++)
    {
        for (j = 0; j < dim_nueva; j++)
        {
            // elementos superiores izquierdos de A:
            a_11[i][j] = A[i][j];
            // elementos superiores derechos de A:
            a_12[i][j] = A[i][j + dim_nueva];
            // elementos inferiores izquierdos de A:
            a_21[i][j] = A[i + dim_nueva][j];
            // elementos inferiores derechos de A:
            a_22[i][j] = A[i + dim_nueva][j + dim_nueva];

          // Lo mismo que arriba pero para B:
            b_11[i][j] = B[i][j];
            b_12[i][j] = B[i][j + dim_nueva];
            b_21[i][j] = B[i + dim_nueva][j];
            b_22[i][j] = B[i + dim_nueva][j + dim_nueva];
        }
    }

    // Calcular p_1 a p_7.
    
    //p_1 = (a_11 + a_22) * (b_11 + b_22)
    sumarMatrices(a_11, a_22, Result_a, dim_nueva);
    sumarMatrices(b_11, b_22, Result_b, dim_nueva);
    Strassen(Result_a, Result_b, p_1, dim_nueva, lim_estandar);

    // p_2 = (a_21 + a_22) * b_11
    sumarMatrices(a_21, a_22, Result_a, dim_nueva);
    Strassen(Result_a, b_11, p_2, dim_nueva, lim_estandar);

    // p_3 = a_11 * (b_12 - b_22)
    restarMatrices(b_12, b_22, Result_b, dim_nueva);
    Strassen(a_11, Result_b, p_3, dim_nueva, lim_estandar);

    // p_4 = a_22 * (b_21 - b_11)
    restarMatrices(b_21, b_11, Result_b, dim_nueva);
    Strassen(a_22, Result_b, p_4, dim_nueva, lim_estandar);

    // p_5 = (a_11 + a_12) * b_22
    sumarMatrices(a_11, a_12, Result_a, dim_nueva);
    Strassen(Result_a, b_22, p_5, dim_nueva, lim_estandar);

    // p_6 = (a_21 - a_11) * (b_11 + b_12)
    restarMatrices(a_21, a_11, Result_a, dim_nueva);
    sumarMatrices(b_11, b_12, Result_b, dim_nueva);
    Strassen(Result_a, Result_b, p_6, dim_nueva, lim_estandar);

    // p_7 = (a_12 - a_22) * (b_21 + b_22)
    restarMatrices(a_12, a_22, Result_a, dim_nueva);
    sumarMatrices(b_21, b_22, Result_b, dim_nueva);
    Strassen(Result_a, Result_b, p_7, dim_nueva, lim_estandar);

    // con lo anterior, calculamos las submatrices resultantes c_ij:

    // c_12 = p_3 + p_5
    sumarMatrices(p_3, p_5, c_12, dim_nueva);
    // c_21 = p_2 + p_4
    sumarMatrices(p_2, p_4, c_21, dim_nueva);
    
    // p_1 + p_4
    sumarMatrices(p_1, p_4, Result_a, dim_nueva);
    // lo anterior: (p1_ + p_4) + p_7
    sumarMatrices(Result_a, p_7, Result_b, dim_nueva);
    // c_11 = p_1 + p_4 - p_5 + p_7
    restarMatrices(Result_b, p_5, c_11, dim_nueva);

    // p_1 + p_3
    sumarMatrices(p_1, p_3, Result_a, dim_nueva);
    // lo anterior: (p_1 + p_3) + p_6
    sumarMatrices(Result_a, p_6, Result_b, dim_nueva);
    // c_22 = p_1 + p_3 - p_2 + p_6
    restarMatrices(Result_b, p_2, c_22, dim_nueva);

    // Agrupamos las submatrices resultantes c_ij en la matriz C:
    for (i = 0; i < dim_nueva; i++)
    {
        for (j = 0; j < dim_nueva; j++)
        {
            C[i][j] = c_11[i][j];
            C[i][j + dim_nueva] = c_12[i][j];
            C[i + dim_nueva][j] = c_21[i][j];
            C[i + dim_nueva][j + dim_nueva] = c_22[i][j];
        }
    }
}

int main() {

    uint32_t n, i, j, d1, p_1, r1, m1, d2, p_2, r2, m2;
    cin >> n >> p_1 >> d1 >> r1 >> m1 >> p_2 >> d2 >> r2 >> m2;

    /* se inicializan las matrices A, B y C de tamaño n x n, y el vector V de tamaño n
       con valores de 0, este vector almacenará los valores resultantes de las operaciones:*/
    vector<vector<uint32_t>> A(n, vector<uint32_t>(n));
    vector<vector<uint32_t>> B(n, vector<uint32_t>(n));
    vector<vector<uint64_t>> C(n, vector<uint64_t>(n));
    vector<uint64_t> V(n, 0);

    /* se generan las matirces A y B utilizando las variables de entrada: */
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            d1 = d1 * p_1 + r1;
            d2 = d2 * p_2 + r2;
            A[i][j] = d1 >> (32 - m1);
            B[i][j] = d2 >> (32 - m2);
        }
    }

    /* se calcula la dimensión nueva como la siguiente potencia de 2 mayor o igual a n y se
       inicializa A_exp, B_exp y C_exp llenas de 0, estas son las que utilizaremos para realizar
       todo el algoritmo de Strassen. */
    int dim_nueva = nextpow2(n);
    vector<uint64_t> z(dim_nueva);
    vector<vector<uint64_t>> A_exp(dim_nueva, z), B_exp(dim_nueva, z), C_exp(dim_nueva, z);

    /* los valores de las matrices A y B se copian a A_exp y B_exp: */
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            A_exp[i][j] = static_cast<uint64_t>(A[i][j]);
            B_exp[i][j] = static_cast<uint64_t>(B[i][j]);
        }
    }

    // límite para cambiar a multiplicación estándar cuando el tamaño es pequeño:
    int lim_estandar = 64; 
    // calculo del algoritmo de Strassen: 
    Strassen(A_exp, B_exp, C_exp, dim_nueva, lim_estandar);

    // copiamos los resultados de C_exp a la matriz original C:
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            C[i][j] = C_exp[i][j];
        }
    }

    for (i = 0; i < n; ++i) {
        V[i] = 0;
        for (j = 0; j < n; ++j) {
            V[i] ^= C[i][j];
        }
    }

    // se imprimen los valores de V separados por espacios:
    for (i = 0; i < n; ++i) {
        cout << V[i] << " ";
    }
    cout << endl;

    return 0;
}