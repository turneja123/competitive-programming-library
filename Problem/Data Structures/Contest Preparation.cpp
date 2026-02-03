//https://ocpc2026w.eolymp.space/en/compete/r1t2e978517l1a1e5a39p463hs/problem/1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll M = 1e9 + 7;

int a[N];
int b[N];
int c[N];
int pos[N];
int need[N];
int disabled[N];

int last[N];
int far[N];

ll calc(int l, int r) {
    if (l == r) {
        return c[l] != -1 && c[l] >= l && c[l] <= l + 1;
    }
    int mid = (l + r) / 2;
    ll ans = calc(l, mid) + calc(mid + 1, r);
    int mn = N, mx = 0, last = -1;

    for (int i = mid; i >= l; i--) {
        need[i] = 0;
        disabled[i] = 1;
    }

    int ct = 0;
    vector<pair<int, int>> enable_mx;
    for (int i = mid; i >= l; i--) {
        if (c[i] == -1 || i <= last) {
            break;
        }
        mx = max(mx, c[i]);
        mn = min(mn, c[i]);
        last = max(last, far[i]);
        if (mn < i) {
            continue;
        }
        disabled[i] = 0;
        if (mx > mid) {
            need[i]++;
            enable_mx.push_back({mx, i});
        }
        ct += !need[i];
    }
    if (enable_mx.size()) {
        reverse(enable_mx.begin(), enable_mx.end());
    }
    mn = N, mx = 0, last = -1;
    int L = l, R = mid;
    for (int i = mid + 1; i <= r; i++) {
        if (c[i] == -1 || far[i] >= mid + 1) {
            break;
        }
        mx = max(mx, c[i]);
        mn = min(mn, c[i]);
        last = max(last, far[i]);

        while (R >= l && R > mn) {
            if (!disabled[R] && need[R] == 0) {
                ct--;
            }
            disabled[R] = 1;
            R--;
        }
        while (L <= mid && L <= last) {
            if (!disabled[L] && need[L] == 0) {
                ct--;
            }
            disabled[L] = 1;
            L++;
        }
        while (enable_mx.size() && enable_mx.back().first <= i + 1) {
            int j = enable_mx.back().second;
            need[j]--;
            if (!need[j] && !disabled[j]) {
                ct++;
            }
            enable_mx.pop_back();
        }
        if (mx <= i + 1) {
            ans += ct;
        }

    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> compr;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            compr.push_back(a[i]);
            last[i] = -1;
        }
        for (int i = 0; i < n - 1; i++) {
            cin >> b[i];
        }
        sort(compr.begin(), compr.end());
        compr.erase(unique(compr.begin(), compr.end()), compr.end());
        for (int i = 0; i < n; i++) {
            int j = lower_bound(compr.begin(), compr.end(), a[i]) - compr.begin();
            pos[j] = i;
        }
        for (int i = 0; i < n - 1; i++) {
            int j = lower_bound(compr.begin(), compr.end(), b[i]) - compr.begin();
            if (j == compr.size() || compr[j] != b[i]) {
                c[i] = -1;
                far[i] = -1;
            } else {
                c[i] = pos[j];
                far[i] = last[c[i]];
                last[c[i]] = i;

            }
        }
        cout << calc(0, n - 2) + n  << endl;
    }

    return 0;
}
