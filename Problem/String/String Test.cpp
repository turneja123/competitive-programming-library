#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 18;
const int SQ = 400;

using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

const u32 B = 911382323;
const u32 B2 = 972663749;

u32 pw[N], h[N];
u32 pw2[N], h2[N];

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

inline u32 get_hash(u32 *a, int l, int r) {
    u32 ans = a[r + 1] + MOD - mul_small(a[l], pw[r - l + 1]);
    if (ans >= MOD) ans -= MOD;
    return ans;
}

inline u32 get_hash2(u32 *a, int l, int r) {
    u32 ans = a[r + 1] + MOD - mul_small(a[l], pw2[r - l + 1]);
    if (ans >= MOD) ans -= MOD;
    return ans;
}

vector<int> a;
vector<int> b;

int n, m;
int cap;
bool long_period;
int per, sz;

struct SuffixArray {
	vector<int> S; int n;
	vector<int> sa, isa, lcp;
	vector<vector<int>> table;
	void init(vector<int> _S) {
        S = _S;
        n = S.size();
        genSa(); genLcp();
        table.resize(K, vector<int>(n, 0));
        for (int i = 1; i <= n - 1; i++) {
            table[0][i] = lcp[i - 1];
        }
        for (int k = 1; k < K; k++) {
            for (int i = 1; i + (1 << k) - 1 <= n - 1; i++) {
                table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    int query(int l, int r) {
        l = isa[l], r = isa[r];
        if (l > r) {
            swap(l, r);
        }
        l++;
        if (l > r) {
            return N;
        }
        int k = 31 - __builtin_clz(r - l + 1);
        return min(table[k][l], table[k][r - (1 << k) + 1]);
    }

	void genSa() {
		sa = vector<int>(n);
		isa = vector<int>(n);
		sa[0] = n - 1;
		iota(1 + sa.begin(), sa.end(), 0);
		sort(1 + sa.begin(), sa.end(), [&](int a, int b) { return S[a] < S[b]; });
		for (int i = 1; i < n; i++) {
            int a = sa[i - 1], b = sa[i];
			isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i;
        }
		for (int len = 1; len < n; len *= 2) {
			vector<int> s(sa), is(isa), pos(n);
			iota(pos.begin(), pos.end(), 0);
			for (int t : s) {
                int T = t - len;
                if (T >= 0) {
                    sa[pos[isa[T]]++] = T;
                }
            }
			for (int i = 1; i < n; i++) {
                int a = sa[i - 1], b = sa[i];
                int x = a + len < n ? is[a + len] : 0;
                int y = b + len < n ? is[b + len] : 0;
                isa[b] = is[a] == is[b] && x == y ? isa[a] : i;
            }
		}
	}
	void genLcp() {
		lcp = vector<int>(n - 1); int h = 0;
		for (int b = 0; b < n - 1; b++) {
            int a = sa[isa[b] - 1];
			while (a + h < n - 1 && S[a + h] == S[b + h]) {
                ++h;
			}
			lcp[isa[b] - 1] = h;
			if (h) {
                h--;
			}
        }
	}
};

SuffixArray sa;

bool comp(int pos, int l1, int r1, int l2, int r2) {
    int x = min(r1 - l1 + 1, sa.query(pos, l1));
    if (x < r1 - l1 + 1) {
        if (pos + x >= m) {
            return true;
        }
        return b[pos + x] < b[l1 + x];
    }
    pos += r1 - l1 + 1;
    if (pos >= m) {
        return true;
    }
    int y = min(r2 - l2 + 1, sa.query(pos, l2));
    if (y < r2 - l2 + 1) {
        if (pos + y >= m) {
            return true;
        }
        return b[pos + y] < b[l2 + y];
    }
    return false;
}

bool starts_with(int pos, int l1, int r1, int l2, int r2) {
    if (pos + r1 - l1 + 1 + r2 - l2 + 1 > m) {
        return false;
    }
    if (sa.query(pos, l1) < r1 - l1 + 1) {
        return false;
    }
    pos += r1 - l1 + 1;
    if (sa.query(pos, l2) < r2 - l2 + 1) {
        return false;
    }

    return true;
}

struct Node {
    int mx;
    int ct;
    Node() {
        mx = -N;
        ct = 0;
    }
    Node(int x) {
        mx = x;
        ct = 1;
    }
    Node(int x, int c) {
        mx = x;
        ct = c;
    }
};

Node combine(Node left, Node right) {
    Node node;
    if (left.mx > right.mx) {
        node.mx = left.mx;
        node.ct = left.ct;
    } else if (left.mx == right.mx) {
        node.mx = left.mx;
        node.ct = left.ct + right.ct;
    } else {
        node.mx = right.mx;
        node.ct = right.ct;
    }
    return node;

}

struct HashNode {
    u32 x;
    u32 y;
    int len;
    HashNode() {
        x = 0;
        y = 0;
        len = 0;
    }
    HashNode(int v) {
        x = v;
        y = v;
        len = 1;
    }
};

HashNode combine_hash(HashNode left, HashNode right) {
    HashNode node;
    node.len = left.len + right.len;
    node.x = mul_small(left.x, pw[right.len]) + right.x;
    if (node.x >= MOD) node.x -= MOD;
    node.y = mul_small(left.y, pw2[right.len]) + right.y;
    if (node.y >= MOD) node.y -= MOD;
    return node;
}

struct Gap {
    int L;
    int R;
    int B;
    int on;
    Gap() {
        L = R = B = on = 0;
    }
    Gap(int l, int r, int b) {
        L = l;
        R = r;
        B = b;
        on = 1;
    }
};

int light[N];
int lcp_long[N];
bool active[N];
bool base_ok[N];
bool blk[N];
int gap_at[N];
int gct[N / SQ + 10];
Node segtree[4 * N];
HashNode hashseg[4 * N];
vector<int> good[N / SQ + 10];
vector<int> base_bucket[N / SQ + 10];
vector<int> br_bucket[N / SQ + 10];
vector<int> gap_bucket[N / SQ + 10];
vector<Gap> gaps;

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel;
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int node) {
    if (l == r) {
        segtree[node] = Node(light[l]);
        return;
    }

    int mid = (l + r) / 2;
    update(l, mid, 2 * node + 1);
    update(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void upd(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return;
    }

    if (lq <= l && rq >= r) {
        update(l, r, node);
        return;
    }

    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, 2 * node + 1);
    upd(mid + 1, r, lq, rq, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(light[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void update_hash(int l, int r, int node, int p) {
    if (l == r) {
        hashseg[node] = HashNode(a[l]);
        return;
    }

    int mid = (l + r) / 2;
    if (p <= mid) {
        update_hash(l, mid, 2 * node + 1, p);
    } else {
        update_hash(mid + 1, r, 2 * node + 2, p);
    }
    hashseg[node] = combine_hash(hashseg[2 * node + 1], hashseg[2 * node + 2]);
}

void build_hash(int l, int r, int node) {
    if (l == r) {
        hashseg[node] = HashNode(a[l]);
        return;
    }

    int mid = (l + r) / 2;
    build_hash(l, mid, 2 * node + 1);
    build_hash(mid + 1, r, 2 * node + 2);
    hashseg[node] = combine_hash(hashseg[2 * node + 1], hashseg[2 * node + 2]);
}

int first_mismatch(int l, int r, int lq, int rq, int base, int node) {
    if (l > rq || r < lq) {
        return rq + 1;
    }

    if (lq <= l && rq >= r) {
        int off = l - base;
        int len = r - l + 1;
        if (hashseg[node].x == get_hash(h, off, off + len - 1) && hashseg[node].y == get_hash2(h2, off, off + len - 1)) {
            return rq + 1;
        }
        if (l == r) {
            return l;
        }
    }

    int mid = (l + r) / 2;
    int x = first_mismatch(l, mid, lq, rq, base, 2 * node + 1);
    if (x <= rq) {
        return x;
    }
    return first_mismatch(mid + 1, r, lq, rq, base, 2 * node + 2);
}

int full_lcp(int pos) {
    int len = min(m, n - pos);
    if (len <= 0) {
        return 0;
    }
    int x = first_mismatch(0, n - 1, pos, pos + len - 1, pos, 0);
    if (x > pos + len - 1) {
        return len;
    }
    return x - pos;
}

void rebuild_good(int id) {
    good[id].clear();
    int l = id * SQ;
    int r = min(n - 1, (id + 1) * SQ - 1);
    for (int i = l; i <= r; i++) {
        if (active[i]) {
            good[id].push_back(i);
        }
    }
}

void rebuild_base(int id) {
    base_bucket[id].clear();
    int l = id * SQ;
    int r = min(n - per, (id + 1) * SQ - 1);
    if (l > r) {
        return;
    }
    for (int i = l; i <= r; i++) {
        if (base_ok[i]) {
            base_bucket[id].push_back(i);
        }
    }
}

void rebuild_br(int id) {
    br_bucket[id].clear();
    int l = id * SQ;
    int r = min(n, (id + 1) * SQ - 1);
    for (int i = l; i <= r; i++) {
        if (blk[i]) {
            br_bucket[id].push_back(i);
        }
    }
}

void clean_gap(int id) {
    vector<int> v;
    for (int x : gap_bucket[id]) {
        if (gaps[x].on && gaps[x].L / SQ == id) {
            v.push_back(x);
        }
    }
    gap_bucket[id].swap(v);
    gct[id] = gap_bucket[id].size();
}

void add_gap(int y, int x) {
    int L = max(0, y - per + 1);
    int R = min(n - cap, x - cap);
    int B = x - 1;
    if (L > R) {
        return;
    }
    gaps.push_back(Gap(L, R, B));
    int id = gaps.size() - 1;
    gap_at[L] = id;
    gap_bucket[L / SQ].push_back(id);
    gct[L / SQ]++;
}

void del_gap(int y, int x) {
    int L = max(0, y - per + 1);
    int R = min(n - cap, x - cap);
    if (L > R) {
        return;
    }
    int id = gap_at[L];
    if (id == -1) {
        return;
    }
    gaps[id].on = 0;
    gap_at[L] = -1;
    gct[L / SQ]--;
    if (gap_bucket[L / SQ].size() > gct[L / SQ] * 4 + 50) {
        clean_gap(L / SQ);
    }
}

int prev_br(int x) {
    x = min(x, n);
    if (x < 0) {
        return -1;
    }
    for (int id = x / SQ; id >= 0; id--) {
        for (int i = br_bucket[id].size() - 1; i >= 0; i--) {
            if (br_bucket[id][i] <= x) {
                return br_bucket[id][i];
            }
        }
    }
    return -1;
}

int next_br(int x) {
    if (x > n) {
        return n;
    }
    for (int id = x / SQ; id <= n / SQ; id++) {
        for (int i : br_bucket[id]) {
            if (i >= x) {
                return i;
            }
        }
    }
    return n;
}

bool is_br(int x) {
    if (x < per || x >= n) {
        return false;
    }
    return a[x] != a[x - per];
}

void insert_br(int x) {
    if (blk[x]) {
        return;
    }
    int nx = next_br(x);
    int pr = prev_br(x);
    del_gap(pr, nx);
    blk[x] = true;
    rebuild_br(x / SQ);
    add_gap(pr, x);
    add_gap(x, nx);
}

void erase_br(int x) {
    if (!blk[x]) {
        return;
    }
    int pr = prev_br(x - 1);
    int nx = next_br(x + 1);
    del_gap(pr, x);
    del_gap(x, nx);
    blk[x] = false;
    rebuild_br(x / SQ);
    add_gap(pr, nx);
}

void refresh_br(int x) {
    if (x < per || x >= n) {
        return;
    }
    bool nw = is_br(x);
    if (!blk[x] && nw) {
        insert_br(x);
    } else if (blk[x] && !nw) {
        erase_br(x);
    }
}

int first_base(int l, int r) {
    if (l > r) {
        return -1;
    }
    r = min(r, n - per);
    if (l > r) {
        return -1;
    }
    for (int id = l / SQ; id <= r / SQ; id++) {
        for (int i : base_bucket[id]) {
            if (i >= l && i <= r) {
                return i;
            }
        }
    }
    return -1;
}

void upd_good_light(int l, int r) {
    if (!long_period || cap == m) {
        return;
    }
    for (int i = l; i <= r; i++) {
        bool old = active[i];
        active[i] = light[i] == cap;
        if (!old && active[i]) {
            lcp_long[i] = full_lcp(i);
        }
    }
    for (int i = l / SQ; i <= r / SQ; i++) {
        rebuild_good(i);
    }
}

void upd_good_far(int pos) {
    if (!long_period || cap == m) {
        return;
    }
    int l = max(0, pos - m + 1);
    int r = min(pos - cap, n - 1);
    if (l > r) {
        return;
    }
    for (int id = l / SQ; id <= r / SQ; id++) {
        for (int i : good[id]) {
            if (i < l || i > r) {
                continue;
            }
            int d = pos - i;
            if (lcp_long[i] < d) {
                continue;
            }
            if (a[pos] != b[d]) {
                lcp_long[i] = d;
            } else if (lcp_long[i] == d) {
                lcp_long[i] = full_lcp(i);
            }
        }
    }
}

Node query_long_sparse(int l, int r) {
    Node node;
    if (!long_period || cap == m) {
        return node;
    }
    int R = r - cap;
    if (R < l) {
        return node;
    }
    for (int id = l / SQ; id <= R / SQ; id++) {
        for (int i : good[id]) {
            if (i < l || i > R) {
                continue;
            }
            int val = min(lcp_long[i], r - i + 1);
            if (val > cap) {
                Node cur = Node(val);
                node = combine(node, cur);
            }
        }
    }
    return node;
}

Node query_long_periodic(int l, int r) {
    Node node;
    if (long_period || cap == m) {
        return node;
    }
    int R = r - cap;
    if (R < l) {
        return node;
    }
    for (int id = 0; id <= n / SQ; id++) {
        for (int q : gap_bucket[id]) {
            if (!gaps[q].on) {
                continue;
            }
            Gap g = gaps[q];
            if (g.R < l || g.L > R) {
                continue;
            }
            int L = max(g.L, l);
            int RR = min(g.R, R);
            int first = first_base(L, RR);
            if (first == -1) {
                continue;
            }
            int C = min(g.B, r);
            int val = min(sz, C - first + 1);
            if (val > cap) {
                int ct = 1;
                if (val == sz) {
                    int U = min(RR, C - sz + 1);
                    ct = U >= first ? (U - first) / per + 1 : 0;
                }
                if (ct) {
                    Node cur = Node(val, ct);
                    node = combine(node, cur);
                }
            }
            if (sz < m && g.B + 1 < n) {
                int i = g.B - sz + 1;
                if (i >= L && i <= RR && r - i + 1 > sz && base_ok[i]) {
                    int v = min(full_lcp(i), r - i + 1);
                    if (v > sz) {
                        Node cur = Node(v);
                        node = combine(node, cur);
                    }
                }
            }
        }
    }
    return node;
}

void build_good() {
    if (!long_period || cap == m) {
        return;
    }
    for (int i = 0; i < n; i++) {
        active[i] = light[i] == cap;
        if (active[i]) {
            lcp_long[i] = full_lcp(i);
        }
    }
    for (int i = 0; i <= (n - 1) / SQ; i++) {
        rebuild_good(i);
    }
}

void build_base() {
    if (long_period || cap == m) {
        return;
    }
    int s = per + 1 + n;
    vector<int> v(s);
    int j = 0;
    for (int i = 0; i < per; i++) {
        v[j++] = b[i];
    }
    v[j++] = 0;
    for (int i = 0; i < n; i++) {
        v[j++] = a[i];
    }
    vector<int> z(s);
    for (int i = 1, l = 0, r = 0; i < s; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < s && v[z[i]] == v[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    for (int i = 0; i < n; i++) {
        base_ok[i] = false;
    }
    for (int i = 0; i + per <= n; i++) {
        int idx = per + 1 + i;
        base_ok[i] = z[idx] >= per;
    }
    for (int i = 0; i <= (n - 1) / SQ; i++) {
        rebuild_base(i);
    }
}

void upd_base(int pos) {
    if (long_period || cap == m) {
        return;
    }
    int l = max(0, pos - per + 1);
    int r = min(pos, n - per);
    if (l > r) {
        return;
    }
    int R = min(n - 1, r + per - 1);
    int s = per + 1 + R - l + 1;
    vector<int> v(s);
    int j = 0;
    for (int i = 0; i < per; i++) {
        v[j++] = b[i];
    }
    v[j++] = 0;
    for (int i = l; i <= R; i++) {
        v[j++] = a[i];
    }
    vector<int> z(s);
    for (int i = 1, l = 0, r = 0; i < s; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < s && v[z[i]] == v[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    for (int i = l; i <= r; i++) {
        int idx = per + 1 + i - l;
        base_ok[i] = z[idx] >= per;
    }
    for (int i = l / SQ; i <= r / SQ; i++) {
        rebuild_base(i);
    }
}

void build_short() {
    if (long_period || cap == m) {
        return;
    }
    for (int i = 0; i <= n; i++) {
        blk[i] = false;
        gap_at[i] = -1;
    }
    for (int i = 0; i <= n / SQ; i++) {
        br_bucket[i].clear();
        gap_bucket[i].clear();
        gct[i] = 0;
    }
    gaps.clear();
    build_base();
    if (per - 1 <= n) {
        blk[per - 1] = true;
    }
    blk[n] = true;
    for (int i = per; i < n; i++) {
        if (is_br(i)) {
            blk[i] = true;
        }
    }
    for (int i = 0; i <= n / SQ; i++) {
        rebuild_br(i);
    }
    int last = -1;
    for (int i = 0; i <= n; i++) {
        if (blk[i]) {
            if (last != -1) {
                add_gap(last, i);
            }
            last = i;
        }
    }
}

void upd_short(int pos) {
    if (long_period || cap == m) {
        return;
    }
    upd_base(pos);
    refresh_br(pos);
    refresh_br(pos + per);
}

void build_period() {
    cap = min(SQ, m);
    per = cap + 1;
    sz = cap;
    if (cap == m) {
        long_period = false;
        return;
    }
    vector<int> pi(cap);
    for (int i = 1; i < cap; i++) {
        int j = pi[i - 1];
        while (j && b[i] != b[j]) {
            j = pi[j - 1];
        }
        if (b[i] == b[j]) {
            j++;
        }
        pi[i] = j;
    }
    per = cap - pi[cap - 1];
    long_period = per * 2 > cap;
    if (!long_period) {
        while (sz < m && b[sz] == b[sz - per]) {
            sz++;
        }
    }
}

void upd_light(int pos) {
    int l = max(0, pos - SQ + 1);
    int r = min(n - 1, pos + SQ - 1);
    int s = min(SQ, m) + 1 + r - l + 1;

    vector<int> v(s);
    int j = 0;
    for (int i = 0; i < min(SQ, m); i++) {
        v[j++] = b[i];
    }
    v[j++] = 0;
    for (int i = l; i <= r; i++) {
        v[j++] = a[i];
    }

    vector<int> z(s);
    for (int i = 1, l = 0, r = 0; i < s; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < s && v[z[i]] == v[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    for (int i = l; i <= pos; i++) {
        int idx = min(SQ, m) + 1 + (i - l);
        int val = min(z[idx], min(min(SQ, m), n - i));
        light[i] = val;
    }
    upd(0, n - 1, l, pos, 0);
    upd_good_light(l, pos);
}

void build_light() {
    int s = min(SQ, m) + 1 + n;

    vector<int> v(s);
    int j = 0;
    for (int i = 0; i < min(SQ, m); i++) {
        v[j++] = b[i];
    }
    v[j++] = 0;
    for (int i = 0; i < n; i++) {
        v[j++] = a[i];
    }

    vector<int> z(s);
    for (int i = 1, l = 0, r = 0; i < s; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < s && v[z[i]] == v[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        int idx = min(SQ, m) + 1 + i;
        int val = min(z[idx], min(min(SQ, m), n - i));
        light[i] = val;
    }
    build(0, n - 1, 0);
}

int main() {
    IOS;
    cin >> n >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    a.push_back(0);

    cin >> m;
    b.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    b.push_back(0);
    pw[0] = 1;
    pw2[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = mul_small(pw[i - 1], B);
        pw2[i] = mul_small(pw2[i - 1], B2);
    }
    h[0] = 0;
    h2[0] = 0;
    for (int i = 0; i < m; i++) {
        h[i + 1] = mul_small(h[i], B) + b[i];
        if (h[i + 1] >= MOD) h[i + 1] -= MOD;
        h2[i + 1] = mul_small(h2[i], B2) + b[i];
        if (h2[i + 1] >= MOD) h2[i + 1] -= MOD;
    }
    build_hash(0, n - 1, 0);


    sa.init(b);
    build_period();
    build_light();
    build_good();
    build_short();

    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int y, z;
            cin >> y >> z;
            y--;
            if (a[y] != z) {
                a[y] = z;
                update_hash(0, n - 1, 0, y);
                if (long_period) {
                    upd_good_far(y);
                }
                upd_light(y);
                if (!long_period) {
                    upd_short(y);
                }
            }
            Node node = segtree[0];
            if (node.mx == cap) {
                Node cur = long_period ? query_long_sparse(0, n - 1) : query_long_periodic(0, n - 1);
                if (cur.mx > cap) {
                    node = cur;
                }
            }
            cout << node.mx << " " << node.ct;

        } else if (t == 2) {
            int y, z;
            cin >> y >> z;
            y--, z--;
            Node node;
            int st = max(y, z - SQ + 1);
            for (int i = st; i <= z; i++) {
                Node cur = Node(min(light[i], z - i + 1));
                node = combine(node, cur);
            }
            if (y < st) {
                Node cur = query(0, n - 1, y, st - 1, 0);
                node = combine(node, cur);
            }
            if (node.mx == cap) {
                Node cur = long_period ? query_long_sparse(y, z) : query_long_periodic(y, z);
                if (cur.mx > cap) {
                    node = cur;
                }
            }
            cout << node.mx << " " << node.ct;
        } else if (t == 3) {
            int y, z;
            cin >> y >> z;
            y--, z--;
            cout << min(m - y, sa.query(y, z));

        } else {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            l1--, r1--, l2--, r2--;
            int l = 1, r = m;
            while (l < r) {
                int mid = (l + r) / 2;
                if (comp(sa.sa[mid], l1, r1, l2, r2)) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            string ans = (starts_with(sa.sa[l], l1, r1, l2, r2) ? "yes" : "no");
            cout << ans;
        }
        cout << endl;
    }

    return 0;
}
