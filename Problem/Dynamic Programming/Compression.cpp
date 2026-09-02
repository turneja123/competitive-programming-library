//https://petlja.org/sr-Latn-RS/biblioteka/r/BBC7FCompression
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const int INF = 1e9;
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

int id[N][N];

pair<ll, ll> pref[N];
ll inv_p[N], inv_q[N];
string s;

pair<ll, ll> get_rising(int l, int r, int n) {
    pair<ll, ll> h = pref[r];
    if (l != 0) {
        h.first = (h.first - pref[l - 1].first + M) * inv_p[l] % M;
        h.second = (h.second - pref[l - 1].second + M) * inv_q[l] % M;
    }
    return h;
}

int cost(int x) {
    int k = 0;
    while (x > 0) {
        k++;
        x /= 10;
    }
    return k;
}

int dp[N];

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    long long p = 0, q = 0;
    long long p_pow = 1, q_pow = 1;
    for (int i = 0; i < n; i++) {
        p = (p + p_pow * (s[i] - 'a' + 200)) % M;
        q = (q + q_pow * (s[i] - 'a' + 200)) % M;
        p_pow = (p_pow * P) % M;
        q_pow = (q_pow * Q) % M;
        pref[i] = {p, q};

        inv_p[i] = (i == 0 ? 1 : inv_p[i - 1] * INV_P % M);
        inv_q[i] = (i == 0 ? 1 : inv_q[i - 1] * INV_Q % M);
    }
    for (int i = 0; i < n; i++) {
        map<ll, int> mp;
        for (int j = 0; j + i - 1 < n; j++) {
            auto h = get_rising(j, j + i - 1, n);
            auto it = mp.find((h.first << 32) + h.second);
            if (it == mp.end()) {
                mp[(h.first << 32) + h.second] = mp.size();
            }
            id[j][j + i - 1] = mp[(h.first << 32) + h.second];
        }
    }
    for (int i = 0; i < n; i++) {
        dp[i] = N;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n - i; j++) {
            int need = id[i][i + j - 1];
            int ct = 1;
            dp[i + j - 1] = min(dp[i + j - 1], (i == 0 ? 0 : dp[i - 1]) + 1 + j);

            int l = i + j;
            while (1) {
                int r = l + j - 1;
                if (r >= n || id[l][r] != need) {
                    break;
                }
                ct++;
                dp[r] = min(dp[r], (i == 0 ? 0 : dp[i - 1]) + cost(ct) + j);
                l = r + 1;
            }
        }
    }
    cout << dp[n - 1];

    return 0;
}
