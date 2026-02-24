//https://judge.beecrowd.com/en/problems/view/1355
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 205;
const int INF = 1e9;
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

int id[N][N];
vector<int> pos[N][N];
map<pair<ll, ll>, int> mp[N];
pair<ll, ll> pref[N];
ll inv_p[N], inv_q[N];
string s;

pair<ll, ll> get_rising(int l, int r, int n) {
    pair<ll, ll> h = pref[r];
    if (l != 0) {
        h.first = (h.first - pref[l - 1].first + M) * inv_p[l] % M;
        h.second = (h.second - pref[l - 1].second + M) * inv_q[l] % M;
    }
    return h;
}


int dp[N][N];
string ans[N][N];

int calc(int l, int r) {
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    if (l == r) {
        ans[l][r] = s[l];
        return dp[l][r] = 1;
    }
    int k = id[l][r], sz = r - l + 1;
    for (int j = 0; j < pos[sz][k].size(); j++) {
        int L = pos[sz][k][j];
        int R = L + sz - 1;
        if (dp[L][R] != -1) {
            dp[l][r] = dp[L][R];
            ans[l][r] = ans[L][R];
            return dp[l][r];
        }

    }
    dp[l][r] = INF;
    if (dp[l][r] > 1 + calc(l + 1, r)) {
        dp[l][r] = 1 + calc(l + 1, r);
        ans[l][r] = s[l] + ans[l + 1][r];
    }

    for (int i = l; i <= r; i++) {
        calc(l, i);
        int sz = i - l + 1;
        int k = id[l][i];

        int last = i;
        vector<int> inds{l};

        while (1) {
            int ind = upper_bound(pos[sz][k].begin(), pos[sz][k].end(), last) - pos[sz][k].begin();
            if (ind == pos[sz][k].size() || pos[sz][k][ind] + sz - 1 > r) {
                break;
            }

            int j = pos[sz][k][ind];
            inds.push_back(j);
            last = j + sz - 1;
        }
        int n = inds.size();
        vector<int> dp_frag(n, INF);
        vector<int> go(n);

        dp_frag[0] = 3 + dp[l][i];
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int L = inds[j] + sz, R = inds[i] - 1;
                int add = 0;
                if (L <= R) {
                    calc(L, R);
                    add = 3 + dp[L][R];
                }
                if (dp_frag[i] > dp_frag[j] + add) {
                    dp_frag[i] = dp_frag[j] + add;
                    go[i] = j;
                }
            }
        }
        int st = -1;
        for (int i = 0; i < n; i++) {
            int L = inds[i], R = inds[i] + sz - 1;
            int add = 0;
            if (R != r) {
                calc(R + 1, r);
                add = dp[R + 1][r];
            }
            if (dp[l][r] > dp_frag[i] + add) {
                dp[l][r] = dp_frag[i] + add;
                st = i;
            }
        }
        if (st != -1) {
            string rs = "";
            int L = inds[st], R = inds[st] + sz - 1;
            if (R != r) {
                rs = ans[R + 1][r];
            }
            vector<tuple<int, int, int>> items;
            int ct = 1;
            while (st != 0) {
                int j = go[st];
                int L = inds[j], R = inds[j] + sz - 1;

                if (R + 1 <= inds[st] - 1) {
                    items.push_back({R + 1, inds[st] - 1, ct});
                }
                st = j;
                ct++;
            }
            string ls = "[" + ans[l][i] + "]" + to_string(ct);
            string ms = "";
            if (items.size()) {
                reverse(items.begin(), items.end());
            }
            for (auto [L, R, ins] : items) {
                ms += "{" + ans[L][R] + "}" + to_string(ct - ins);
            }
            ans[l][r] = ls + ms + rs;
        }

    }
    return dp[l][r];
}

int main() {
    //IOS;
    while (cin >> s) {

        int n = s.size();
        long long p = 0, q = 0;
        long long p_pow = 1, q_pow = 1;
        for (int i = 0; i < n; i++) {
            p = (p + p_pow * (s[i] - 'a' + 200)) % M;
            q = (q + q_pow * (s[i] - 'a' + 200)) % M;
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
            pref[i] = {p, q};

            inv_p[i] = (i == 0 ? 1 : inv_p[i - 1] * INV_P % M);
            inv_q[i] = (i == 0 ? 1 : inv_q[i - 1] * INV_Q % M);
        }
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int sz = j - i + 1;
                auto h = get_rising(i, j, n);
                auto it = mp[sz].find(h);
                if (it == mp[sz].end()) {
                    mp[sz][h] = mp[sz].size();
                }
                id[i][j] = mp[sz][h];
                pos[sz][mp[sz][h]].push_back(i);
                dp[i][j] = -1;
            }
        }
        calc(0, n - 1);
        cout << dp[0][n - 1] << " " << ans[0][n - 1] << endl;
        for (int i = 0; i <= n; i++) {
            mp[i].clear();
            for (int j = 0; j <= n; j++) {
                pos[i][j].clear();
            }
        }

    }

    return 0;
}
