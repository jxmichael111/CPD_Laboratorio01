#include <iostream>
#include <chrono>
using namespace std;

const int N = 2000;

int main() {
    static double A[N][N];
    static double x[N], y[N];

    // Inicializamos A con unos, x con unos y y con ceros
    for (int i = 0; i < N; i++) {
        x[i] = 1.0;
        y[i] = 0.0;
        for (int j = 0; j < N; j++) {
            A[i][j] = 1.0;
        }
    }

    // Primer bucle (recorrido por filas)
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double> tiempoFila = t2 - t1;
    cout << "Tiempo recorrido por filas: " << tiempoFila.count() << " s" << endl;

    // Reiniciamos y a 0
    for (int i = 0; i < N; i++) y[i] = 0.0;

    // Segundo bucle (recorrido por columnas)
    auto t3 = chrono::high_resolution_clock::now();
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
    auto t4 = chrono::high_resolution_clock::now();
    chrono::duration<double> tiempoColumna = t4 - t3;
    cout << "Tiempo recorrido por columnas: " << tiempoColumna.count() << " s" << endl;

    return 0;
}
