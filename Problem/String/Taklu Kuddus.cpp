//https://www.spoj.com/problems/TKUDDUS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

string a, b;

const int N = 1e6 + 5;
const int K = 20;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 9923, INV_Q = 452282579;

vector<int> pos;

int up[K][N];

pair<long long, long long> calc(string s) {
    int n = s.size();
    long long p = 0, q = 0;
    long long p_pow = 1, q_pow = 1;
    for (int i = 0; i < n; i++) {
        p = (p + p_pow * (s[i] - 'a' + 1)) % M;
        q = (q + q_pow * (s[i] - 'a' + 1)) % M;
        p_pow = (p_pow * P) % M;
        q_pow = (q_pow * Q) % M;
    }
    return make_pair(p, q);
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        cin >> a >> b;
        a += 'A';
        int n = a.size(), m = b.size();
        pair<long long, long long> h = calc(b);
        long long p = 0, q = 0;
        long long p_pow = 1, q_pow = 1;
        for (int i = 0; i < min(n, m); i++) {
            p = (p + p_pow * (a[i] - 'a' + 1)) % M;
            q = (q + q_pow * (a[i] - 'a' + 1)) % M;
            if (i != m - 1) {
                p_pow = (p_pow * P) % M;
                q_pow = (q_pow * Q) % M;
            }
        }
        pair<long long, long long> sub = make_pair(p, q);
        if (sub == h && n >= m) {
            pos.push_back(0);
        }
        for (int i = m; i < n; i++) {
            p = ((p - (a[i - m] - 'a' + 1) + M) * INV_P + p_pow * (a[i] - 'a' + 1)) % M;
            q = ((q - (a[i - m] - 'a' + 1) + M) * INV_Q + q_pow * (a[i] - 'a' + 1)) % M;
            sub = make_pair(p, q);
            if (sub == h) {
                pos.push_back(i - m + 1);
            }
        }
        for (int i = 0; i < n; i++) {
            if (pos.size() == 0) {
                up[0][i] = -1;
                continue;
            }
            int j = lower_bound(pos.begin(), pos.end(), i) - pos.begin();
            if (j == pos.size()) {
                up[0][i] = -1;
            } else {
                up[0][i] = pos[j] + m;
            }
        }
        for (int k = 1; k < K; k++) {
            for (int i = 0; i < n; i++) {
                if (up[k - 1][i] == -1) {
                    up[k][i] = -1;
                } else {
                    up[k][i] = up[k - 1][up[k - 1][i]];
                }
            }
        }
        int qr;
        cin >> qr;
        cout << "Case " << tt << ":" << endl;
        for (int i = 0; i < qr; i++) {
            int l, r;
            cin >> l >> r;
            if (pos.empty()) {
                cout << 0 << endl;
                continue;
            }
            int ans = 0;
            for (int k = K - 1; k >= 0; k--) {
                if (up[k][l] != -1 && up[k][l] <= r + 1) {
                    l = up[k][l];
                    ans += 1 << k;
                }
            }

            cout << ans << endl;
        }
        pos.clear();

    }
    return 0;
}
