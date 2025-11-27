#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string longestDupSubstring(const string &s) {
    int n = s.size();
    const ll BASE = 256;
    const ll MOD = 1e9 + 7;

    auto check = [&](int L) -> string {
        ll hash = 0, power = 1;
        unordered_set<ll> seen;

        for (int i = 0; i < L; i++) {
            hash = (hash * BASE + (s[i] - 'a' + 1)) % MOD;
            if (i > 0) power = (power * BASE) % MOD;
        }
        seen.insert(hash);

        for (int i = 1; i + L <= n; i++) {
            hash = (hash - (s[i - 1] - 'a' + 1) * power % MOD + MOD) % MOD;
            hash = (hash * BASE + (s[i + L - 1] - 'a' + 1)) % MOD;
            if (seen.count(hash)) return s.substr(i, L);
            seen.insert(hash);
        }
        return "";
    };

    int left = 1, right = n - 1;
    string ans = "";

    while (left <= right) {
        int mid = left + (right - left) / 2;
        string candidate = check(mid);
        if (!candidate.empty()) {
            ans = candidate;       
            left = mid + 1;        
        } else {
            right = mid - 1;      
        }
    }
    return ans;
}

int main() {
    string s;
    cin >> s;
    cout << longestDupSubstring(s) << endl;
    return 0;
}
