//https://cses.fi/problemset/task/2193/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
};


int main() {
    IOS;
    int n;
    cin >> n;
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i] = PT(x, y);
    }
    //a = i + b / 2 - 1
    ll a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        a += (ll)p[i].x * p[j].y - (ll)p[j].x * p[i].y;
        int dx = abs(p[i].x - p[j].x);
        int dy = abs(p[i].y - p[j].y);
        if (dx == 0) {
            b += dy;
        } else if (dy == 0) {
            b += dx;
        } else {
            b += __gcd(dx, dy);
        }
    }
    ll i = (abs(a) - b + 2) / 2;
    cout << i << " " << b;

    return 0;
}
