//https://codeforces.com/contest/1591/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int seen[N];

struct BIT {
    int n;
    vector<int> t;
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

ll inv(vector<int> a) {
    ll I = 0;
    int n = a.size();
    BIT bit(n);
    for (int i = 0; i < n; i++) {
        I += bit.query(a[i] + 1, n);
        bit.upd(a[i] + 1, 1);
    }
    return I;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string ans = "NO";
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            if (seen[a[i]]) {
                ans = "YES";
            } else {
                seen[a[i]] = true;
            }
        }
        if (ans == "NO" && inv(a) % 2 == 0) {
            ans = "YES";
        }
        for (int i = 0; i < n; i++) {
            seen[a[i]] = false;
        }
        cout << ans << endl;

    }
    return 0;
}
