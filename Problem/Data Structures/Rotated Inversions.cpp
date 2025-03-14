//https://atcoder.jp/contests/abc396/tasks/abc396_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

long long freq[N];
long long x[N], y[N];
long long diff[N];

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    BIT(int _n, vector<long long> &a) {
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
        i++;
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    long long query(int l, int r) {
        l++, r++;
        if (l > r) {
            return 0;
        }
        return query(r) - query(l - 1);
    }
};



int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    BIT bit(m + 1);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans += bit.query(a[i] + 1, m - 1);
        bit.upd(a[i], 1);
        x[a[i]] += bit.query(0, a[i] - 1);
        freq[a[i]]++;
    }
    BIT suf(m + 1);
    for (int i = n - 1; i >= 0; i--) {
        y[a[i]] += suf.query(a[i] + 1, m - 1);
        suf.upd(a[i], 1);
    }
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        if (freq[i]) {
            diff[m - i] += (x[i] - y[i]) * 2 + freq[i] * (n - freq[i] - sum * 2);
            sum += freq[i];
        }
    }
    sum = 0;
    for (int i = 0; i < m; i++) {
        sum += diff[i];
        cout << ans + sum << endl;
    }
    return 0;
}
