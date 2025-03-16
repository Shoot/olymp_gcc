#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Function to perform component-wise AND between two binary vectors
vector<int> vectorAND(const vector<int>& v1, const vector<int>& v2) {
    vector<int> result(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] & v2[i];
    }
    return result;
}

// Function to print a binary vector
void printVector(const vector<int>& v) {
    for (int bit : v) {
        cout << bit;
    }
    cout << endl;
}

// Function to compute the number of distinct vectors achievable using AND
int countDistinctANDVectors(vector<vector<int>>& vectors) {
    // Use a set to store unique vectors
    set<vector<int>> uniqueVectors(vectors.begin(), vectors.end());

    bool newVectorAdded = true;
    while (newVectorAdded) {
        newVectorAdded = false;
        set<vector<int>> newVectorsToAdd;

        // Try ANDing every pair of vectors in the current set
        for (const auto& v1 : uniqueVectors) {
            for (const auto& v2 : uniqueVectors) {
                vector<int> andResult = vectorAND(v1, v2);
                if (uniqueVectors.find(andResult) == uniqueVectors.end()) {
                    newVectorsToAdd.insert(andResult);
                    newVectorAdded = true;
                }
            }
        }

        // Add newly found vectors to the set
        for (const auto& v : newVectorsToAdd) {
            uniqueVectors.insert(v);
        }
    }

    // Print all distinct vectors
    cout << "Distinct vectors:" << endl;
    for (const auto& v : uniqueVectors) {
        printVector(v);
    }

    return uniqueVectors.size();
}

int main() {
    // Example input: a set of binary vectors
    vector<vector<int>> vectors = {
            {1, 1, 0, 1, 0, 1, 0},
            {1, 0, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 1, 1},
            {0, 1, 0, 0, 1, 0, 0},
    };

    // Compute the number of distinct vectors achievable using AND
    int numDistinctVectors = countDistinctANDVectors(vectors);

    // Output the result
    cout << "Number of distinct vectors: " << numDistinctVectors << endl;

    return 0;
}