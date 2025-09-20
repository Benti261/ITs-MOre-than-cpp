#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    bool ismin1 = false;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int min1 = INT_MAX;
    int min2 = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (min1 >= arr[i]) {
            min1 = arr[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if ( not(ismin1) and arr[i] == min1) {
            ismin1 = true;
            continue;
        } else {
            if (min2 >= arr[i]) {
            min2 = arr[i];
        }
        }
    }
    cout << min1 << " " << min2 << endl;
    return 0;
}

