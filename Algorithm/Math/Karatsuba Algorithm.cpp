#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int M = 1e9 + 7;

vector<int> karatsuba(vector<int> &a, vector<int> &b) {
    int n = a.size();
    if (n <= 16) {
        vector<int> ans(2 * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[i + j] = (ans[i + j] + (ll)a[i] * b[j]) % M;
            }
        }
        return ans;
    }
    int m = n / 2;
    vector<int> a0(m), a1(m);
    vector<int> b0(m), b1(m);
    for (int i = 0; i < m; i++) {
        a0[i] = a[i], a1[i] = a[i + m];
        b0[i] = b[i], b1[i] = b[i + m];
    }
    vector<int> z0 = karatsuba(a0, b0);
    vector<int> z2 = karatsuba(a1, b1);
    for (int i = 0; i < m; i++) {
        a0[i] += a1[i];
        if (a0[i] >= M) {
            a0[i] -= M;
        }
        b0[i] += b1[i];
        if (b0[i] >= M) {
            b0[i] -= M;
        }
    }
    vector<int> z1 = karatsuba(a0, b0);
    for (int i = 0; i < n; i++) {
        z1[i] -= z0[i];
        if (z1[i] < 0) {
            z1[i] += M;
        }
        z1[i] -= z2[i];
        if (z1[i] < 0) {
            z1[i] += M;
        }
    }
    vector<int> ans(2 * n);
    for (int i = 0; i < n; i++) {
        ans[i] += z0[i];
        if (ans[i] >= M) {
            ans[i] -= M;
        }
        ans[i + m] += z1[i];
        if (ans[i + m] >= M) {
            ans[i + m] -= M;
        }
        ans[i + n] += z2[i];
        if (ans[i + n] >= M) {
            ans[i + n] -= M;
        }
    }
    return ans;
}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    int s = 1;
    while (s < max(n, m)) {
        s *= 2;
    }
    a.resize(s), b.resize(s);
    vector<int> ans = karatsuba(a, b);
    for (int i = 0; i < n + m - 1; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
