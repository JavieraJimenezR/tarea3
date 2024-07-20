#include "bloom_filter.hpp"

int main() {
    BloomFilter bloomFilter(1000, 7); // tamaño del filtro y número de funciones hash

    // Añadir elementos al filtro
    bloomFilter.add("Alice");
    bloomFilter.add("Bob");
    bloomFilter.add("Charlie");

    // Verificar si los elementos están posiblemente en el filtro
    cout << "Alice: " << bloomFilter.contains("Alice") << endl;
    cout << "Bob: " << bloomFilter.contains("Bob") << endl;
    cout << "Charlie: " << bloomFilter.contains("Charlie") << endl;
    cout << "David: " << bloomFilter.contains("David") << endl;


    return 0;
}
