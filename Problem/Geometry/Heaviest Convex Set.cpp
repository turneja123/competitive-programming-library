//https://ocpc2026w.eolymp.space/en/compete/g6s5o5k4n93719vrc5sak0hi3k/problem/8
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e4 + 5;
const int K = 22;
const ll INF = 1e18;

struct PT {
    ll x, y, wt;
    PT() { x = 0, y = 0, wt = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT(ll x, ll y, ll wt) : x(x), y(y), wt(wt) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
    bool operator < (const PT &a) const { return x < a.x || (x == a.x && y < a.y); }
};

int orientation(PT &p1, PT &p2, PT &p3) {
    long long cross = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    if (cross > 0) return 1; // ccw
    if (cross < 0) return -1; // cw
    return 0; // collinear
}

bool cw(PT &p1, PT &p2, PT &p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x) < 0;
}

PT p0;

int half(PT &a) {
    return a.y >= p0.y;
}

ll distsq(PT &a, PT &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool comp(PT &a, PT &b) {
    int ha = half(a), hb = half(b);
    if (ha != hb) {
        return ha > hb;
    }
    int o = orientation(p0, a, b);
    if (o == -1) {
        return 1;
    }
    if (o == 1) {
        return 0;
    }
    return distsq(p0, a) < distsq(p0, b);
}


ll dp[K][K][N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        p[i] = {x, y, w};
    }
    sort(p.begin(), p.end());

    vector<PT> tmp = p;
    ll ans = -INF;
    for (int j = 0; j < K; j++) {
        for (int z = 0; z < K; z++) {
            for (int i = 0; i < n; i++) {
                dp[j][z][i] = -INF;
            }
        }
    }
    for (int st = 0; st <= k; st++) {
        p = tmp;
        p0 = p[st];
        sort(p.begin() + st + 1, p.end(), comp);

        dp[0][st][st] = p[st].wt;
        for (int i = st + 1; i < n; i++) {
            for (int j = i - 1; j >= max(st, i - k - 1); j--) {
                int add = i - j - 1;
                for (int d = st; d <= k - add; d++) {
                    for (int last = 0; last <= d + 1; last++) {
                        if (dp[last][d][j] == -INF) {
                            continue;
                        }
                        int ok = (last == 0 ? 1 : cw(p[j - last], p[j], p[i]));
                        if (ok) {
                            dp[i - j][d + add][i] = max(dp[i - j][d + add][i], dp[last][d][j] + p[i].wt);
                        }
                    }
                }
            }
        }
        for (int i = st + 1; i < n; i++) {
            for (int j = 0; j < K; j++) {
                for (int z = st; z <= k; z++) {
                    if (dp[j][z][i] == -INF) {
                        continue;
                    }
                    int d = z + n - i - 1;
                    if (d <= k && n - d >= 3) {
                        ans = max(ans, dp[j][z][i]);
                    }
                    dp[j][z][i] = -INF;
                }
            }
        }
    }
    if (ans == -INF) {
        cout << "impossible";
    } else {
        cout << ans;
    }
    return 0;
}
