#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 1e9 + 7;

int a[N];
ll l[N];
ll r[N];
ll sol[N];

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t;

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        t.insert(a[i]);
    }
    for (int i = 0; i < n; i++) {
        a[i] = t.order_of_key(a[i]);
    }
    stack <pair<int, int>> s;
    for (int i = 0; i < n; i++) {
        while (s.size() && s.top().first < a[i]) {
            s.pop();
        }
        if (s.empty()) {
            l[i] = -1;
        } else {
            l[i] = s.top().second;
        }
        s.push({a[i], i});
    }
    while (s.size()) {
        s.pop();
    }
    for (int i = n - 1; i >= 0; i--) {
        while (s.size() && s.top().first <= a[i]) {
            s.pop();
        }
        if (s.empty()) {
            r[i] = n;
        } else {
            r[i] = s.top().second;
        }
        s.push({a[i], i});
    }
    int prev = -1;
    int ct = 0;
    for (ll i = 0; i < n; i++) {
        ll dod = (i - l[i]) * (r[i] - i);
        sol[a[i]] += dod;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int c;
        cin >> c;
        if (t.find(c) == t.end()) {
            cout << 0 << endl;
            continue;
        }
        c = t.order_of_key(c);
        cout << sol[c] % M << endl;
    }
    return 0;


}

