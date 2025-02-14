//https://codeforces.com/contest/1943/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 20;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 9923, INV_Q = 452282579;

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];

pair<long long, long long> pref[N], suf[N];

long long sum_even[N], sum_odd[N];

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

struct Sparse {
    vector<int> table[K];

    Sparse(int n, vector<int> &a) {
        for (int i = 0; i < K; i++) {
            table[i].resize(n + 1);
        }
        for (int i = 1; i <= n; i++) {
            table[0][i] = a[i - 1];
        }
        for (int k = 1; k < K; k++) {
            for (int i = 1; i + (1 << k) - 1 <= n; i++) {
                table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int l, int r) {
        l++, r++;
        int k = 31 - __builtin_clz(r - l + 1);
        return min(table[k][l], table[k][r - (1 << k) + 1]);
    }

};

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        if (i % 2 == 1) {
            sum_odd[i] += i;
        } else {
            sum_even[i] += i;
        }
        sum_odd[i] += sum_odd[i - 1];
        sum_even[i] += sum_even[i - 1];
    }
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        vector<int> even(n - 1, 0), odd(n, 0);
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
            odd[i] = ans;
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
                    even[i] = ans;
                } else {
                    even[i] = -1;
                }
            }
        }
        Sparse t_even(n - 1, even), t_odd(n, odd);
        for (int i = 0; i < q; i++) {
            int lq, rq;
            cin >> lq >> rq;
            lq--, rq--;
            long long sum = 0;
            int window = (rq - lq + 1 - 1) / 2;
            int l = 0, r = window, ans = 1 + 2 * window;
            while (l <= r) {
                int mid = (l + r) / 2;
                int sz = 1 + 2 * mid;
                int lf = lq + mid, rt = rq - mid;
                int mn = t_odd.query(lf, rt);
                if (1 + 2 * mn < sz) {
                    ans = sz - 1;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            sum += sum_odd[1 + 2 * window] - sum_odd[ans];
            if ((rq - lq + 1) % 2 == 1) {
                pair<long long, long long> h1 = get_pref(lq, rq, n);
                pair<long long, long long> h2 = get_suf(lq, rq, n);
                if (h1.first == h2.first && h1.second == h2.second && ans < rq - lq + 1) {
                    sum -= rq - lq + 1;
                }
            }

            window = (rq - lq + 1 - 2) / 2;
            l = 0, r = window, ans = 2 + 2 * window;
            while (l <= r) {
                int mid = (l + r) / 2;
                int sz = 2 + 2 * mid;
                int lf = lq + mid, rt = rq - mid - 1;
                int mn = t_even.query(lf, rt);
                if (2 + 2 * mn < sz) {
                    ans = sz - 1;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            sum += sum_even[2 + 2 * window] - sum_even[ans];
            if ((rq - lq + 1) % 2 == 0) {
                pair<long long, long long> h1 = get_pref(lq, rq, n);
                pair<long long, long long> h2 = get_suf(lq, rq, n);
                if (h1.first == h2.first && h1.second == h2.second && ans < rq - lq + 1) {
                    sum -= rq - lq + 1;
                }
            }
            cout << sum << endl;

        }
    }
    return 0;
}
