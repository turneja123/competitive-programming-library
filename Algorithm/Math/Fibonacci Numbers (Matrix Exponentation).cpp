//https://cses.fi/problemset/task/1722
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

int main() {
    IOS;
    long long n;
    cin >> n;
    vector<vector<long long>> m{{1, 1}, {1, 0}};
    m = expo(m, 2, n - 1);
    vector<vector<long long>> fib{{1}, {0}};
    fib = mul(m, fib);
    cout << ((n > 0) ? fib[0][0] : 0);

    return 0;
}
