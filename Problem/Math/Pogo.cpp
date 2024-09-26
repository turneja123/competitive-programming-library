//https://dmoj.ca/problem/utso15p3
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int n, m;
map<int, int> mp;

const long long M = 1e9 + 7;

vector<long long> s[4], c[4];

vector<long long> mul(int n, vector<long long> &a, vector<long long> &b, vector<long long> &tr) {
    vector<long long> res(n * 2 + 1, 0);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            res[i + j] = (res[i + j] + a[i] * b[j]) % M;
        }
    }
    for (int i = 2 * n; i > n; --i) {
        for (int j = 0; j < n; j++) {
            res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % M;
        }
    }
    res.resize(n + 1);
    return res;
}

long long solve(vector<long long> &c, vector<long long> &s, long long k) {
    int n = c.size();
    if (n == 0) {
        return 0;
    }
    if (k < n) {
        return s[k];
    }
    vector<long long> x(n + 1), a(x);
    x[0] = 1, a[1] = 1;
    for (++k; k; k /= 2) {
        if (k % 2) {
            x = mul(n, x, a, c);
        }
        a = mul(n, a, a, c);
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + x[i + 1] * s[i]) % M;
    }
    return res;
}

void dfs(int u, vector<bool> &vis, int ct) {
    if (u == n - 1) {
        mp[ct]++;
        return;
    }
    for (int i = max(0, u - m); i <= min(n - 1, u + m); i++) {
        if (!vis[i]) {
            vis[i] = true;
            dfs(i, vis, ct + 1);
            vis[i] = false;
        }
    }
}

int main() {
    IOS;
    int k;
    cin >> k >> m;
    if (m == 1) {
        cout << 1;
        return 0;
    }
    c[2] = {1, 0, 1};
    s[2] = {1, 1, 1};
    s[3] = {1, 1, 1, 2, 6, 14, 28, 56};
    c[3] = {2, 1000000006, 2, 1, 1, 0, 1000000006, 1000000006};
    /*vector<long long> s;
    for (int i = 1; i < 20; i++) {
        n = i;
        vector<bool> vis(n, false);
        vis[0] = true;
        dfs(0, vis, 0);
        int mx = 0;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            mx = max(mx, it->first);
        }
        s.push_back(mp[mx]);
        mp.clear();
    }
    vector<long long> c = berlekamp_massey(s);
    for (int i = 0; i < c.size(); i++) {
        cout << s[i] << ", ";
    }*/
    cout << solve(c[m], s[m], k - 1);
    return 0;
}
