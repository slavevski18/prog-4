
#include <bits/stdc++.h>
using namespace std;

struct Hash {
    static const long long mod = 1000000007;
    static const long long base = 31;
    vector<long long> h, p;
    Hash(const string &s) {
        int n = s.size();
        h.resize(n+1,0);
        p.resize(n+1,0);
        p[0] = 1;
        for (int i = 1; i <= n; i++) p[i] = (p[i-1] * base) % mod;
        for (int i = 0; i < n; i++)
            h[i+1] = (h[i] * base + s[i]) % mod;
    }
    long long get(int l, int r) {
        long long res = (h[r+1] - h[l] * p[r-l+1]) % mod;
        if (res < 0) res += mod;
        return res;
    }
};

bool isPalindrome(const string &s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

void solve(const string &s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<long long> res(n+1,0);

    Hash H(s);

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;

            if (len == 1) dp[i][j] = 1;
            else if (isPalindrome(s, i, j)) dp[i][j] = 1;
            else continue;

            int half = len / 2;

            if (half > 0) {
                int L1 = i;
                int R1 = i + half - 1;

                int L2 = j - half + 1;
                int R2 = j;

                if (H.get(L1, R1) == H.get(L2, R2)) {
                    int prev = dp[i][R1];
                    if (prev > 0) dp[i][j] = prev + 1;
                }
            }

            res[dp[i][j]]++;
        }
    }

    for (int k = n - 1; k >= 1; k--)
        res[k] += res[k+1];

    for (int k = 1; k <= n; k++)
        cout << res[k] << " ";

    cout << endl;
}

int main() {
    string s;
    cin >> s;
    solve(s);
    return 0;
}
