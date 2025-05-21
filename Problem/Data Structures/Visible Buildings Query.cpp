//https://cses.fi/problemset/task/3304/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int l[N];
int ans[N];
vector<int> add[N];
vector<pair<int, int>> queries[N];

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    BIT(int _n, vector<int> &a) {
        n = _n;
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                t[j] += t[i];
            }
        }
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, long long val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    stack<int> st;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        while (st.size() && a[st.top()] < a[i]) {
            st.pop();
        }
        if (st.size()) {
            l[i] = st.top() + 1;
        } else {
            l[i] = 0;
        }
        st.push(i);
        add[l[i]].push_back(i);
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[l].push_back(make_pair(r, i));
    }
    BIT bit(n);
    for (int i = 0; i < n; i++) {
        for (int j : add[i]) {
            bit.upd(j + 1, 1);
        }
        for (auto [r, j] : queries[i]) {
            ans[j] = bit.query(i + 1, r + 1);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
