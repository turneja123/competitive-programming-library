//https://www.spoj.com/problems/KMEDIAL/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int pref[N];

int l_dup[2 * N], r_dup[2 * N], dup[2 * N];

ll calc(int l, int r) {
    if (l >= r) {
        return 0;
    }
    int mid = (l + r) / 2;
    int s = 0;
    vector<pair<int, int>> L, R;
    for (int i = mid; i >= l; i--) {
        L.push_back({pref[i] - s, pref[i] + s});
        l_dup[pref[i] - s + N]++;
        r_dup[pref[i] + s + N]++;
        if (s == 0) {
            dup[pref[i] + N]++;
        }
        s += a[i] == 0;
    }
    ll ans = 0;
    s = 0;
    for (int i = mid + 1; i <= r; i++) {
        s += a[i] == 0;
        R.push_back({pref[i] - s, pref[i] + s});
        ans -= l_dup[pref[i] + s + N];
        ans -= r_dup[pref[i] - s + N];
        if (s == 0) {
            ans += dup[pref[i] + N];
        }
    }
    vector<tuple<int, int, int>> events;
    for (auto [l, r] : L) {
        events.push_back({l, 0, r});
    }
    for (auto [l, r] : R) {
        events.push_back({l, 1, r});
    }
    sort(events.begin(), events.end());
    priority_queue<int> pqa, pqb;
    int cta = 0, ctb = 0;
    for (auto [l, t, r] : events) {
        while (cta && -pqa.top() < l) {
            pqa.pop();
            cta--;
        }
        while (ctb && -pqb.top() < l) {
            pqb.pop();
            ctb--;
        }

        if (t == 1) {
            ans += cta;
            ctb++;
            pqb.push(-r);
        } else {
            ans += ctb;
            cta++;
            pqa.push(-r);
        }
    }
    s = 0;
    for (int i = mid; i >= l; i--) {
        l_dup[pref[i] - s + N]--;
        r_dup[pref[i] + s + N]--;
        if (s == 0) {
            dup[pref[i] + N]--;
        }
        s += a[i] == 0;
    }
    return ans + calc(l, mid) + calc(mid + 1, r);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            if (x < k) {
                a[i] = -1;
            } else if (x == k) {
                a[i] = 0;
            } else {
                a[i] = 1;
            }
        }
        int s = 0;
        for (int i = 0; i <= n; i++) {
            s += a[i];
            pref[i] = s;
        }
        cout << calc(0, n) << endl;
    }
    return 0;
}
