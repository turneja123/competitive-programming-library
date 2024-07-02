//https://codeforces.com/problemset/problem/920/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int spf[N];
int ind[N];
bool is_prime[N];
bool sorted[N];
int num_divs[N];

long long a[N];
long long segtree[4 * N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

int factor(int n) {
    int last = -1, ct = 0, cnt = 1;
    while (n > 1) {
        int p = spf[n];
        if (p != last) {
            last = p;
            cnt *= ct + 1;
            ct = 1;
        } else {
            ct++;
        }
        n = n / p;
    }
    if (ct > 0) {
        cnt *= ct + 1;
    }
    return cnt;
}

long long query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, long long val, int node) {
    if (l == r) {
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int main() {
	IOS;
	sieve(N);
	num_divs[1] = 1;
    for (int i = 2; i < N; i++) {
        num_divs[i] = factor(i);
    }
    int n, q;
    cin >> n >> q;
    set<int> pos;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos.insert(i);
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            l--, r--;
            auto it = pos.lower_bound(l);
            vector<int> rem;
            while (it != pos.end() && *it <= r) {
                a[*it] = num_divs[a[*it]];
                update(0, n - 1, *it, a[*it], 0);
                if (a[*it] == 1 || a[*it] == 2) {
                    rem.push_back(*it);
                }
                ++it;
            }
            for (int x : rem) {
                pos.erase(x);
            }
        } else {
            l--, r--;
            cout << query(0, n - 1, l, r, 0) << endl;
        }
    }


	return 0;
}
