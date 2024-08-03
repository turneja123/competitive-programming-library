//https://judge.yosupo.jp/problem/static_range_mode_query
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int a[N];
int vals[N];
int freq[N];
int sz;
tuple<int, int, int> queries[N];
pair<int, int> ans[N];
gp_hash_table<int, int, custom_hash> pos;
gp_hash_table<int, int, custom_hash> ct[N];


bool comp(tuple<int, int, int> a, tuple<int, int, int> b) {
    int block1 = get<0>(a) / sz;
    int block2 = get<0>(b) / sz;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(a);
    int r2 = get<1>(b);
    return r1 < r2;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    sz = sqrt(n);
    if (sz * sz != n) {
        sz++;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vals[i] = a[i];
        ct[0][vals[i]] = 1;
        if (pos.find(a[i]) == pos.end()) {
            pos[a[i]] = pos.size();
        }
    }
    for (int i = 0; i < n; i++) {
        a[i] = pos[a[i]];
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        r--;
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    int mx = 0, best = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        while (r < rq) {
            r++;
            ct[freq[a[r]]].erase(vals[r]);
            freq[a[r]]++;
            ct[freq[a[r]]][vals[r]] = 1;
            if (freq[a[r]] > mx) {
                mx = freq[a[r]];
            }
        }
        while (r > rq) {
            ct[freq[a[r]]].erase(vals[r]);
            if (freq[a[r]] == mx && ct[freq[a[r]]].size() == 0) {
                mx--;
            }
            freq[a[r]]--;
            ct[freq[a[r]]][vals[r]] = 1;
            r--;
        }
        while (l < lq) {
            ct[freq[a[l]]].erase(vals[l]);
            if (freq[a[l]] == mx && ct[freq[a[l]]].size() == 0) {
                mx--;
            }
            freq[a[l]]--;
            ct[freq[a[l]]][vals[l]] = 1;
            l++;
        }
        while (l > lq) {
            l--;
            ct[freq[a[l]]].erase(vals[l]);
            freq[a[l]]++;
            ct[freq[a[l]]][vals[l]] = 1;
            if (freq[a[l]] > mx) {
                mx = freq[a[l]];
            }
        }
        ans[cur] = make_pair(ct[mx].begin()->first, mx);
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}
