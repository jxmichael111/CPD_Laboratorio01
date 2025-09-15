#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
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

void multiplicarPorBloques(const vector<vector<double>>& A,
                           const vector<vector<double>>& B,
                           vector<vector<double>>& C,
                           int n, int tamBloque) {
    for (int ii = 0; ii < n; ii += tamBloque) {
        for (int jj = 0; jj < n; jj += tamBloque) {
            for (int kk = 0; kk < n; kk += tamBloque) {
                int iMax = min(ii + tamBloque, n);
                int jMax = min(jj + tamBloque, n);
                int kMax = min(kk + tamBloque, n);
                for (int i = ii; i < iMax; i++) {
                    for (int k = kk; k < kMax; k++) {
                        double a = A[i][k];
                        for (int j = jj; j < jMax; j++) {
                            C[i][j] += a * B[k][j];
                        }
                    }
                }
            }
        }
    }
}


double diferenciaMaxima(const vector<vector<double>>& X,
                        const vector<vector<double>>& Y, int n) {
    double maxDiff = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double d = fabs(X[i][j] - Y[i][j]);
            if (d > maxDiff) maxDiff = d;
        }
    }
    return maxDiff;
}

int main() {
    vector<int> tamanos = {200, 400}; 
    vector<int> bloques = {8, 16, 32, 64}; 

    for (int n : tamanos) {
        cout << "=== n = " << n << " ===" << endl;

        vector<vector<double>> A(n, vector<double>(n));
        vector<vector<double>> B(n, vector<double>(n));
        vector<vector<double>> C1(n, vector<double>(n, 0.0));
        vector<vector<double>> C2(n, vector<double>(n, 0.0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }

        // clasica
        auto inicio1 = chrono::high_resolution_clock::now();
        multiplicarMatrices(A, B, C1, n);
        auto fin1 = chrono::high_resolution_clock::now();
        chrono::duration<double> tiempoClasico = fin1 - inicio1;
        cout << "Clasica: " << tiempoClasico.count() << " s" << endl;

        //  bloques
        for (int tamBloque : bloques) {
            // Reiniciar C2 a 0
            for (int i = 0; i < n; i++) {
                fill(C2[i].begin(), C2[i].end(), 0.0);
            }

            auto inicio2 = chrono::high_resolution_clock::now();
            multiplicarPorBloques(A, B, C2, n, tamBloque);
            auto fin2 = chrono::high_resolution_clock::now();
            chrono::duration<double> tiempoBloques = fin2 - inicio2;

            double diff = diferenciaMaxima(C1, C2, n);

            cout << "Bloques " << tamBloque
                 << " -> " << tiempoBloques.count() << " s"
                 << " (speedup = " << tiempoClasico.count() / tiempoBloques.count() << "x)"
                 << " diferencia = " << diff << endl;
        }

        cout << endl;
    }

    return 0;
}
