//https://codeforces.com/contest/717/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;
using vi = vector<vector<ld>>;

vi mul(vi a, vi b) {
    vi c(a.size(), vector<ld>(b[0].size(), 0));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < a[0].size(); k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

vi matPow(vi a, ll k) {
    int n = a.size();
    vi id(n, vector<ld>(n, 0));
    for (int i = 0; i < n; i++) {
        id[i][i] = 1;
    }
    while (k > 0) {
        if (k % 2) {
            id = mul(id, a);
        }
        a = mul(a, a);
        k /= 2;
    }
    return id;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int k, n;
    cin >> k >> n;
    vector<ld> a(128, 0);
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    vector<ld> v(128, 0);
    v[0] = 1.0;
    vi c = {v};
    vi mat(128, vector<ld>(128, 0));
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            int k = i ^ j;
            mat[k][i] += a[j];
        }
    }
    c = mul(c, matPow(mat, k));
    cout << 1.0 - c[0][0];
    return 0;
}
