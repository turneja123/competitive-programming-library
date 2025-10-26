//https://codeforces.com/contest/1083/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct CHT {
  vector<ll> m, b;
  int ptr = 0;

  bool bad(int l1, int l2, int l3) {
    //return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query min),(slope inc+query max)
    return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  > 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query max), (slope inc+query min)
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
    while(ptr < m.size() - 1 && f(ptr + 1, x) > f(ptr, x)) ptr++; // > for max
    return f(ptr, x);
  }

  ll bs(int l, int r, ll x) {
    int mid = (l + r) / 2;
    if(mid + 1 < m.size() && f(mid + 1, x) > f(mid, x)) return bs(mid + 1, r, x); // > for max
    if(mid - 1 >= 0 && f(mid - 1, x) > f(mid, x)) return bs(l, mid - 1, x); // > for max
    return f(mid, x);
  }
};

int main() {
    IOS;
    int n;
    cin >> n;
    vector<tuple<int, int, ll>> v(n);
    for (int i = 0; i < n; i++) {
        int x, y; ll a;
        cin >> x >> y >> a;
        v[i] = make_tuple(x, y, a);
    }
    sort(v.begin(), v.end());
    CHT cht;
    cht.add(0, 0);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        auto [x, y, a] = v[i];
        //ll dp = (ll)x * y + cht.bs(0, cht.m.size(), y) - a;
        ll dp = (ll)x * y + cht.query(y) - a;
        ans = max(ans, dp);
        cht.add(-x, dp);
    }
    cout << ans;

    return 0;
}
