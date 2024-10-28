//https://tlx.toki.id/contests/troc-39/problems/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
pair<int, int> p[N];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    uint64_t operator()(const std::tuple<int, int, int>& t) const {
        uint64_t h1 = get<0>(t);
        uint64_t h2 = get<1>(t);
        uint64_t h3 = get<2>(t);
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();


        return splitmix64((h1 << 6) + (h2 << 12) + (h3 << 18) + FIXED_RANDOM);
    }
};

gp_hash_table<tuple<int, int, int>, set<int>, custom_hash> mp;


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
    }
    if (n == 1) {
        cout << 0;
        return 0;
    }
    for (int k = 0; k < 1200000; k++) {
        int i = generator() % n, j = generator() % n;
        if (i == j) {
            continue;
        }
        if (p[i].second > p[j].second) {
            swap(i, j);
        }
        int a, b, c;
        if (p[i].first == p[j].first) {
            a = 1, b = 0, c = -p[i].first;
        } else {
            a = p[j].second - p[i].second, b = p[i].first - p[j].first;
            c = p[j].first * p[i].second - p[i].first * p[j].second;
        }
        int g = __gcd(abs(c), __gcd(abs(a), abs(b)));
        a /= g, b /= g, c /= g;
        mp[make_tuple(a, b, c)].insert(i);
        mp[make_tuple(a, b, c)].insert(j);
    }
    vector<pair<int, tuple<int, int, int>>> lines;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        lines.push_back(make_pair(it->second.size(), it->first));
    }
    sort(lines.begin(), lines.end());
    int ans = 0;
    for (int j = lines.size() - 1, ct = 0; j >= 0 && ct < 2500; j--, ct++) {
        tuple<int, int, int> line = lines[j].second;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            int e = p[i].first * get<0>(line) + p[i].second * get<1>(line) + get<2>(line);
            if (e == 0) {
                cur++;
            }
        }
        ans = max(ans, cur);
    }
    ans = ans >> 8;
    cout << ans;

    return 0;
}
