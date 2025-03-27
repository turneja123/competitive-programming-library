//https://www.spoj.com/problems/LNGPALN/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];

pair<long long, long long> pref[N], suf[N];
int prefct[N];

pair<long long, long long> get_pref(int l, int r, int n) {
    pair<long long, long long> ans = pref[r];
    if (l != 0) {
        ans.first = (ans.first - pref[l - 1].first + M) * inv_p[l] % M;
        ans.second = (ans.second - pref[l - 1].second + M) * inv_q[l] % M;
    }
    return ans;
}

pair<long long, long long> get_suf(int l, int r, int n) {
    pair<long long, long long> ans = suf[l];
    if (r != n - 1) {
        ans.first = (ans.first - suf[r + 1].first + M) * inv_p[n - 1 - r] % M;
        ans.second = (ans.second - suf[r + 1].second + M) * inv_q[n - 1 - r] % M;
    }
    return ans;
}

bool comp(int a, int b, int sz, int n, string &s) {
    int l = 0, r = sz - 1, m = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (get_pref(a, a + mid, n) == get_pref(b, b + mid, n)) {
            m = mid + 1;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    if (m == sz) {
        return true;
    }
    if (s[a + m] < s[b + m]) {
        return true;
    }
    return false;
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
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            prefct[i] = (i == 0 ? 0 : prefct[i - 1] + (s[i] == s[i - 1]));
            pref[i].first = ((i == 0 ? 0 : pref[i - 1].first) + (s[i] - 'A' + 1) * pw_p[i]) % M;
            pref[i].second = ((i == 0 ? 0 : pref[i - 1].second) + (s[i] - 'A' + 1) * pw_q[i]) % M;
        }
        for (int i = n - 1; i >= 0; i--) {
            suf[i].first = ((i == n - 1 ? 0 : suf[i + 1].first) + (s[i] - 'A' + 1) * pw_p[n - 1 - i]) % M;
            suf[i].second = ((i == n - 1 ? 0 : suf[i + 1].second) + (s[i] - 'A' + 1) * pw_q[n - 1 - i]) % M;
        }
        int best = 0;
        pair<int, int> sub;
        for (int i = 0; i < n; i++) {
            int l = 0, r = min(i, n - 1 - i), ans = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                int lf = i - mid, rt = i + mid;
                if (lf != rt) {
                    int ct = prefct[rt] - prefct[lf];
                    if (ct) {
                        r = mid - 1;
                        continue;
                    }
                }

                pair<long long, long long> h1 = get_pref(i - mid, i, n);
                pair<long long, long long> h2 = get_suf(i, i + mid, n);
                if (h1.first == h2.first && h1.second == h2.second) {
                    ans = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if (1 + 2 * ans > best) {
                best = 1 + 2 * ans;
                sub = make_pair(i - ans, i + ans);
            } else if (1 + 2 * ans == best) {
                if (comp(i - ans, sub.first, 1 + 2 * ans, n, s)) {
                    sub = make_pair(i - ans, i + ans);
                }
            }
        }
        cout << s.substr(sub.first, sub.second - sub.first + 1) << endl;
    }
    return 0;
}
