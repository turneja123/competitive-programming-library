//https://codeforces.com/gym/102644/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<vector<double>> mul(vector<vector<double>> base, vector<vector<double>> mat) {
    int n = base.size(), m = mat[0].size(), k = mat.size();
    vector<vector<double>> ret;
    ret.assign(n, vector<double>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int p = 0; p < k; p++) {
                ret[i][j] += base[i][p] * mat[p][j];
            }
        }
    }
    return ret;
}

vector<vector<double>> expo(vector<vector<double>> base, int n, long long k) {
    vector<vector<double>> ans;
    ans.assign(n, vector<double>(n, 0));
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
    cout << fixed;
    cout << setprecision(6);
    long long n; double p;
    cin >> n >> p;
    vector<vector<double>> m{{1 - p, p, 0}, {p - 1, -p, 1}, {0, 0, 1}};
    m = expo(m, 3, n);
    vector<vector<double>> prob{{1}, {0}, {1}};
    prob = mul(m, prob);
    cout << prob[0][0];

    return 0;
}
