//https://leetcode.com/contest/weekly-contest-420/problems/check-if-dfs-strings-are-palindromes/
const int N = 1e5 + 5;
bool ans[N];
vector<int> adj[N];
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;
long long p_pow[N];
long long q_pow[N];
long long inv_p[N];
long long inv_q[N];
int sz[N];
pair<long long, long long> pref[N];
pair<long long, long long> suf[N];

class Solution {
public:
    void precalc(int N) {
        p_pow[0] = 1, q_pow[0] = 1;
        inv_p[0] = 1, inv_q[0] = 1;
        for (int i = 1; i < N; i++) {
            p_pow[i] = (p_pow[i - 1] * P) % M;
            q_pow[i] = (q_pow[i - 1] * Q) % M;
            inv_p[i] = (inv_p[i - 1] * INV_P) % M;
            inv_q[i] = (inv_q[i - 1] * INV_Q) % M;
        }
    }

    void dfs(int u, int p, string &s) {
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, s);
                sz[u] += sz[v];
            }
        }
        int c = s[u] - 'a' + 1;
        if (s[u] == 1) {
            pref[u] = make_pair(c, c);
            suf[u] = pref[u];
            ans[u] = true;
            return;
        }
        int cur = 0;
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != p) {
                pref[u].first = (pref[u].first + p_pow[cur] * pref[v].first) % M;
                pref[u].second = (pref[u].second + q_pow[cur] * pref[v].second) % M;
                cur += sz[v];
            }
        }
        pref[u].first = (pref[u].first + p_pow[cur] * c) % M;
        pref[u].second = (pref[u].second + q_pow[cur] * c) % M;

        suf[u].first = c;
        suf[u].second = c;
        cur = 1;
        for (int i = adj[u].size() - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (v != p) {
                suf[u].first = (suf[u].first + p_pow[cur] * suf[v].first) % M;
                suf[u].second = (suf[u].second + q_pow[cur] * suf[v].second) % M;
                cur += sz[v];
            }
        }
        if (pref[u].first == suf[u].first && pref[u].second == suf[u].second) {
            ans[u] = true;
        } else {
            ans[u] = false;
        }
    }

    vector<bool> findAnswer(vector<int>& parent, string s) {
        if (p_pow[1] == 0) {
            precalc(N);
        }
        int n = parent.size();
        for (int i = 1; i < n; i++) {
            adj[i].push_back(parent[i]);
            adj[parent[i]].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            sort(adj[i].begin(), adj[i].end());
        }
        dfs(0, 0, s);
        vector<bool> can(n, false);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            can[i] = ans[i];
            pref[i] = make_pair(0, 0);
            suf[i] = make_pair(0, 0);
        }
        return can;
    }
};
