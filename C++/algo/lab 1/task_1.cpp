#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    int counter = 0;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i <= n; i++) {
        cin >> nums[i];
    }
    for (int i = 1; i < n - 1; i++) {
        //cout << nums[i] << endl;
        if (nums[i] > nums[i-1] and nums[i] > nums[i+1]) {
            counter++;
        }
    }
    cout << counter << endl;
}
