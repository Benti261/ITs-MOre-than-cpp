#include <iostream>
#include <vector>
#include <string>
using namespace std;

int count(string word, char let) {
    int len = word.size();
    int ans = 0;
    for (int i = 0; i < len; i++) {
        if (word[i] == let) {
            ans++;
        }
    }
    return ans;
}

int main() {
    vector<char> alph = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q', 'p', 'o', 'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
    string code;
    cin >> code;
    
    for (int i = 0; i < 26; i++) {
        if (count(code, alph[i]) > 0) {
            cout << alph[i] << endl;
            return 0;
        }
    }
    
    return 0;
}
