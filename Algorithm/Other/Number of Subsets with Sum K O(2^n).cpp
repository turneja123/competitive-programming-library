//solution for https://cses.fi/problemset/task/1628/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
gp_hash_table <int, ll, custom_hash> mp;
int main() {
    IOS;
    int n; ll x;
    cin >> n >> x;
    int na = n / 2 + n % 2;
    int nb = n / 2;
    ll a[na] = { };
    ll b[nb] = { };
    for (int i = 0; i < na; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < nb; i++) {
        cin >> b[i];
    }
    int pwa = 1 << na;
    int pwb = 1 << nb;
    for (int i = 0; i < pwa; i++) {
        ll cur = 0;
        for (int j = 0; j < na; j++) {
            if (i & (1 << j)) cur += a[j];
        }
        if (cur <= x) {
            auto it = mp.find(cur);
            if (it == mp.end()) {
                mp.insert({cur, 1});
            } else {
                it->second++;
            }
        }
    }
    ll sol = 0;
    for (int i = 0; i < pwb; i++) {
        ll cur = 0;
        for (int j = 0; j < nb; j++) {
            if (i & (1 << j)) cur += b[j]; {
            }
        }
        if (cur <= x) {
            auto it = mp.find(x - cur);
            if (it != mp.end()) {
                sol += it->second;
            }
        }
    }
    cout << sol;
    return 0;
}
