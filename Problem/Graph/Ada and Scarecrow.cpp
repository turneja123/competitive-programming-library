#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 151;

struct Clique {
    vector<bitset<N>> e;
    int n, d[N], qmax;

    int get(bitset<N> b) {
        for (int i = 0; i < N; i++) {
            if (b[i]) {
                return i;
            }
        }
        return -1;
    }

    int greedy(bitset<N> cur) {
        int ans = 0;
        while (1) {
            for (int i = 0; i < n; i++) {
                d[i] = 0;
                if (cur[i]) {
                    d[i] = (e[i] & cur).count();
                }
            }
            int ok = 0;
            for (int i = 0; i < n; i++) {
                if (cur[i] && !d[i]) {
                    cur.reset(i);
                    ok = 1;
                }
            }
            if (ok) {
                continue;
            }
            for (int i = 0; i < n; i++) {
                if (cur[i] && d[i] == 1) {
                    bitset<N> t = e[i] & cur;
                    cur.reset(i);
                    cur &= ~t;
                    ans++;
                    ok = 1;
                    break;
                }
            }
            if (ok) {
                continue;
            }
            int v = -1, mx = 0;
            for (int i = 0; i < n; i++) {
                if (cur[i] && d[i] > mx) {
                    mx = d[i];
                    v = i;
                }
            }
            if (!mx) {
                return ans;
            }
            cur.reset(v);
            ans++;
        }
    }

    int calc(bitset<N> cur, int lim) {
        if (lim < 0) {
            return N;
        }
        int ans = 0;
        while (1) {
            if (ans > lim) {
                return N;
            }
            for (int i = 0; i < n; i++) {
                d[i] = 0;
                if (cur[i]) {
                    d[i] = (e[i] & cur).count();
                }
            }
            int ok = 0;
            for (int i = 0; i < n; i++) {
                if (cur[i] && !d[i]) {
                    cur.reset(i);
                    ok = 1;
                }
            }
            if (ok) {
                continue;
            }
            for (int i = 0; i < n; i++) {
                if (cur[i] && d[i] == 1) {
                    bitset<N> t = e[i] & cur;
                    cur.reset(i);
                    cur &= ~t;
                    ans++;
                    ok = 1;
                    break;
                }
            }
            if (ok) {
                continue;
            }
            for (int i = 0; i < n; i++) {
                if (cur[i] && d[i] == 2) {
                    bitset<N> t = e[i] & cur;
                    int a = get(t);
                    if (a == -1) {
                        continue;
                    }
                    t.reset(a);
                    int b = get(t);
                    if (b == -1) {
                        continue;
                    }
                    if (e[a][b]) {
                        cur.reset(i);
                        cur.reset(a);
                        cur.reset(b);
                        ans += 2;
                        ok = 1;
                        break;
                    }
                }
            }
            if (ok) {
                continue;
            }
            for (int i = 0; i < n; i++) {
                if (cur[i] && d[i] == 2) {
                    bitset<N> x = e[i] & cur;
                    int a = get(x);
                    if (a == -1) {
                        continue;
                    }
                    x.reset(a);
                    int b = get(x);
                    if (b == -1) {
                        continue;
                    }
                    if (!e[a][b]) {
                        bitset<N> old = e[i], t = (e[a] | e[b]) & cur, nxt = cur;
                        t.reset(i);
                        t.reset(a);
                        t.reset(b);
                        e[i] = t;
                        for (int j = 0; j < n; j++) {
                            e[j][i] = t[j];
                        }
                        nxt.reset(a);
                        nxt.reset(b);
                        int res = calc(nxt, lim - ans - 1);
                        e[i] = old;
                        for (int j = 0; j < n; j++) {
                            e[j][i] = old[j];
                        }
                        if (res > lim - ans - 1) {
                            return N;
                        }
                        return ans + 1 + res;
                    }
                }
            }
            break;
        }
        if (ans > lim) {
            return N;
        }
        if (!cur.any()) {
            return ans;
        }
        bitset<N> cc, q, rem = cur;
        int s = get(rem);
        if (s == -1) {
            return ans;
        }
        cc.set(s);
        q.set(s);
        rem.reset(s);
        while (1) {
            int u = get(q);
            if (u == -1) {
                break;
            }
            q.reset(u);
            bitset<N> t = e[u] & rem;
            cc |= t;
            q |= t;
            rem &= ~t;
        }
        if (rem.any()) {
            int x = calc(cc, lim - ans);
            if (x > lim - ans) {
                return N;
            }
            int y = calc(rem, lim - ans - x);
            if (y > lim - ans - x) {
                return N;
            }
            return ans + x + y;
        }
        int lb = 0;
        bitset<N> tmp = cur;
        for (int i = 0; i < n; i++) {
            if (!tmp[i]) {
                continue;
            }
            int j = get(e[i] & tmp);
            if (j != -1) {
                tmp.reset(i);
                tmp.reset(j);
                lb++;
            }
        }
        if (ans + lb > lim) {
            return N;
        }
        int v = -1, mx = 0;
        for (int i = 0; i < n; i++) {
            if (cur[i] && d[i] > mx) {
                mx = d[i];
                v = i;
            }
        }
        lim = min(lim, ans + greedy(cur));
        bitset<N> a = cur;
        a.reset(v);
        int res = N;
        int x = calc(a, lim - ans - 1);
        if (x <= lim - ans - 1) {
            res = ans + 1 + x;
            lim = min(lim, res - 1);
        }
        bitset<N> t = e[v] & cur, b = cur;
        b.reset(v);
        b &= ~t;
        int y = calc(b, lim - ans - (int)t.count());
        if (y <= lim - ans - (int)t.count()) {
            res = min(res, ans + (int)t.count() + y);
        }
        return res;
    }

    Clique(vector<bitset<N>> g) : e(g), n(e.size()) {
        bitset<N> cur;
        for (int i = 0; i < n; i++) {
            cur.set(i);
        }
        qmax = calc(cur, greedy(cur));
    }

};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<bitset<N>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].set(v);
            adj[v].set(u);
        }
        Clique c(adj);
        cout << c.qmax << endl;

    }
    return 0;
}
