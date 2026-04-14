//https://codeforces.com/contest/1436/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
vector<int> pos[N];
vector<pair<int, int>> ivals[N];
int ok[N];
int seg[2 * N];

void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = -1;
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    }
}

void update(int pos, int val, int n) {
    pos += n;
    if (val >= 0) {
        seg[pos] = val;
    } else {
        seg[pos] = -1;
    }
    while (pos > 1) {
        pos /= 2;
        seg[pos] = min(seg[2 * pos], seg[2 * pos + 1]);
    }
}

int rmq(int l, int r, int n) {
    l += n;
    r += n;
    int mn = 1e9;
    while (l < r) {
        if (r % 2 == 1) {
            mn = min(mn, seg[--r]);
        }
        if (l % 2 == 1) {
            mn = min(mn, seg[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return mn;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    if (pos[1].size() == n) {
        cout << 1;
        return 0;
    }
    if (pos[1].size() == 0) {
        cout << 2;
        return 0;
    }
    build(n + 1);
    for (int j = 1; j <= n + 1; j++) {
        int p = -1;
        for (int x : pos[j]) {
            if (p + 1 <= x - 1) {
                ivals[x - 1].push_back({p + 1, j});
            }
            p = x;
        }
        if (p + 1 <= n - 1) {
            ivals[n - 1].push_back({p + 1, j});
        }
    }
    for (int i = 0; i < n; i++) {
        update(a[i] - 1, i, n + 1);
        for (auto [l, j] : ivals[i]) {
            int L = 0, R = n;
            while (L < R) {
                int mid = (L + R) / 2;
                if (rmq(0, mid + 1, n + 1) < l) {
                    R = mid;
                } else {
                    L = mid + 1;
                }
            }
            if (L + 1 == j) {
                ok[j] = 1;
            }
        }
    }
    for (int j = 1; j <= n + 1; j++) {
        if (!ok[j]) {
            cout << j;
            return 0;
        }
    }
    cout << n + 2;
    return 0;
}
