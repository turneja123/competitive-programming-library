//https://codeforces.com/contest/2038/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int M = 998244353;

int a[N];


struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        i++;
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
            if (t[i] >= M) {
                t[i] -= M;
            }
        }
    }
    int query(int i) {
        i++;
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
            if (ans >= M) {
                ans -= M;
            }
        }
        return ans;
    }
    int query(int l, int r) {
        return (query(r) - query(l - 1) + M) % M;
    }
};


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    map<int, int> mp;
    vector<tuple<int, int, int, int>> queries;
    for (int i = 1; i <= n; i++) {
        map<int, int> mp_nx;
        mp_nx[a[i]] = i;
        for (auto [x, l] : mp) {

            auto it = mp_nx.find(x | a[i]);
            if (it == mp_nx.end()) {
                mp_nx[x | a[i]] = l;
            } else {
                it->second = min(it->second, l);
            }
        }
        mp = mp_nx;

        vector<pair<int, int>> v;
        for (auto [x, l] : mp) {
            v.push_back({l, x});
        }
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        int r = i;

        for (auto [l, x] : v) {
            queries.push_back({x, i, l - 1, r - 1});
            r = l - 1;
        }
    }
    BIT bit(n + 2);
    bit.upd(0, 1);
    sort(queries.begin(), queries.end());
    for (auto [_, i, l, r] : queries) {
        int x = bit.query(l, r);
        bit.upd(i, x);
    }
    cout << bit.query(n, n);

    return 0;
}
