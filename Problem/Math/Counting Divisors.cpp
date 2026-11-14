//https://www.spoj.com/problems/DIVCNT1/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

ll n;

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

bool out(ll x, ll y) {
    return (__int128)x * y > n;
}

bool cut(ll x, ll dx, ll dy) {
    return (__int128)x * x * dy >= (__int128)n * dx;
}

__int128 calc() {
    ll w = sqrtl(n), v = cbrtl(n);
    ll x = n / w, y = w + 1;
    __int128 ans = 0;
    vector<pair<ll, ll>> st{{1, 0}, {1, 1}};
    while (1) {
        ll dx1 = st.back().first, dy1 = st.back().second;
        st.pop_back();
        while (out(x + dx1, y - dy1)) {
            ans += x * dy1 + (dy1 + 1) * (dx1 - 1) / 2;
            x += dx1, y -= dy1;
        }
        if (y <= v) {
            break;
        }
        ll dx2 = dx1, dy2 = dy1;
        while (1) {
            dx1 = st.back().first, dy1 = st.back().second;
            if (out(x + dx1, y - dy1)) {
                break;
            }
            dx2 = dx1, dy2 = dy1;
            st.pop_back();
        }
        while (1) {
            ll mx = dx1 + dx2, my = dy1 + dy2;
            if (out(x + mx, y - my)) {
                st.push_back({mx, my});
                dx1 = mx, dy1 = my;
            } else if (cut(x + mx, dx1, dy1)) {
                break;
            } else {
                dx2 = mx, dy2 = my;
            }
        }
    }
    for (y--; y > 0; y--) {
        ans += n / y;
    }
    return 2 * ans - (__int128)w * w;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        print(calc());
        putchar('\n');
    }

    return 0;
}
