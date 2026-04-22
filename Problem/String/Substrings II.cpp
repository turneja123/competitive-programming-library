//https://www.spoj.com/problems/NSUBSTR2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
std::vector<int> sa_is(const std::vector<int>& s, int upper) {
    int n = int(s.size());
    if (n == 0) return {};
    if (n == 1) return {0};
    if (n == 2) {
        if (s[0] < s[1]) {
            return {0, 1};
        } else {
            return {1, 0};
        }
    }


    std::vector<int> sa(n);
    std::vector<bool> ls(n);
    for (int i = n - 2; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    std::vector<int> sum_l(upper + 1), sum_s(upper + 1);
    for (int i = 0; i < n; i++) {
        if (!ls[i]) {
            sum_s[s[i]]++;
        } else {
            sum_l[s[i] + 1]++;
        }
    }
    for (int i = 0; i <= upper; i++) {
        sum_s[i] += sum_l[i];
        if (i < upper) sum_l[i + 1] += sum_s[i];
    }

    auto induce = [&](const std::vector<int>& lms) {
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<int> buf(upper + 1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for (auto d : lms) {
            if (d == n) continue;
            sa[buf[s[d]]++] = d;
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        sa[buf[s[n - 1]]++] = n - 1;
        for (int i = 0; i < n; i++) {
            int v = sa[i];
            if (v >= 1 && !ls[v - 1]) {
                sa[buf[s[v - 1]]++] = v - 1;
            }
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        for (int i = n - 1; i >= 0; i--) {
            int v = sa[i];
            if (v >= 1 && ls[v - 1]) {
                sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        }
    };

    std::vector<int> lms_map(n + 1, -1);
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms_map[i] = m++;
        }
    }
    std::vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms.push_back(i);
        }
    }

    induce(lms);

    if (m) {
        std::vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (int v : sa) {
            if (lms_map[v] != -1) sorted_lms.push_back(v);
        }
        std::vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;
        for (int i = 1; i < m; i++) {
            int l = sorted_lms[i - 1], r = sorted_lms[i];
            int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
            int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
            bool same = true;
            if (end_l - l != end_r - r) {
                same = false;
            } else {
                while (l < end_l) {
                    if (s[l] != s[r]) {
                        break;
                    }
                    l++;
                    r++;
                }
                if (l == n || s[l] != s[r]) same = false;
            }
            if (!same) rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        auto rec_sa =
            sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

        for (int i = 0; i < m; i++) {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}

const int N = 1e5 + 5;
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

bool comp(string &s, string &a, int j, int n) {
    int m = a.size();
    int i = 0;
    for (; i < m && j < n; i++, j++) {
        if (s[j] < a[i]) {
            return false;
        }
        if (s[j] > a[i]) {
            return true;
        }
    }
    if (i == m) {
        return true;
    }
    return false;
}

int main() {
    IOS;
    string s;
    cin >> s;

    int n = s.size();
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        x[i] = s[i] - 'a';
    }
    vector<int> sa = sa_is(x, 26);
    sa.insert(sa.begin(), n);

    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    for (int i = 0; i < n; i++) {
        pref[i].first = ((i == 0 ? 0 : pref[i - 1].first) + (s[i] - 'a' + 1) * pw_p[i]) % M;
        pref[i].second = ((i == 0 ? 0 : pref[i - 1].second) + (s[i] - 'a' + 1) * pw_q[i]) % M;
    }

    int q, A, B;
    cin >> q >> A >> B;
    int n_last = n;
    for (int i = 0; i < q; i++) {
        string t;
        cin >> t;
        int ans = 0, m = t.size();
        if (m > n) {
            cout << ans << endl;
        } else {

            int l = 1, r = n_last, lf = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                bool f = comp(s, t, sa[mid], n_last);
                if (!f) {
                    lf = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            int rt = 0;
            l = 1, r = n_last;
            t += '~';
            while (l <= r) {
                int mid = (l + r) / 2;
                bool f = comp(s, t, sa[mid], n_last);
                if (!f) {
                    rt = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            ans += rt - lf;
            pair<ll, ll> h = {0, 0};
            for (int i = 0; i < m; i++) {
                h.first = ((i == 0 ? 0 : h.first) + (t[i] - 'a' + 1) * pw_p[i]) % M;
                h.second = ((i == 0 ? 0 : h.second) + (t[i] - 'a' + 1) * pw_q[i]) % M;
            }

            for (int j = n_last; j < n; j++) {
                int l = j - m + 1;
                if (l >= 0) {
                    if (get_pref(l, j, n) == h) {
                        ans++;
                    }
                }
            }
            cout << ans << endl;
        }

        int c = (A * ans + B) % 26;
        x.push_back(c);
        s += c + 'a';
        pref[n].first = (pref[n - 1].first + (s[n] - 'a' + 1) * pw_p[n]) % M;
        pref[n].second = (pref[n - 1].second + (s[n] - 'a' + 1) * pw_q[n]) % M;
        n++;
        if (n - n_last > 700) {
            sa = sa_is(x, 26);
            sa.insert(sa.begin(), n);
            n_last = n;
        }
    }



    return 0;
}
