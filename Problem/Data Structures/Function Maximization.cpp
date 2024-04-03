//https://dmoj.ca/problem/bts18p8
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 5005;

int n, q; long long k;

long long a[N];

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
vector<long long> pos;

bitset<K> segtree[4 * N];
int lazy[4 * N];


void compose(int parent, int child) {
    lazy[child] += lazy[parent];
}

void apply(int node, int l, int r) {
    if (lazy[node] > 0) {
        segtree[node] <<= lazy[node];
    } else if (lazy[node] < 0) {
        segtree[node] >>= abs(lazy[node]);
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] | segtree[node * 2 + 2];
}

long long query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return -1;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        for (int i = pos.size() - 1; i >= 0; i--) {
            if (segtree[node][pos[i]] == 1) {
                return k + pos[i];
            }
        }
        return -1;
    }
    int mid = (l + r) / 2;
    return max(query(l, mid, lq, rq, 2 * node + 1),
               query(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node].set(a[l] - k, 1);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] | segtree[node * 2 + 2];
}

__int128 binpower(__int128 base, __int128 e, __int128 mod) {
    __int128 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(__int128 n, __int128 a, __int128 d, int s) {
    __int128 x = binpower(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1) {
            return false;
        }
    }
    return true;
};


bool is_prime(__int128 n) {
    if (n < 2) {
        return false;
    }
    int r = 0;
    __int128 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : primes) {
        if (n == a) {
            return true;
        }
        if (check_composite(n, a, d, r)) {
            return false;
        }
    }
    return true;
}

int main() {
    IOS;
    cin >> n >> q >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (long long i = k; i <= k + 5000; i++) {
        if (is_prime(i)) {
            pos.push_back(i - k);
        }
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            cout << query(0, n - 1, l - 1, r - 1, 0) << endl;
        } else {
            int l, r, d;
            cin >> l >> r >> d;
            incUpdate(0, 0, n - 1, l - 1, r - 1, d);
        }
    }

    return 0;
}
