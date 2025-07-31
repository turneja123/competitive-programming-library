//https://cses.fi/problemset/task/1734/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = 450;

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
int freq[N];
tuple<int, int, int> queries[N];
int ans[N];
gp_hash_table<int, int, custom_hash> pos;

bool comp(tuple<int, int, int> a, tuple<int, int, int> b) {
    int block1 = get<0>(a) / SQ;
    int block2 = get<0>(b) / SQ;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(a);
    int r2 = get<1>(b);
    return r1 < r2;
}

int ct = 0;

void add(int x) {
    freq[x]++;
    if (freq[x] == 1) {
        ct++;
    }
}

void rem(int x) {
    freq[x]--;
    if (freq[x] == 0) {
        ct--;
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
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
        l--, r--;
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    for (int i = 0; i < q; i++) {
        auto [lq, rq, cur] = queries[i];
        while (r < rq) {
            r++;
            add(a[r]);
        }
        while (l > lq) {
            l--;
            add(a[l]);
        }
        while (r > rq) {
            rem(a[r]);
            r--;
        }
        while (l < lq) {
            rem(a[l]);
            l++;
        }
        ans[cur] = ct;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}

