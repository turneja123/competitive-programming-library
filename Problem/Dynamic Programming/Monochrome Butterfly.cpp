//https://ocpc2025s.eolymp.space/en/compete/995jqjr9ep1vr04atvo1l2ifr0/problem/5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 7;
const int P = 2500;
const long long M = 998244353;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}


long long dp[P][P];
long long dp_nx[P][P];
long long pw[10];
bool seen[P][P];
vector<int> pos[P];


int main() {
    IOS;
    long long n, m;
    cin >> n >> m;
    if (n > m) {
        swap(n, m);
    }
    if (n < 3) {
        cout << 0;
        return 0;
    }
    if (n >= 7) {
        cout << modPow(2, n * m);
        return 0;
    }
    if (n >= 5 && m >= 10) {
        cout << modPow(2, n * m);
        return 0;
    }
    int p = 3;
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * p;
    }
    for (int i = 0; i < pw[n]; i++) {
        pos[i].resize(n);
        int j = 0, mask = i;
        while (mask > 0) {
            pos[i][j++] = mask % p;
            mask /= p;
        }
    }
    long long ans = 0;
    vector<pair<int, int>> go;
    for (int i = 0; i < 1 << n; i++) {
        int maska = 0, maskb = 0;
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (c == 0) {
                maska += pw[j];
            } else {
                maskb += pw[j];
            }
        }
        if (!seen[maska][maskb]) {
            seen[maska][maskb] = true;
            go.push_back({maska, maskb});
        }
        dp[maska][maskb]++;
        for (auto [maska, maskb] : go) {
            seen[maska][maskb] = false;
        }
    }
    for (int row = 1; row < m; row++) {
        vector<pair<int, int>> nx;
        for (auto [ia, ib] : go) {
            for (int i = 0; i < 1 << n; i++) {
                int maska = 0, maskb = 0;
                int la = n, ra = -1, lb = n, rb = -1;
                int bad = 0;
                for (int j = 0; j < n && !bad; j++) {
                    int c = i & (1 << j);
                    if (c == 0) {
                        la = min(la, j);
                        ra = max(ra, j);
                        if (pos[ia][j] == 2) {
                            bad = 1;
                        }
                    } else {
                        lb = min(lb, j);
                        rb = max(rb, j);
                        if (pos[ib][j] == 2) {
                            bad = 1;
                        }
                    }
                }
                if (bad) {
                    continue;
                }
                for (int j = 0; j < n; j++) {
                    int pa = pos[ia][j], pb = pos[ib][j];
                    int c = i & (1 << j);
                    if (c == 0) {
                        if (j > la && j < ra && pa == 1) {
                            pa = 2;
                        }
                        pa = max(pa, 1);

                    } else {
                        if (j > lb && j < rb && pb == 1) {
                            pb = 2;
                        }
                        pb = max(pb, 1);

                    }
                    maska += pa * pw[j];
                    maskb += pb * pw[j];
                }
                if (!seen[maska][maskb]) {
                    seen[maska][maskb] = 1;
                    nx.push_back({maska, maskb});
                }
                dp_nx[maska][maskb] = (dp_nx[maska][maskb] + dp[ia][ib]) % M;
                if (row == m - 1) {
                    ans = (ans + dp[ia][ib]) % M;
                }
            }
        }
        for (auto [maska, maskb] : go) {
            dp[maska][maskb] = 0;
        }
        go = nx;
        for (auto [maska, maskb] : go) {
            seen[maska][maskb] = false;
            dp[maska][maskb] = dp_nx[maska][maskb];
            dp_nx[maska][maskb] = 0;
        }
    }
    cout << (modPow(2, n * m) - ans + M) % M;

    return 0;
}
