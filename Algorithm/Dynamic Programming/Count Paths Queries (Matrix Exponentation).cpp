//https://codeforces.com/gym/102644/problem/I
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 2e9;

vector<vector<long long>> e[32];

vector<vector<long long>> mul(vector<vector<long long>> base, vector<vector<long long>> m, int n) {
    vector<vector<long long>> ret;
    ret.assign(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int p = 0; p < n; p++) {
                ret[i][j] = (ret[i][j] + base[i][p] * m[p][j]) % M;
            }
        }
    }
    return ret;
}

void expo(vector<vector<long long>> base, int n, int k) {
    int ct = 0;
    while (k) {
        e[ct] = base;
        base = mul(base, base, n);
        k /= 2;
        ct++;
    }
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<long long>> a;
    a.assign(n, vector<long long>(n, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        a[u][v] = 1;
    }
    expo(a, n, N);
    for (int t = 0; t < q; t++) {
        int u, v, k;
        cin >> u >> v >> k;
        u--, v--;
        vector<long long> ans;
        bool flag = true;
        for (int i = 0; i < 32; i++) {
            int cmp = k & (1 << i);
            if (cmp != 0) {
                if (flag) {
                    ans = e[i][u];
                    flag = false;
                } else {
                    vector<long long> temp(n, 0);
                    for (int j = 0; j < n; j++) {
                        for (int p = 0; p < n; p++) {
                            temp[p] = (temp[p] + ans[j] * e[i][j][p]) % M;
                        }
                    }
                    ans = temp;
                }
            }
        }
        cout << ans[v] << endl;

    }
    return 0;
}
