//https://leetcode.com/problems/count-paths-that-can-form-a-palindrome-in-a-tree/description/
#pragma GCC target("popcnt")
bool bb[70000000];
map<int, int> mp[27][100005];
int vals[100005];
vector<pair<int, int>> adj[100005];
int parent[100005];
int sz[100005];

class Solution {
public:
    long long ans = 0;
    int dsu_find(int p) {
        if (parent[p] == p) {
            return p;
        }
        parent[p] = dsu_find(parent[p]);
        return parent[p];
    }

    void dsu_merge(int a, int b) {
        if (sz[a] > sz[b]) {
            swap(a, b);
        }
        parent[a] = b;
        for (int i = 0; i <= 26; i++) {
            for (auto it = mp[i][a].begin(); it != mp[i][a].end(); ++it) {
                int x = it->first, pc = __builtin_popcount(x);
                auto f = mp[pc][b].find(x);
                if (f != mp[pc][b].end()) {
                    ans += (long long)it->second * f->second;
                }
                for (int j = 0; j < 26; j++) {
                    int y = x ^ (1 << j); pc = __builtin_popcount(y);
                    if (!bb[y]) {
                        continue;
                    }
                    auto f = mp[pc][b].find(x ^ (1 << j));
                    if (f != mp[pc][b].end()) {
                        ans += (long long)it->second * f->second;
                    }
                }
            }
        }
        for (int i = 0; i <= 26; i++) {
            for (auto it = mp[i][a].begin(); it != mp[i][a].end(); ++it) {
                mp[__builtin_popcount(it->first)][b][it->first] += it->second;
            }
        }
        sz[b] = 0;
        for (int i = 0; i <= 26; i++) {
            sz[b] += mp[i][b].size();
        }
        return;
    }

    void dfs(int u, int p, int val) {
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = it->first, x = it->second;
            if (v != p) {
                dfs(v, u, val ^ (1 << x));
            }
        }
        mp[__builtin_popcount(val)][u][val]++;
        bb[val] = true;
        vals[u] = val;
        sz[u] = 1;
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = it->first;
            if (v != p) {
                int a = dsu_find(u), b = dsu_find(v);
                dsu_merge(a, b);
            }
        }

        return;
    }

    long long countPalindromePaths(vector<int>& par, string s) {
        int n = par.size();
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < n; j++) {
                mp[i][j].clear();
            }
        }
        for (int i = 1; i < n; i++) {
            adj[i].push_back(make_pair(par[i], s[i] - 'a'));
            adj[par[i]].push_back(make_pair(i, s[i] - 'a'));
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 0;
        }
        dfs(0, 0, 0);
        for (int i = 0; i < n; i++) {
            bb[vals[i]] = false;
            adj[i].clear();
        }
        return ans;
    }
};
