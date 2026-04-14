//https://atcoder.jp/contests/arc069/tasks/arc069_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e4 + 5;
const ll INF = 1e18;

int idx = 0;
int L[5 * N];
int R[5 * N];

int who[N];
int pos[N];
int where[N];
vector<int> adj[5 * N];
vector<int> rev[5 * N];

void upd(int l, int r, int lq, int rq, int node, int v) {
    if (l > rq || r < lq) {
        return;
    }

    if (lq <= l && rq >= r) {
        adj[v].push_back(node);
        rev[node].push_back(v);
        return;
    }

    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, L[node], v);
    upd(mid + 1, r, lq, rq, R[node], v);
}

void build(int l, int r, int node) {
    if (l == r) {
        adj[node].push_back(l);
        rev[l].push_back(node);
        return;
    }

    int mid = (l + r) / 2;
    L[node] = idx;
    build(l, mid, idx++);
    R[node] = idx;
    build(mid + 1, r, idx++);
    adj[node].push_back(L[node]);
    adj[node].push_back(R[node]);
    rev[L[node]].push_back(node);
    rev[R[node]].push_back(node);
}

int vis[5 * N];
int parent[5 * N];
stack<int> s;

void fillStack(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            fillStack(v);
        }
    }
    s.push(u);
}

void dfs(int u, int j) {
    vis[u] = true;
    parent[u] = j;
    for (int v : rev[u]) {
        if (!vis[v]) {
            dfs(v, j);
        }
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<tuple<int, int, int>> a;
    vector<int> lens;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back({x, 0, i});
        a.push_back({y, 1, i});
        lens.push_back(x);
        lens.push_back(y);
    }
    sort(a.begin(), a.end());
    sort(lens.begin(), lens.end());
    for (int i = 0; i < 2 * n; i++) {
        auto [d, j, ind] = a[i];
        where[ind + j * n] = d;

        who[i] = ind + !j * n;
        pos[ind + !j * n] = i;
    }
    int l = 0, r = 1e9, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        idx = 2 * n;
        int root = idx++;
        build(0, 2 * n - 1, root);

        for (int i = 0; i < 2 * n; i++) {
            int x = where[i];

            int sl = pos[i], sr = pos[(i + n) % (2 * n)];
            if (sl > sr) {
                swap(sl, sr);
            }

            int l = lower_bound(lens.begin(), lens.end(), x - mid) - lens.begin();
            int r = upper_bound(lens.begin(), lens.end(), x + mid) - lens.begin() - 1;
            if (l > r) {
                continue;
            }
            if (l <= sl) {
                upd(0, 2 * n - 1, l, min(r, sl - 1), root, pos[i]);
                l = sl + 1;
            }
            if (l > r) {
                continue;
            }
            if (l <= sr) {
                upd(0, 2 * n - 1, l, min(r, sr - 1), root, pos[i]);
                l = sr + 1;
            }
            if (l > r) {
                continue;
            }
            upd(0, 2 * n - 1, l, r, root, pos[i]);
        }

        for (int i = 0; i < idx; i++) {
            if (!vis[i]) {
                fillStack(i);
            }
        }
        for (int i = 0; i < idx; i++) {
            vis[i] = 0;
        }
        int j = 0;
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            if (vis[v] == false) {
                dfs(v, j++);
            }
        }
        int ok = 1;
        for (int i = 0; i < n; i++) {
            if (parent[pos[i]] == parent[pos[i + n]]) {
                ok = 0;
            }
        }
        for (int i = 0; i < idx; i++) {
            adj[i].clear();
            rev[i].clear();
            vis[i] = 0;
        }
        if (ok) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans + 1 ;

    return 0;
}
