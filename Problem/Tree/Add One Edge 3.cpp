//https://atcoder.jp/contests/abc401/tasks/abc401_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

vector<int> adj[N];

int depth[N];
int subtree[N];
int aux[N];
int child[N];
int dp[N];

using cd = complex<double>;
const double PI = acos(-1);

int reverse(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
        if (num & (1 << i)) {
            res |= 1 << (lg_n - 1 - i);
        }
    }
    return res;
}

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n) {
        lg_n++;
    }

    for (int i = 0; i < n; i++) {
        if (i < reverse(i, lg_n)) {
            swap(a[i], a[reverse(i, lg_n)]);
        }
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<long long> multiply(vector<long long> & a, vector<long long> & b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);

    vector<long long> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }
    return result;
}

void dfs_subtree(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_subtree(v, u);
            if (subtree[v] + 1 > subtree[u]) {
                subtree[u] = subtree[v] + 1;
                child[u] = v;
            }
        }
    }
    for (int v : adj[u]) {
        if (v != p && v != child[u]) {
            aux[u] = max(aux[u], subtree[v] + 1);
        }
    }
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p && v != child[u]) {
            dp[v] = max(dp[u] + 1, subtree[u] + 1);
        } else if (v != p && v == child[u]) {
            dp[v] = max(dp[u] + 1, aux[u] + 1);
        }
        if (v != p) {
            dfs(v, u);
        }
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        u += n, v += n;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_subtree(0, 0);
    dfs(0, 0);
    dfs_subtree(n, n);
    dfs(n, n);
    int d = 0;
    vector<long long> a(n + 1, 0);
    for (int i = 0; i < n; i++) {
        d = max({d, subtree[i], dp[i]});
        a[max(subtree[i], dp[i]) + 1]++;
    }
    vector<long long> b(m, 0);
    for (int i = n; i < n + m; i++) {
        d = max({d, subtree[i], dp[i]});
        b[max(subtree[i], dp[i])]++;
    }
    vector<long long> c = multiply(a, b);
    long long ans = 0;
    for (int i = 0; i < c.size(); i++) {
        ans += c[i] * max(i, d);
    }
    cout << ans;
    return 0;
}
