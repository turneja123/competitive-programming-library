//https://dmoj.ca/problem/ccoprep3p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

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
    while(ptr < m.size() - 1 && f(ptr + 1, x) < f(ptr, x)) ptr++; // > for max
    return f(ptr, x);
  }
};


ll a[N];
ll dp[N];
ll pref[N];


int main() {
    IOS;
    int n; ll L;
    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    CHT cht;
    for (int i = 0; i <= n; i++) {
        pref[i] = a[i];
        if (i != 0) {
            pref[i] += pref[i - 1];
            dp[i] = cht.query(pref[i] + i) + (pref[i] + i - 2 * L) * (pref[i] + i) + L * L;
        }
        cht.add(-2 * (pref[i] + i + 1), (pref[i] + i + 1 + 2 * L) * (pref[i] + i + 1) + dp[i]);
    }
    cout << dp[n];

    return 0;
}
