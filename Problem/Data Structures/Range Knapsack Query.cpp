//https://atcoder.jp/contests/abc426/tasks/abc426_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e4 + 5;
const int Q = 3e5 + 5;
const int K = 20;
const int W = 505;

struct Data {
    array<ll, W> x;
    Data() {
        for (int i = 0; i < W; i++) {
            x[i] = 0;
        }
    }
    Data(int w, int v) {
        for (int i = 0; i < W; i++) {
            x[i] = 0;
        }
        for (int i = w; i < W; i++) {
            x[i] = v;
        }
    }
};

Data dat[N];
int lev[N];
ll ans[Q];
int wt[N];
int val[N];

Data combine(Data left, int w, int v) {
    Data data;
    for (int i = 1; i < W; i++) {
        data.x[i] = left.x[i];
        if (i - w >= 0) {
            data.x[i] = max(data.x[i], left.x[i - w] + v);
        }
    }
    return data;
}

int table[K][N];
int mx[K][N];

vector<tuple<int, int, int, int, int>> queries[K];
vector<tuple<int, int, int>> process[K];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = lev[i - 1];
        mx[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table[k - 1][i] < table[k - 1][i + (1 << (k - 1))]) {
                table[k][i] = table[k - 1][i];
                mx[k][i] = mx[k - 1][i];
            } else {
                table[k][i] = table[k - 1][i + (1 << (k - 1))];
                mx[k][i] = mx[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    if (table[k][l] < table[k][r - (1 << k) + 1]) {
        return mx[k][l];
    }
    return mx[k][r - (1 << k) + 1];
}

void calc(int l, int r, int d) {
    int mid = (l + r) / 2;
    lev[mid] = d;
    process[lev[mid]].push_back({l, mid, r});
    if (l < mid) {
        calc(l, mid - 1, d + 1);
    }
    if (mid < r) {
        calc(mid + 1, r, d + 1);
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> wt[i] >> val[i];
    }
    calc(0, n - 1, 0);
    build(n);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        l--, r--;
        int mid = query(l, r);
        queries[lev[mid]].push_back({l, r, mid, i, c});
    }
    for (int i = 0; i < K; i++) {
        for (auto [l, mid, r] : process[i]) {
            dat[mid] = Data(wt[mid], val[mid]);
            for (int i = mid - 1; i >= l; i--) {
                dat[i] = combine(dat[i + 1], wt[i], val[i]);
            }
            if (mid + 1 <= r) {
                dat[mid + 1] = Data(wt[mid + 1], val[mid + 1]);
                for (int i = mid + 2; i <= r; i++) {
                    dat[i] = combine(dat[i - 1], wt[i], val[i]);
                }
            }
        }
        for (auto [l, r, mid, j, c] : queries[i]) {
            if (l == r) {
                if (c >= wt[l]) {
                    ans[j] = val[l];
                } else {
                    ans[j] = 0;
                }
            } else {
                for (int i = 0; i <= c; i++) {
                    ans[j] = max(ans[j], dat[l].x[i] + (r > mid ? dat[r].x[c - i] : 0));
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
