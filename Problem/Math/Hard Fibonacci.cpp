//https://www.spoj.com/problems/FIBHARD/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long P = 1996488708, M = 998244353;

long long read() {
    long long x = 0, f = 1;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar_unlocked();
    }
    return x * f;
}

void print(long long x) {
    if (x < 0) {
        putchar_unlocked('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar_unlocked(x % 10 + '0');
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
    if (k < n) {
        return s[k];
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

int main() {
    //IOS;
    int t, i, j;
    vector<long long> s{0, 1}, c{1, 1};
    t = read();
    while (t--) {
        long long n = 0; j = 0;
        while (isdigit(i = getchar_unlocked())) {
            n = n * 10 + i - '0';
            if (j > 7) {
                n %= P;
                j = 0;
            } else {
                j++;
            }
        }
        n %= P;
        print(solve(c, s, n));
        putchar_unlocked('\n');
    }

    return 0;
}
