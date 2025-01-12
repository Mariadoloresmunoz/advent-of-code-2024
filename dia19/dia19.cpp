
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

struct TreeNode {
    std::string word;
    TreeNode *left = nullptr, *right = nullptr;
    TreeNode(const std::string& w) : word(w) {}
};

TreeNode* insert(TreeNode* root, const std::string& word) {
    if (!root) return new TreeNode(word);
    if (word < root->word) root->left = insert(root->left, word);
    else if (word > root->word) root->right = insert(root->right, word);
    return root;
}

bool search(TreeNode* root, const std::string& word) {
    while (root) {
        if (root->word == word) return true;
        root = word < root->word ? root->left : root->right;
    }
    return false;
}

bool canBuild(TreeNode* root, const std::string& word, std::map<std::string, bool>& cache) {
    if (auto it = cache.find(word); it != cache.end()) return it->second;
    if (search(root, word)) return cache[word] = true;
    for (size_t i = 1; i < word.size(); ++i) {
        if (canBuild(root, word.substr(0, i), cache) && canBuild(root, word.substr(i), cache))
            return cache[word] = true;
    }
    return cache[word] = false;
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Cannot open file input.txt\n";
        return EXIT_FAILURE;
    }

    std::string line;
    std::getline(file, line);  // Leer la primera línea para el árbol
    std::istringstream iss(line);
    TreeNode* root = nullptr;
    for (std::string word; iss >> word; ) {
        if (word.back() == ',') word.pop_back();
        root = insert(root, word);
    }

    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
	
    int count = 1; //Inicializamos a 1 para contar con el nodo raíz 
    std::map<std::string, bool> cache;
    for (size_t i = 2; i < lines.size(); ++i) {  // Procesar desde la segunda línea
        if (canBuild(root, lines[i], cache)) ++count;
    }

    std::cout << count << '\n';
    return EXIT_SUCCESS;
}


