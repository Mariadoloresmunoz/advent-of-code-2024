#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <fstream> // For file handling

using namespace std;

// Directions for moving up, down, left, or right
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

// Function to check if a position is within bounds
// Ensures that we do not go out of the map's grid
bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

// Perform BFS to find all reachable '9's from a given trailhead
// BFS ensures that we follow the "exactly increasing by 1" constraint
int bfs(const vector<vector<int>> &map, int startX, int startY) {
    int rows = map.size(); // Number of rows in the map
    int cols = map[0].size(); // Number of columns in the map
    
    queue<pair<int, int>> q; // Queue to store the positions to explore
    set<pair<int, int>> visited; // Set to track visited positions

    // Initialize BFS with the starting position
    q.push({startX, startY});
    visited.insert({startX, startY});

    int score = 0; // Tracks the number of reachable '9's

    while (!q.empty()) {
        auto [x, y] = q.front(); // Get the current position
        q.pop();

        // If the current position is height 9, increment the score
        if (map[x][y] == 9) {
            score++;
            continue; // Skip further exploration from this position
        }

        // Explore neighbors in all four directions
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i]; // New x-coordinate
            int ny = y + dy[i]; // New y-coordinate

            // Check if the neighbor is valid, not visited, and increases by 1 in height
            if (isValid(nx, ny, rows, cols) && !visited.count({nx, ny}) && map[nx][ny] == map[x][y] + 1) {
                q.push({nx, ny}); // Add the neighbor to the queue
                visited.insert({nx, ny}); // Mark it as visited
            }
        }
    }

    return score; // Return the total number of reachable '9's
}

// Function to read the map from a file
vector<vector<int>> readMapFromFile(const string &filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Could not open the file!" << endl;
        exit(1);
    }

    vector<vector<int>> map;
    string line;

    // Parse the input file line by line
    while (getline(inputFile, line)) {
        vector<int> row;
        for (char c : line) {
            if (isdigit(c)) {
                row.push_back(c - '0'); // Convert character to integer
            }
        }
        if (!row.empty()) {
            map.push_back(row);
        }
    }
    inputFile.close();
    return map;
}

// Function to calculate the total score for all trailheads
int calculateTotalScore(const vector<vector<int>> &map) {
    int rows = map.size();
    int cols = map[0].size();
    int totalScore = 0;

    // Find all trailheads (height 0) and calculate their scores
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == 0) { // Check if the current position is a trailhead
                totalScore += bfs(map, i, j); // Add the score for this trailhead
            }
        }
    }

    return totalScore;
}

int main() {
    // Read the map from a file
    vector<vector<int>> map = readMapFromFile("map.txt");

    // Calculate the total score for all trailheads
    int totalScore = calculateTotalScore(map);

    // Output the total score
    cout << "Total Score: " << totalScore << endl;
    return 0;
}
