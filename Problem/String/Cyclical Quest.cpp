//https://codeforces.com/contest/235/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct Node {
    int len, link, firstpos;
    map<char, int> nxt;
};

struct SuffixAutomaton {

    int sz, last;
    vector<Node> t;
    vector<int> terminal;
    vector<long long> dp;
    vector<vector<int>> g;
    SuffixAutomaton() {}
    SuffixAutomaton(int n) {
        t.resize(2 * n); terminal.resize(2 * n, 0);
        dp.resize(2 * n, -1); sz = 1; last = 0;
        g.resize(2 * n);
        t[0].len = 0; t[0].link = -1; t[0].firstpos = 0;
    }
    void extend(char c) {
        int p = last;
        if (t[p].nxt.count(c)) {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1) {
                last = q;
                return;
            }
            int clone = sz++;
            t[clone] = t[q];
            t[clone].len = t[p].len + 1;
            t[q].link = clone;
            last = clone;
            while (p != -1 && t[p].nxt[c] == q) {
                t[p].nxt[c] = clone;
                p = t[p].link;
            }
            return;
        }
        int cur = sz++;
        t[cur].len = t[last].len + 1;
        t[cur].firstpos = t[cur].len;
        p = last;
        while (p != -1 && !t[p].nxt.count(c)) {
            t[p].nxt[c] = cur;
            p = t[p].link;
        }
        if (p == -1) t[cur].link = 0;
        else {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len) t[cur].link = q;
            else {
                int clone = sz++;
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                while (p != -1 && t[p].nxt[c] == q) {
                    t[p].nxt[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        last = cur;
    }
    void build_tree() {
        for (int i = 1; i < sz; i++) g[t[i].link].push_back(i);
    }
    void build(string &s) {
        for (auto x: s) {
            extend(x);
            terminal[last] = 1;
        }
        build_tree();
    }
    long long cnt(int i) { //number of times i-th node occurs in the string
        if (dp[i] != -1) return dp[i];
        long long ret = terminal[i];
        for (auto &x: g[i]) ret += cnt(x);
        return dp[i] = ret;
    }
    ll calc(string &s, int n, vector<int> &repend) {
        int cur = 0; ll ans = 0;
        int l = 0, i = 0, r = n - 1;
        for (int r = n - 1; r < 2 * n - 1; r++) {
            int found = 1;
            while (i <= r) {
                auto it = t[cur].nxt.find(s[i]);
                if (it == t[cur].nxt.end()) {
                    found = 0;
                    break;
                }
                i++;
                cur = it->second;
            }

            if (found && !repend[r]) {
                ans += cnt(cur);
            }
            if (cur != 0) {
                int L = i - l - 1;
                while (t[cur].link != -1 && t[t[cur].link].len >= L) {
                    cur = t[cur].link;
                }
            }
            if (i == l) {
                i++;
            }
            l++;
        }
        return ans;
    }
};

const ll M = 1e9 + 7;
const ll P = 26, INV_P = 576923081;
const ll Q = 53, INV_Q = 56603774;

int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    SuffixAutomaton sa(n);
    sa.build(s);
    int t;
    cin >> t;
    while (t--) {
        string a;
        cin >> a;
        int n = a.size();
        for (int i = 0; i < n - 1; i++) {
            a += a[i];
        }
        ll p = 0, q = 0;
        ll p_pow = 1, q_pow = 1;
        for (int i = 0; i < n; i++) {
            p = (p + p_pow * (a[i] - 'a' + 1)) % M;
            q = (q + q_pow * (a[i] - 'a' + 1)) % M;
            if (i != n - 1) {
                p_pow = (p_pow * P) % M;
                q_pow = (q_pow * Q) % M;
            }
        }
        vector<int> repend(2 * n - 1, 0);
        set<pair<ll, ll>> st;
        st.insert({p, q});
        for (int i = n; i < 2 * n - 1; i++) {
            p = (p - (a[i - n] - 'a' + 1) + M) * INV_P % M;
            q = (q - (a[i - n] - 'a' + 1) + M) * INV_Q % M;
            p = (p + p_pow * (a[i] - 'a' + 1)) % M;
            q = (q + q_pow * (a[i] - 'a' + 1)) % M;
            auto it = st.find({p, q});
            if (it == st.end()) {
                st.insert({p, q});
            } else {
                repend[i] = 1;
            }
        }

        cout << sa.calc(a, n, repend) << endl;
    }


    return 0;
}
