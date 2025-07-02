//https://ocpc2025s.eolymp.space/en/compete/sk55ojcma10djasruv04qdm2fo/problem/1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6e5 + 5;

int a[N];
vector<pair<int, int>> pos[N];
pair<int, int> p[N];
bool seen[N];
int ans[N];

set<pair<int, int>> segtree[4 * N];

queue<int> q;

void query(int l, int r, int lq, int rq, int ly, int ry, int d, int node) {
    if (lq <= l && rq >= r) {
        auto it = segtree[node].lower_bound({ly, -1});
        while (it != segtree[node].end() && it->first <= ry) {
            int i = it->second;
            if (!seen[i]) {
                seen[i] = true;
                ans[i] = d + 1;
                q.push(i);
            }
            it = segtree[node].erase(it);
        }
        return;
    }

    if (l > rq || r < lq) {
        return;
    }

    int mid = (l + r) / 2;
    query(l, mid, lq, rq, ly, ry, d, 2 * node + 1);
    query(mid + 1, r, lq, rq, ly, ry, d, 2 * node + 2);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        for (int i = 0; i < pos[l].size(); i++) {
            segtree[node].insert(pos[l][i]);
        }
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    for (auto it : segtree[2 * node + 1]) {
        segtree[node].insert(it);
    }
    for (auto it : segtree[2 * node + 2]) {
        segtree[node].insert(it);
    }
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int e = 0;
        int stx, sty, enx, eny;
        cin >> stx >> sty >> enx >> eny;
        stx--, sty--, enx--, eny--;
        int stpos, enpos;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[e];
                int x = i + j, y = i - j;
                pos[x].push_back({y, e});
                p[e] = {x, y};
                if (i == stx && j == sty) {
                    stpos = e;
                }
                if (i == enx && j == eny) {
                    enpos = e;
                }
                e++;
            }
        }
        build(0, n + m - 1, 0);
        seen[stpos] = 1;
        ans[stpos] = 0;
        q.push(stpos);
        int dist = -1;
        while (q.size()) {
            int u = q.front();
            q.pop();
            if (u == enpos) {
                dist = ans[u];
                break;
            }
            auto [x, y] = p[u];
            int lx = max(0, x - a[u]);
            int rx = min(n + m - 1, x + a[u]);
            query(0, n + m - 1, lx, rx, y - a[u], y + a[u], ans[u], 0);

        }
        cout << dist << endl;
        while (q.size()) {
            q.pop();
        }
        for (int i = 0; i < 4 * (n * m + 1); i++) {
            segtree[i].clear();
        }
        for (int i = 0; i < 2 * (n * m + 1); i++) {
            pos[i].clear();
            seen[i] = 0;
            ans[i] = 0;
        }
    }

    return 0;
}
