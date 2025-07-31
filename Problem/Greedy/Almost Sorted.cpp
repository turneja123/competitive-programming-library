//https://olympicode.rs/problem/35
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
int mn[N];

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
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    mn[n] = N;
    for (int i = n - 1; i >= 0; i--) {
        mn[i] = min(a[i], mn[i + 1]);
    }
    long long ans = 0;
    BIT bit(n);
    for (int i = 0; i < n; i++) {
        if (mn[i] < a[i]) {
            ans--;
        }
        ans += bit.query(a[i] + 1, n);
        bit.upd(a[i] + 1, 1);
    }
    cout << ans;


    return 0;
}
