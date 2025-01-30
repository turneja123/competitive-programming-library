//https://zerojudge.tw/ShowProblem?problemid=c571
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

struct Data {
    int x, y, z, i;
    Data() {};
    Data(int x, int y, int z, int i) : x(x), y(y), z(z), i(i) {};

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

vector<Data> calc(int l, int r, BIT &bit) {
    if (l == r) {
        return {a[l]};
    }
    int mid = (l + r) / 2;
    vector<Data> lf = calc(l, mid, bit);
    vector<Data> rt = calc(mid + 1, r, bit);
    vector<Data> v;
    int i = 0, j = 0;
    while (i < lf.size() && j < rt.size()) {
        if (lf[i].y > rt[j].y) {
            bit.upd(lf[i].z, 1);
            v.push_back(lf[i++]);
        } else {
            ans[rt[j].i] += bit.query(rt[j].z + 1, N);
            v.push_back(rt[j++]);
        }
    }
    while (i < lf.size()) {
        bit.upd(lf[i].z, 1);
        v.push_back(lf[i++]);
    }
    while (j < rt.size()) {
        ans[rt[j].i] += bit.query(rt[j].z + 1, N);
        v.push_back(rt[j++]);
    }
    for (int i = 0; i < lf.size(); i++) {
        bit.upd(lf[i].z, -1);
    }
    return v;
}

int main() {
    IOS;
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        a[i] = Data(x, y, z, i);
    }
    sort(a.begin(), a.end(),
         [](Data a, Data b) -> bool {
            return (a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y < b.y) : a.x > b.x);
            });
    BIT bit(N);
    calc(0, n - 1, bit);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
