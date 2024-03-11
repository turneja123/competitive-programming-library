//solution for https://cses.fi/problemset/task/1724/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long INF = 2e18;

vector<vector<long long>> mul(vector<vector<long long>> base, vector<vector<long long>> m, int n) {
    vector<vector<long long>> ret;
    ret.assign(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int p = 0; p < n; p++) {
                ret[i][j] = min(ret[i][j], base[i][p] + m[p][j]);
            }
        }
    }
    return ret;
}

vector<vector<long long>> expo(vector<vector<long long>> base, int n, int k) {
    vector<vector<long long>> ans;
    ans.assign(n, vector<long long>(n, 0));
    bool flag = true;
    while (k) {
        if (k % 2 == 1) {
            if (flag) {
                ans = base;
                flag = false;
            } else {
                ans = mul(ans, base, n);
            }
        }
        base = mul(base, base, n);
        k /= 2;
    }
    return ans;
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<long long>> a;
    a.assign(n, vector<long long>(n, INF));
    for (int i = 0; i < m; i++) {
        int u, v; long long wt;
        cin >> u >> v >> wt;
        u--, v--;
        a[u][v] = min(a[u][v], wt);
    }
    vector<vector<long long>> ans = expo(a, n, k);
    if (ans[0][n - 1] == INF) {
        cout << -1 << endl;
    } else {
        cout << ans[0][n - 1] << endl;
    }
    return 0;
}
