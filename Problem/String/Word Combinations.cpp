//https://cses.fi/problemset/task/1731/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5005;

const long long P = 26;
const long long Q = 53;
const unsigned long long M = 1e9 + 7;

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* M + x.second; }
};
gp_hash_table<pair<long long, long long>, bool, chash> mp[N];


long long dp[N];

void calc_hash(string a) {
    long long p_pow = 1;
    long long q_pow = 1;
    long long p = 0, q = 0;
    for (int j = a.size() - 1; j >= 0; j--) {
        long long c = (a[j] - 'a') + 1;
        p = (p + c * p_pow) % M;
        q = (q + c * q_pow) % M;
        p_pow = (p_pow * P) % M;
        q_pow = (q_pow * Q) % M;
    }
    mp[a.size()][make_pair(p, q)] = true;
    return;
}

int main() {
	IOS;
    string s;
    cin >> s;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string a;
        cin >> a;
        calc_hash(a);
    }
    for (int i = 0; i < s.size(); i++) {
        long long p_pow = 1;
        long long q_pow = 1;
        long long p = 0, q = 0;
        for (int j = i; j >= 0; j--) {
            long long c = (s[j] - 'a') + 1;
            p = (p + c * p_pow) % M;
            q = (q + c * q_pow) % M;
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
            auto it = mp[i - j + 1].find(make_pair(p, q));
            if (it != mp[i - j + 1].end()) {
                if (j == 0) {
                    dp[i] = (dp[i] + 1) % M;
                } else {
                    dp[i] = (dp[i] + dp[j - 1]) % M;
                }
            }
        }
    }
    cout << dp[s.size() - 1];
	return 0;
}
