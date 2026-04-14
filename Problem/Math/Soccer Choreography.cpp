//https://www.spoj.com/problems/WM06/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2205;
const int S = 2 * N + 5;
const int HURDLE = 1;
const int GREATHURDLE = 2;
const int SUPERHURDLE = 4;
const int INF = 1e9;

struct Comp {
    int index;
    int oriented;
    int blocks;
    int hurdle;
    int left;
    int right;
};

int permv[S];
int donev[S];
int grey[S];
int stk[S];
int orientedv[S];
int ccv[S];
int labeled[S];
Comp compv[S];

int num_breakpoints(int sz) {
    int b = 0;
    if (permv[1] != 1) {
        b++;
    }
    for (int i = 2; i < sz - 1; i += 2) {
        int a = permv[i];
        int a1 = (a == sz ? 1 : a + 1);
        int b0 = permv[i + 1];
        int b1 = (b0 == sz ? 1 : b0 + 1);
        if (b0 != a1 && a != b1) {
            b++;
        }
    }
    return b;
}

int num_cycles(int sz) {
    int *inv = donev;
    int c = 0;

    for (int i = 0; i < sz; i++) {
        inv[permv[i]] = i;
        grey[i] = -1;
    }

    int j1 = inv[1];
    if (j1 != 1) {
        grey[0] = j1;
    }

    for (int i = 1; i < sz - 1; i += 2) {
        int ind = permv[i];
        int j2;
        if (ind < permv[i + 1]) {
            j1 = inv[ind - 1];
            j2 = inv[ind + 2];
        } else {
            j1 = inv[ind + 1];
            j2 = inv[ind - 2];
        }
        if (j1 != i - 1) {
            grey[i] = j1;
        }
        if (j2 != i + 2) {
            grey[i + 1] = j2;
        }
    }

    j1 = inv[sz - 2];
    if (j1 != sz - 2) {
        grey[sz - 1] = j1;
    }

    for (int i = 0; i < sz; i++) {
        donev[i] = 0;
    }

    for (int i = 0; i < sz; i++) {
        if (donev[i] == 0 && grey[i] != -1) {
            labeled[i] = i;
            donev[i] = 1;
            int nx = i;
            do {
                if (nx % 2 == 0) {
                    nx++;
                } else {
                    nx--;
                }
                donev[nx] = 1;
                labeled[nx] = i;
                nx = grey[nx];
                donev[nx] = 1;
                labeled[nx] = i;
            } while (nx != i);
            c++;
        }
    }

    return c;
}

void connected_component(int sz, int &num_components) {
    int *next = stk;
    int *stack_root = stk;
    int *range = orientedv;
    int *stack_range = ccv;
    int *cc = ccv;
    int *parent = labeled;

    int stack_ptr = -1;
    num_components = 0;

    for (int i = 0; i < sz; i++) {
        if (grey[i] == -1) {
            continue;
        }
        range[labeled[i]] = i;
    }

    for (int i = 0; i < sz; i++) {
        if (grey[i] == -1) {
            continue;
        }
        if (parent[i] == i) {
            stack_ptr++;
            stack_root[stack_ptr] = i;
            stack_range[stack_ptr] = range[i];
        } else {
            int right = i;
            while (stack_root[stack_ptr] > parent[i]) {
                parent[stack_root[stack_ptr]] = parent[i];
                if (right < stack_range[stack_ptr]) {
                    right = stack_range[stack_ptr];
                }
                stack_ptr--;
            }
            if (stack_range[stack_ptr] < right) {
                stack_range[stack_ptr] = right;
            }
            if (stack_range[stack_ptr] <= i) {
                compv[num_components].index = stack_root[stack_ptr];
                num_components++;
                stack_ptr--;
            }
        }
    }

    for (int i = 0; i < sz; i++) {
        next[i] = -1;
    }
    for (int i = 0; i < sz; i++) {
        if (grey[i] == -1) {
            cc[i] = -1;
        } else if (i != parent[i]) {
            next[i] = next[parent[i]];
            next[parent[i]] = i;
        }
    }
    for (int i = 0; i < num_components; i++) {
        int p = compv[i].index;
        while (p != -1) {
            cc[p] = i;
            p = next[p];
        }
    }
}

void num_hurdles_and_fortress(int sz, int &num_hurdles, int &num_fortress) {
    num_hurdles = 0;
    num_fortress = 0;

    int num_components;
    connected_component(sz, num_components);
    if (num_components == 0) {
        return;
    }

    for (int i = 0; i < sz; i++) {
        int j = grey[i];
        if (j == -1) {
            orientedv[i] = 0;
        } else if (i < j) {
            if ((j - i) % 2 != 0) {
                orientedv[i] = 0;
                orientedv[j] = 0;
            } else {
                orientedv[i] = 1;
                orientedv[j] = 1;
            }
        }
    }

    for (int i = 0; i < num_components; i++) {
        compv[i].oriented = 0;
    }
    for (int i = 0; i < sz; i++) {
        if (orientedv[i]) {
            compv[ccv[i]].oriented = 1;
        }
    }

    int num_oriented = 0;
    for (int i = 0; i < num_components; i++) {
        if (!compv[i].oriented) {
            num_oriented++;
        }
    }
    if (num_oriented == 0) {
        return;
    }

    for (int i = 0; i < num_components; i++) {
        compv[i].blocks = 0;
        compv[i].hurdle = 0;
        compv[i].left = -1;
        compv[i].right = -1;
    }

    int first_comp = -1;
    int last_comp = -1;
    int num_block = -1;

    for (int i = 0; i < sz; i++) {
        int c = ccv[i];
        if (c != -1 && !compv[c].oriented) {
            if (c != last_comp) {
                if (last_comp == -1) {
                    first_comp = c;
                } else {
                    compv[last_comp].right = c;
                    compv[c].left = last_comp;
                }
                last_comp = c;
                num_block++;
                compv[c].blocks++;
            }
        }
    }

    for (int i = 0; i < num_components; i++) {
        if (!compv[i].oriented && compv[i].blocks == 1) {
            compv[i].hurdle = HURDLE;
            num_hurdles++;
        }
    }

    if (first_comp == last_comp && first_comp != -1 && compv[first_comp].blocks == 2) {
        compv[first_comp].hurdle = HURDLE | GREATHURDLE;
        num_hurdles++;
    }

    if (num_hurdles < 3) {
        return;
    }

    int num_super = 0;
    for (int i = 0; i < num_components; i++) {
        if (compv[i].hurdle) {
            if (compv[i].left == compv[i].right && compv[i].left != -1) {
                int l = compv[i].left;
                if (compv[l].blocks == 2 && ((compv[l].hurdle & GREATHURDLE) == 0)) {
                    compv[i].hurdle |= SUPERHURDLE;
                    num_super++;
                } else {
                    return;
                }
            } else {
                return;
            }
        }
    }

    if (num_hurdles == num_super && (num_super % 2 == 1)) {
        num_fortress = 1;
    }
}

int calc_dist(const vector<int> &a) {
    int n = a.size();
    int sz = 2 * n + 2;

    permv[0] = 0;
    int p = 1;
    for (int x : a) {
        int y = abs(x);
        if (x > 0) {
            permv[p] = 2 * y - 1;
            permv[p + 1] = 2 * y;
        } else {
            permv[p] = 2 * y;
            permv[p + 1] = 2 * y - 1;
        }
        p += 2;
    }
    permv[sz - 1] = 2 * n + 1;

    int b = num_breakpoints(sz);
    int c = num_cycles(sz);
    int h, f;
    num_hurdles_and_fortress(sz, h, f);
    return b - c + h + f;
}

void do_rev(vector<int> &a, int l, int r) {
    reverse(a.begin() + l, a.begin() + r + 1);
    for (int i = l; i <= r; i++) {
        a[i] = -a[i];
    }
}

struct Cand {
    int score;
    int len;
    int l;
    int r;
};

vector<Cand> oriented_candidates(const vector<int> &a) {
    int n = a.size();
    int m = n + 1;
    int W = (m + 63) >> 6;

    vector<int> pos(n + 1), sgn(n + 1);
    for (int i = 0; i < n; i++) {
        pos[abs(a[i])] = i + 1;
        sgn[abs(a[i])] = (a[i] > 0 ? 1 : -1);
    }

    vector<int> L(m), R(m);
    for (int x = 0; x <= n; x++) {
        int u, v;
        if (x == 0) {
            u = 0;
        } else {
            u = (sgn[x] > 0 ? 2 * pos[x] : 2 * pos[x] - 1);
        }
        if (x == n) {
            v = 2 * n + 1;
        } else {
            int y = x + 1;
            v = (sgn[y] > 0 ? 2 * pos[y] - 1 : 2 * pos[y]);
        }
        if (u > v) {
            swap(u, v);
        }
        L[x] = u;
        R[x] = v;
    }

    vector<vector<unsigned long long>> adj(m, vector<unsigned long long>(W));
    vector<int> deg(m), ori(m);

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if ((L[i] < L[j] && L[j] < R[i] && R[i] < R[j]) || (L[j] < L[i] && L[i] < R[j] && R[j] < R[i])) {
                adj[i][j >> 6] |= 1ULL << (j & 63);
                adj[j][i >> 6] |= 1ULL << (i & 63);
                deg[i]++;
                deg[j]++;
            }
        }
    }

    int T = 0;
    for (int i = 0; i < m; i++) {
        ori[i] = deg[i] & 1;
        T += ori[i];
    }

    vector<Cand> ret;
    for (int x = 0; x < m; x++) {
        if (!ori[x]) {
            continue;
        }
        int O = 0;
        for (int w = 0; w < W; w++) {
            unsigned long long z = adj[x][w];
            while (z) {
                int b = __builtin_ctzll(z);
                int y = (w << 6) + b;
                if (y < m && ori[y]) {
                    O++;
                }
                z &= z - 1;
            }
        }
        int U = deg[x] - O;
        int sc = T + U - O - 1;

        int pa, sa;
        if (x == 0) {
            pa = 0;
            sa = 1;
        } else {
            pa = pos[x];
            sa = (sgn[x] > 0 ? 1 : 0);
        }

        int pb, sb;
        if (x == n) {
            pb = n + 1;
            sb = 0;
        } else {
            pb = pos[x + 1];
            sb = (sgn[x + 1] > 0 ? 0 : 1);
        }

        int l, r;
        if (pa < pb) {
            l = pa + (sa == 1);
            r = pb - (sb == 0);
        } else {
            l = pb + (sb == 1);
            r = pa - (sa == 0);
        }

        l--;
        r--;
        ret.push_back({-sc, r - l + 1, l, r});
    }

    sort(ret.begin(), ret.end(), [](const Cand &a, const Cand &b) {
        if (a.score != b.score) {
            return a.score < b.score;
        }
        if (a.len != b.len) {
            return a.len < b.len;
        }
        if (a.l != b.l) {
            return a.l < b.l;
        }
        return a.r < b.r;
    });
    ret.erase(unique(ret.begin(), ret.end(), [](const Cand &a, const Cand &b) {
        return a.l == b.l && a.r == b.r;
    }), ret.end());
    return ret;
}

void reduce_positive(const vector<int> &a, vector<int> &q, vector<int> &segl, vector<int> &segr) {
    int n = a.size();
    vector<int> ext(n + 2);
    ext[0] = 0;
    for (int i = 0; i < n; i++) {
        ext[i + 1] = a[i];
    }
    ext[n + 1] = n + 1;

    vector<array<int, 4>> runs;
    int s = 0;
    for (int i = 1; i < n + 2; i++) {
        if (ext[i] != ext[i - 1] + 1) {
            runs.push_back({s, i - 1, ext[s], ext[i - 1]});
            s = i;
        }
    }
    runs.push_back({s, n + 1, ext[s], ext[n + 1]});

    vector<int> ord(runs.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return runs[i][2] < runs[j][2];
    });

    vector<int> id(runs.size());
    for (int i = 0; i < (int)ord.size(); i++) {
        id[ord[i]] = i;
    }

    q.clear();
    segl.assign(runs.size(), INF);
    segr.assign(runs.size(), -INF);

    for (int i = 0; i < (int)runs.size(); i++) {
        int v = id[i];
        q.push_back(v);
        int l = max(1, runs[i][0]);
        int r = min(n, runs[i][1]);
        segl[v] = l - 1;
        segr[v] = r - 1;
    }
}

vector<pair<int, int>> hurdles_q(const vector<int> &q) {
    int m = q.size();
    vector<int> pos(m);
    for (int i = 0; i < m; i++) {
        pos[q[i]] = i;
    }

    vector<pair<int, int>> all;
    vector<int> mn(m, INF);

    for (int a = 0; a < m; a++) {
        int pa = pos[a];
        int mx = -1;
        for (int len = 1; len <= m; len++) {
            int v = q[(pa + len - 1) % m];
            int d = (v - a + m) % m;
            if (d > mx) {
                mx = d;
            }
            if (len > 2 && mx < len && v == (a + len - 1) % m) {
                all.push_back({a, len});
                if (len < mn[a]) {
                    mn[a] = len;
                }
            }
        }
    }

    vector<int> B(2 * m, INF);
    for (int i = 0; i < 2 * m; i++) {
        if (mn[i % m] < INF) {
            B[i] = mn[i % m] + i;
        }
    }

    int SZ = 1;
    while (SZ < 2 * m) {
        SZ <<= 1;
    }
    vector<int> st(2 * SZ, INF);
    for (int i = 0; i < 2 * m; i++) {
        st[SZ + i] = B[i];
    }
    for (int i = SZ - 1; i >= 1; i--) {
        st[i] = min(st[i << 1], st[i << 1 | 1]);
    }

    auto query = [&](int l, int r) {
        if (l > r) {
            return INF;
        }
        l += SZ;
        r += SZ;
        int ans = INF;
        while (l <= r) {
            if (l & 1) {
                ans = min(ans, st[l++]);
            }
            if (!(r & 1)) {
                ans = min(ans, st[r--]);
            }
            l >>= 1;
            r >>= 1;
        }
        return ans;
    };

    vector<pair<int, int>> hur;
    for (auto [a, len] : all) {
        if (query(a + 1, a + len - 1) > a + len) {
            hur.push_back({a, len});
        }
    }
    sort(hur.begin(), hur.end());
    hur.erase(unique(hur.begin(), hur.end()), hur.end());
    return hur;
}

void add_endpoints(int u, int v, const vector<int> &q, const vector<int> &posq, const vector<int> &segl, const vector<int> &segr, vector<pair<int, int>> &cand) {
    int m = q.size();
    int pu = posq[u];
    int pv = posq[v];
    int l = min(pu, pv);
    int r = max(pu, pv);

    if (pu < pv) {
        if (u == 0 || u == m - 1) {
            l++;
        }
        if (v == 0 || v == m - 1) {
            r--;
        }
    } else {
        if (v == 0 || v == m - 1) {
            l++;
        }
        if (u == 0 || u == m - 1) {
            r--;
        }
    }

    if (l > r) {
        return;
    }

    int L = INF;
    int R = -INF;
    for (int i = l; i <= r; i++) {
        int x = q[i];
        if (segl[x] <= segr[x]) {
            L = min(L, segl[x]);
            R = max(R, segr[x]);
        }
    }

    if (L <= R) {
        cand.push_back({L, R});
    }
}

vector<pair<int, int>> hurdle_candidates(const vector<int> &a) {
    vector<int> q, segl, segr;
    reduce_positive(a, q, segl, segr);
    vector<pair<int, int>> hur = hurdles_q(q);
    int m = q.size();

    vector<int> posq(m);
    for (int i = 0; i < m; i++) {
        posq[q[i]] = i;
    }

    vector<pair<int, int>> cut;
    for (auto [s, len] : hur) {
        vector<int> ord(len);
        for (int i = 0; i < len; i++) {
            ord[i] = q[(posq[s] + i) % m];
        }
        int e = ord.back();
        for (int i = 1; i < len - 1; i++) {
            int x = ord[i];
            add_endpoints(s, x, q, posq, segl, segr, cut);
            add_endpoints(x, e, q, posq, segl, segr, cut);
        }
    }

    sort(cut.begin(), cut.end());
    cut.erase(unique(cut.begin(), cut.end()), cut.end());
    return cut;
}

vector<pair<int, int>> merge_candidates(const vector<int> &a) {
    vector<int> q, segl, segr;
    reduce_positive(a, q, segl, segr);
    vector<pair<int, int>> hur = hurdles_q(q);
    int h = hur.size();
    int m = q.size();

    vector<int> posq(m);
    for (int i = 0; i < m; i++) {
        posq[q[i]] = i;
    }

    vector<pair<int, int>> cand;
    auto ok = [&](int i, int j) {
        if (h == 2) {
            return true;
        }
        bool consec = (j == i + 1) || (i == 0 && j == h - 1);
        if (h == 3) {
            return true;
        }
        return !consec;
    };

    for (int i = 0; i < h; i++) {
        for (int j = i + 1; j < h; j++) {
            if (!ok(i, j)) {
                continue;
            }
            int u = (hur[i].first + hur[i].second - 1) % m;
            int v = hur[j].first;
            add_endpoints(u, v, q, posq, segl, segr, cand);
        }
    }

    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());
    return cand;
}




pair<int, int> vertex_to_reversal(const vector<int> &a, int v) {
    int n = a.size();
    vector<int> pos(n + 1), sgn(n + 1);
    for (int i = 0; i < n; i++) {
        pos[abs(a[i])] = i + 1;
        sgn[abs(a[i])] = (a[i] > 0 ? 1 : -1);
    }

    int pa, sa;
    if (v == 0) {
        pa = 0;
        sa = 1;
    } else {
        pa = pos[v];
        sa = (sgn[v] > 0 ? 1 : 0);
    }

    int pb, sb;
    if (v == n) {
        pb = n + 1;
        sb = 0;
    } else {
        pb = pos[v + 1];
        sb = (sgn[v + 1] > 0 ? 0 : 1);
    }

    int l, r;
    if (pa < pb) {
        l = pa + (sa == 1);
        r = pb - (sb == 0);
    } else {
        l = pb + (sb == 1);
        r = pa - (sa == 0);
    }

    return {l - 1, r - 1};
}

struct Wish {
    int v;
    int l;
    int r;
    bool tw;
};

vector<Wish> get_wishes(const vector<int> &a) {
    int n = a.size();
    vector<int> pi(2 * n + 2);
    pi[0] = 0;
    for (int i = 0; i < n; i++) {
        int x = abs(a[i]);
        if (a[i] > 0) {
            pi[2 * i + 1] = 2 * x - 1;
            pi[2 * i + 2] = 2 * x;
        } else {
            pi[2 * i + 1] = 2 * x;
            pi[2 * i + 2] = 2 * x - 1;
        }
    }
    pi[2 * n + 1] = 2 * n + 1;

    vector<int> pos(2 * n + 2);
    for (int i = 0; i < 2 * n + 2; i++) {
        pos[pi[i]] = i;
    }

    vector<Wish> w;
    for (int i = 0; i <= n; i++) {
        int l = pos[2 * i];
        int r = pos[2 * i + 1];
        if (abs(l - r) == 1) {
            continue;
        }
        if (l > r) {
            swap(l, r);
        }
        w.push_back({i, l, r, (l + r) & 1});
    }

    sort(w.begin(), w.end(), [](const Wish &a, const Wish &b) {
        if (a.l != b.l) {
            return a.l < b.l;
        }
        return a.r < b.r;
    });
    return w;
}

int happy_vertex(const vector<int> &a) {
    vector<Wish> w = get_wishes(a);
    vector<Wish> c;
    int t = -1;

    for (auto x : w) {
        if (x.tw) {
            continue;
        }
        if (c.empty()) {
            c.push_back(x);
            continue;
        }
        if (c.back().r < x.l) {
            break;
        }
        if (t != -1 && t < x.r) {
            continue;
        }
        if (x.r < c.back().r) {
            t = c.back().r;
            c.clear();
            c.push_back(x);
            continue;
        }
        if (x.l <= c[0].r) {
            c.push_back(x);
            continue;
        }
        c.clear();
        c.push_back(x);
    }

    if (c.empty()) {
        return -1;
    }

    int k = c.size();
    vector<int> cl(k), cr(k), diff(k + 1);
    for (int i = 0; i < k; i++) {
        cl[i] = c[i].l;
        cr[i] = c[i].r;
    }

    for (auto x : w) {
        if (!x.tw) {
            continue;
        }

        int l1 = lower_bound(cl.begin(), cl.end(), x.l) - cl.begin();
        int le = upper_bound(cl.begin(), cl.end(), x.l) - cl.begin();
        int rl = lower_bound(cl.begin(), cl.end(), x.r) - cl.begin();
        int gl = upper_bound(cr.begin(), cr.end(), x.l) - cr.begin();
        int gr = lower_bound(cr.begin(), cr.end(), x.r) - cr.begin();
        int ge = upper_bound(cr.begin(), cr.end(), x.r) - cr.begin();

        int l = gl;
        int r = min(l1, gr) - 1;
        if (l <= r) {
            diff[l]++;
            diff[r + 1]--;
        }

        l = max(le, ge);
        r = rl - 1;
        if (l <= r) {
            diff[l]++;
            diff[r + 1]--;
        }
    }

    int sum = 0;
    int mx = -1;
    int who = 0;
    for (int i = 0; i < k; i++) {
        sum += diff[i];
        if (sum > mx) {
            mx = sum;
            who = i;
        }
    }

    return c[who].v;
}
int main() {
    IOS;

    while (true) {
        int n;
        cin >> n;
        if (!cin || n == 0) {
            break;
        }

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        vector<int> pos(n + 1), sgn(n + 1);
        for (int i = 0; i < n; i++) {
            pos[abs(b[i])] = i + 1;
            sgn[abs(b[i])] = (b[i] > 0 ? 1 : -1);
        }

        vector<int> cur(n);
        for (int i = 0; i < n; i++) {
            int x = abs(a[i]);
            int t = (a[i] > 0 ? 1 : -1) * sgn[x];
            cur[i] = pos[x] * t;
        }

        vector<pair<int, int>> ops;
        int d = calc_dist(cur);

        while (d > 0) {
            bool ok = false;

            int v = happy_vertex(cur);
            if (v != -1) {
                auto [l, r] = vertex_to_reversal(cur, v);
                do_rev(cur, l, r);
                ops.push_back({l, r});
                d--;
                ok = true;
            }
            if (ok) {
                continue;
            }

            vector<pair<int, int>> hc = hurdle_candidates(cur);
            for (auto [l, r] : hc) {
                do_rev(cur, l, r);
                int nd = calc_dist(cur);
                if (nd == d - 1) {
                    ops.push_back({l, r});
                    d = nd;
                    ok = true;
                    break;
                }
                do_rev(cur, l, r);
            }
            if (ok) {
                continue;
            }

            vector<pair<int, int>> mc = merge_candidates(cur);
            for (auto [l, r] : mc) {
                do_rev(cur, l, r);
                int nd = calc_dist(cur);
                if (nd == d - 1) {
                    ops.push_back({l, r});
                    d = nd;
                    ok = true;
                    break;
                }
                do_rev(cur, l, r);
            }

            if (!ok) {
                return 0;
            }
        }

        cout << (int)ops.size() << " Steps" << endl;
        vector<int> now = a;
        for (int i = 0; i < n; i++) {
            if (i) {
                cout << ' ';
            }
            if (now[i] > 0) {
                cout << '+' << now[i];
            } else {
                cout << now[i];
            }
        }
        cout << endl;

        for (auto [l, r] : ops) {
            do_rev(now, l, r);
            for (int i = 0; i < n; i++) {
                if (i) {
                    cout << ' ';
                }
                if (now[i] > 0) {
                    cout << '+' << now[i];
                } else {
                    cout << now[i];
                }
            }
            cout << endl;
        }
    }

    return 0;
}
