//https://www.codechef.com/problems/KBIGNUMB
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long M;

vector<vector<long long>> mul(vector<vector<long long>> base, vector<vector<long long>> mat) {
    int n = base.size(), m = mat[0].size(), k = mat.size();
    vector<vector<long long>> ret;
    ret.assign(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int p = 0; p < k; p++) {
                ret[i][j] += base[i][p] * mat[p][j];
            }
            ret[i][j] %= M;
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
        long long a, n;
        cin >> a >> n >> M;
        long long x = 1;
        while (a >= x) {
            x *= 10;
        }
        if (n == 1) {
            cout << a % M << endl;
            continue;
        }
        vector<vector<long long>> m{{x % M, 0, 1}, {1, 0, 0}, {0, 0, 1}};
        m = expo(m, 3, n - 2);
        vector<vector<long long>> ans{{(a * x % M + a % M) % M}, {a % M}, {a % M}};
        ans = mul(m, ans);
        cout << ans[0][0] << endl;

    }


    return 0;
}
