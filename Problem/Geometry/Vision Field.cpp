//https://www.spoj.com/problems/VISION/
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
    return (m[l2] - m[l1]) * (b[l3] - b[l1]) >= (m[l3] - m[l1]) * (b[l2] - b[l1]);
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
};

ll floor(ll a, ll b) {
    if (a >= 0) {
        return a / b;
    }
    return -((-a + b - 1) / b);
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<ll> ans;
    CHT cht;
    for (int i = 1; i <= n; i++) {
        ll a;
        cin >> a;
        cht.add(i, a);
        ll cur = 1;
        if (cht.m.size() >= 2) {
            ll x1 = cht.m[cht.m.size() - 2];
            ll y1 = cht.b[cht.b.size() - 2];
            cur = max(cur, floor(i * y1 - x1 * a, i - x1) + 1);
        }

        ans.push_back(cur);
    }
    sort(ans.begin(), ans.end());
    int q;
    cin >> q;
    while (q--) {
        ll a;
        cin >> a;
        cout << upper_bound(ans.begin(), ans.end(), a) - ans.begin() << endl;
    }

  return 0;
}
