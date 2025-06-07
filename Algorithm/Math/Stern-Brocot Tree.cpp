//https://judge.yosupo.jp/problem/rational_approximation
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

bool comp(pair<ll, ll> a, pair<ll, ll> b) {
    __int128 x = (__int128)a.first * b.second;
    __int128 y = (__int128)b.first * a.second;
    return x < y;
}

pair<ll, ll> approx(ll p, ll q, ll n, int side) {
    pair<ll, ll> R = {p, q};
    if (p <= n && q <= n) {
        return R;
    }
    if (comp(R, {1, n})) {
        if (side == 0) {
            return {0, 1};
        } else {
            return {1, n};
        }
    }
    if (comp({n, 1}, R)) {
        if (side == 0) {
            return {n, 1};
        } else {
            return {1, 0};
        }
    }

    pair<ll, ll> lf, rt;
    int dir;
    if (p < q) {
        lf = {0, 1};
        rt = {1, 1};
        dir = 0;
    } else {
        lf = {1, 1};
        rt = {1, 0};
        dir = 1;
    }
    pair<ll, ll> ans = {1, 1};
    while (1) {
        pair<ll, ll> nw = {lf.first + rt.first, lf.second + rt.second};
        if (nw.first > n || nw.second > n) {
            break;
        }
        nw = {-1, -1};
        ll l = 1, r = 1e18, spl = 1;
        while (l <= r) {
            ll mid = (l + r) / 2;
            pair<__int128, __int128> tmp;
            if (dir == 0) {
                tmp = {(__int128)lf.first * mid + rt.first, (__int128)lf.second * mid + rt.second};
            } else {
                tmp = {lf.first + (__int128)mid * rt.first, lf.second + (__int128)mid * rt.second};
            }
            if (tmp.first > n || tmp.second > n) {
                r = mid - 1;
                continue;
            }
            pair<ll, ll> cur;
            cur.first = tmp.first, cur.second = tmp.second;
            if (dir == 0) {
                if (comp(cur, R)) {
                    r = mid - 1;
                    nw = cur;
                    if (side == 0) {
                        ans = cur;
                    }
                } else {
                    l = mid + 1;
                    if (side == 1) {
                        ans = cur;
                    }
                }
            } else {
                if (comp(R, cur)) {
                    r = mid - 1;
                    nw = cur;
                    if (side == 1) {
                        ans = cur;
                    }
                } else {
                    l = mid + 1;
                    if (side == 0) {
                        ans = cur;
                    }
                }
            }
        }
        if (nw.first == -1) {
            break;
        }
        if (dir == 0) {
            rt = {nw.first - lf.first, nw.second - lf.second};
            lf = nw;
        } else {
            lf = {nw.first - rt.first, nw.second - rt.second};
            rt = nw;
        }
        dir ^= 1;
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        ll n, p, q;
        cin >> n >> p >> q;
        ll g = __gcd(p, q);
        p /= g, q /= g;
        pair<ll, ll> l = approx(p, q, n, 0), r = approx(p, q, n, 1);
        cout << l.first << " " << l.second << " " << r.first << " " << r.second << endl;
        vector<pair<long long, char>> v = f(p, q);
        reverse(v.begin(), v.end());
        assert(calc(v) == make_pair(p, q));
    }
    return 0;
}
