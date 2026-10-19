//bbc18q
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 1;
const ll M = 998244353;

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

vector<vector<ll>> expo(vector<vector<ll>> mat, ll k) {
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
    int n, a; ll k;
    cin >> n >> a >> k;
    vector<int> freq(N);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }
    int mx = N;
    for (int i = 0; i < 15; i++) {
        int nx_mx = 0;
        for (int j = 0; j <= mx; j++) {
            if (!freq[j]) {
                continue;
            }
            if (j == 0) {
                nx_mx = max(nx_mx, 1);
                continue;
            }
            string s = to_string(j);
            int sz = s.size();
            if (sz % 2 == 0) {
                int l = stoi(s.substr(0, sz / 2));
                int r = stoi(s.substr(sz / 2, sz / 2));
                nx_mx = max({nx_mx, l, r});
            } else {
                nx_mx = max({nx_mx, j * a});
            }
        }
        vector<int> freq_nx(nx_mx + 1, 0);
        for (int j = 0; j <= mx; j++) {
            if (!freq[j]) {
                continue;
            }
            if (j == 0) {
                freq_nx[1] = (freq_nx[1] + freq[j]) % M;
                continue;
            }
            string s = to_string(j);
            int sz = s.size();
            if (sz % 2 == 0) {
                int l = stoi(s.substr(0, sz / 2));
                int r = stoi(s.substr(sz / 2, sz / 2));
                freq_nx[l] = (freq_nx[l] + freq[j]) % M;
                freq_nx[r] = (freq_nx[r] + freq[j]) % M;
            } else {
                freq_nx[j * a] = (freq_nx[j * a] + freq[j]) % M;
            }
        }
        k--;
        mx = nx_mx;
        freq = freq_nx;
        freq_nx.clear();
        if (k == 0) {
            ll ans = accumulate(freq.begin(), freq.end(), 0);
            cout << ans % M;
            return 0;
        }
    }
    vector<ll> tmp(100);
    for (int i = 0; i <= mx; i++) {
        tmp[i] = freq[i];
    }
    vector<vector<ll>> v{tmp};
    vector<vector<ll>> mat(100, vector<ll>(100, 0));
    mat[0][1]++;
    for (int i = 1; i <= 9; i++) {
        mat[i][i * a]++;
    }
    for (int i = 10; i < 100; i++) {
        mat[i][i / 10]++;
        mat[i][i % 10]++;
    }
    mat = expo(mat, k);
    v = mul(v, mat);
    ll ans = accumulate(v[0].begin(), v[0].end(), 0ll);
    cout << ans % M;


    return 0;
}
