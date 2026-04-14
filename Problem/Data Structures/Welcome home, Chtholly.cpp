//https://codeforces.com/contest/896/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int SQ = 600;

struct Block {
    int f[N];
    int parent[N];
    int sz[N];
    int val[N];
    int restore[N];
    bool vis[N];
    int mx;
    int lazy;
    int ptr;
    vector<int> v;

    void init() {
        for (int i = 0; i < N; i++) {
            f[i] = 0;
            parent[i] = i;
            val[i] = i;
            sz[i] = 0;
            vis[i] = 0;
        }
        mx = 0;
        lazy = 0;
        ptr = 0;
        for (int i : v) {
            mx = max(mx, i);
            f[i]++;
            sz[i]++;
            if (!vis[i]) {
                vis[i] = 1;
                restore[ptr++] = i;
            }
        }
    }

    void build() {
        for (int j = 0; j < ptr; j++) {
            int i = restore[j];
            f[i] = 0;
            parent[i] = i;
            val[i] = i;
            sz[i] = 0;
            vis[i] = 0;
        }
        mx = 0;
        lazy = 0;
        ptr = 0;
        for (int i : v) {
            mx = max(mx, i);
            f[i]++;
            sz[i]++;
            if (!vis[i]) {
                vis[i] = 1;
                restore[ptr++] = i;
            }
        }
    }

    int dsu_find(int a) {
        if (parent[a] == a) {
            return a;
        }
        return parent[a] = dsu_find(parent[a]);
    }

    int dsu_unite(int a, int b) {
        a = dsu_find(a), b = dsu_find(b);
        if (a == b) {
            return a;
        }
        if (sz[a] > sz[b]) {
            swap(a, b);
        }
        f[val[a]] -= sz[a];
        f[val[b]] -= sz[b];

        sz[b] += sz[a];
        parent[a] = b;
        return b;
    }

    void upd(int x) {
        if (mx <= x) {
            return;
        }
        if (2 * x >= mx) {
            for (int i = x + 1 + lazy; i <= mx + lazy && i < N; i++) {
                if (!vis[i]) {
                    vis[i] = 1;
                    restore[ptr++] = i;
                }
                if (!vis[i - x]) {
                    vis[i - x] = 1;
                    restore[ptr++] = i - x;
                }

                int a = dsu_unite(i, i - x);
                val[a] = i - x;
                f[val[a]] += sz[a];
            }
            mx = max(x, mx - x);
        } else {
            for (int i = 1 + lazy; i <= x + lazy && i + x < N; i++) {
                if (!vis[i]) {
                    vis[i] = 1;
                    restore[ptr++] = i;
                }
                if (!vis[i + x]) {
                    vis[i + x] = 1;
                    restore[ptr++] = i + x;
                }

                int a = dsu_unite(i, i + x);
                val[a] = i + x;
                f[val[a]] += sz[a];
            }
            lazy += x;
            mx -= x;
        }

    }

};

int a[N];
Block b[N / SQ + 3];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i / SQ].v.push_back(a[i]);
    }
    for (int i = 0; i * SQ < n; i++) {
        b[i].init();
    }
    for (int i = 0; i < q; i++) {
        int t, l, r, x;
        cin >> t >> l >> r >> x;
        l--, r--;

        int bl = l / SQ;
        if (l % SQ != 0) {
            bl++;
        }
        int br = r / SQ;
        if ((r + 1) % SQ != 0) {
            br--;
        }

        auto f_upd = [&](int l, int r, int j) -> void {
            for (int i = j * SQ, ptr = 0; i < min(n, (j + 1) * SQ); i++, ptr++) {
                a[i] = b[j].val[b[j].dsu_find(a[i])] - b[j].lazy;
                if (i >= l && i <= r && a[i] > x) {
                    a[i] -= x;
                }
                b[j].v[ptr] = a[i];
            }
            b[j].build();
        };

        auto f_query = [&](int l, int r, int j, int z) -> int {
            int ans = 0;
            for (int i = l; i <= r; i++) {
                ans += (b[j].val[b[j].dsu_find(a[i])] - b[j].lazy == z);

            }
            return ans;
        };

        if (t == 1) {
            if (l / SQ == r / SQ) {
                f_upd(l, r, l / SQ);
                continue;
            }
            if (l < bl * SQ) {
                f_upd(l, bl * SQ - 1, l / SQ);
            }
            if (r >= (br + 1) * SQ) {
                f_upd((br + 1) * SQ, r, r / SQ);
            }
            for (int i = bl; i <= br; i++) {
                b[i].upd(x);
            }
        } else {
            int ans = 0;
            if (l / SQ == r / SQ) {
                ans += f_query(l, r, l / SQ, x);
                cout << ans << endl;
                continue;
            }
            if (l < bl * SQ) {
                ans += f_query(l, bl * SQ - 1, l / SQ, x);
            }
            if (r >= (br + 1) * SQ) {
                ans += f_query((br + 1) * SQ, r, r / SQ, x);
            }
            for (int i = bl; i <= br; i++) {
                if (x + b[i].lazy < N) {
                    ans += b[i].f[x + b[i].lazy];
                }
            }
            cout << ans << endl;

        }

    }


    return 0;
}
