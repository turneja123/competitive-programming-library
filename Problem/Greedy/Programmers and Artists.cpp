//https://cses.fi/problemset/task/2426/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n, a, b;
    cin >> a >> b >> n;
    vector<pair<int, int>> v(n);
    vector<ll> suf(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v[i] = {x, y};
    }
    sort(v.begin(), v.end(), [&](auto a, auto b) {return a.first - a.second > b.first - b.second;});
    ll s = 0;
    priority_queue<ll> pq;
    for (int i = n - 1; i >= 0; i--) {
        s += v[i].second;
        pq.push(-v[i].second);
        if (pq.size() > b) {
            s += pq.top();
            pq.pop();
        }
        suf[i] = s;
    }
    s = 0;
    while (pq.size()) {
        pq.pop();
    }
    ll ans = (a == 0 ? suf[0] : 0);
    for (int i = 0; i < n - b; i++) {
        s += v[i].first;
        pq.push(-v[i].first);
        if (pq.size() > a) {
            s += pq.top();
            pq.pop();
        }
        if (i + 1 >= a) {
            ans = max(ans, s + (i == n - 1 ? 0 : suf[i + 1]));
        }
    }
    cout << ans;

    return 0;
}
