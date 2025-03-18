//https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
int freqs[N];
vector<int> adj[N];
long long ans[N];

using cd = complex<double>;
const double PI = acos(-1);

long long reverse(long long num, int lg_n) {
    long long res = 0;
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

    for (long long i = 0; i < n; i++) {
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
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

int dfs_depth1(int u, int p) {
    int low = depth[u];
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            low = max(low, dfs_depth1(v, u));
        }
    }
    return low;
}

void dfs_depth2(int u, int p, vector<long long> &f) {
    f[depth[u]]++;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_depth2(v, u, f);
        }
    }
    return;
}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;

    vector<pair<int, int>> temp;

    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            int m = dfs_depth1(v, v);
            temp.push_back(make_pair(m, v));
        }
    }
    int mx = 0;
    sort(temp.begin(), temp.end());
    for (auto [m, v] : temp) {
        vector<long long> cur(m + 1, 0);
        dfs_depth2(v, v, cur);
        if (mx != 0) {
            vector<long long> have(mx + 1, 0);
            for (int i = 0; i <= mx; i++) {
                have[i] = freqs[i];
            }
            vector<long long> prod = multiply(cur, have);
            for (int i = 0; i < prod.size(); i++) {
                ans[i] += prod[i];
            }
        }
        mx = max(mx, m);
        for (int i = 0; i <= m; i++) {
            ans[i] += cur[i];
            freqs[i] += cur[i];
        }

    }
    for (int i = 0; i <= mx; i++) {
        freqs[i] = 0;
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1);
    for (int i = 1; i < n; i++) {
        cout << ans[i] << " ";
    }


    return 0;
}
