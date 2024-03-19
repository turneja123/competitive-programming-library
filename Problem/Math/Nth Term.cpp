//https://lightoj.com/problem/nth-term
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 10007;

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
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        long long n, a, b, c;
        cin >> n >> a >> b >> c;
        vector<vector<long long>> m{{a, 0, b, 1}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}};
        m = expo(m, 4, n - 3);
        vector<vector<long long>> ans{{c}, {0}, {0}, {c}};
        ans = mul(m, ans);
        cout << "Case " << i << ": ";
        cout << ((n > 2) ? ans[0][0] : 0) << endl;
    }

    return 0;
}
