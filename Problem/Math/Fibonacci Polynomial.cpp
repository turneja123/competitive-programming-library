//https://www.spoj.com/problems/FIBONOMIAL/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;

vector<vector<long long>> mul(vector<vector<long long>> base, vector<vector<long long>> mat) {
    int n = base.size(), m = mat[0].size(), k = mat.size();
    vector<vector<long long>> ret;
    ret.assign(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int p = 0; p < k; p++) {
                ret[i][j] += (base[i][p] * mat[p][j]) % M;
                ret[i][j] %= M;
            }
        }
    }
    return ret;
}

vector<vector<long long>> expo(vector<vector<long long>> base, int n, long long k) {
    vector<vector<long long>> ans;
    ans.assign(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = (i == j);
        }
    }
    while (k) {
        if (k % 2 == 1) {
            ans = mul(ans, base);
        }
        base = mul(base, base);
        k /= 2;
    }
    return ans;
}

long long modPow(long long x, long long y) {
    if (x == 0 && y == 0) {
        return 1;
    }
    long long res = 1;
    x = x % M;
    if (x == 0) {
        return 0;
    }
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % M;
        }
        y >>= 1;
        x = (x * x) % M;
    }
    return res;
}

long long modDivide(long long a, long long b, long long m) {
    a = a % m;
    long long inv = modPow(b, m - 2);
    return (inv * a) % m;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long n, x;
        cin >> n >> x;
        if (x == 0) {
            cout << 0 << endl;
            continue;
        }
        vector<vector<long long>> m{{1, 1}, {1, 0}};
        m = expo(m, 2, n);
        vector<vector<long long>> fib{{1}, {0}};
        fib = mul(m, fib);
        x %= M;
        long long xn = modPow(x, n), x2 = (x * x) % M;
        long long ans = modDivide((((xn * x2) % M * fib[1][0]) % M + ((xn * x) % M * fib[0][0]) % M - x + M) % M, (x2 + x - 1 + M) % M, M);
        cout << ans << endl;
    }

    return 0;
}
