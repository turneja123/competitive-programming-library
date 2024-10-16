//https://www.codechef.com/problems/TRICOUNT1?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int ans = 0;
int a[N];
set<pair<int, int>> ivals;

void interval_insert(int l, int r) {
    if (ivals.empty()) {
        ivals.insert(make_pair(l, r));
        ans += r - l + 1;
        return;
    }
    auto it = ivals.lower_bound({l, r});
    if (it != ivals.begin()) {
        --it;
        if (it->second < l - 1) {
            ++it;
        }
    }
    int new_l = l;
    int new_r = r;
    while (it != ivals.end() && it->first <= r + 1) {
        new_l = min(new_l, it->first);
        new_r = max(new_r, it->second);
        ans -= it->second - it->first + 1;
        it = ivals.erase(it);
    }
    ivals.insert(make_pair(new_l, new_r));
    ans += new_r - new_l + 1;
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        for (int i = 0; i < n - 1; i++) {
            int r = a[i], l = a[i + 1] - a[i];
            if (l <= r - 1) {
                interval_insert(l, r - 1);
            }
        }
        for (int i = 0; i < n - 1; i++) {
            int r = a[i + 1], l = a[i];
            l = max(l, a[i + 1] - a[i]);
            if (l <= r - 1) {
                interval_insert(l, r - 1);
            }
        }
        for (int i = 1; i < n; i++) {
            int l = a[i], r = a[i] + a[i - 1] - 1;
            if (l <= r - 1) {
                interval_insert(l, r - 1);
            }
        }
        cout << ans << endl;
        ans = 0;
        ivals.clear();

    }

    return 0;
}
