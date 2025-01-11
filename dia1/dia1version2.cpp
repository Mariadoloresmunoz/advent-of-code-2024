#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib> // Para usar atoi
#include <algorithm> // Para usar std::count

using namespace std;

// Función para convertir poder convertir las listas de string a enteros 
int StringAEntero(const string &cadena) {
    return atoi(cadena.c_str());
}

// Función para leer fichero y convertir a vectores
// tambien es aqui donde separamos el fichero en dos listas distintas
void LeerLista(vector<int> &lista1, vector<int> &lista2) {
	
    ifstream archivo("lista.txt");
    string linea, data;
    
    while (getline(archivo, linea)) {
        stringstream iss(linea);
        iss >> data;
        lista1.push_back(StringAEntero(data));
        iss >> data;
        lista2.push_back(StringAEntero(data));
    }
}

// funcion merge y merge sort para ordenar la lista 
void merge(vector<int> &arr, int left, int mid, int right) {
	// creamos dos vectores a partir de dividir las listas
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
    }
    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
    }
}

// funcion en la que hacemos la llamada recursiva de las divisiones y luego la union de los resultados 
void mergeSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);       // Divide la mitad izquierda
        mergeSort(arr, mid + 1, right);  // Divide la mitad derecha
        merge(arr, left, mid, right);    // Combina los resultados
    }
}

// funcion que calcula la diferencia entre las dos listas
int EncontrarDiferencia(const vector<int> &lista1, const vector<int> &lista2) {
    int suma = 0;
    for (int i = 0; i < lista1.size(); i++) {
        cout << lista1[i] << " - " << lista2[i] << " = " << abs(lista2[i] - lista1[i]) << endl;
        suma += abs(lista2[i] - lista1[i]);
    }
    return suma;
}

// funcion para calcular la similitud
int calcularSimilitud(const vector<int> &lista1, const vector<int> &lista2, int left, int right) {
    if (left > right) {
        return 0;
    }
    if (left == right) {
        return lista1[left] * count(lista2.begin(), lista2.end(), lista1[left]);
    }
    // volvemos a aplicar DyV para ir recorriendo las listas para ir mirando la similitud 
    int mid = left + (right - left) / 2;
    int leftSim = calcularSimilitud(lista1, lista2, left, mid);
    int rightSim = calcularSimilitud(lista1, lista2, mid + 1, right);
    return leftSim + rightSim;
}

int main() {
    vector<int> lista1, lista2;

    // Leer las líneas y añadirlas a los vectores
    LeerLista(lista1, lista2);

    // Ordenar vectores usando merge sort
    mergeSort(lista1, 0, lista1.size() - 1);
    mergeSort(lista2, 0, lista2.size() - 1);

    // Encontrar diferencia
    int suma = EncontrarDiferencia(lista1, lista2);

    // Calcular similitud usando divide y vencerás
    int similitud = calcularSimilitud(lista1, lista2, 0, lista1.size() - 1);


    cout << "El puntaje de similitud total es: " << similitud << endl;
    cout << "El valor total que deseas es: " << suma << endl;

    return 0;
}
