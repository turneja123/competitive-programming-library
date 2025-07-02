//https://ocpc2025s.eolymp.space/en/compete/1kvhss06dl7d13loo53cn0nk1k/problem/6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long M = 998244353;

struct trygub_num {
  // maintains a big number in the given base b
  const int K = 30;
  const int b = 2;
  const int base = 1 << K; // for base b use b^K base to make the computation faster
  map<int, long long> digs; // tracks digits in (-base, base)
  void clear() {
    digs.clear();
  }
  // add x * b^e to this number: x, e both can be negative
  // O(log_b(n)^2 / K) amortized
  void add(long long x, int e) {
    if (e >= 0) {
      x = x * (1 << (e % K)); // x * b ^ (e % K)
      e /= K;
    }
    else {
      int k = (e % K + K) % K;
      x = x * (1 << k);
      e = e / K - (e % K != 0);
    }
    digs[e] += x;
    long long t;
    do {
      t = digs[e] / base;
      digs[e + 1] += t;
      digs[e] -= t * base;
      if (digs[e] == 0) {
        digs.erase(e);
      }
      e++;
    } while(t);

    if(digs[e] == 0) {
      digs.erase(e);
    }
  }

  // assuming this number is >= 0, find the kth digit in the base b
  int kth_digit(int k) {
    int cur_k = k / K;
    auto it = digs.lower_bound(cur_k);
    int ans = it == digs.end() || it->first > cur_k ? 0 : it->second;
    if(it != digs.begin() && prev(it)->second < 0) {
      ans--;
    }
    ans = (ans + base) % base;
    return (ans >> (k % K)) & 1; // (k % K) th digit of ans in base b
  }

  int sign() { // if the number is >= 0
    if (digs.empty()) return 1; // number = 0
    auto it = prev(digs.end());
    return it -> second > 0;
  }

};

int a[N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int main() {
    IOS;
    int n;
    cin >> n;

    int g = -1000000000;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        g = max(g, a[i]);
    }
    if (g < 0) {
        cout << 0;
        return 0;
    }
    trygub_num cur, d;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= 0) {
            cur.add(1, a[i]);
            d.add(1, a[i]);
        } else {
            cur.add(-1, -a[i]);
            d.add(-1, -a[i]);
        }

        if (cur.sign() == 0) {
            for (auto [e, x] : cur.digs) {
                d.add(-x, e * 30);
            }
            cur.clear();
        }
        if (d.sign() == 1) {
            for (auto [e, x] : d.digs) {
                ans = (ans + (x + M * M) % M * modPow(2, e * 30)) % M;
            }
            d.clear();
        }
    }
    cout << ans;

    return 0;
}
