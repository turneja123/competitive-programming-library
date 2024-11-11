//https://leetcode.com/contest/weekly-contest-247/problems/count-ways-to-build-rooms-in-an-ant-colony/
const int N = 1e5 + 5;
const long long M = 1e9 + 7;
vector<int> adj[N];
long long inv[N];
long long fact[N];
long long factinv[N];
long long dp[N];
int sz[N];

class Solution {
public:
    void precalc() {
        fact[0] = 1, factinv[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
        }
    }

    long long binomial(long long n, long long k) {
        return fact[n] * factinv[k] % M * factinv[n - k] % M;
    }

    void dfs(int u, int p) {
        dp[u] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        }
        int m = sz[u];
        for (int v : adj[u]) {
            if (v != p) {
                dp[u] = dp[u] * binomial(m, sz[v]) % M * dp[v] % M;
                m -= sz[v];
            }
        }
        sz[u]++;
        return;
    }

    int waysToBuildRooms(vector<int>& prevRoom) {
        if (fact[0] == 0) {
            precalc();
        }
        int n = prevRoom.size();
        for (int i = 1; i < n; i++) {
            adj[i].push_back(prevRoom[i]);
            adj[prevRoom[i]].push_back(i);
        }
        dfs(0, 0);
        long long ans = dp[0];
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            dp[i] = 0, sz[i] = 0;
        }
        return ans;
    }
};
