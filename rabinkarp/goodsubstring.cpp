#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
const long long BASE = 31;

void solve(const string& s, const string& num, int k) {

    int n = s.size();
    unordered_set<long long> dobri;

    vector<long long> powers(n + 1);
    powers[0] = 1;
    for (int i = 1; i <= n; i++) {
        powers[i] = (powers[i - 1] * BASE) % MOD;
    }

    for (int i = 0; i < n; i++) {
        long long hash = 0;
        int losi = 0;

        for (int j = i; j < n; j++) {

            int index = s[j] - 'a';

            if (num[index] == '0') {
                losi++;
            }

            if (losi > k) {
                break;
            }

            long long char_val = s[j] - 'a' + 1;
            int length_of_substring = j - i;

            hash = (hash + char_val * powers[length_of_substring]) % MOD;
            if (hash < 0) hash += MOD;

            dobri.insert(hash);
        }
    }

    cout << dobri.size() << endl;
}

int main() {
    string s;
    string num;
    int k;

    cin >> s;
    cin >> num;
    cin >> k;

    solve(s, num, k);

    return 0;
}