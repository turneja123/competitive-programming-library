//https://eolymp.com/en/problems/12323
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll INF = 1e18;

ll a[N];
int k[N];
ll x[N];
ll suf[N];

struct CHT {
  vector<ll> m, b;
  int ptr = 0;

  bool bad(int l1, int l2, int l3) {
    return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query min),(slope inc+query max)
    //return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  > 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query max), (slope inc+query min)
  }

  void add(ll _m, ll _b) {
    m.push_back(_m);
    b.push_back(_b);
    int s = m.size();
    while(s >= 3 && bad(s - 3, s - 2, s - 1)) {
      s--;
      m.erase(m.end() - 2);
      b.erase(b.end() - 2);
    }
  }

  ll f(int i, ll x) {
    return m[i] * x + b[i];
  }

  //(slope dec+query min), (slope inc+query max) -> x increasing
  //(slope dec+query max), (slope inc+query min) -> x decreasing
  ll query(ll x) {
    if(ptr >= m.size()) ptr = m.size() - 1;
    while(ptr < m.size() - 1 && f(ptr + 1, x) < f(ptr, x)) ptr++; // > for max
    return f(ptr, x);
  }

  ll bs(int l, int r, ll x) {
    int mid = (l + r) / 2;
    if(mid + 1 < m.size() && f(mid + 1, x) > f(mid, x)) return bs(mid + 1, r, x); // > for max
    if(mid - 1 >= 0 && f(mid - 1, x) > f(mid, x)) return bs(l, mid - 1, x); // > for max
    return f(mid, x);
  }
};


struct Node {
    CHT cht;
    vector<pair<ll, ll>> lines;
    ll mx;
    Node() {}
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.mx = max(left.mx, right.mx);
    for (auto [m, b] : left.lines) {
        node.cht.add(m, b);
        node.lines.push_back({m, b});
    }
    for (auto [m, b] : right.lines) {
        node.cht.add(m, b);
        node.lines.push_back({m, b});
    }
    return node;
}

ll query(int l, int r, int lq, int rq, ll x, int node) {
    if (l > rq || r < lq) {
        return -INF;
    }

    if (lq <= l && rq >= r) {
        return segtree[node].cht.bs(0, segtree[node].cht.m.size() - 1, x);
    }

    int mid = (l + r) / 2;
    return max(query(l, mid, lq, rq, x, 2 * node + 1), query(mid + 1, r, lq, rq, x, 2 * node + 2));
}

ll query_suf(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return -INF;
    }

    if (lq <= l && rq >= r) {
        return segtree[node].mx;
    }

    int mid = (l + r) / 2;
    return max(query_suf(l, mid, lq, rq, 2 * node + 1), query_suf(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node();
        segtree[node].cht.add(-(n - 1 - l), suf[l]);
        segtree[node].lines.push_back({-(n - 1 - l), suf[l]});
        segtree[node].mx = suf[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for (int i = n - 2; i >= 0; i--) {
        suf[i] = suf[i + 1] - a[i + 1];
    }
    build(0, n - 1, 0, n);
    ll ans = -INF;
    for (int i = 0; i < n; i++) {
        ll cur = -suf[i] + a[i];
        int l = i, r = min(n - 1, i + k[i] - 1);
        if (l <= r) {
            ans = max(ans, cur + (n - i) * x[i] + query(0, n - 1, l, r, x[i], 0));
        }

        l = r + 1, r = n - 1;
        if (l <= r) {
            ans = max(ans, cur + k[i] * x[i] + query_suf(0, n - 1, l, r, 0));
        }
    }
    cout << ans;
    return 0;
}
