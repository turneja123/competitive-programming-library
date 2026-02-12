//https://codeforces.com/contest/1887/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int r_big[N];
int l_big[N];
int ans[N];
int a[N];
int pos[N];

vector<pair<int, int>> add[N], rem[N], ask[N];

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
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
};


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        pos[a[i]] = i;
    }
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (st.size() && a[st.top()] < a[i]) {
            st.pop();
        }
        if (st.size()) {
            r_big[i] = st.top();
        } else {
            r_big[i] = n;
        }
        st.push(i);
    }
    while (st.size()) {
        st.pop();
    }
    for (int i = 0; i < n; i++) {
        while (st.size() && a[st.top()] < a[i]) {
            st.pop();
        }
        if (st.size()) {
            l_big[i] = st.top();
        } else {
            l_big[i] = -1;
        }
        st.push(i);
    }
    set<int> ind;
    for (int i = 0; i < n; i++) {
        int r = r_big[pos[i]];
        int R;
        auto it = ind.lower_bound(r);
        if (it == ind.end()) {
            R = n;
        } else {
            R = *it;
        }
        R--;
        add[l_big[pos[i]] + 1].push_back({r_big[pos[i]], R});
        rem[r_big[pos[i]] - 1].push_back({r_big[pos[i]], R});
        ind.insert(pos[i]);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        ask[l].push_back({r, i});
    }
    BIT bit(n);
    for (int i = 0; i < n; i++) {
        for (auto [l, r] : add[i]) {
            bit.upd(l + 1, r + 1, 1);
        }
        for (auto [r, j] : ask[i]) {
            if (bit.query(r + 1)) {
                ans[j] = 1;
            } else {
                ans[j] = 0;
            }
        }
        for (auto [l, r] : rem[i]) {
            bit.upd(l + 1, r + 1, -1);
        }
    }
    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }


    return 0;
}
