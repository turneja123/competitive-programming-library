//https://ocpc2026w.eolymp.space/en/compete/g6s5o5k4n93719vrc5sak0hi3k/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct Info {
    ll a;
    ll b;
    bool operator < (const Info &x) const {
        return a * x.b < b * x.a;
    }
};

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    set<Info> events;
    map<Info, vector<int>> add, rem;
    for (int i = 0; i < n; i++) {
        int l, r, v;
        cin >> l >> r >> v;
        if (l > x) {
            continue;
        }
        Info st;
        if (r >= x) {
            st = {0, 1};
        } else {
            int g = __gcd(x - r, v);
            st = {(x - r) / g, v / g};
        }
        events.insert(st);
        add[st].push_back(r - l);
        Info en;
        if (l >= x) {
            en = {0, 1};
        } else {
            int g = __gcd(x - l, v);
            en = {(x - l) / g, v / g};
        }
        events.insert(en);
        rem[en].push_back(r - l);
    }
    multiset<int> st;
    int ans = 0;
    for (Info i : events) {
        for (int x : add[i]) {
            st.insert(x);
        }
        if (st.size()) {
            ans = max(ans, *st.begin());
        }
        for (auto x : rem[i]) {
            st.erase(st.find(x));
        }
        if (st.size()) {
            ans = max(ans, *st.begin());
        }
    }
    cout << ans;
    return 0;
}
