#include <iostream>
using namespace std;

int count_char(const char *word, char let) {
    int ans = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == let) {
            ans++;
        }
    }
    return ans;
}

int main() {
    char alph[26] = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q', 'p', 'o', 'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
    char code[1001];
    cin >> code;
    
    for (int i = 0; i < 26; i++) {
        if (count_char(code, alph[i]) > 0) {
            cout << alph[i] << endl;
            return 0;
        }
    }
    
    return 0;
}
