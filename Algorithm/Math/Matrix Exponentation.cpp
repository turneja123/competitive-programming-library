//solution for https://www.spoj.com/problems/MPOW/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;

vector<vector<long long>> mul(vector<vector<long long>> base, vector<vector<long long>> m, int n) {
    vector<vector<long long>> ret;
    ret.assign(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int p = 0; p < n; p++) {
                ret[i][j] += (base[i][p] * m[p][j]) % M;
                ret[i][j] %= M;
            }
        }
    }
    return ret;
}

vector<vector<long long>> expo(vector<vector<long long>> base, int n, int k) {
    vector<vector<long long>> ans;
    ans.assign(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = (i == j);
        }
    }
    while (k) {
        if (k % 2 == 1) {
            ans = mul(ans, base, n);
        }
        base = mul(base, base, n);
        k /= 2;
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<vector<long long>> a;
        a.assign(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }
        vector<vector<long long>> ans = expo(a, n, k);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }

    }
    return 0;
}
