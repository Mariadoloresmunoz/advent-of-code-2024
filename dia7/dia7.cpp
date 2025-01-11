#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

// Helper function to evaluate expressions left-to-right
long evaluateLeftToRight(const vector<int>& nums, const vector<char>& ops) {
	
    long result = nums[0];
    
    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == '+') {
   			 result = result + nums[i + 1];
    	}
 		else {
    		result = result * nums[i + 1];
		}
    }
    return result;
}

// Recursive function to explore all operator combinations
bool isPossibleToReachTarget(const vector<int>& nums, int target, vector<char>& ops, int pos) {
    if (pos == nums.size() - 1) {
    	return evaluateLeftToRight(nums, ops) == target;
	}

   	char operations[] = {'+', '*'};
   	
	for (int i = 0; i < 2; ++i) {
    	char op = operations[i];
    	ops.push_back(op);  // Agrega operador
    	if (isPossibleToReachTarget(nums, target, ops, pos + 1)) return true;  // Verifica recursivamente
    	ops.pop_back();  // Limpia para retroceder
	}


    return false;
}

// Main function to process each equation and calculate the total sum
int processEquations(const vector<pair<int, vector<int>>>& equations) {
    int totalSum = 0;
    for (const auto& [target, nums] : equations) {
        if (nums.size() == 1 && nums[0] == target) {
            totalSum += target;
            continue;
        }
        vector<char> ops;
        if (isPossibleToReachTarget(nums, target, ops, 0)) {
            totalSum += target;
        }
    }
    return totalSum;
}

// Function to read input from a file
vector<pair<int, vector<int>>> readInput(const string& filename) {
    ifstream file(filename);
    vector<pair<int, vector<int>>> equations;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return equations;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int target;
        char colon;

        if (ss >> target >> colon) {
            vector<int> nums;
            int num;
            while (ss >> num) nums.push_back(num);
            equations.emplace_back(target, nums);
        } else {
            cerr << "Error: Malformed line: " << line << endl;
        }
    }

    return equations;
}

int main() {
    string filename = "input.txt"; // Input file name
    vector<pair<int, vector<int>>> equations = readInput(filename);

    int result = processEquations(equations);
    cout << "Total sum of valid calibration values: " << result << endl;

    return 0;
}
