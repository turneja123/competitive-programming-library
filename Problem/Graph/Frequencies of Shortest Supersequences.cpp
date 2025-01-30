//https://leetcode.com/contest/weekly-contest-434/problems/frequencies-of-shortest-supersequences/
class Solution {
public:
    vector<int> adj[26];

    bool cycle;
    int color[26];

    void dfs(int u, vector<bool> &skip) {
        color[u] = 1;
        for (int v : adj[u]) {
            if (skip[v]) {
                continue;
            }

            if (color[v] == 0) {
                dfs(v, skip);
            } else if (color[v] == 1) {
                cycle = true;
            }
            if (cycle) {
                color[u] = 2;
                return;
            }
        }
        color[u] = 2;
        return;

    }


    vector<vector<int>> supersequences(vector<string>& words) {
        vector<int> seen(26, false);
        vector<int> db(26, false);
        for (int i = 0; i < words.size(); i++) {
            int x = words[i][0] - 'a', y = words[i][1] - 'a';
            if (x == y) {
                seen[x] = true;
                db[x] = true;
                continue;
            }
            seen[x] = true;
            seen[y] = true;
            adj[x].push_back(y);
        }
        vector<int> c;
        for (int i = 0; i < 26; i++) {
            if (seen[i]) {
                c.push_back(i);
            }
        }
        int n = c.size();
        vector<vector<int>> ans;
        int mn = n;
        for (int i = 0; i < 1 << n; i++) {
            bool bad = false;
            vector<bool> skip(26, 0);
            for (int j = 0; j < n; j++) {
                int ch = i & (1 << j);
                if (ch == 0 && db[c[j]] == true) {
                    bad = true;
                    break;
                }
                if (ch) {
                    skip[c[j]] = true;
                }
            }
            if (bad) {
                continue;
            }
            cycle = false;
            for (int j = 0; j < n; j++) {
                if (!color[c[j]] && !skip[c[j]]) {
                    dfs(c[j], skip);
                }
            }
            for (int j = 0; j < n; j++) {
                color[c[j]] = 0;
            }
            if (!cycle) {
                int ct = __builtin_popcount(i);
                if (ct > mn) {
                    continue;
                }
                if (ct < mn) {
                    mn = ct;
                    ans.clear();
                }
                vector<int> cur(26, 0);
                for (int j = 0; j < n; j++) {
                    int ch = i & (1 << j);
                    if (ch) {
                        cur[c[j]] = 2;
                    } else {
                        cur[c[j]] = 1;
                    }
                }
                ans.push_back(cur);
            }
        }
        return ans;
    }
};
