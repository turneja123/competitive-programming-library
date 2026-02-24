//https://atcoder.jp/contests/arc215/tasks/arc215_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
int freqs[N];
vector<int> adj[N];
long long ans[N];
int subtree[N];
int dp[N];
int child[N];
int aux[N];

vector<int> NEED[N];

using cd = complex<double>;
const double PI = acos(-1);

int D, node;

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

int low[N];

int dfs_depth1(int u, int p) {
    low[u] = depth[u];
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            low[u] = max(low[u], dfs_depth1(v, u));
        }
    }
    return low[u];
}

void dfs_depth2(int u, int p, vector<long long> &f) {
    int go = -1, ok = 1;
    for (int v : adj[u]) {
        if (v != p && seen_c[v] && binary_search(NEED[u].begin(), NEED[u].end(), v)) {
            return;
        }

        if (v != p && !seen_c[v] && binary_search(NEED[u].begin(), NEED[u].end(), v)) {
            if (go != -1) {
                ok = 0;
            } else {
                go = v;
            }
        }
    }
    if (!ok) {
        return;
    }
    if (go != -1) {
        dfs_depth2(go, u, f);
        return;
    }
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
    int ok = 1;
    for (int v : adj[c]) {
        if (seen_c[v] && binary_search(NEED[c].begin(), NEED[c].end(), v)) {
            ok = 0;
        }
    }
    if (ok) {
        vector<pair<int, int>> need, temp;

        for (int v : adj[c]) {
            if (!seen_c[v]) {
                depth[v] = 1;
                int m = dfs_depth1(v, v);
                if (binary_search(NEED[c].begin(), NEED[c].end(), v)) {
                    need.push_back(make_pair(m, v));
                } else {
                    temp.push_back(make_pair(m, v));
                }
            }
        }
        if (need.empty()) {
            ans[0]++;
        }
        int mx = 0;
        sort(temp.begin(), temp.end());
        sort(need.begin(), need.end());
        if (need.size() <= 2) {
            for (auto [m, v] : temp) {
                if (need.size() == 2) {
                    break;
                }
                vector<long long> cur(m + 1, 0);
                dfs_depth2(v, c, cur);
                if (mx != 0) {
                    vector<long long> have(mx + 1, 0);
                    for (int i = 0; i <= mx; i++) {
                        have[i] = freqs[i];
                    }
                    vector<long long> prod = multiply(cur, have);
                    for (int i = 0; i < prod.size(); i++) {
                        ans[i] += (need.size() == 0 ? prod[i] : 0);
                    }
                }
                mx = max(mx, m);
                for (int i = 0; i <= m; i++) {
                    ans[i] += (need.size() == 0 ? cur[i] : 0);
                    freqs[i] += cur[i];
                }

            }
            for (auto [m, v] : need) {
                vector<long long> cur(m + 1, 0);
                dfs_depth2(v, c, cur);
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
                    ans[i] += (need.size() == 1 ? cur[i] : 0);
                    freqs[i] += cur[i];
                }

            }

            for (int i = 0; i <= mx; i++) {
                freqs[i] = 0;
            }
        }
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}


void dfs_diam(int u, int p, int d) {
    for (int v : adj[u]) {
        if (v != p) {
            if (d + 1 > D) {
                D = d + 1;
                node = v;
            }
            dfs_diam(v, u, d + 1);
        }
    }
    return;
}


vector<int> st;
vector<int> diam;

void obtain_diam(int u, int p, int g) {
    st.push_back(u);
    if (u == g) {
        diam = st;
    }
    for (int v : adj[u]) {
        if (v != p) {
            obtain_diam(v, u, g);
        }
    }
    st.pop_back();
}


void dfs_subtree_dp(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_subtree_dp(v, u);
            if (subtree[v] + 1 > subtree[u]) {
                subtree[u] = subtree[v] + 1;
                child[u] = v;
            }
            if (subtree[v] >= D) {
                NEED[u].push_back(v);
            }
        }
    }
    for (int v : adj[u]) {
        if (v != p && v != child[u]) {
            aux[u] = max(aux[u], subtree[v] + 1);
        }
    }
}

void dfs_dp(int u, int p) {
    for (int v : adj[u]) {
        if (v != p && v != child[u]) {
            dp[v] = max(dp[u] + 1, subtree[u] + 1);
        } else if (v != p && v == child[u]) {
            dp[v] = max(dp[u] + 1, aux[u] + 1);
        }
        if (v != p && dp[v] > D) {
            NEED[v].push_back(u);
        }
        if (v != p) {
            dfs_dp(v, u);
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
    D = 0;
    dfs_diam(0, -1, 0);
    D = 0;
    int L = node;
    dfs_diam(node, -1, 0);
    int R = node;
    D = 0;

    obtain_diam(L, L, R);
    vector<int> DIST(n, INF);
    queue<int> q;
    for (int u : diam) {
        DIST[u] = 0;
        q.push(u);
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        D = max(D, DIST[u]);
        for (int v : adj[u]) {
            if (DIST[v] > DIST[u] + 1) {
                DIST[v] = DIST[u] + 1;
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        child[i] = -1;
    }
    dfs_subtree_dp(0, 0);
    dfs_dp(0, 0);


    for (int i = 0; i < n; i++) {
        sort(NEED[i].begin(), NEED[i].end());
    }


    build(0, -1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }


    return 0;
}
