//https://codeforces.com/contest/852/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;


vector<vector<ll>> mul(vector<vector<ll>> a, vector<vector<ll>> b) {
    int n = a.size(), m = a[0].size(), p = b[0].size();
    vector<vector<ll>> ans(n, vector<ll>(p, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % M;
            }
        }
    }
    return ans;
}

vector<vector<ll>> expo(vector<vector<ll>> mat, int k) {
    int n = mat.size();
    vector<vector<ll>> id(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
        id[i][i] = 1;
    }
    while (k > 0) {
        if (k % 2 == 1) {
            id = mul(id, mat);
        }
        mat = mul(mat, mat);
        k /= 2;
    }
    return id;
}

int main() {
    IOS;
    int n, k, m;
    cin >> n >> k >> m;

    vector<ll> v(m, 0);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        v[c % m]++;
    }

    vector<int> cost(n);
    vector<ll> coef(m, 0);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        cost[i] = c;
        coef[c % m]++;
    }
    vector<vector<ll>> mat(m, vector<ll>(m, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int k = (i + j) % m;
            mat[i][k] = (mat[i][k] + coef[j]) % M;
        }
    }

    mat = expo(mat, k - 2);
    vector<vector<ll>> V{v};
    V = mul(V, mat);

    v = V[0];
    coef.clear();
    coef.assign(m, 0);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        coef[(cost[i] + c) % m]++;
    }
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int k = (i + j) % m;
            if (k == 0) {
                ans = (ans + v[i] * coef[j]) % M;
            }
        }
    }
    cout << ans;

    return 0;
}
