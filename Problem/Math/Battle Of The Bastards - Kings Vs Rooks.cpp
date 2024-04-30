//https://www.spoj.com/problems/BATTLECRY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

long long M = 7340033;

int ki, kj, ri, rj, Ri, Rj, n; long long ans = 0;

vector<long long> mul(int n, vector<long long> &a, vector<long long> &b, vector<long long> &tr) {
    vector<long long> res(n * 2 + 1, 0);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            res[i + j] = (res[i + j] + a[i] * b[j]) % M;
        }
    }
    for (int i = 2 * n; i > n; --i) {
        for (int j = 0; j < n; j++) {
            res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % M;
        }
    }
    res.resize(n + 1);
    return res;
}

long long solve(vector<long long> &c, vector<long long> &s, long long k) {
    int n = c.size();
    if (n == 0) {
        return 0;
    }
    if (k < 0) {
        return 0;
    }
    if (k < n) {
        return s[k] % M;
    }
    vector<long long> x(n + 1), a(x);
    x[0] = 1, a[1] = 1;
    for (++k; k; k /= 2) {
        if (k % 2) {
            x = mul(n, x, a, c);
        }
        a = mul(n, a, a, c);
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + x[i + 1] * s[i]) % M;
    }
    return res;
}

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

vector<long long> berlekamp_massey(vector<long long> s) {
    int n = s.size(), l = 0, m = 0;
    vector<long long> c(n), b(n), t(n);
    c[0] = 1, b[0] = 1;
    long long d = 1;
    for (int i = 0; i < n; i++) {
        m++;
        long long d_next = s[i];
        for (int j = 1; j <= l; j++) {
            d_next = (d_next + (c[j] * s[i - j]) % M) % M;
        }
        if (d_next == 0) {
            continue;
        }
        t = c;
        long long coef = (d_next * modPow(d, M - 2)) % M;
        for (int j = m; j < n; j++) {
            c[j] = (c[j] - (coef * b[j - m]) % M + M) % M;
        }
        if (2 * l > i) {
            continue;
        }
        l = i + 1 - l, b = t, d = d_next, m = 0;
    }
    c.resize(l + 1);
    c.erase(c.begin());
    for (int i = 0; i < l; i++) {
        c[i] *= -1;
        c[i] = (c[i] + M) % M;
    }
    return c;
}

vector<pair<int, int>> chk;

void mark(int x, int y, vector<vector<int>> &v, bool b) {
    for (int i = x - 1; i > 0; i--) {
        if (!v[i][y] && b) {
            chk.push_back(make_pair(i, y));
        }
        v[i][y] = b;
        if (i == ki && y == kj) {
            break;
        }
    }
    for (int i = x + 1; i <= n; i++) {
        if (!v[i][y] && b) {
            chk.push_back(make_pair(i, y));
        }
        v[i][y] = b;
        if (i == ki && y == kj) {
            break;
        }
    }
    for (int i = y - 1; i > 0; i--) {
        if (!v[x][i] && b) {
            chk.push_back(make_pair(x, i));
        }
        v[x][i] = b;
        if (x == ki && i == kj) {
            break;
        }
    }
    for (int i = y + 1; i <= n; i++) {
        if (!v[x][i] && b) {
            chk.push_back(make_pair(x, i));
        }
        v[x][i] = b;
        if (x == ki && i == kj) {
            break;
        }
    }
}

void calc(vector<vector<int>> &v) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (abs(dx) + abs(dy) != 0) {
                v[ki + dx][kj + dy] = true;
            }
        }
    }
    mark(ri, rj, v, true);
    mark(Ri, Rj, v, true);
    for (int k = 0; k < chk.size(); k++) {
        int i = chk[k].first, j = chk[k].second;
        if ((i == ki && j == kj) || (i == ri && j == rj) || (i == Ri && j == Rj)) {
            continue;
        }
        int add = 1, ct = 0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                ct += v[i + dx][j + dy];
                if (i + dx == ki && j + dy == kj) {
                    add = 0;
                }
            }
        }
        if (ct != 9) {
            add = 0;
        }
        ans += add;
    }
    chk.clear();
    mark(ri, rj, v, false);
    mark(Ri, Rj, v, false);
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (abs(dx) + abs(dy) != 0 && ki + dx > 0 && ki + dx <= n && kj + dy > 0 && kj + dy <= n) {
                v[ki + dx][kj + dy] = false;
            }
        }
    }
}


void rook2(vector<vector<int>> &v) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!(i == ki && j == kj) && !(i == ri && j == rj)) {
                Ri = i, Rj = j;
                calc(v);
            }
        }
    }
}

void rook1(vector<vector<int>> &v) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!(i == ki && j == kj)) {
                ri = i, rj = j;
                rook2(v);
            }
        }
    }
}

int main() {
    IOS;
    int t = 16;
    vector<long long> s{232,1432,5188,14536,34464,72392,138652,246968,414936,664504,1022452,1520872,2197648,3096936};
    for (n = 17; n <= t; n++) {
        vector<vector<int>> v(n + 2, vector<int>(n + 2, 0));
        for (int j = 0; j < n + 2; j++) {
            v[0][j] = 1;
            v[n + 1][j] = 1;
        }
        for (int j = 0; j < n + 2; j++) {
            v[j][0] = 1;
            v[j][n + 1] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                ki = i, kj = j;
                rook1(v);
            }
        }
        cout << ans / 2 << endl;
        ans = 0;
    }
    vector<long long> c = berlekamp_massey(s);
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int k;
        cin >> k;
        cout << "Case " << i << ": " << solve(c, s, k - 3) << endl;
    }

    return 0;
}
