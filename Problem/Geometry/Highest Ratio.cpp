//https://atcoder.jp/contests/abc341/tasks/abc341_g
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
  vector<ll> m, b, i;
  int ptr = 0;

  bool bad(int z, int j, int i) {
    return (__int128)(b[j] - b[i]) * (m[z] - m[i]) <= (__int128)(b[z] - b[i]) * (m[j] - m[i]);
  }

  void add(ll _m, ll _b, int _i) {
    m.push_back(_m);
    b.push_back(_b);
    i.push_back(_i);
    int s = m.size();
    while(s >= 3 && bad(s - 3, s - 2, s - 1)) {
      s--;
      m.erase(m.end() - 2);
      b.erase(b.end() - 2);
      i.erase(i.end() - 2);
    }
  }
};

ll a[N];
ll p[N];


int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        p[i] = (i == 0 ? 0 : p[i - 1]) + a[i];
    }
    vector<ld> v;
    CHT cht;
    cht.add(n, p[n - 1], n);
    for (int i = n - 1; i >= 0; i--) {
        cht.add(i, (i == 0 ? 0 : p[i - 1]), i);
        int j = cht.i[cht.i.size() - 2];
        ld ans = (ld)(p[j - 1] - (i == 0 ? 0 : p[i - 1])) / (ld)(j - i);
        v.push_back(ans);
    }
    reverse(v.begin(), v.end());
    for (ld u : v) {
        cout << u << endl;
    }

    return 0;
}
