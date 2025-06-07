//https://atcoder.jp/contests/abc408/tasks/abc408_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

auto f(long long p, long long q) {
    bool right = true;
    vector<pair<long long, char>> res;
    while(q) {
        res.emplace_back(p / q, right ? 'R' : 'L');
        tie(p, q) = make_pair(q, p % q);
        right ^= 1;
    }
    res.back().first--;
    return res;
}

pair<long long, long long> calc(vector<pair<long long, char>> &v) {
    long long a = 1, b = 1;
    for (auto [x, dir] : v) {
        if (dir == 'R') {
            a += x * b;
        } else {
            b += x * a;
        }
    }
    return make_pair(a, b);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        long long g1 = __gcd(b, a), g2 = __gcd(d, c);
        b /= g1, a /= g1, d /= g2, c /= g2;
        auto x1 = f(a, b);
        auto x2 = f(c, d);
        vector<pair<long long, char>> v;
        int i = 0, j = 0;
        while (i < x1.size() && j < x2.size()) {
            if (x1[i].first == 0) {
                i++;
                continue;
            }
            if (x2[j].first == 0) {
                j++;
                continue;
            }
            if (x1[i].second != x2[j].second) {
                break;
            }
            long long mn = min(x1[i].first, x2[j].first);
            v.push_back(make_pair(mn, x1[i].second));
            x1[i].first -= mn;
            x2[j].first -= mn;
        }
        if (i == x1.size()) {
            v.push_back({1, 'R'});
            while (x2[j].first == 0) {
                j++;
            }
            x2[j].first--;
            int f = 0;
            while (j < x2.size()) {
                if (x2[j].first == 0) {
                    j++;
                    continue;
                }
                if (x2[j].second == 'L') {
                    v.push_back(x2[j]);
                    j++;
                } else {
                    f = 1;
                    break;
                }
            }
            if (!f) {
                v.push_back({1, 'L'});
            }
        } else if (j == x2.size()) {
            v.push_back({1, 'L'});
            while (x1[i].first == 0) {
                i++;
            }
            x1[i].first--;
            int f = 0;
            while (i < x1.size()) {
                if (x1[i].first == 0) {
                    i++;
                    continue;
                }
                if (x1[i].second == 'R') {
                    v.push_back(x1[i]);
                    i++;
                } else {
                    f = 1;
                    break;
                }
            }
            if (!f) {
                v.push_back({1, 'R'});
            }

        }
        reverse(v.begin(), v.end());
        pair<long long, long long> ans = calc(v);

        cout << ans.second << endl;
    }
    return 0;
}
