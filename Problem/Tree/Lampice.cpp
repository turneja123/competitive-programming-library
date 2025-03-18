//https://dmoj.ca/problem/coci19c3p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e4 + 5;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* M + x.second; }
};

pair<long long, long long> single(char a) {
    return make_pair(a - 'a' + 1, a - 'a' + 1);
}

pair<long long, long long> mul(pair<long long, long long> a, pair<long long, long long> b) {
    return make_pair(a.first * b.first % M, a.second * b.second % M);
}

pair<long long, long long> sub(pair<long long, long long> a, pair<long long, long long> b) {
    return make_pair((a.first - b.first + M) % M, (a.second - b.second + M) % M);
}

pair<long long, long long> add(pair<long long, long long> a, pair<long long, long long> b) {
    return make_pair((a.first + b.first + M) % M, (a.second + b.second + M) % M);
}

string s;
int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];
vector<int> adj[N];
pair<long long, long long> rising[N], falling[N];

gp_hash_table<pair<long long, long long>, int, chash> mp;
int ans = 1;
bool found = false;
vector<int> stk;

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

void dfs1(int u, int p) {
    if (found) {
        return;
    }
    rising[u] = add(rising[p], mul(single(s[u]), make_pair(pw_p[depth[u]], pw_q[depth[u]])));
    falling[u] = add(mul(falling[p], make_pair(P, Q)), single(s[u]));
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs1(v, u);
        }
    }
    return;
}

void dfs2(int u, int p, int k) {
    if (found) {
        return;
    }
    stk.push_back(u);
    if (depth[u] + 1 == k) {
        if (rising[u] == falling[u]) {
            found = true;
        }
    } else if (depth[u] + 1 < k) {
        int anc = k - (depth[u] + 1);
        if (anc <= depth[u]) {
            anc = stk[depth[u] - anc];
            if (rising[anc] == falling[anc]) {
                pair<long long, long long> h = mul(sub(rising[u], rising[anc]), make_pair(inv_p[depth[anc] + 1], inv_q[depth[anc] + 1]));
                auto it = mp.find(h);
                if (it != mp.end() && it->second > 0) {
                    found = true;
                }
            }
        }
    }
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs2(v, u, k);
        }
    }
    stk.pop_back();
    return;
}

void dfs3(int u, int p, int c, int add) {
    if (found) {
        return;
    }
    mp[mul(sub(rising[u], rising[c]), make_pair(INV_P, INV_Q))] += add;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs3(v, u, c, add);
        }
    }
    return;
}


void build(int u, int p, int n, int k) {
    if (found) {
        return;
    }
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;
    stk.push_back(c);
    rising[c] = make_pair(s[c] - 'a' + 1, s[c] - 'a' + 1);
    falling[c] = rising[c];
    depth[c] = 0;
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs1(v, c);
            dfs3(v, c, c, 1);
        }
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            dfs3(v, c, c, -1);
            dfs2(v, c, k);
            dfs3(v, c, c, 1);
        }
    }
    mp.clear();
    stk.pop_back();
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c, n, k);
        }
    }
    return;
}


int main() {
    IOS;
    int n;
    cin >> n >> s;
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < n; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    int l = 0, r = n / 2;
    while (l <= r) {
        found = false;
        int mid = (l + r) / 2;
        build(0, -1, n, 2 * mid + 1);
        for (int i = 0; i < n; i++) {
            seen_c[i] = false;
        }
        stk.clear();
        if (found) {
            ans = max(ans, 2 * mid + 1);
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    l = 1, r = n / 2;
    while (l <= r) {
        found = false;
        int mid = (l + r) / 2;
        build(0, -1, n, 2 * mid);
        for (int i = 0; i < n; i++) {
            seen_c[i] = false;
        }
        stk.clear();
        if (found) {
            ans = max(ans, 2 * mid);
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans;

    return 0;
}
