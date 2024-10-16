//https://www.codechef.com/problems/TRICOUNT2
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

void add1(int x, int y) {
    int r = x, l = y - x;
    if (l <= r - 1) {
        interval_insert(l, r - 1);
    }
}

void add2(int x, int y) {
    int r = y, l = x;
    l = max(l, y - x);
    if (l <= r - 1) {
        interval_insert(l, r - 1);
    }
}

void add3(int x, int y) {
    int l = y, r = y + x - 1;
    if (l <= r - 1) {
        interval_insert(l, r - 1);
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        set<int> vals;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (vals.size()) {
                auto it = vals.lower_bound(a[i]);
                if (it != vals.end()) {
                    add1(a[i], *it);
                    add2(a[i], *it);
                    add3(a[i], *it);
                }
                if (it != vals.begin()) {
                    --it;
                    add1(*it, a[i]);
                    add2(*it, a[i]);
                    add3(*it, a[i]);
                }
                cout << ans << " ";
            }
            vals.insert(a[i]);
        }
        cout << endl;
        ivals.clear();
        ans = 0;
    }

    return 0;
}
