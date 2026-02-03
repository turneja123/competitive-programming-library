//https://ocpc2026w.eolymp.space/en/compete/mi9vnankul3g72sfvkn0heloj8/problem/12
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll N = 1e12;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

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

ll conv(string s) {
    ll ans = 0;
    vector<int> mp(28, -1);
    int j = 1;
    for (int i = 0, j = 1; i < s.size(); i++) {
        int d = s[i] - 'a';
        if (mp[d] == -1) {
            mp[d] = j++;
        }
        if (mp[d] == 10) {
            mp[d] = 0;
        }
        if (mp[d] > 10) {
            return -1;
        }
        ans = ans * 10 + mp[d];
    }
    return ans;
}

int main() {
    IOS;
    gp_hash_table<ll, ll, custom_hash> mp;
    for (ll i = 1; i * i < N; i++) {
        ll j = i * i;
        vector<int> id(10, -1);
        string s = "";
        while (j > 0) {
            s += 'a' + (j % 10);
            j /= 10;
        }
        reverse(s.begin(), s.end());
        ll ans = conv(s);
        mp[ans] = i * i;
    }
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        ll x = conv(s);
        auto it = mp.find(x);
        if (it == mp.end()) {
            cout << -1 << endl;
        } else {
            cout << it->second << endl;
        }
    }

    return 0;
}
