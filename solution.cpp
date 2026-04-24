#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    
    vector<vector<int>> compressed(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> compressed[i][j];
        }
    }
    
    // Output 3m x 3n matrix
    for (int i = 0; i < m; i++) {
        for (int bi = 0; bi < 3; bi++) {
            for (int j = 0; j < n; j++) {
                for (int bj = 0; bj < 3; bj++) {
                    int row = i * 3 + bi;
                    int col = j * 3 + bj;
                    
                    // Center position
                    if (bi == 1 && bj == 1) {
                        cout << compressed[i][j];
                    } else {
                        // Calculate based on neighboring centers
                        vector<int> typeA, typeB;
                        
                        // Check all compressed pixels to find A and B types
                        for (int ci = 0; ci < m; ci++) {
                            for (int cj = 0; cj < n; cj++) {
                                int centerRow = ci * 3 + 1;
                                int centerCol = cj * 3 + 1;
                                int manhattanDist = abs(row - centerRow) + abs(col - centerCol);
                                
                                if (manhattanDist == 1) {
                                    typeA.push_back(compressed[ci][cj]);
                                } else if (manhattanDist == 2) {
                                    typeB.push_back(compressed[ci][cj]);
                                }
                            }
                        }
                        
                        int result;
                        if (typeA.empty()) {
                            // No type A, use type B average
                            int sum = 0;
                            for (int val : typeB) sum += val;
                            result = sum / typeB.size();
                        } else if (typeB.empty()) {
                            // No type B, use type A average
                            int sum = 0;
                            for (int val : typeA) sum += val;
                            result = sum / typeA.size();
                        } else {
                            // Both exist, use weighted average
                            int sumA = 0, sumB = 0;
                            for (int val : typeA) sumA += val;
                            for (int val : typeB) sumB += val;
                            double avgA = (double)sumA / typeA.size();
                            double avgB = (double)sumB / typeB.size();
                            result = (int)floor(avgA * 0.8 + avgB * 0.2);
                        }
                        
                        // Clamp to 0-100 range
                        result = max(0, min(100, result));
                        cout << result;
                    }
                    
                    if (j < n - 1 || bj < 2) {
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }
    }
    
    return 0;
}