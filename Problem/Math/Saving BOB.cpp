//https://www.spoj.com/problems/DCEPCA06/
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
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<vector<long long>> m(10, vector<long long>(10, 0));
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (abs(i - j) >= k) {
                    m[i][j] = 1;
                }
            }
        }
        vector<vector<long long>> ans(10, vector<long long>(1, 1));
        ans[0][0] = 0;
        m = expo(m, 10, n - 1);
        ans = mul(m, ans);
        long long sum = 0;
        for (int i = 0; i < 10; i++) {
            sum = (sum + ans[i][0]) % M;
        }
        cout << sum << endl;
    }

    return 0;
}
