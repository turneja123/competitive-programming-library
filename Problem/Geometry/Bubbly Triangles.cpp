//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136691
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;

int ctx[N];
int cty[N];

set<long long> st;

long long get(int x, int y) {
    return (long long)N * x + y;
}

long long k(int x, int y) {
    int dx = abs(x), dy = abs(y);
    int g = __gcd(dx, dy);
    dx /= g, dy /= g;
    long long coef = (long long)N * dx + dy;
    if ((x > 0 && y > 0) || (x < 0 && y < 0)) {
        return coef;
    }
    return -coef;
}

int main() {
    IOS;
    int n;
    cin >> n;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 2) {
            st.erase(st.find(get(x, y)));
            ctx[x]--;
            cty[y]--;
        }
        map<long long, int> mp;
        for (auto it = st.begin(); it != st.end(); ++it) {
            int x0 = (long long)*it / N, y0 = (long long)*it % N;
            int dx = x - x0, dy = y - y0;
            if (dx == 0 || dy == 0) {
                continue;
            }
            mp[k(dx, dy)]++;
        }
        long long add = 0;
        for (auto it = st.begin(); it != st.end(); ++it) {
            int x0 = (long long)*it / N, y0 = (long long)*it % N;
            int dx = x - x0, dy = y - y0;
            if (dx == 0 || dy == 0) {
                continue;
            }
            add += st.size() - mp[k(dx, dy)] - ctx[x] - cty[y] - ctx[x0] - cty[y0] + 2;
            if (st.find((long long)N * x + y0) != st.end()) {
                add++;
            }
            if (st.find((long long)N * x0 + y) != st.end()) {
                add++;
            }
        }
        add /= 2;
        if (t == 1) {
            ans += add;
            ctx[x]++;
            cty[y]++;
            st.insert(get(x, y));
        } else {
            ans -= add;
        }
        cout << ans << endl;
    }

    return 0;
}
