//https://dmoj.ca/problem/coci14c5p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e6 + 5;

string strings[N];
vector<int> idx;
int ans[N];
int a[N];
int freq[N];
pair<int, int> ival[N];
vector<int> pos[N];
int ptr[N];

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    BIT(int _n, vector<int> &a) {
        n = _n;
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                t[j] += t[i];
            }
        }
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, int val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

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

void calc(int l, int r, vector<tuple<int, int, int, int>> &queries, BIT &bit) {
    if (l > r) {
        return;
    }
    int mid = (l + r) / 2;
    vector<tuple<int, int, int, int>> lf, rt;
    for (auto [L, R, tim, ind] : queries) {
        if (tim < l) {
            continue;
        }
        if (tim < mid) {
            lf.push_back(make_tuple(L, R, tim, ind));
        } else {
            rt.push_back(make_tuple(L, R, tim, ind));
        }
    }
    priority_queue<pair<int, int>> pq;
    for (int i = l; i <= mid; i++) {
        ptr[i] = 0;
        if (pos[i].empty()) {
            continue;
        }
        pq.push(make_pair(-pos[i][0], i));
        bit.upd(pos[i][0], 1);
    }
    sort(rt.begin(), rt.end());
    for (auto [L, R, tim, ind] : rt) {
        while (pq.size() && -pq.top().first < L) {
            auto [j, i] = pq.top();
            j = -j;
            bit.upd(j, -1);
            ptr[i]++;
            if (ptr[i] < pos[i].size()) {
                bit.upd(pos[i][ptr[i]], 1);
                pq.push(make_pair(-pos[i][ptr[i]], i));
            }
            pq.pop();
        }
        ans[ind] += bit.query(L, R);
    }
    while (pq.size()) {
        auto [j, i] = pq.top();
        j = -j;
        bit.upd(j, -1);
        pq.pop();
    }
    calc(l, mid - 1, lf, bit);
    calc(mid + 1, r, rt, bit);
    return;
}

int main() {
    IOS;

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> strings[i];
        reverse(strings[i].begin(), strings[i].end());
        ival[i] = make_pair(-1, -1);
    }


    string S = "";
    vector<int> S_int;
    int q;
    cin >> q;
    vector<pair<int, int>> queries_init;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            string c;
            cin >> c;
            for (int j = 0; j < c.size(); j++) {
                idx.push_back(i);
            }
            S += c;
            for (int j = 0; j < c.size(); j++) {
                S_int.push_back(c[j] - 'a');
            }
            S_int.push_back(26);
            S += '}';
            idx.push_back(N - 1);
        } else {
            int j;
            cin >> j;
            j--;
            queries_init.push_back(make_pair(j, i));
        }
    }
    reverse(S.begin(), S.end());
    reverse(S_int.begin(), S_int.end());
    reverse(idx.begin(), idx.end());
    int n = S.size();
    vector<int> sa = sa_is(S_int, 27);
    sa.insert(sa.begin(), n);
    vector<int> isa(n + 1);
    for (int i = 0; i <= n; i++) {
        isa[sa[i]] = i;
    }
    vector<int> lcp(n);
    int h = 0;
    for (int b = 0; b < n; b++) {
        int a = sa[isa[b] - 1];
        while (a + h < n && S[a + h] == S[b + h]) {
            ++h;
        }
        lcp[isa[b] - 1] = h;
        if (h) {
            h--;
        }
    }

    vector<tuple<int, int, int, int>> queries;
    int J = 0;

    for (auto [j, tim] : queries_init) {
        if (ival[j].first != -1) {
            queries.push_back(make_tuple(ival[j].first, ival[j].second, tim, J++));
            continue;
        }
        string a = strings[j];
        int l = 1, r = n, lf = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            bool f = comp(S, a, sa[mid], n);
            if (!f) {
                lf = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        int rt = 0;
        l = 1, r = n;
        a += '~';
        while (l <= r) {
            int mid = (l + r) / 2;
            bool f = comp(S, a, sa[mid], n);
            if (!f) {
                rt = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ival[j] = make_pair(lf + 1, rt);
        queries.push_back(make_tuple(ival[j].first, ival[j].second, tim, J++));
    }
    for (int i = 1; i <= n; i++) {
        a[i] = idx[sa[i]];
        pos[a[i]].push_back(i);
    }

    BIT bit(n + 1);
    calc(0, q - 1, queries, bit);
    for (int i = 0; i < queries.size(); i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
