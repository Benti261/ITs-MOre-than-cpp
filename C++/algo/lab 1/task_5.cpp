#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    vector<int> answer(n);
    for (int i = 0; i < n -1; i++) {
        answer[i+1] = numbers[i];
    }
    answer[0] = numbers[n - 1];
    for (int i = 0; i < n; i++) {
        cout << answer[i] << " ";
    }
    cout << endl;
}

