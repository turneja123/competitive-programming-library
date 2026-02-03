//https://ocpc2026w.eolymp.space/en/compete/9umgdpquih09n7lf096jj2cqvk/problem/5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 2e5 + 5;

struct CHT {
  vector<ld> m, b;
  int ptr = 0;

  bool bad(int l1, int l2, int l3) {
    return (b[l3] - b[l1]) * (m[l1] - m[l2])  <= (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query min),(slope inc+query max)
    return (b[l3] - b[l1]) * (m[l1] - m[l2])  > (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query max), (slope inc+query min)
  }

  void add(ld _m, ld _b) {
    m.push_back(_m);
    b.push_back(_b);
    int s = m.size();
    while(s >= 3 && bad(s - 3, s - 2, s - 1)) {
      s--;
      m.erase(m.end() - 2);
      b.erase(b.end() - 2);
    }
  }

  ld f(int i, ld x) {
    return m[i] * x + b[i];
  }

  ld bs(int l, int r, ld x) {
    int mid = (l + r) / 2;
    if(mid + 1 < m.size() && f(mid + 1, x) < f(mid, x)) return bs(mid + 1, r, x); // > for max
    if(mid - 1 >= 0 && f(mid - 1, x) < f(mid, x)) return bs(l, mid - 1, x); // > for max
    return f(mid, x);
  }
};

vector<int> adj[N];
ld dp[N];

int main() {
    IOS;
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> compr;
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        compr.push_back(u);
        compr.push_back(v);
    }
    compr.push_back(0);
    compr.push_back(l);
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    int k = compr.size();
    for (auto [l, r] : edges) {
        l = lower_bound(compr.begin(), compr.end(), l) - compr.begin();
        r = lower_bound(compr.begin(), compr.end(), r) - compr.begin();
        adj[l].push_back(r);
    }
    vector<pair<ld, ld>> lines;
    for (int i = 0; i < m; i++) {
        ld c, x;
        cin >> c >> x;
        lines.push_back({1.0 / x, c});
    }
    sort(lines.begin(), lines.end());
    reverse(lines.begin(), lines.end());
    CHT cht;
    for (int i = 0; i < lines.size(); i++) {
        auto [m, b] = lines[i];
        cht.add(m, b);
    }
    for (int i = k - 2; i >= 0; i--) {
        dp[i] = dp[i + 1] + compr[i + 1] - compr[i];
        for (int j : adj[i]) {
            dp[i] = min(dp[i], cht.bs(0, cht.m.size() - 1, dp[j]));
        }
    }
    cout << fixed;
    cout << setprecision(9);
    cout << dp[0];
    return 0;
}
