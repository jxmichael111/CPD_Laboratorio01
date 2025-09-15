#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
using namespace std;

void multiplicarMatrices(const vector<vector<double>>& A,
                         const vector<vector<double>>& B,
                         vector<vector<double>>& C,
                         int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double suma = 0.0;
            for (int k = 0; k < n; k++) {
                suma += A[i][k] * B[k][j];
            }
            C[i][j] = suma;
        }
    }
}

int main() {
    // Diferentes tamaños de matriz
    vector<int> tamanos = {200, 400, 600, 800};

    for (int n : tamanos) {
        vector<vector<double>> A(n, vector<double>(n));
        vector<vector<double>> B(n, vector<double>(n));
        vector<vector<double>> C(n, vector<double>(n, 0.0));

        // Inicializar con valores aleatorios 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }

        auto inicio = chrono::high_resolution_clock::now();
        multiplicarMatrices(A, B, C, n);
        auto fin = chrono::high_resolution_clock::now();

        chrono::duration<double> duracion = fin - inicio;
        cout << "n = " << n << " -> tiempo: " << duracion.count() << " s" << endl;
    }

    return 0;
}
