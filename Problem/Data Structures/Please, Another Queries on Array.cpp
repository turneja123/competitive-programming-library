//https://codeforces.com/problemset/problem/1114/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int P = 301;
const int N = 4e5 + 5;
const long long M = 1e9 + 7;

vector<int> primes{2};
bool is_prime[P];

int a[N];
bitset<64> prime[N];

long long inv[P];
long long segtree[4 * N];
long long lazy[4 * N];
bitset<64> segtree_prime[4 * N];
bitset<64> lazy_prime[4 * N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

void compose(int parent, int child) {
    lazy[child] = (lazy[child] * lazy[parent]) % M;
    lazy_prime[child] |= lazy_prime[parent];
}

void apply(int node, int l, int r) {
    segtree[node] = (segtree[node] * modPow(lazy[node], (r - l + 1))) % M;
    segtree_prime[node] |= lazy_prime[node];
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 1;
    lazy_prime[node].reset();
}

void incUpdate(int node, int l, int r, int lq, int rq, long long add, bitset<64> add_prime) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] = lazy[node] * add % M;
        lazy_prime[node] |= add_prime;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add, add_prime);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add, add_prime);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] * segtree[node * 2 + 2] % M;
    segtree_prime[node] = segtree_prime[node * 2 + 1] | segtree_prime[node * 2 + 2];
}

long long getProd(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 1;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return getProd(l, mid, lq, rq, 2 * node + 1) * getProd(mid + 1, r, lq, rq, 2 * node + 2) % M;
}

bitset<64> getPrimes(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree_prime[node];
    }
    int mid = (l + r) / 2;
    return getPrimes(l, mid, lq, rq, 2 * node + 1) | getPrimes(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    lazy[node] = 1;
    lazy_prime[node].reset();
    if (l == r) {
        segtree[node] = a[l];
        segtree_prime[node] = prime[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] * segtree[node * 2 + 2] % M;
    segtree_prime[node] = segtree_prime[node * 2 + 1] | segtree_prime[node * 2 + 2];
}

int main() {
    IOS;
    is_prime[2] = true;
    for (int i = 3; i < P; i += 2) {
        is_prime[i] = true;
    }
    for (int i = 3; i < P; i += 2) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j < P; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int n, q, m = primes.size();
    vector<int> f(m, 0);
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        bitset<64> bit;
        bit.reset();
        for (int p = 0; p < m; p++) {
            if (a[i] % primes[p] == 0) {
                bit[p] = true;
            }
        }
        prime[i] = bit;
    }
    for (int p = 0; p < m; p++) {
        inv[p] = modPow(primes[p], M - 2);
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        if (s == "TOTIENT") {
            int l, r;
            cin >> l >> r;
            l--, r--;
            long long prod = getProd(0, n - 1, l, r, 0);
            bitset<64> bit = getPrimes(0, n - 1, l, r, 0);
            for (int p = 0; p < m; p++) {
                if (bit[p] == true) {
                    prod = ((prod * (primes[p] - 1)) % M) * inv[p] % M;
                }
            }
            cout << prod << endl;
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            bitset<64> bit;
            bit.reset();
            for (int p = 0; p < m; p++) {
                if (x % primes[p] == 0) {
                    bit[p] = true;
                }
            }
            incUpdate(0, 0, n - 1, l, r, x, bit);
        }
    }
    return 0;
}
