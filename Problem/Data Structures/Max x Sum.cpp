//https://atcoder.jp/contests/abc376/tasks/abc376_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> t;

pair<long long, long long> a[N];
long long sum = 0;

void st_add(int n, int j, int x) {
    if (x > t.size()) {
        t.insert(make_pair(n, j));
        sum += n;
    } else {
        int k = t.order_of_key(make_pair(n, j));
        if (k < x) {
            sum += n;
            auto it = t.find_by_order(x - 1);
            sum -= it->first;
        }
        t.insert(make_pair(n, j));
    }

    return;
}

void st_remove(int n, int j, int x) {
    if (x >= t.size()) {
        t.erase(make_pair(n, j));
        sum -= n;
    } else {
        int k = t.order_of_key(make_pair(n, j));
        if (k < x) {
            sum -= n;
            t.erase(make_pair(n, j));
            auto it = t.find_by_order(x - 1);
            sum += it->first;
        } else {
            t.erase(make_pair(n, j));
        }
    }
    return;
}

int main() {
    IOS;
    int tt;
    cin >> tt;
    while (tt--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i].first;
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i].second;
        }
        sort(a, a + n, greater<pair<int, int>>());
        long long ans = 1e18;
        for (int i = 0; i < n; i++) {
            st_add(a[i].second, i, k);
        }
        int i = 0;
        while (i < n) {
            if (t.size() >= k) {
                ans = min(ans, sum * a[i].first);
            }
            int cur = a[i].first;
            while (i < n && a[i].first == cur) {
                st_remove(a[i].second, i, k);
                i++;
            }
        }
        cout << ans << endl;
        sum = 0;
        t.clear();
    }
    return 0;
}
