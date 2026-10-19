//https://codeforces.com/contest/1045/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll M = 1e9 + 7;
const ll P = 26, INV_P = 576923081;
const ll Q = 53, INV_Q = 56603774;

ll pw_p[N], pw_q[N];
ll inv_p[N], inv_q[N];

pair<ll, ll> pref[N], suf[N];

pair<ll, ll> get_pref(int l, int r, int n) {
    pair<ll, ll> ans = pref[r];
    if (l != 0) {
        ans.first = (ans.first - pref[l - 1].first + M) * inv_p[l] % M;
        ans.second = (ans.second - pref[l - 1].second + M) * inv_q[l] % M;
    }
    return ans;
}

pair<ll, ll> get_suf(int l, int r, int n) {
    pair<ll, ll> ans = suf[l];
    if (r != n - 1) {
        ans.first = (ans.first - suf[r + 1].first + M) * inv_p[n - 1 - r] % M;
        ans.second = (ans.second - suf[r + 1].second + M) * inv_q[n - 1 - r] % M;
    }
    return ans;
}

int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    int n, m;
    cin >> n >> m;
    vector<int> a(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    if (n == 1) {
        cout << 1 << endl << (a[0] + a[0]) % m << endl;
        return 0;
    }

    vector<int> d(2 * n - 1);
    for (int i = 0; i < 2 * n - 1; i++) {
        d[i] = (a[i + 1] - a[i] + m) % m;
    }

    for (int i = 0; i < 2 * n - 1; i++) {
        pref[i].first = ((i == 0 ? 0 : pref[i - 1].first) + (d[i] + 1) * pw_p[i]) % M;
        pref[i].second = ((i == 0 ? 0 : pref[i - 1].second) + (d[i] + 1) * pw_q[i]) % M;
    }
    for (int i = 2 * n - 1 - 1; i >= 0; i--) {
        suf[i].first = ((i == 2 * n - 1 - 1 ? 0 : suf[i + 1].first) + (d[i] + 1) * pw_p[2 * n - 1 - 1 - i]) % M;
        suf[i].second = ((i == 2 * n - 1 - 1 ? 0 : suf[i + 1].second) + (d[i] + 1) * pw_q[2 * n - 1 - 1 - i]) % M;
    }
    set<int> ans;
    int add = 0;
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            add = (add + d[i - 1]);
        }
        if (get_pref(i, i + n - 2, 2 * n - 1) == get_suf(i, i + n - 2, 2 * n - 1)) {
            if (n % 2 == 0) {
                ans.insert((a[i + n / 2 - 1] + a[i + n / 2]) % m);
            } else {
                ans.insert((a[i + n / 2] + a[i + n / 2]) % m);
            }
        }
        if (n % 2 == 0 && get_pref(i, i + n - 1, 2 * n - 1) == get_suf(i, i + n - 1, 2 * n - 1)) {
            ans.insert((a[i] + a[i]) % m);
        }
    }
    cout << ans.size() << endl;
    for (int x : ans) {
        cout << x << " ";
    }

    return 0;
}
