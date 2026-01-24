//https://qoj.ac/contest/2828/problem/16117
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 61;
const ll M = 1e9 + 7;

class Basis {
public:
    array<ll, K> basis;
    int sz;

    Basis() {
        sz = 0;
    }

    int insert_vector(ll a) {
        for (int i = K - 1; i >= 0; i--) {
            ll c = a & (1ll << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                basis[i] = a;
                sz++;
                return 1;
            }
            a ^= basis[i];
        }
        return 0;
    }

    int f(ll a) {
        for (int i = K - 1; i >= 0; i--) {
            ll c = a & (1ll << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                return 1;
            }
            a ^= basis[i];
        }
        return 0;
    }
};

Basis b[K];
Basis cur;
ll pw[N];
int fix[K];

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
    }
    int n;
    cin >> n;
    for (int i = 0, j = 0; i < n; i++) {
        ll a;
        cin >> a;
        int f = cur.f(a);
        for (int k = 0; k < j; k++) {
            if (!fix[k]) {
                b[k].insert_vector(a);
            }
        }
        if (f) {
            b[j++] = cur;
        }
        cur.insert_vector(a);

        ll ans = (i + 1 - j) * pw[i - cur.sz] % M;
        for (int k = 0; k < j; k++) {
            ans = (ans + pw[i - (fix[k] ? cur.sz : b[k].sz)]) % M;
            if (b[k].sz == cur.sz) {
                fix[k] = 1;
            }
        }
        ans = (pw[i + 1] - ans + M) % M;
        cout << ans << endl;

    }


    return 0;
}
