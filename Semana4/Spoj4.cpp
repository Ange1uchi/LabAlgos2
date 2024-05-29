#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;
typedef long long ll;

void add(const vector<vector<ll>>& A, const vector<vector<ll>>& B, vector<vector<ll>>& C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(const vector<vector<ll>>& A, const vector<vector<ll>>& B, vector<vector<ll>>& C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(vector<vector<ll>>& A, vector<vector<ll>>& B, vector<vector<ll>>& C, int n);

int main() {
    uint32_t n, i, j, d1, p1, r1, m1, d2, p2, r2, m2;
    cin >> n >> p1 >> d1 >> r1 >> m1 >> p2 >> d2 >> r2 >> m2;

    vector<vector<ll>> A(n, vector<ll>(n));
    vector<vector<ll>> B(n, vector<ll>(n));
    vector<vector<ll>> C(n, vector<ll>(n));
    vector<ll> V(n);

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            d1 = d1 * p1 + r1;
            d2 = d2 * p2 + r2;
            A[i][j] = d1 >> (32 - m1);
            B[i][j] = d2 >> (32 - m2);
        }
    }

    strassen(A, B, C, n);


    for (i = 0; i < n; ++i) {
        V[i] = 0;
        for (j = 0; j < n; ++j) {
            V[i] ^= C[i][j];
        }
    }

    for (i = 0; i < n; ++i) {
        cout << V[i] << (i < n - 1 ? " " : "\n");
    }

    return 0;
}

void strassen(vector<vector<ll>>& A, vector<vector<ll>>& B, vector<vector<ll>>& C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    vector<vector<ll>> a11(newSize, vector<ll>(newSize));
    vector<vector<ll>> a12(newSize, vector<ll>(newSize));
    vector<vector<ll>> a21(newSize, vector<ll>(newSize));
    vector<vector<ll>> a22(newSize, vector<ll>(newSize));
    vector<vector<ll>> b11(newSize, vector<ll>(newSize));
    vector<vector<ll>> b12(newSize, vector<ll>(newSize));
    vector<vector<ll>> b21(newSize, vector<ll>(newSize));
    vector<vector<ll>> b22(newSize, vector<ll>(newSize));

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newSize];
            a21[i][j] = A[i + newSize][j];
            a22[i][j] = A[i + newSize][j + newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newSize];
            b21[i][j] = B[i + newSize][j];
            b22[i][j] = B[i + newSize][j + newSize];
        }
    }

    vector<vector<ll>> p1(newSize, vector<ll>(newSize));
    vector<vector<ll>> p2(newSize, vector<ll>(newSize));
    vector<vector<ll>> p3(newSize, vector<ll>(newSize));
    vector<vector<ll>> p4(newSize, vector<ll>(newSize));
    vector<vector<ll>> p5(newSize, vector<ll>(newSize));
    vector<vector<ll>> p6(newSize, vector<ll>(newSize));
    vector<vector<ll>> p7(newSize, vector<ll>(newSize));

    vector<vector<ll>> aResult(newSize, vector<ll>(newSize));
    vector<vector<ll>> bResult(newSize, vector<ll>(newSize));


    add(a11, a22, aResult, newSize); // a11 + a22
    add(b11, b22, bResult, newSize); // b11 + b22
    strassen(aResult, bResult, p1, newSize); // p1 = (a11+a22) * (b11+b22)

    add(a21, a22, aResult, newSize); // a21 + a22
    strassen(aResult, b11, p2, newSize); // p2 = (a21+a22) * (b11)

    subtract(b12, b22, bResult, newSize); // b12 - b22
    strassen(a11, bResult, p3, newSize); // p3 = (a11) * (b12 - b22)

    subtract(b21, b11, bResult, newSize); // b21 - b11
    strassen(a22, bResult, p4, newSize); // p4 = (a22) * (b21 - b11)

    add(a11, a12, aResult, newSize); // a11 + a12
    strassen(aResult, b22, p5, newSize); // p5 = (a11+a12) * (b22)   

    subtract(a21, a11, aResult, newSize); // a21 - a11
    add(b11, b12, bResult, newSize); // b11 + b12
    strassen(aResult, bResult, p6, newSize); // p6 = (a21-a11) * (b11+b12)

    subtract(a12, a22, aResult, newSize); // a12 - a22
    add(b21, b22, bResult, newSize); // b21 + b22
    strassen(aResult, bResult, p7, newSize); // p7 = (a12-a22) * (b21+b22)

    // Calculate c11, c12, c21, c22
    vector<vector<ll>> c11(newSize, vector<ll>(newSize));
    vector<vector<ll>> c12(newSize, vector<ll>(newSize));
    vector<vector<ll>> c21(newSize, vector<ll>(newSize));
    vector<vector<ll>> c22(newSize, vector<ll>(newSize));

    add(p1, p4, aResult, newSize); // p1 + p4
    add(aResult, p7, bResult, newSize); // p1 + p4 + p7
    subtract(bResult, p5, c11, newSize); // c11 = p1 + p4 - p5 + p7

    add(p3, p5, c12, newSize); // c12 = p3 + p5

    add(p2, p4, c21, newSize); // c21 = p2 + p4

    add(p1, p3, aResult, newSize); // p1 + p3
    add(aResult, p6, bResult, newSize); // p1 + p3 + p6
    subtract(bResult, p2, c22, newSize); // c22 = p1 + p3 - p2 + p6

    // Combinar los resultados en C
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }
    }
}