//https://www.spoj.com/problems/LCS2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAXN = 1e6 + 100;

int id[MAXN];
vector<string> strs;

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

bool chk(vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        if (!a[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    IOS;
    string line;
    while (cin >> line) {
        strs.push_back(line);
    }
    int M = strs.size();
    vector<int> s;
    for (int i = 0; i < M; i++) {
        strs[i] += '~';
        for (int j = 0; j < strs[i].size(); j++) {
            id[j + s.size()] = i;
        }
        for (int j = 0; j < strs[i].size() - 1; j++) {
            s.push_back(strs[i][j] - 'a');
        }
        s.push_back(26);
    }
    int N = s.size();
    vector<int> sa = sa_is(s, 27);
    sa.insert(sa.begin(), N);
    vector<int> isa(N + 1);
    for (int i = 0; i <= N; i++) {
        isa[sa[i]] = i;
    }
    vector<int> lcp(N);
    int h = 0;
    for (int b = 0; b < N; b++) {
        int a = sa[isa[b] - 1];
        while (a + h < N && s[a + h] == s[b + h] && s[a + h] != 26) {
            ++h;
        }
        lcp[isa[b] - 1] = h;
        if (h) {
            h--;
        }
    }

    vector<int> ct(M, 0);
    int ans = 0;
    multiset<int> st;
    for (int i = 1, l = 0; i <= N; i++) {
        while (l < N && !chk(ct)) {
            ct[id[sa[l + 1]]]++;
            st.insert(lcp[l]);
            l++;
        }
        if (!chk(ct)) {
            break;
        }
        st.erase(st.find(lcp[i - 1]));
        if (*st.begin() > ans) {
            ans = *st.begin();
        }
        ct[id[sa[i]]]--;
    }
    cout << ans;
    return 0;
}
