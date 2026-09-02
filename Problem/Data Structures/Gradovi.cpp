//https://arena.petlja.org/sr-Latn-RS/competition/2025-2026-sio-1-testiranje#tab_143608
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 200000 + 5;
const int SQ = 4000;
const int B = 64;

unsigned char city[N], keep_edge[N], used[N];

struct DSU {
    int par[N], sz[N], vill[N];
    unsigned char has[N];

    int bad, h;

    int ha[N], hb[N], hsza[N], hvilla[N], hbad[N];
    unsigned char hhasa[N];

    inline int root(int x) {
        while (par[x] != x) {
            x = par[x];
        }
        return x;
    }

    inline int root_comp(int x) {
        int r = x;
        while (par[r] != r) {
            r = par[r];
        }
        while (par[x] != x) {
            int p = par[x];
            par[x] = r;
            x = p;
        }
        return r;
    }

    inline void init(int n) {
        h = 0;
        bad = 0;
        for (int i = 1; i <= n; i++) {
            par[i] = i;
            sz[i] = 1;
            has[i] = city[i];
            vill[i] = city[i] ^ 1;
            bad += vill[i];
        }
    }

    inline void copy_from(DSU &d, int n) {
        h = 0;
        bad = d.bad;
        memcpy(par + 1, d.par + 1, n * sizeof(int));
        memcpy(sz + 1, d.sz + 1, n * sizeof(int));
        memcpy(vill + 1, d.vill + 1, n * sizeof(int));
        memcpy(has + 1, d.has + 1, n * sizeof(unsigned char));
    }

    inline void merge_vals(int a, int b) {
        bad -= (!has[a] && vill[a]);
        bad -= (!has[b] && vill[b]);

        par[b] = a;
        sz[a] += sz[b];
        has[a] |= has[b];
        vill[a] += vill[b];

        bad += (!has[a] && vill[a]);
    }

    inline void unite_base(int a, int b) {
        a = root_comp(a), b = root_comp(b);
        if (a == b) {
            return;
        }
        if (sz[a] < sz[b]) {
            swap(a, b);
        }
        merge_vals(a, b);
    }

    inline void unite(int a, int b) {
        a = root(a), b = root(b);
        if (a == b) {
            return;
        }
        if (sz[a] < sz[b]) {
            swap(a, b);
        }

        ha[h] = a;
        hb[h] = b;
        hsza[h] = sz[a];
        hhasa[h] = has[a];
        hvilla[h] = vill[a];
        hbad[h] = bad;
        h++;

        merge_vals(a, b);
    }

    inline void rollback(int snap = 0) {
        while (h > snap) {
            --h;
            int a = ha[h], b = hb[h];
            par[b] = b;
            sz[a] = hsza[h];
            has[a] = hhasa[h];
            vill[a] = hvilla[h];
            bad = hbad[h];
        }
    }
} pref, suff, work;

int snap[N], suf[N], forcebuf[N];

int head[N], to[2 * N], nxt[2 * N], eid[2 * N], ecnt;
int mark[N], que[N], timer_;

inline void add_edge_final(int id, int u, int v) {
    to[++ecnt] = v;
    eid[ecnt] = id;
    nxt[ecnt] = head[u];
    head[u] = ecnt;

    to[++ecnt] = u;
    eid[ecnt] = id;
    nxt[ecnt] = head[v];
    head[v] = ecnt;
}

inline int get_side_max(int st, int ban) {
    int mx = 0, l = 0, r = 0;

    ++timer_;
    que[r++] = st;
    mark[st] = timer_;

    while (l < r) {
        int u = que[l++];
        for (int e = head[u]; e; e = nxt[e]) {
            if (eid[e] == ban) {
                continue;
            }
            int v = to[e];
            if (mark[v] == timer_) {
                continue;
            }
            mark[v] = timer_;
            que[r++] = v;
            if (eid[e] > mx) {
                mx = eid[e];
            }
        }
    }

    return mx;
}

void Gradovi(int n, int m, int k, int q, int* U, int* V, int* G, int* S) {
    memset(city + 1, 0, n);
    memset(keep_edge + 1, 0, m);

    for (int i = 1; i <= k; i++) {
        city[G[i]] = 1;
    }

    work.init(n);

    if (work.bad <= q) {
        int ct = 0;
        for (int i = 1; i <= n && ct < q; i++) {
            if (!city[i]) {
                S[++ct] = i;
            }
        }
        return;
    }

    int lim = 0;
    for (int i = 1; i <= m; i++) {
        work.unite_base(U[i], V[i]);
        if (work.bad <= q) {
            lim = i;
            break;
        }
    }

    keep_edge[lim] = 1;

    int firstR = lim - 1;
    int firstL = max(1, firstR - SQ + 1);

    pref.init(n);
    snap[0] = 0;

    for (int e = 1; e < firstL; e++) {
        pref.unite(U[e], V[e]);
        snap[e] = pref.h;
    }

    suff.init(n);
    suff.unite_base(U[lim], V[lim]);

    int sufct = 1;
    suf[1] = lim;

    for (int R = firstR; R >= 1; R -= SQ) {
        int L = max(1, R - SQ + 1);

        if (L - 1 <= sufct) {
            work.copy_from(suff, n);
            for (int e = 1; e < L; e++) {
                work.unite_base(U[e], V[e]);
            }
        } else {
            work.copy_from(pref, n);
            for (int i = 1; i <= sufct; i++) {
                int e = suf[i];
                work.unite_base(U[e], V[e]);
            }
        }

        for (int rr = R; rr >= L; rr -= B) {
            int lft = max(L, rr - B + 1);
            int snap_base = work.h;

            for (int e = L; e < lft; e++) {
                work.unite(U[e], V[e]);
            }

            int fct = 0;

            for (int j = rr; j >= lft; j--) {
                int snap_j = work.h;

                for (int e = lft; e < j; e++) {
                    work.unite(U[e], V[e]);
                    if (work.bad <= q) {
                        break;
                    }
                }

                if (work.bad > q) {
                    keep_edge[j] = 1;
                    forcebuf[++fct] = j;
                }

                work.rollback(snap_j);

                if (keep_edge[j]) {
                    work.unite(U[j], V[j]);
                }
            }

            work.rollback(snap_base);

            for (int i = 1; i <= fct; i++) {
                int e = forcebuf[i];
                work.unite_base(U[e], V[e]);
            }
        }

        for (int e = L; e <= R; e++) {
            if (keep_edge[e]) {
                suff.unite_base(U[e], V[e]);
                suf[++sufct] = e;
            }
        }

        int nextR = L - 1;
        if (nextR >= 1) {
            int nextL = max(1, nextR - SQ + 1);
            pref.rollback(snap[nextL - 1]);
        }
    }

    work.copy_from(suff, n);

    memset(head + 1, 0, n * sizeof(int));
    ecnt = 0;

    for (int e = 1; e <= lim; e++) {
        if (keep_edge[e]) {
            add_edge_final(e, U[e], V[e]);
        }
    }

    memset(used + 1, 0, n);
    memset(mark + 1, 0, n * sizeof(int));
    timer_ = 0;

    int ct = 0;

    for (int i = 1; i <= n; i++) {
        if (work.root(i) != i || work.has[i] || work.vill[i] == 0) {
            continue;
        }

        int mx = 0, a = i, b = i;
        int l = 0, r = 0;

        ++timer_;
        que[r++] = i;
        mark[i] = timer_;

        while (l < r) {
            int u = que[l++];

            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                if (mark[v] == timer_) {
                    continue;
                }

                mark[v] = timer_;
                que[r++] = v;

                if (eid[e] > mx) {
                    mx = eid[e];
                    a = u;
                    b = v;
                }
            }
        }

        int choose = i;

        if (mx != 0) {
            int ma = get_side_max(a, mx);
            int mb = get_side_max(b, mx);
            choose = (ma >= mb ? a : b);
        }

        S[++ct] = choose;
        used[choose] = 1;
    }

    for (int i = 1; i <= n && ct < q; i++) {
        if (!city[i] && !used[i]) {
            S[++ct] = i;
            used[i] = 1;
        }
    }
}
