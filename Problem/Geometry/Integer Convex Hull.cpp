//https://atcoder.jp/contests/abc202/tasks/abc202_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 80;
const int P = 1e5 + 5;
const ll M = 1e9 + 7;

ll pw[P];
int ct[N][N][N];

struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
    bool operator < (const PT &a) const { return x < a.x || (x == a.x && y < a.y); }
};

vector<PT> p;

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

bool comp_ord(int a, int b) {
    return comp(p[a], p[b]);
}

ll area(PT &a, PT &b, PT &c) {
    return abs(a.x * b.y - a.x * c.y + b.x * c.y - b.x * a.y + c.x * a.y - c.x * b.y);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < P; i++) {
        pw[i] = (i == 0 ? 1 : pw[i - 1] * 2) % M;
    }
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p.push_back({x, y});
    }
    sort(p.begin(), p.end());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int z = 0; z < n; z++) {
                    if (z == i || z == j || z == k || i == j || i == k || j == k) {
                        continue;
                    }
                    ct[i][j][k] += (area(p[z], p[i], p[j]) + area(p[z], p[j], p[k]) + area(p[z], p[i], p[k]) == area(p[i], p[j], p[k]));
                }
            }
        }
    }

    vector<PT> tmp = p;
    ll ans = 0;
    for (int st = 0; st < n; st++) {
        p = tmp;
        p0 = p[st];
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin() + st + 1, ord.end(), comp_ord);
        vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2, 0)));

        dp[st][st][0] = 1;
        for (int I = st + 1; I < n; I++) {
            for (int J = I - 1; J >= st; J--) {
                for (int LAST = st; LAST <= J; LAST++) {
                    for (int m = 0; m < 2; m++) {
                        int i = ord[I], j = ord[J], last = ord[LAST];
                        int ok = (last == j ? 1 : cw(p[last], p[j], p[i]));
                        if (ok) {
                            int add = (last == j ? 0 : area(p[st], p[j], p[i]) % 2);
                            ll mul = (last == j ? 1 : pw[ct[st][j][i]]);

                            dp[j][i][(add + m) % 2] = (dp[j][i][(add + m) % 2] + dp[last][j][m] * mul) % M;
                            if ((add + m) % 2 == 0 && last != j) {
                                ans = (ans + dp[last][j][m] * mul) % M;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}
