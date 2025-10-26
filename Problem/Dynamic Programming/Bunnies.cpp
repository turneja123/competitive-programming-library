//https://www.spoj.com/problems/BUNNIES/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const ll INF = 1e18;

int a[N];

struct CHT {
  vector<ll> m, b;
  int ptr = 0;

  bool bad(int l1, int l2, int l3) {
    return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query min),(slope inc+query max)
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
    while(ptr < m.size() - 1 && f(ptr + 1, x) < f(ptr, x)) ptr++;
    return f(ptr, x);
  }

  ll bs(int l, int r, ll x) {
    int mid = (l + r) / 2;
    if(mid + 1 < m.size() && f(mid + 1, x) < f(mid, x)) return bs(mid + 1, r, x); // > for max
    if(mid - 1 >= 0 && f(mid - 1, x) < f(mid, x)) return bs(l, mid - 1, x); // > for max
    return f(mid, x);
  }
};

CHT cht[N];
ll dp[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        reverse(a, a + n);
        for (int i = 0; i < n; i++) {
            dp[i][1] = (ll)(i + 1) * a[i];
            for (int j = 2; j <= min(i + 1, k); j++) {
                dp[i][j] = (ll)(i + 1) * a[i] + cht[j - 1].bs(0, cht[j - 1].m.size(), a[i]);
            }
            for (int j = 1; j <= min(i + 1, k); j++) {
                cht[j].add(-(i + 1), dp[i][j]);
            }
        }
        ll ans = INF;
        for (int i = k - 1; i < n; i++) {
            ans = min(ans, dp[i][k]);
        }
        for (int i = 0; i <= k; i++) {
            cht[i].m.clear();
            cht[i].b.clear();
            cht[i].ptr = 0;
        }
        cout << ans << endl;
    }
    return 0;
}
