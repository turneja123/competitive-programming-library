//https://codeforces.com/contest/1202/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;


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
pair<long long, long long> calc(string s) {
    int n = s.size();
    long long p = 0, q = 0;
    long long p_pow = 1, q_pow = 1;
    for (int i = 0; i < n; i++) {
        p = (p + p_pow * (s[i] - 'a' + 1)) % M;
        q = (q + q_pow * (s[i] - 'a' + 1)) % M;
        p_pow = (p_pow * P) % M;
        q_pow = (q_pow * Q) % M;
    }
    return make_pair(p, q);
}

pair<ll, ll> pref[N];
ll l[N], r[N];
ll inv_p[N], inv_q[N];
gp_hash_table<ll, int, custom_hash> mp[N];

pair<ll, ll> get_rising(int l, int r, int n) {
    pair<ll, ll> h = pref[r];
    if (l != 0) {
        h.first = (h.first - pref[l - 1].first + M) * inv_p[l] % M;
        h.second = (h.second - pref[l - 1].second + M) * inv_q[l] % M;
    }
    return h;
}

int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size(), m;
    cin >> m;
    vector<int> sizes;
    for (int i = 0; i < m; i++) {
        string a;
        cin >> a;
        auto h = calc(a);

        mp[a.size()][h.first + (h.second << 32)]++;
        sizes.push_back(a.size());
    }
    long long p = 0, q = 0;
    long long p_pow = 1, q_pow = 1;
    for (int i = 0; i < n; i++) {
        p = (p + p_pow * (s[i] - 'a' + 1)) % M;
        q = (q + q_pow * (s[i] - 'a' + 1)) % M;
        p_pow = (p_pow * P) % M;
        q_pow = (q_pow * Q) % M;
        pref[i] = {p, q};

        inv_p[i] = (i == 0 ? 1 : inv_p[i - 1] * INV_P % M);
        inv_q[i] = (i == 0 ? 1 : inv_q[i - 1] * INV_Q % M);
    }
    sort(sizes.begin(), sizes.end());
    sizes.erase(unique(sizes.begin(), sizes.end()), sizes.end());
    for (int i = 0; i < n; i++) {
        for (int s : sizes) {
            if (i - s + 1 < 0) {
                break;
            }
            pair<ll, ll> h = get_rising(i - s + 1, i, n);
            ll z = h.first + (h.second << 32);

            auto it = mp[s].find(z);
            if (it != mp[s].end()) {
                l[i] += it->second;
            }
        }
        for (int s : sizes) {
            if (i + s - 1 >= n) {
                break;
            }
            pair<ll, ll> h = get_rising(i, i + s - 1, n);
            ll z = h.first + (h.second << 32);

            auto it = mp[s].find(z);
            if (it != mp[s].end()) {
                r[i] += it->second;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans += l[i] * r[i + 1];
    }
    cout << ans;

    return 0;
}
