//https://atcoder.jp/contests/abc305/tasks/abc305_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 150;
const int K = 12;
const long long M = 998244353;

bool can[1 << K];
string s[N];
long long dp[500][1 << K];

bool contains(string &a, string &b) {
    int n = a.size(), m = b.size();
    if (n < m) {
        return false;
    }
    for (int i = 0; i <= n - m; i++) {
        string sub = a.substr(i, m);
        if (sub == b) {
            return true;
        }
    }
    return false;
}


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

int main() {
	IOS;
	long long n; int m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
        cin >> s[i];
	}
	for (int i = 0; i < 1 << K; i++) {
        string mask = "";
        for (int j = 0; j < K; j++) {
            int c = i & (1 << j);
            if (c) {
                mask += 'b';
            } else {
                mask += 'a';
            }
        }
        can[i] = true;
        for (int j = 0; j < m; j++) {
            can[i] &= !(contains(mask, s[j]));
        }
	}
	vector<long long> S(500, 0);
	for (int k = 1; k < K; k++) {
        for (int i = 0; i < 1 << k; i++) {
            string mask = "";
            for (int j = 0; j < k; j++) {
                int c = i & (1 << j);
                if (c) {
                    mask += 'b';
                } else {
                    mask += 'a';
                }
            }
            bool can = true;
            for (int j = 0; j < m; j++) {
                can &= !(contains(mask, s[j]));
            }
            if (can) {
                S[k]++;
            }
        }
	}
	for (int i = 0; i < 1 << K; i++) {
        if (can[i]) {
            S[K]++;
            dp[K][i] = 1;
        }
	}
	if (n <= K) {
        cout << S[n];
        return 0;
	}
	for (int k = K + 1; k < 500; k++) {
        for (int i = 0; i < 1 << K; i++) {
            int mask = i << 1;
            if (mask >= (1 << K)) {
                mask -= 1 << K;
            }
            if (can[mask]) {
                dp[k][mask] = (dp[k][mask] + dp[k - 1][i]) % M;
            }
            if (can[mask + 1]) {
                dp[k][mask + 1] = (dp[k][mask + 1] + dp[k - 1][i]) % M;
            }
        }
        for (int i = 0; i < 1 << K; i++) {
            S[k] = (S[k] + dp[k][i]) % M;
        }
	}
	vector<long long> C = berlekamp_massey(S);
	cout << solve(C, S, n) << endl;
	return 0;
}
