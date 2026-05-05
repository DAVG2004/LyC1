#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono> 
#include <iomanip>

using namespace std;

void ejecutarCalculo(int n, double x, string nombreArchivo) {
    
    auto inicio = chrono::high_resolution_clock::now();

   
    double* coef = new double[1];
    coef[0] = 1.0;

    for (int i = 1; i <= n; i++) {
        double* nuevaFila = new double[i + 1];
        nuevaFila[0] = nuevaFila[i] = 1.0;
        for (int j = 1; j < i; j++) {
            nuevaFila[j] = coef[j - 1] + coef[j]; 
        }
        delete[] coef; 
        coef = nuevaFila;
    }

    
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo." << endl;
        return;
    }

    archivo << "--- RESULTADOS PARA (x+1)^" << n << " ---" << endl;
    archivo << "Valor de x: " << x << "\n" << endl;

    
    archivo << "Polinomio extendido:" << endl;
    for (int i = 0; i <= n; i++) {
        int potencia = n - i;
        if (potencia == 0) archivo << coef[i];
        else if (coef[i] == 1) archivo << "x^" << potencia << " + ";
        else archivo << fixed << setprecision(0) << coef[i] << "x^" << potencia << " + ";
    }
    archivo << "\n\nEvaluacion paso a paso:" << endl;

   
    double resultadoF = 0;
    for (int i = 0; i <= n; i++) {
        int exp = n - i;
        double valPot = pow(x, exp);
        double termino = coef[i] * valPot;
        archivo << "  Paso " << i + 1 << ": " << coef[i] << " * (" << x << "^" << exp << ") = " << termino << endl;
        resultadoF += termino;
    }

   
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> tiempoTotal = fin - inicio;

   
    archivo << "\n" << string(40, '=') << endl;
    archivo << "RESULTADO FINAL f(" << x << "): " << resultadoF << endl;
    archivo << "TIEMPO DE EJECUCION: " << fixed << setprecision(6) << tiempoTotal.count() << " segundos" << endl;
    archivo << string(40, '=') << endl;

    archivo.close();
    delete[] coef; 
    
    cout << "\nProceso completado. Resultados guardados en: " << nombreArchivo << endl;
}

int main() {
    int nObjetivo = 100;
    double xUsuario;

    cout << "Evaluando (x+1)^" << nObjetivo << " en C++." << endl;
    cout << "Ingrese el valor de x: ";
    if (!(cin >> xUsuario)) {
        cout << "Entrada invalida." << endl;
        return 1;
    }

    ejecutarCalculo(nObjetivo, xUsuario, "resultado_cpp_n100.txt");

    return 0;
}