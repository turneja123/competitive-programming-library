//https://dmoj.ca/problem/dmopc19c7p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

struct Data {
    int t, i, x;
    Data() {};
    Data(int t, int i, int x) : t(t), i(i), x(x) {};

};

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
    int query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

vector<Data> a;
int ans[N];

int A[N], P[N];

vector<Data> calc(int l, int r, BIT &bit, int f) {
    if (l == r) {
        return {a[l]};
    }
    int mid = (l + r) / 2;
    vector<Data> lf = calc(l, mid, bit, f);
    vector<Data> rt = calc(mid + 1, r, bit, f);
    vector<Data> v;
    int i = 0, j = 0;
    while (i < lf.size() && j < rt.size()) {
        if (!f) {
            if (lf[i].i < rt[j].i) {
                bit.upd(lf[i].x, 1);
                v.push_back(lf[i++]);
            } else {
                ans[rt[j].t] += bit.query(rt[j].x + 1, N);
                v.push_back(rt[j++]);
            }
        } else {
            if (lf[i].i > rt[j].i) {
                bit.upd(lf[i].x, 1);
                v.push_back(lf[i++]);
            } else {
                ans[rt[j].t] += bit.query(1, rt[j].x - 1);
                v.push_back(rt[j++]);
            }
        }
    }
    while (j < rt.size()) {
        if (!f) {
            ans[rt[j].t] += bit.query(rt[j].x + 1, N);
        } else {
            ans[rt[j].t] += bit.query(1, rt[j].x - 1);
        }
        v.push_back(rt[j++]);
    }
    for (int k = 0; k < i; k++) {
        bit.upd(lf[k].x, -1);
    }
    while (i < lf.size()) {
        v.push_back(lf[i++]);
    }
    return v;
}

int main() {
    IOS;
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> P[i];
        a[i - 1] = Data(i, P[i], A[P[i]]);
    }

    BIT bit(N);
    calc(0, n - 1, bit, 0);
    calc(0, n - 1, bit, 1);

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += ans[i];
        cout << sum << endl;
    }
    return 0;
}
