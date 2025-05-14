//https://cses.fi/problemset/task/3150
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> pos[N];
int ptr[N];
int a[N];


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
    int n;
    cin >> n;
    vector<pair<int, int>> compr;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr.push_back(make_pair(a[i], i));
    }
    sort(compr.begin(), compr.end());
    int last = -1, m = -1;
    for (int i = 0; i < n; i++) {
        if (last != compr[i].first) {
            last = compr[i].first;
            m++;
        }
        a[compr[i].second] = m;
    }
    m++;
    for (int i = 0; i < n; i++) {
        pos[a[i]].push_back(i);
    }
    BIT bit(n);
    for (int i = 0; i < m; i++) {
        bit.upd(pos[i][0] + 1, n - pos[i][0]);
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += bit.query(i + 1, n);
        ptr[a[i]]++;
        if (ptr[a[i]] < pos[a[i]].size()) {
            int j = pos[a[i]][ptr[a[i]]];
            bit.upd(j + 1, n - j);
        }
    }
    cout << ans;

    return 0;
}
