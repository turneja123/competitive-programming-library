//https://atcoder.jp/contests/arc181/tasks/arc181_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int val[N];
int inv[N];
int b[N];

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, int val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    IOS;
    int n, k;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }
    sort(v.begin(), v.end());
    int last = -1, m = -1;
    for (int i = 0; i < n; i++) {
        if (last != v[i].first) {
            m++;
            last = v[i].first;
        }
        a[v[i].second] = m;
        val[m] = v[i].first;
    }
    m++;
    BIT bit(m);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        inv[i] = (a[i] == m ? 0 : bit.query(a[i] + 1, m));
        bit.upd(a[i], 1);
        ans += inv[i];
    }
    multiset<int> st;
    last = 0;
    for (int i = 0; i < k; i++) {
        for (int j = last; j < b[i]; j++) {
            st.insert(inv[j] + i);
        }
        while (st.size() && *st.begin() - i <= 0) {
            st.erase(st.begin());
        }
        ans -= st.size();
        last = b[i];
        cout << ans << endl;
    }
    return 0;
}
