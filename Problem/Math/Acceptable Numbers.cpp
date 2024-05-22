//https://www.spoj.com/problems/KBASEEN/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<vector<__int128>> mul(vector<vector<__int128>> base, vector<vector<__int128>> mat, __int128 M) {
    int n = base.size(), m = mat[0].size(), k = mat.size();
    vector<vector<__int128>> ret;
    ret.assign(n, vector<__int128>(m, 0));
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

vector<vector<__int128>> expo(vector<vector<__int128>> base, int n, long long k, __int128 M) {
    vector<vector<__int128>> ans;
    ans.assign(n, vector<__int128>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = (i == j);
        }
    }
    while (k) {
        if (k % 2 == 1) {
            ans = mul(ans, base, M);
        }
        base = mul(base, base, M);
        k /= 2;
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long n, k, M;
        cin >> n >> k >> M;
        /*dp[1][0] = 0, dp[1][1] = k - 1;
        for (int i = 2; i <= n; i++) {
            dp[i][0] = dp[i - 1][1];
            dp[i][1] = (k - 1) * (dp[i - 1][0] + dp[i - 1][1]);
        }*/
        k = (k - 1 + M) % M;
        vector<vector<__int128>> m{{k, k}, {1, 0}};
        vector<vector<__int128>> ans{{k}, {0}};
        m = expo(m, 2, n - 1, M);
        ans = mul(m, ans, M);
        long long sum = (ans[0][0] + ans[1][0]) % M;
        cout << (sum + (n == 1)) % M << endl;
    }
    return 0;
}
