//https://codeforces.com/contest/1146/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 305;

struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
    bool operator < (const PT &a) const { return x < a.x || (x == a.x && y < a.y); }
    ll norm2() { return x * x + y * y; }
};

ll cross(PT &a, PT &b) {
    return a.x * b.y - a.y * b.x;
}

int half(PT &p) {
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

ll dp[N][N][6];


int main() {
    IOS;
    int n;
    cin >> n;
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i] = {x, y};
    }
    vector<pair<int, int>> vecs;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                vecs.push_back({i, j});
            }
        }
    }
    sort(vecs.begin(), vecs.end(), [&](pair<int, int> x, pair<int, int> y) {
        PT a = p[x.second] - p[x.first], b = p[y.second] - p[y.first];
        return make_tuple(half(a), 0, a.norm2()) < make_tuple(half(b), cross(a, b), b.norm2());
    });
    for (int i = 0; i < n; i++) {
        dp[i][i][0] = 1;
    }
    for (auto [u, v] : vecs) {
        for (int i = 0; i < 5; i++) {
            for (int s = 0; s < n; s++) {
                dp[s][v][i + 1] += dp[s][u][i];
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dp[i][i][5];
    }
    cout << ans;

    return 0;
}
