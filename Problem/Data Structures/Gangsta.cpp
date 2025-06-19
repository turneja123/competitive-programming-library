//https://codeforces.com/contest/2121/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

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

long long calc(vector<int> &a, int f) {
    int n = a.size();
    int mid =  n + 2;
    BIT sum(2 * n + 5);
    BIT ct(2 * n + 5);
    sum.upd(mid + 0, 0);
    ct.upd(mid + 0, 1);
    int s = 0, j = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        s += a[i];
        j += a[i] == 1;
        int r = s - f + mid;
        ans += (long long)j * ct.query(r) - sum.query(r);
        ct.upd(s + mid, 1);
        sum.upd(s + mid, j);
    }
    return ans;
}



int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                a[i] = 1;
            } else {
                a[i] = -1;
            }
        }
        long long ans = calc(a, 0);
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                a[i] = -1;
            } else {
                a[i] = 1;
            }
        }
        ans += calc(a, 1);
        cout << ans << endl;
    }

    return 0;
}
