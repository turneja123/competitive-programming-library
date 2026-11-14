//https://www.spoj.com/problems/AFS3/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct vec {
    ll dx, dy;
    __int128 s0, s1, s2;
};

ll n;

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

__int128 tri(__int128 x) {
    return x * (x + 1) / 2;
}

vec med(vec a, vec b) {
    return {a.dx + b.dx, a.dy + b.dy, a.s0 + b.s0 + (__int128)a.dx * b.dy, a.s1 + b.s1 + a.dy * b.s0 + a.dx * (tri(b.dy) + (__int128)a.dy * b.dy), a.s2 + b.s2 + 2 * a.dx * b.s0 + (__int128)a.dx * a.dx * b.dy};
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
    vector<vec> st{{1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}};
    while (1) {
        vec a = st.back();
        st.pop_back();
        while (out(x + a.dx, y - a.dy)) {
            __int128 q0 = (__int128)a.dy * (x - 1) + a.s0, q1 = tri(a.dy) * (x - 1) + a.s1, q2 = (__int128)a.dy * (x - 1) * (x - 1) + 2 * (x - 1) * a.s0 + a.s2;
            ans += (q2 + q0) / 2 + y * q0 - q1;
            x += a.dx, y -= a.dy;
        }
        if (y <= v) {
            break;
        }
        vec b = a;
        while (1) {
            a = st.back();
            if (out(x + a.dx, y - a.dy)) {
                break;
            }
            b = a;
            st.pop_back();
        }
        while (1) {
            ll mx = a.dx + b.dx, my = a.dy + b.dy;
            if (out(x + mx, y - my)) {
                a = med(a, b);
                st.push_back(a);
            } else if (cut(x + mx, a.dx, a.dy)) {
                break;
            } else {
                b = med(a, b);
            }
        }
    }
    for (y--; y > 0; y--) {
        ans += tri(n / y) + (__int128)y * (n / y);
    }
    return ans - w * tri(w) - tri(n);
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
