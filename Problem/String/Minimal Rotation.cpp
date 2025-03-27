//https://cses.fi/problemset/task/1110/
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
const long long Q = 53, INV_Q = 56603774;

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];

pair<long long, long long> pref[N];

pair<long long, long long> get_pref(int l, int r, int n) {
    if (l <= r) {
        pair<long long, long long> ans = pref[r];
        if (l != 0) {
            ans.first = (ans.first - pref[l - 1].first + M) * inv_p[l] % M;
            ans.second = (ans.second - pref[l - 1].second + M) * inv_q[l] % M;
        }
        return ans;
    }
    pair<long long, long long> ans = pref[n - 1];
    if (l != 0) {
        ans.first = (ans.first - pref[l - 1].first + M) * inv_p[l] % M;
        ans.second = (ans.second - pref[l - 1].second + M) * inv_q[l] % M;
    }
    ans.first = (ans.first + pref[r].first * pw_p[n - l]) % M;
    ans.second = (ans.second + pref[r].second * pw_q[n - l]) % M;
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
        pref[i].first = ((i == 0 ? 0 : pref[i - 1].first) + (s[i] - 'A' + 1) * pw_p[i]) % M;
        pref[i].second = ((i == 0 ? 0 : pref[i - 1].second) + (s[i] - 'A' + 1) * pw_q[i]) % M;
    }
    int i = 0;
    for (int j = 1; j < n; j++) {
        int l = 0, r = n - 1, sz = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            pair<long long, long long> hi = get_pref(i, (i + mid) % n, n), hj = get_pref(j, (j + mid) % n, n);
            if (hi == hj) {
                sz = mid + 1;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (sz == n) {
            continue;
        }
        if (s[(i + sz) % n] > s[(j + sz) % n]) {
            i = j;
        }
    }
    string t = "";
    for (int j = 0; j < n; j++, i = (i + 1) % n) {
        t += s[i];
    }
    cout << t;
    return 0;
}
