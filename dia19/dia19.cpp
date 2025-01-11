
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Función para leer el archivo "input.txt"
bool readFile(vector<string>& lines) {
    ifstream in("input.txt");
    if (!in) {
        cerr << "No se pudo abrir el archivo input.txt\n";
        return false;
    }
    string str;
    while (getline(in, str)) {
        lines.push_back(str);
    }
    return true;
}

// Función para cargar las palabras iniciales en un conjunto
set<string> loadWords(const string& line) {
	
    set<string> wordSet;// creamos un conjunto para almacenar palabras unicas
    istringstream iss(line);
    string word;
    while (iss >> word) {// vamos leyendo y separando las palabras utilizando la coma separador 
        if (word.back() == ',') {
            word.pop_back();
        }
        if (!word.empty()) {
            wordSet.insert(word);
        }
    }
    return wordSet; // devolvemos el conjunto con las palabras unicas
}

// Función para determinar si una palabra puede construirse a partir de otras
bool canBuild(const set<string>& words, const string& word, map<string, bool>& cache) {
    if (auto it = cache.find(word); it != cache.end()) {
        return it->second; // si la palabra está en la caché, devuelve su valor 
    }
    if (words.count(word)) {// si la palabra está en el conjunto entonces es contruible
        cache[word] = true; // alamacenamos la palabra en cache como verdadera
        return true;
    }
    // recorremos cada posible particion de la palabra
    for (size_t i = 1; i < word.size(); ++i) {
    	// comprobamos si ambas partes son contruibles
        if (canBuild(words, word.substr(0, i), cache) && canBuild(words, word.substr(i), cache)) {
            return cache[word] = true;
        }
    }
    return cache[word] = false; // si no podemos contruir guardamos como falso y devolvemos 
}

int main() {
    vector<string> lines; // creamos vector para almacenar las lineas
    
    if (!readFile(lines) || lines.empty()) {
        return EXIT_FAILURE;
    }

    set<string> wordSet = loadWords(lines[0]);
    map<string, bool> cache;
    int count = 0;

	// recorremos lineas e incementamos contador si la palabra es construible
    for (size_t i = 2; i < lines.size(); ++i) {
        if (canBuild(wordSet, lines[i], cache)) {
            ++count;
        }
    }
    
    cout << count << '\n'; // imprimimos contador con cantidad de palabras construibles 
    return EXIT_SUCCESS;
}
