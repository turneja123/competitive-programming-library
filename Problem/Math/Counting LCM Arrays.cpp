//https://cses.fi/problemset/task/3169/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1200;
const long long M = 1e9 + 7;

long long dp[N][N];

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
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin>> m >> n;
        vector<int> divs;
        vector<int> prime_pow;
        int tmp = n;
        for (int i = 1; i <= sqrt(n); i++) {
            if (n % i == 0) {
                divs.push_back(i);
                if (n / i != i) {
                    divs.push_back(n / i);
                }
            }
            if (tmp % i == 0 && i != 1) {
                int pe = 1;
                while (tmp % i == 0) {
                    tmp /= i;
                    pe *= i;
                }
                prime_pow.push_back(pe);
            }
        }
        if (tmp > 1) {
            prime_pow.push_back(tmp);
        }
        int d = divs.size(), e = prime_pow.size();
        int full = (1 << e) - 1;
        vector<int> mask(d, 0);
        vector<int> freq(full + 1, 0);
        for (int i = 0; i < d; i++) {
            for (int j = 0; j < e; j++) {
                if (divs[i] % prime_pow[j] == 0) {
                    mask[i] += 1 << j;
                }
            }
            freq[mask[i]]++;
        }
        for (int j = 0; j <= full; j++) {
            dp[0][j] = freq[j];
        }
        vector<long long> sos(full + 1, 0);
        for (int j = 0; j <= full; j++) {
            sos[j] = dp[0][j];
        }
        for (int k = 0; k < e; k++) {
            for (int j = 0; j <= full; j++) {
                int c = j & (1 << k);
                if (!c) {
                    sos[j] = (sos[j] + sos[j | (1 << k)]) % M;
                }
            }
        }
        vector<long long> s;
        for (int i = 1; i < 82; i++) {
            s.push_back(0);
            for (int j = 0; j <= full; j++) {
                dp[i][j] = sos[full ^ j] * freq[j] % M;
                s[i - 1] = (s[i - 1] + dp[i][j]) % M;
            }
            for (int j = 0; j <= full; j++) {
                sos[j] = dp[i][j];
            }
            for (int k = 0; k < e; k++) {
                for (int j = 0; j <= full; j++) {
                    int c = j & (1 << k);
                    if (!c) {
                        sos[j] = (sos[j] + sos[j | (1 << k)]) % M;
                    }
                }
            }
            if ((int)berlekamp_massey(s).size() < i / 2 - 3) {
                break;
            }
        }
        vector<long long> c = berlekamp_massey(s);
        cout << solve(c, s, m - 2) << endl;
    }
    return 0;
}
