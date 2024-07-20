#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<string> readFromCSV(const string& filename) {
    vector<string> names;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        names.push_back(line);
    }
    return names;
}

// Función para generar una secuencia de nombres con una proporción p de nombres presentes en el CSV
vector<string> generateTestSequence(const vector<string>& names, const vector<string>& filmNames, size_t N, double p) {
    vector<string> testSequence;
    size_t numPresent = static_cast<size_t>(N * p);
    size_t numAbsent = N - numPresent;

    sample(names.begin(), names.end(), back_inserter(testSequence), numPresent, mt19937{random_device{}()});
    sample(filmNames.begin(), filmNames.end(), back_inserter(testSequence), numAbsent, mt19937{random_device{}()});

    return testSequence;
}
