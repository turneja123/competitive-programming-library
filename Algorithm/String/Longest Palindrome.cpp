//https://judge.yosupo.jp/problem/enumerate_palindromes
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

pair<long long, long long> pref[N], suf[N];

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

int main() {
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
    for (int i = n - 1; i >= 0; i--) {
        suf[i].first = ((i == n - 1 ? 0 : suf[i + 1].first) + (s[i] - 'a' + 1) * pw_p[n - 1 - i]) % M;
        suf[i].second = ((i == n - 1 ? 0 : suf[i + 1].second) + (s[i] - 'a' + 1) * pw_q[n - 1 - i]) % M;
    }
    for (int i = 0; i < n; i++) {
        int l = 0, r = min(i, n - 1 - i), ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            pair<long long, long long> h1 = get_pref(i - mid, i, n);
            pair<long long, long long> h2 = get_suf(i, i + mid, n);
            if (h1.first == h2.first && h1.second == h2.second) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << 1 + 2 * ans << " ";
        if (i != n - 1) {
            if (s[i] == s[i + 1]) {
                int l = 0, r = min(i, n - 1 - (i + 1)), ans = 0;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    pair<long long, long long> h1 = get_pref(i - mid, i, n);
                    pair<long long, long long> h2 = get_suf(i + 1, i + 1 + mid, n);
                    if (h1.first == h2.first && h1.second == h2.second) {
                        ans = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                cout << 2 + 2 * ans << " ";
            } else {

                cout << 0 << " ";
            }
        }
    }
    return 0;
}
