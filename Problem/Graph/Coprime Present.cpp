//https://atcoder.jp/contests/abc195/tasks/abc195_f
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 73;

bitset<N> adj[N];
bitset<N> cur;

long long ans = 0;

void calc(int i, int n) {
    if (i == n) {
        ans++;
        return;
    }
    if ((cur & adj[i]) == cur) {
        cur.set(i);
        calc(i + 1, n);
        cur.reset(i);
    }
    calc(i + 1, n);
}

int main() {
    IOS;
    long long l, r;
    cin >> l >> r;
    vector<long long> a;
    int ct = 0;
    if (l % 2 == 1) {
        for (long long i = l + 1; i <= r; i += 2) {
            a.push_back(i);
            ct++;
        }
        for (long long i = l; i <= r; i += 2) {
            a.push_back(i);
        }
    } else {
        for (long long i = l; i <= r; i += 2) {
            a.push_back(i);
            ct++;
        }
        for (long long i = l + 1; i <= r; i += 2) {
            a.push_back(i);
        }
    }
    for (int i = 0; i < r - l + 1; i++) {
        for (int j = i + 1; j < r - l + 1; j++) {
            if (__gcd(a[i], a[j]) == 1) {
                adj[i].set(j);
                adj[j].set(i);
            }
        }
    }
    calc(ct, r - l + 1);
    for (int i = 0; i < ct; i++) {
        cur.set(i);
        calc(ct, r - l + 1);
        cur.reset(i);
    }
    cout << ans;
    return 0;
}
