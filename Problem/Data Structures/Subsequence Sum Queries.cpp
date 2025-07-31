//https://qoj.ac/problem/11745
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 21;
const long long M = 1e9 + 7;
int m;

struct Data {
    array<int, K> x;
    Data() {
        for (int i = 0; i < K; i++) {
            x[i] = 0;
        }
    }
    Data(int _x) {
        for (int i = 0; i < K; i++) {
            x[i] = 0;
        }
        x[_x % m]++;
    }
};

Data dat[N];
int lev[N];
int a[N];
int ans[N];

Data combine(Data left, Data right) {
    Data data;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            data.x[(i + j) % m] = (data.x[(i + j) % m] + (ll)left.x[i] * right.x[j] % M) % M;
        }
        data.x[i] = (data.x[i] + left.x[i]) % M;
        data.x[i] = (data.x[i] + right.x[i]) % M;
    }
    return data;
}

Data combine(Data left, int x) {
    Data data;
    for (int i = 0; i < K; i++) {
        data.x[i] = (data.x[i] + left.x[i]) % M;
        data.x[(i + x) % m] = (data.x[(i + x) % m] + left.x[i]) % M;
    }
    data.x[x % m] = (data.x[x % m] + 1) % M;
    return data;
}

int table[K][N];
int mx[K][N];

vector<tuple<int, int, int, int>> queries[K];
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
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    calc(0, n - 1, 0);
    build(n);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int mid = query(l, r);
        queries[lev[mid]].push_back({l, r, mid, i});
    }
    for (int i = 0; i < K; i++) {
        for (auto [l, mid, r] : process[i]) {
            dat[mid] = Data(a[mid]);
            for (int i = mid - 1; i >= l; i--) {
                dat[i] = combine(dat[i + 1], a[i]);
            }
            if (mid + 1 <= r) {
                dat[mid + 1] = Data(a[mid + 1]);
                for (int i = mid + 2; i <= r; i++) {
                    dat[i] = combine(dat[i - 1], a[i]);
                }
            }
        }
        for (auto [l, r, mid, j] : queries[i]) {
            if (l == r) {
                Data data(a[l]);
                ans[j] = (data.x[0] + 1) % M;
            } else {
                Data data = dat[l];
                if (r > mid) {
                    data = combine(data, dat[r]);
                }
                ans[j] = (data.x[0] + 1) % M;
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
