//https://codeforces.com/contest/1599/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = double;

const ld INF = 1e18;

struct pt {
    int x;
    int y;
    int i;

};

ld dist(pt a, pt b) {
    double ax = a.x, ay = a.y, bx = b.x, by = b.y;
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}


ld best_line(int k, int left_end, int right_end, vector<pt> &v) {
    if (left_end && right_end) {
        return 0;
    }
    ld ans = INF;
    ans = min(ans, dist(v[k], v.back()) + (left_end ? 0 : dist(v.back(), v[0])));
    ans = min(ans, dist(v[k], v[0]) + (right_end ? 0 : dist(v[0], v.back())));
    return ans;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int n, k;
    cin >> n >> k;
    k--;
    vector<pt> v;
    map<int, int> mpx, mpy;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back({x, y, i});
        mpx[x]++, mpy[y]++;
    }
    if (n == 3) {
        int i = (k == 0 ? 1 : 0);
        int j = (k == 2 ? 1 : 2);

        ld ans = min(dist(v[k], v[i]) + dist(v[i], v[j]), dist(v[k], v[j]) + dist(v[i], v[j]));
        cout << ans;
        return 0;

    }
    sort(v.begin(), v.end(), [&](pt a, pt b) {
         if (a.x != b.x) {
            return a.x < b.x;
         }
         return a.y < b.y;
    });
    int p = -1;
    for (int i = 0; i < n; i++) {
        if (mpx.size() == 2 && mpx[v[i].x] == 1) {
            p = i;
        }
    }
    if (p == -1) {
        for (int i = 0; i < n; i++) {
            if (mpy.size() == 2 && mpy[v[i].y] == 1) {
                p = i;
            }
        }
    }
    if (p == -1) {
        auto cross = [&](pt a, pt b, pt c) {
            return (ll)(b.x - a.x) * (c.y - a.y) - (ll)(b.y - a.y) * (c.x - a.x);
        };
        int x = -1, y = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                int ct = 0;
                for (int k = 0; k < n; k++) {
                    ct += cross(v[i], v[j], v[k]) == 0;
                }
                if (ct == n - 1) {
                    x = i;
                    y = j;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (cross(v[x], v[y], v[i]) != 0) {
                p = i;
                break;
            }
        }
    }
    pt van = v[p];
    v.erase(v.begin() + p);
    if (van.i == k) {
        ld ans = INF;
        for (int i = 0; i < n - 1; i++) {
            ans = min(ans, dist(van, v[i]) + dist(v[i], v[0]) + dist(v[0], v[n - 2]));
            ans = min(ans, dist(van, v[i]) + dist(v[i], v[n - 2]) + dist(v[n - 2], v[0]));
        }
        cout << ans;
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        if (v[i].i == k) {
            k = i;
            break;
        }
    }
    ld ans = INF;
    for (int i = k; i < n - 1; i++) {
        if (i != n - 2) {
            ans = min(ans, dist(v[k], v[i]) + dist(v[i], van) + dist(van, v[i + 1]) + best_line(i + 1, k == 0, i + 1 == n - 2, v));
            ans = min(ans, 2 * dist(v[k], v[0]) + dist(v[k], v[i]) + dist(v[i], van) + dist(van, v[i + 1]) + best_line(i + 1, 1, i + 1 == n - 2, v));
        }
        if (k != 0) {
            ans = min(ans, dist(v[k], v[i]) + dist(v[i], van) + dist(van, v[k - 1]) + best_line(k - 1, k - 1 == 0, i == n - 2, v));
        }
    }
    for (int i = k; i >= 0; i--) {
        if (i != 0) {
            ans = min(ans, dist(v[k], v[i]) + dist(v[i], van) + dist(van, v[i - 1]) + best_line(i - 1, i - 1 == 0, k == n - 2, v));
            ans = min(ans, 2 * dist(v[k], v[n - 2]) + dist(v[k], v[i]) + dist(v[i], van) + dist(van, v[i - 1]) + best_line(i - 1, i - 1 == 0, 1, v));
        }
        if (k != n - 2) {
            ans = min(ans, dist(v[k], v[i]) + dist(v[i], van) + dist(van, v[k + 1]) + best_line(k + 1, i == 0, k + 1 == n - 2, v));
        }
    }
    ans = min(ans, dist(v[k], v[0]) + dist(v[0], v[n - 2]) + dist(v[n - 2], van));
    ans = min(ans, dist(v[k], v[n - 2]) + dist(v[n - 2], v[0]) + dist(v[0], van));
    cout << ans;


    return 0;
}
