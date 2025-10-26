//https://cses.fi/problemset/task/2087/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

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
    while(ptr < m.size() - 1 && f(ptr + 1, x) > f(ptr, x)) ptr++; // > for max
    return f(ptr, x);
  }

  ll bs(int l, int r, ll x) {
    int mid = (l + r) / 2;
    if(mid + 1 < m.size() && f(mid + 1, x) < f(mid, x)) return bs(mid + 1, r, x); // > for max
    if(mid - 1 >= 0 && f(mid - 1, x) < f(mid, x)) return bs(l, mid - 1, x); // > for max
    return f(mid, x);
  }
};

CHT cht_f[N], cht_g[N];
ll a[N];
ll pref[N];
ll pref_rising[N];
ll pref_falling[N];

ll f[N][N], g[N][N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
        pref_rising[i] = pref_rising[i - 1] + a[i] * i;
        pref_falling[i] = pref_falling[i - 1] + a[i] * (n - i + 1);
    }
    cht_g[0].add(0, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j > 0; j--) {
            if (cht_g[j - 1].m.size()) {
                f[i][j] = -cht_g[j - 1].query(i - 1 - n) + pref_falling[i - 1] - pref[i - 1] * (n - i + 1);
            }
            if (cht_g[j - 1].m.size()) {
                cht_f[j].add(i, -f[i][j] + pref_rising[i] - pref[i] * i);
            }
            if (cht_f[j].m.size()) {
                g[i][j] = -cht_f[j].query(pref[i]) + pref_rising[i];
            }


            if (cht_f[j].m.size()) {
                cht_g[j].add(pref[i], -g[i][j] + pref_falling[i]);
            }
        }

    }
    cout << g[n][k];


    return 0;
}
