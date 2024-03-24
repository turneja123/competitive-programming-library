//https://www.spoj.com/problems/ACRYM2/
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e4 + 5;
const int M = 255;
const long long MOD = 1e9 + 7;
const long long P = 26;
const long long Q = 53;

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* MOD + x.second; }
};

long long dp[N][M]; // index, broj zavrsenih reci
long long pref[N][M];
long long add[M];
bool w[M];
set<string> wild = {"on", "at", "to", "of", "from", "for", "with", "and", "in"};
string words[M];
string s;
gp_hash_table<pair<long long, long long>, int, chash> hash_words[M];
pair<long long, long long> hash_sub[N][M];
pair<long long, long long> full[M];

void precalc_s(int i) {
    long long p_pow = 1;
    long long q_pow = 1;
    long long p_sub = 0, q_sub = 0;
    for (int j = i; j >= 0; j--) {
        long long c = (s[j] - 'a') + 1;
        p_sub = (p_sub + c * p_pow) % MOD;
        q_sub = (q_sub + c * q_pow) % MOD;
        if (j != 0) {
            p_pow = (p_pow * P) % MOD;
            q_pow = (q_pow * Q) % MOD;
        }
    }
    hash_sub[0][i] = make_pair(p_sub, q_sub);

    for (int j = 1; i + j < s.size(); j++) {
        long long c_prev = (s[j - 1] - 'a') + 1;
        long long c = (s[i + j] - 'a') + 1;
        p_sub = ((((p_sub - (c_prev * p_pow) % MOD) + MOD) % MOD) * P + c) % MOD;
        q_sub = ((((q_sub - (c_prev * q_pow) % MOD) + MOD) % MOD) * Q + c) % MOD;
        hash_sub[j][i] = make_pair(p_sub, q_sub);
    }
    return;
}

void precalc(int m, int mx) {
    for (int i = 0; i < mx; i++) {
        precalc_s(i);
        for (int j = 0; j < m; j++) {
            if (words[j].size() <= i) {
                continue;
            }
            long long p_pow = 1;
            long long q_pow = 1;
            long long p = 0, q = 0;
            for (int k = i; k >= 0; k--) {
                long long c = (words[j][k] - 'a') + 1;
                p = (p + c * p_pow) % MOD;
                q = (q + c * q_pow) % MOD;
                p_pow = (p_pow * P) % MOD;
                q_pow = (q_pow * Q) % MOD;
            }
            hash_words[j][make_pair(p, q)]++;
            if (i == words[j].size() - 1) {
                full[j] = make_pair(p, q);
            }
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int m, n, mx = 0;
        cin >> m >> s;
        n = s.size();
        for (int i = 0; i < m; i++) {
            cin >> words[i];
            mx = max(mx, (int)words[i].size());
            if (wild.find(words[i]) != wild.end()) {
                w[i] = true;
            }
        }
        precalc(m, mx);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                add[j] = (add[j] + pref[i][j] + MOD) % MOD;
                dp[i][j] = add[j];

                if (w[j]) {
                    if (j == 0) {
                        dp[i][j] = (dp[i][j] + 1) % MOD;
                    } else {
                        dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
                    }
                }
                int l = 1, r = min((int)words[j].size(), (int)(s.size() - i)), len = 0;
                bool flag = true;
                for (int k = i; k - i < words[j].size() && k - i < 8 && k < n; k++) {
                    if (words[j][k - i] != s[k]) {
                        flag = false;
                        break;
                    }
                    l++, len++;
                    if (k == n - 1) {
                        flag = false;
                    }
                }
                if (flag) {
                    if (hash_sub[i][r - 1] == full[j]) {
                        len = r;
                    } else {
                        while (l <= r) {
                            int mid = (l + r) / 2;
                            if (hash_words[j].find(hash_sub[i][mid - 1]) != hash_words[j].end()) {
                                len = max(len, mid);
                                l = mid + 1;
                            } else {
                                r = mid - 1;
                            }
                        }
                    }
                }
                int prev = i - 1;
                if (len != 0) {
                    if (prev == -1) {
                        if (j == 0) {
                            dp[i][j] = (dp[i][j] + 1) % MOD;
                            add[j] = (add[j] + 1) % MOD;
                            pref[i + len][j] = (pref[i + len][j] - 1 + MOD) % MOD;
                        }
                    } else {
                        if (j != 0) {
                            dp[i][j] = (dp[i][j] + dp[prev][j - 1]) % MOD;
                            add[j] = (add[j] + dp[prev][j - 1]) % MOD;
                            pref[i + len][j] = (pref[i + len][j] - dp[prev][j - 1] + MOD) % MOD;
                        }
                    }
                }
            }
        }
        cout << dp[n - 1][m - 1] << endl;
        for (int i = 0; i < m; i++) {
            hash_words[i].clear();
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                dp[i][j] = 0;
                pref[i][j] = 0;
                add[j] = 0;
                w[j] = false;
            }
        }
    }
    return 0;
}
