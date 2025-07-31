//https://www.codechef.com/START194A/problems/TERST
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;
const long long M = 1e9 + 7;

int a[N];

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
            t[i] = (t[i] + val) % M;
        }
    }
    void upd(int l, int r, long long val) {
        upd(l, val);
        upd(r + 1, (M - val));
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans = (ans + t[i]) % M;
        }
        return ans;
    }
    long long query(int l, int r) {
        return (query(r) - query(l - 1) + M) % M;
    }
};


int table_mn[K][N];
int table_mx[K][N];
int mn[K][N];
int mx[K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table_mn[0][i] = a[i - 1];
        table_mx[0][i] = a[i - 1];
        mn[0][i] = i - 1;
        mx[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table_mn[k - 1][i] < table_mn[k - 1][i + (1 << (k - 1))]) {
                table_mn[k][i] = table_mn[k - 1][i];
                mn[k][i] = mn[k - 1][i];
            } else {
                table_mn[k][i] = table_mn[k - 1][i + (1 << (k - 1))];
                mn[k][i] = mn[k - 1][i + (1 << (k - 1))];
            }

            if (table_mx[k - 1][i] > table_mx[k - 1][i + (1 << (k - 1))]) {
                table_mx[k][i] = table_mx[k - 1][i];
                mx[k][i] = mx[k - 1][i];
            } else {
                table_mx[k][i] = table_mx[k - 1][i + (1 << (k - 1))];
                mx[k][i] = mx[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

pair<int, int> query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    int a, b;
    if (table_mn[k][l] < table_mn[k][r - (1 << k) + 1]) {
        a = mn[k][l];
    } else {
        a = mn[k][r - (1 << k) + 1];
    }

    if (table_mx[k][l] > table_mx[k][r - (1 << k) + 1]) {
        b = mx[k][l];
    } else {
        b = mx[k][r - (1 << k) + 1];
    }

    return {a, b};
}


ll calc(int l, int r, BIT &bit) {
    if (l == r) {
        return 1;
    }

    int mid = l;
    while (mid < r) {
        pair<int, int> ql = query(l, mid), qr = query(mid + 1, r);
        if (a[ql.second] < a[qr.first]) {
            return calc(l, mid, bit) * calc(mid + 1, r, bit) % M;
        }
        mid = qr.first;
    }


    ll ans = 0;
    for (int i = l; i <= r; i++) {
        ll add = 1 + bit.query(1, a[i]);
        bit.upd(a[i], add);
        ans = (ans + add) % M;
    }
    for (int i = l; i <= r; i++) {
        ll add = bit.query(a[i], a[i]);
        bit.upd(a[i], M - add);
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
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(n);
        BIT bit(n);
        cout << calc(0, n - 1, bit) << endl;
    }
    return 0;
}
