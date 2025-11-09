//https://cses.fi/problemset/task/3138/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 1e9 + 7;
const int P = 26;
const int Q = 53;


ll modPow(ll a, ll y) {
    ll ans = 1;
    while (y > 0) {
        if (y % 2 == 1) {
            ans = ans * a % M;
        }
        a = a * a % M;
        y /= 2;
    }
    return ans;
}

struct Node {
    int mx;
    int lazy;
    Node() {
        mx = 0;
        lazy = 0;
    }

};

Node segtree[4 * N];

void apply(int l, int r, int node) {
    if (segtree[node].lazy) {
        segtree[node].mx = max(segtree[node].mx, segtree[node].lazy);
        if (l != r) {
            int mid = (l + r) /2;
            segtree[2 * node + 1].lazy = max(segtree[2 * node + 1].lazy, segtree[node].lazy);
            segtree[2 * node + 2].lazy = max(segtree[2 * node + 2].lazy, segtree[node].lazy + (mid - l + 1) * 2);
        }
        segtree[node].lazy = 0;
    }
}

void upd(int l, int r, int node, int lq, int rq, int val) {
    apply(l, r, node);
    if (l > rq || r < lq) {
        return;
    }
    if (lq <= l && r <= rq) {
        segtree[node].lazy = val + 2 * (l - lq);
        return;
    }

    int mid = (l + r) / 2;
    upd(l, mid, 2 * node + 1, lq, rq, val);
    upd(mid + 1, r, 2 * node + 2, lq, rq, val);
}

int query(int l, int r, int node, int ind) {
    apply(l, r, node);
    if (l == r) {
        return segtree[node].mx;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return query(l, mid, 2 * node + 1, ind);
    } else {
        return query(mid + 1, r, 2 * node + 2, ind);
    }
}


pair<ll, ll> rising[N];
pair<ll, ll> falling[N];

ll pw_p[N], pw_q[N];
ll inv_p[N], inv_q[N];

pair<ll, ll> get_rising(int l, int r, int n) {
    pair<ll, ll> h = rising[r];
    if (l != 0) {
        h.first = (h.first - rising[l - 1].first + M) * inv_p[l] % M;
        h.second = (h.second - rising[l - 1].second + M) * inv_q[l] % M;
    }
    return h;
}

pair<ll, ll> get_falling(int l, int r, int n) {
    pair<ll, ll> h = falling[l];
    if (r != n - 1) {
        h.first = (h.first - falling[r + 1].first + M) * inv_p[n - 1 - r] % M;
        h.second = (h.second - falling[r + 1].second + M) * inv_q[n - 1 - r] % M;
    }
    return h;
}

int main() {
    IOS;
    int INV_P = modPow(P, M - 2);
    int INV_Q = modPow(Q, M - 2);
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 1; i < n; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    rising[0] = {s[0] - 'a' + 1, s[0] - 'a' + 1};
    for (int i = 1; i < n; i++) {
        rising[i] = {(rising[i - 1].first + pw_p[i] * (s[i] - 'a' + 1)) % M, (rising[i - 1].second + pw_q[i] * (s[i] - 'a' + 1)) % M};
    }
    falling[n - 1] = {s[n - 1] - 'a' + 1, s[n - 1] - 'a' + 1};
    for (int i = n - 2; i >= 0; i--) {
        falling[i] = {(falling[i + 1].first + pw_p[n - 1 - i] * (s[i] - 'a' + 1)) % M, (falling[i + 1].second + pw_q[n - 1 - i] * (s[i] - 'a' + 1)) % M};
    }
    for (int i = 0; i < n; i++) {
        int l = 0, r = n - 1, spl = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int L = i - mid, R = i + mid;
            if (L < 0 || R >= n) {
                r = mid - 1;
                continue;
            }
            pair<ll, ll> a = get_rising(L, R, n);
            pair<ll, ll> b = get_falling(L, R, n);
            if (a == b) {
                spl = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        upd(0, n - 1, 0, i, i + spl, 1);
        if (i < n - 1 && s[i] == s[i + 1]) {
            int l = 0, r = n - 1, spl = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                int L = i - mid, R = i + 1 + mid;
                if (L < 0 || R >= n) {
                    r = mid - 1;
                    continue;
                }
                pair<ll, ll> a = get_rising(L, R, n);
                pair<ll, ll> b = get_falling(L, R, n);
                if (a == b) {
                    spl = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            upd(0, n - 1, 0, i + 1, i + 1 + spl, 2);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << query(0, n - 1, 0, i) << " ";
    }

    return 0;
}
