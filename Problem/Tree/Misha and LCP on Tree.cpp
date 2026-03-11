//https://codeforces.com/contest/504/problem/E
#pragma GCC optimize("Ofast,unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

const int N = 3e5 + 5;
const int K = 19;
const int INF = 1e9;

int timer = 0;
int tin[N];
int tout[N];
int pos[N];
int id[N];
int up[K][N];
vector<int> adj[N];
int sz[N];
int depth[N];
int tail[N];
bool head[N];
int edges[N];


using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

static const u32 MOD = 1e9 + 7;


static inline u32 fastmod_u64(u64 x) {
    static const u64 inv = (u64)((u128(1) << 64) / MOD);
    u64 q = (u64)((u128)x * inv >> 64);
    u64 r = x - q * (u64)MOD;
    if (r >= MOD) r -= MOD;
    if (r >= MOD) r -= MOD;
    return (u32)r;
}

static inline u32 mul_small(u32 a, u32 b) {
    return fastmod_u64((u64)a * b);
}

void dfs(int u, int p) {
    tin[u] = ++timer;
    up[0][u] = p;
    sz[u] = 1;
    for (int i = 1; i < K; i++) {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    tout[u] = ++timer;
    return;
}

void dfs_markedges(int u, int p) {
    int heavy = -1;
    for (int v : adj[u]) {
        if (v != p) {
            if (sz[v] >= sz[u] / 2 + sz[u] % 2) {
                edges[v] = 1;
                head[u] = false;
                heavy = v;
            } else {
                edges[v] = 0;
            }
        }
    }
    if (heavy != -1) {
        dfs_markedges(heavy, u);
    }
    for (int v : adj[u]) {
        if (v != p && v != heavy) {
            dfs_markedges(v, u);
        }
    }

}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int kth(int u, int k) {
    for (int i = K - 1; i >= 0; --i) {
        int c = k & (1 << i);
        if (c) {
            u = up[i][u];
        }
    }
    return u;
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int i = K - 1; i >= 0; --i) {
        if (!is_ancestor(up[i][u], v)) {
            u = up[i][u];
        }
    }
    return up[0][u];
}

struct Path {
    vector<pair<ll, ll>> hash_up;
    vector<pair<ll, ll>> hash_down;
    int m;

};

const ll M = 1e9 + 7;
const ll P = 26, INV_P = 576923081;
const ll Q = 53, INV_Q = 56603774;

int n[N];
string s[N];

ll pw_p[N], pw_q[N];
ll inv_p[N], inv_q[N];



Path paths[N];
string S;

pair<ll, ll> get_pref(int l, int r, vector<pair<ll, ll>> &pref) {
    int n = pref.size();
    pair<ll, ll> ans = pref[r];
    if (l != 0) {
        ans.first = mul_small((ans.first - pref[l - 1].first + M), inv_p[l]);
        ans.second = mul_small((ans.second - pref[l - 1].second + M), inv_q[l]);
    }
    return ans;
}

pair<ll, ll> get_suf(int l, int r, vector<pair<ll, ll>> &suf) {
    int n = suf.size();
    pair<ll, ll> ans = suf[l];
    if (r != n - 1) {
        ans.first = mul_small((ans.first - suf[r + 1].first + M), inv_p[n - 1 - r]);
        ans.second = mul_small((ans.second - suf[r + 1].second + M), inv_q[n - 1 - r]);
    }
    return ans;
}



pair<ll, ll> calc_path(int u, int v, int l, int k) {

    pair<ll, ll> ans = {0, 0};

    int p = 0, ok = 0;
    if (u != l) {
        ok = 1;
        int anc = l;
        if (depth[u] - depth[l] > k - 1) {
            anc = kth(u, k - 1);
        }
        int node = u;
        while (1) {
            int j = id[node];
            int L = pos[node], R = (id[node] != id[anc] ? paths[j].m - 1 : pos[anc]);
            pair<ll, ll> cur = get_pref(L, R, paths[j].hash_up);
            ans.first = ans.first + mul_small(cur.first, pw_p[p]);
            ans.second = ans.second + mul_small(cur.second, pw_q[p]);
            if (ans.first >= M) {
                ans.first -= M;
            }
            if (ans.second >= M) {
                ans.second -= M;
            }
            int sz = R - L + 1;
            p += sz;
            k -= sz;
            if (id[node] == id[anc]) {
                break;
            }
            node = up[0][tail[node]];
        }
    }
    if (k == 0) {
        return ans;
    }
    int anc = l;
    if (ok) {
        int d = depth[v] - depth[l];
        anc = kth(v, d - 1);
    }
    int node = v;
    if (depth[v] - depth[anc] > k - 1) {
        node = kth(v, depth[v] - depth[anc] - (k - 1));
    }

    int p_now = p;
    p = 0;
    pair<ll, ll> ans_down = {0, 0};

    while (1) {
        int j = id[node];
        int L = pos[node], R = (id[node] != id[anc] ? paths[j].m - 1 : pos[anc]);
        int sz = R - L + 1;

        pair<ll, ll> cur = get_suf(L, R, paths[j].hash_down);
        ans_down.first = mul_small(ans_down.first, pw_p[sz]) + cur.first;
        ans_down.second = mul_small(ans_down.second, pw_q[sz]) + cur.second;
        if (ans_down.first >= M) {
            ans_down.first -= M;
        }
        if (ans_down.second >= M) {
            ans_down.second -= M;
        }

        p += sz;
        k -= sz;
        if (id[node] == id[anc]) {
            break;
        }
        node = up[0][tail[node]];
    }
    ans.first = (ans.first + ans_down.first * pw_p[p_now]) % M;
    ans.second = (ans.second + ans_down.second * pw_q[p_now]) % M;

    return ans;
}

int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }

    int n, q;
    cin >> n;
    cin >> S;
    for (int i = 0; i < n; i++) {
        head[i] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    dfs_markedges(0, 0);
    for (int i = 0, j = 0; i < n; i++) {
        if (head[i]) {
            vector<int> path;
            int v = i;
            while (1) {
                path.push_back(v);
                if (edges[v] == 0) {
                    break;
                }
                v = up[0][v];
            }
            int m = path.size();
            paths[j].hash_up.resize(m);
            paths[j].hash_down.resize(m);
            paths[j].m = m;

            for (int i = 0; i < m; i++) {
                int u = path[i];
                tail[u] = path.back();
                id[u] = j;
                pos[u] = i;
                paths[j].hash_up[i].first = ((i == 0 ? 0 : paths[j].hash_up[i - 1].first) + (S[u] - 'a' + 1) * pw_p[i]) % M;
                paths[j].hash_up[i].second = ((i == 0 ? 0 : paths[j].hash_up[i - 1].second) + (S[u] - 'a' + 1) * pw_q[i]) % M;
            }
            for (int i = m - 1; i >= 0; i--) {
                int u = path[i];
                paths[j].hash_down[i].first = ((i == m - 1 ? 0 : paths[j].hash_down[i + 1].first) + (S[u] - 'a' + 1) * pw_p[m - 1 - i]) % M;
                paths[j].hash_down[i].second = ((i == m - 1 ? 0 : paths[j].hash_down[i + 1].second) + (S[u] - 'a' + 1) * pw_q[m - 1 - i]) % M;
            }

            j++;

        }
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int u1, v1, u2, v2;
        cin >> u1 >> v1 >> u2 >> v2;
        u1--, v1--, u2--, v2--;

        if (S[u1] != S[u2]) {
            cout << 0 << endl;
            continue;
        }

        int lc1 = lca(u1, v1), lc2 = lca(u2, v2);


        int k1 = depth[u1] + depth[v1] - 2 * depth[lc1];
        int k2 = depth[u2] + depth[v2] - 2 * depth[lc2];

        int l = 2, r = min(k1, k2) + 1, ans = 1;
        while (l <= r) {
            int mid = (l + r) / 2;

            pair<ll, ll> h1 = calc_path(u1, v1, lc1, mid);
            pair<ll, ll> h2 = calc_path(u2, v2, lc2, mid);
            if (h1 == h2) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
