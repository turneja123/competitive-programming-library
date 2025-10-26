//https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-1/problems/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

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

ll s2(ll n) {
    return n * (n + 1) / 2;
}

ll s3(ll n) {
    return n * (n + 1) * (n + 2) / 6;
}

int main() {
    IOS;
    freopen("1.txt", "r", stdin);
    freopen("2.txt", "w", stdout);

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;
        gp_hash_table<int, int, custom_hash> mp;
        ll ans = s3(n);
        int a = 0;
        mp[0]++;
        for (int i = 0; i < n; i++) {
            int b;
            cin >> b;
            a ^= b;
            mp[a]++;
        }
        for (auto [_, m] : mp) {
            ans -= s2(m - 1) + s3(m - 2);
        }


        cout << "Case #" << tt << ": " << ans << endl;
    }

    return 0;
}
