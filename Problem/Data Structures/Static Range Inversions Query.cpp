//https://judge.yosupo.jp/problem/static_range_inversions_query
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int SQ = 100;

int a[N];

vector<int> b[N];
int blk[N / SQ + 5][N];
int sz[N / SQ + 5];

ll ans[N / SQ + 5][N / SQ + 5];

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
        }
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        l++, r++;
        return query(r) - query(l - 1);
    }
};

int calc(vector<int> &a, vector<int> &b) {
    int ans = 0, n = a.size(), m = b.size();
    for (int i = 0, j = 0; j < m; j++) {
        while (i < n && a[i] <= b[j]) {
            i++;
        }
        ans += n - i;
    }
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<int> compr(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr[i] = a[i];
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(compr.begin(), compr.end(), a[i]) - compr.begin();
    }
    int m = compr.size();
    for (int i = 0; i * SQ < n; i++) {
        BIT bit(m + 2);
        for (int j = i * SQ; j < min(n, (i + 1) * SQ); j++) {
            ans[i][i] += bit.query(a[j] + 1, m);
            bit.upd(a[j], 1);
            b[i].push_back(a[j]);
        }
        sort(b[i].begin(), b[i].end());
        sz[i] = b[i].size();
        for (int j = 0, ptr = 0; j < m; j++) {
            while (ptr < sz[i] && b[i][ptr] < j) {
                ptr++;
            }
            blk[i][j] = ptr;
            if (i != 0) {
                blk[i][j] += blk[i - 1][j];
            }
        }
        for (int j = 0; j < i; j++) {
            ans[j][i] = (j == 0 ? 0 : ans[j - 1][i]) + calc(b[j], b[i]);
        }
        if (i != 0) {
            ans[i][i] += ans[i - 1][i];
            sz[i] += sz[i - 1];
        }
    }
    BIT bit(m + 2);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        r--;
        int bl = l / SQ;
        if (l % SQ != 0) {
            bl++;
        }
        int br = r / SQ;
        if ((r + 1) % SQ != 0) {
            br--;
        }
        ll sum = 0;
        auto f = [&](int l, int r, int e, int f) -> void {
            for (int j = l; j < r; j++) {
                if (e == 1) {
                    if (br >= bl) {
                        if (f == 0) {
                            sum += blk[br][a[j]] - (bl == 0 ? 0 : blk[bl - 1][a[j]]);
                        } else if (a[j] != m - 1) {
                            sum += sz[br] - blk[br][a[j] + 1] - (bl == 0 ? 0 : sz[bl - 1] - blk[bl - 1][a[j] + 1]);
                        }
                    }
                    sum += bit.query(a[j] + 1, m);
                }
                bit.upd(a[j], e);
            }
        };
        if (bl > br) {
            f(l, r + 1, 1, 0);
            f(l, r + 1, -1, 0);
        } else {
            for (int j = bl; j <= br; j++) {
                sum += ans[j][j] - (bl == 0 ? 0 : ans[bl - 1][j]);
            }
            f(l, bl * SQ, 1, 0);
            f((br + 1) * SQ, r + 1, 1, 1);
            f(l, bl * SQ, -1, 0);
            f((br + 1) * SQ, r + 1, -1, 1);
        }
        cout << sum << endl;
    }


    return 0;
}
