#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bloom_filter.hpp"
#include "utils.hpp"

using namespace std;

int main() {
    // Leer nombres desde los archivos CSV
    vector<string> names = readFromCSV("Popular-Baby-Names.csv");
    vector<string> filmNames = readFromCSV("Film-Names.csv");

    // Tamaños de N y proporciones p a experimentar
    vector<size_t> N_values = {1024, 4096, 16384, 65536};  // 2^10, 2^12, 2^14, 2^16
    vector<double> p_values = {0.0, 0.25, 0.5, 0.75, 1.0};
    vector<size_t> k_values = {3, 5, 7, 10};         // Diferentes valores de k para experimentar
    vector<size_t> m_values = {5000, 10000, 20000};  // Diferentes tamaños del arreglo

    // Archivo de salida
    ofstream outputFile("resultados.csv");
    outputFile << "N,p,k,m,TiempoSinBloom,TiempoConBloom,ErrorRate\n";

    // Realizar experimentación
    for (size_t N : N_values) {
        for (double p : p_values) {
            for (size_t k : k_values) {
                for (size_t m : m_values) {
                    // Crear el filtro de Bloom con los valores actuales de k y m
                    BloomFilter bloomFilter(m, k);

                    // Añadir nombres al filtro de Bloom
                    for (const auto& name : names) {
                        bloomFilter.add(name);
                    }

                    vector<string> testSequence = generateTestSequence(names, filmNames, N, p);

                    // Búsqueda sin filtro de Bloom
                    auto start = chrono::high_resolution_clock::now();
                    for (const auto& name : testSequence) {
                        find(names.begin(), names.end(), name);
                    }
                    auto end = chrono::high_resolution_clock::now();
                    auto timeWithoutBloom = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                    // Búsqueda con filtro de Bloom
                    auto start_wb = chrono::high_resolution_clock::now();
                    for (const auto& name : testSequence) {
                        if (bloomFilter.contains(name)) {
                            find(names.begin(), names.end(), name);
                        }
                    }
                    auto end_wb = chrono::high_resolution_clock::now();
                    auto timeWithBloom = chrono::duration_cast<chrono::milliseconds>(end_wb - start_wb).count();

                    // Calcular porcentaje de error del filtro de Bloom
                    size_t falsePositivesCount = 0;
                    vector<string> falsePositives;
                    for (const auto& name : testSequence) {
                        if (bloomFilter.contains(name) && find(names.begin(), names.end(), name) == names.end()) {
                            falsePositives.push_back(name);
                            falsePositivesCount++;
                        }
                    }
                    double errorRate = static_cast<double>(falsePositivesCount) / N;

                    // Imprimir los falsos positivos
                    cout << "Falsos positivos: ";
                    for (const auto& name : falsePositives) {
                        cout << name << ", ";
                    }
                    cout << endl;

                    // Guardar resultados en el archivo CSV
                    outputFile << N << "," << p << "," << k << "," << m << "," << timeWithoutBloom << "," << timeWithBloom << "," << errorRate * 100 << "\n";

                    // Mostrar resultados
                    cout << "N: " << N << ", p: " << p << ", k: " << k << ", m: " << m << endl;
                    cout << "Tiempo de búsqueda sin filtro de Bloom: " << timeWithoutBloom << " ms" << endl;
                    cout << "Tiempo de búsqueda con filtro de Bloom: " << timeWithBloom << " ms" << endl;
                    cout << "Porcentaje de error del filtro de Bloom: " << errorRate * 100 << "%" << endl;
                    cout << "----------------------------------------" << endl;
                }
            }
        }
    }

    outputFile.close();
    return 0;
}
