
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <fstream>


// funcion para leer los archivos rules y updates. lo hemos divido en 2 archivos para no tener todo en un 
void parseInput(std::ifstream& ruleFile, std::ifstream& updateFile,
                std::vector<std::pair<int, int>>& rules, std::vector<std::vector<int>>& updates) {
    std::string line;
    // abrimos archivo de las reglas y leemos linea por linea.
    // al leer cada linea separamos los nuemros en x|y y los almacenamos como un par en la lista rules
    while (std::getline(ruleFile, line)) {
        std::stringstream ss(line);
        int x, y;
        char sep;
        ss >> x >> sep >> y;
        rules.emplace_back(x, y);
    }
    //abrimos archivo de updates y leemos linea por linea
    //convertimos cada linea en una lista y gardamos todas las listas en una lista llamada updates 
    while (std::getline(updateFile, line)) {
        std::stringstream ss(line);
        std::vector<int> pages;
        int page;
        char sep;
        while (ss >> page) {
            pages.push_back(page);
            ss >> sep; // Consume ','
        }
        updates.push_back(pages);
    }
}

// funcion para hacer el grafico en funcion de las reglas 
void buildGraph(const std::vector<std::pair<int, int>>& rules, 
                std::unordered_map<int, std::vector<int>>& graph,
                std::unordered_map<int, int>& inDegree) {
  //
    for (const auto& rule : rules) {
        int from = rule.first;
        int to = rule.second;
        graph[from].push_back(to);
        inDegree[to]++;
        if (inDegree.find(from) == inDegree.end()) {
            inDegree[from] = 0;
        }
    }
}

// fucnion para ver si un update respeta las reglas comparando las posicion del elemento en la lista updates con el grafo con las reglas
bool isUpdateValid(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules) {
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_map<int, int> inDegree;
    // creamos el arbol y un mapa de grados de entrada basados en la reglas
    buildGraph(rules, graph, inDegree);

    // mapear las paginas de la actualizacion a sus posiciones 
    std::unordered_map<int, int> pagePosition;
    for (size_t i = 0; i < update.size(); ++i) {
        pagePosition[update[i]] = i;
    }

    // verificamos que al actualizar se cumplan las reglas 
    for (const auto& rule : rules) {
      int x = rule.first;//pagina que debe ir primero 
      int y = rule.second;// pagina que deberia de ir la segunda
      // comprobamos que ambas paginas estén en la actualizacion 
        if (pagePosition.count(x) && pagePosition.count(y)) {
	  if (pagePosition[x] >= pagePosition[y]) {// condicion que comprueba que se cumpla la regla
                return false;
            }
        }
    }
    return true;
}
// funcion para encontrar y devolver la pagina del medio en una actualizacion 
int findMiddlePage(const std::vector<int>& update) {
    return update[update.size() / 2];
}

// Función para procesar las actualizaciones y calcular la suma de las páginas del medio
int processUpdates(const std::vector<std::pair<int, int>>& rules, const std::vector<std::vector<int>>& updates) {
    int sumOfMiddlePages = 0; // Inicializar la suma
    for (const auto& update : updates) {
        if (isUpdateValid(update, rules)) { // Verificar si la actualización es válida
            sumOfMiddlePages += findMiddlePage(update); // Agregar la página del medio a la suma
        }
    }
    return sumOfMiddlePages; // Devolver la suma total
}


int main() {
    // abrimos los archivos 
    std::ifstream ruleFile("rules.txt");
    std::ifstream updateFile("updates.txt");

    if (!ruleFile.is_open() || !updateFile.is_open()) {
        std::cerr << "Error: Unable to open input files." << std::endl;
        return 1;
    }

    // analizmos los archivos 
    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;
    parseInput(ruleFile, updateFile, rules, updates);

    // una vez que ya hemos leido todos los archivos y tenemos las listas con los datos modificados podemos cerrar los archivos 
    ruleFile.close();
    updateFile.close();

    
    // Procesar las actualizaciones y calcular la suma de las páginas del medio
    int sumOfMiddlePages = processUpdates(rules, updates);
    
    // Output the result
    std::cout << "sumas de las paginas del medio de las actualizaciones correctas: " << sumOfMiddlePages << std::endl;

    return 0;
}
