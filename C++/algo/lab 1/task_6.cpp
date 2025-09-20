#include <iostream>
#include <vector>
using namespace std;

void printMatrix(const vector<int>& vec, int m, int k) {
    for (int i = 0; i < (m * k); ++i) {
        if (i % k == 0 && i != 0) {
            cout << endl;
        } else if (i != 0) {cout << " ";};
        cout << vec[i];
    }
    cout << endl;
}

vector<int> multMatrix(const vector<int>& mat1, int n1, int m1,
                       const vector<int>& mat2, int m2, int k) {
    vector<int> res(n1 * k);
    int counter = 0;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < k; j++) {
            int number = 0;
            for (int p = 0; p < m1; p++) {
                number += mat1[i * m1 + p] * mat2[p * k + j];
            }
            res[counter] = number;
            counter++;
        }
    }
    return res;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> mat1(n * m);
    vector<int> mat2(m * k);
    
    for (int i = 0; i < (n * m); ++i)
        cin >> mat1[i];
    
    for (int i = 0; i < (m * k); ++i)
        cin >> mat2[i];
    
    vector<int> answer = multMatrix(mat1, n, m, mat2, m, k);
    printMatrix(answer, n, k);
    cout << endl;
    return 0;
}
