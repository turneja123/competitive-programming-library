//https://codeforces.com/contest/2159/problem/D1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 4e5 + 5;
const ll INF = 2e18;

struct CHT {
  vector<ld> m; vector<ll> b; vector<int> d;
  int ptr = 0;

  bool bad(int l1, int l2, int l3) {
    return (ld)(b[l3] - b[l1]) * (m[l1] - m[l2])  <= (ld)(b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query min),(slope inc+query max)
  }

  void add(ld _m, ll _b, int _d) {
    m.push_back(_m);
    b.push_back(_b);
    d.push_back(_d);
    int s = m.size();
    while(s >= 3 && bad(s - 3, s - 2, s - 1)) {
      s--;
      m.erase(m.end() - 2);
      b.erase(b.end() - 2);
      d.erase(d.end() - 2);
    }
  }

  ld f(int i, ll x) {
    return m[i] * (ld)x + (ld)b[i];
  }

  //(slope dec+query min), (slope inc+query max) -> x increasing
  //(slope dec+query max), (slope inc+query min) -> x decreasing

  int bs(int l, int r, ll x) {
    int mid = (l + r) / 2;
    if(mid + 1 < m.size() && f(mid + 1, x) < f(mid, x)) return bs(mid + 1, r, x); // > for max
    if(mid - 1 >= 0 && f(mid - 1, x) < f(mid, x)) return bs(l, mid - 1, x); // > for max
    return d[mid];
  }
};

ll a[N];
ll mn[N];
ll dp[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        ll cur = INF;
        for (int i = n; i >= 0; i--) {
            mn[i] = cur;
            cur = min(cur, a[i]);
        }
        CHT cht;
        cht.add((ld)1.0 / (ld)mn[0], 0, 0);
        for (int i = 1; i <= n; i++) {
            int j = cht.bs(0, cht.d.size() - 1, a[i]);
            dp[i] = dp[j] + (a[i] + mn[j] - 1) / mn[j];
            cht.add((ld)1.0 / mn[i], dp[i], i);
        }
        cout << dp[n] << endl;
    }




    return 0;
}
