#include <bits/stdc++.h>
using namespace std;

vector<int> rabinKarp(const string &pattern, const string &text) {
    const int base = 31; 
    const long long mod = 1000000009;
    int lenPattern = pattern.size();
    int lenText = text.size();

    vector<long long> power(max(lenPattern, lenText));
    power[0] = 1;
    for (int i = 1; i < (int)power.size(); i++) {
        power[i] = (power[i - 1] * base) % mod;
    }

    vector<long long> hashText(lenText + 1, 0);
    for (int i = 0; i < lenText; i++) {
        hashText[i + 1] = (hashText[i] + (text[i] - 'a' + 1) * power[i]) % mod;
    }

    long long hashPattern = 0;
    for (int i = 0; i < lenPattern; i++) {
        hashPattern = (hashPattern + (pattern[i] - 'a' + 1) * power[i]) % mod;
    }

    vector<int> occurrences;
    for (int i = 0; i + lenPattern - 1 < lenText; i++) {
        long long currentHash = (hashText[i + lenPattern] - hashText[i] + mod) % mod;
        if (currentHash == (hashPattern * power[i]) % mod) {
            occurrences.push_back(i + 1); 
        }
    }

    return occurrences;
}

int main() {
    int testCases;
    cin >> testCases;

    for (int tc = 0; tc < testCases; tc++) {
        string text, pattern;
        cin >> text >> pattern;

        vector<int> result = rabinKarp(pattern, text);

        if ((int)result.size() == 0) {
            cout << "Not Found" << endl;
        } else {
            cout << result.size() << endl;
            for (int i = 0; i < (int)result.size(); i++) {
                cout << result[i];
                if (i + 1 < (int)result.size()) cout << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
