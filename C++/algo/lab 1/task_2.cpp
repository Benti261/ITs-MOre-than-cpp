#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    int x;
    cin >> n;
    vector<int> numbers(n);
    
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    
    cin >> x;
    int ans;
    int minDiff = INT_MAX;
    
    for (int i = 0; i < n; i++) { 
        int diff = abs(numbers[i] - x);
        
        if (diff < minDiff) {
            minDiff = diff;
            ans = numbers[i];
        }
    }
    
    cout << ans;
    return 0;
}
