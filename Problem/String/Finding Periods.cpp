//https://cses.fi/problemset/task/1733
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 9923, INV_Q = 452282579;

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];

pair<long long, long long> pref[N];

pair<long long, long long> get_pref(int l, int r, int n) {
    pair<long long, long long> ans = pref[r];
    if (l != 0) {
        ans.first = (ans.first - pref[l - 1].first + M) * inv_p[l] % M;
        ans.second = (ans.second - pref[l - 1].second + M) * inv_q[l] % M;
    }
    return ans;
}

int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < n; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    for (int i = 0; i < n; i++) {
        pref[i].first = ((i == 0 ? 0 : pref[i - 1].first) + (s[i] - 'a' + 1) * pw_p[i]) % M;
        pref[i].second = ((i == 0 ? 0 : pref[i - 1].second) + (s[i] - 'a' + 1) * pw_q[i]) % M;
    }
    for (int i = 1; i <= n; i++) {
        bool can = true;
        for (int j = i; j < n && can; j += i) {
            int sz = min(i, n - j);
            if (get_pref(0, sz - 1, n) != get_pref(j, j + sz - 1, n)) {
                can = false;
            }
        }
        if (can) {
            cout << i << " ";
        }
    }
    return 0;
}
