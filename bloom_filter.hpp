#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Estructura para implementar un Bloom Filter
struct BloomFilter {
    vector<bool> bits;  // Vector de bits para almacenar los datos
    size_t numHashes;   // Número de funciones hash a utilizar

    BloomFilter(size_t m, size_t k)
        : bits(m), numHashes(k) {}

    void add(const string& item) {
        for (size_t i = 0; i < numHashes; ++i) {
            // Calcula la posición del bit usando la función hash y marca el bit
            size_t hashValue = hash(item, i) % bits.size();
            bits[hashValue] = true;
        }
    }

    bool contains(const string& item) const {
        // Para simular tener k funciones de hash, se llama a hash() k veces
        for (size_t i = 0; i < numHashes; ++i) {
            // Calcula la posición del bit usando la función hash
            size_t hashValue = hash(item, i) % bits.size();
            // Si algún bit no está marcado, el elemento no está presente
            if (!bits[hashValue]) {
                return false;
            }
        }
        // Todos los bits están marcados, el elemento probablemente está presente
        return true;
    }

   private:
    // Función hash que genera un valor hash para el elemento y un índice
    size_t hash(const string& item, size_t i) const {
        // Combina el elemento con el índice para generar un valor hash único
        return std::hash<string>{}(item + to_string(i));
    }
};
