//https://leetcode.com/contest/weekly-contest-405/problems/construct-string-with-minimum-cost/
const int N = 50005;
const int INF = 1e9;
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;
class Solution {
public:
    struct chash {
        long long operator()(pair<int, int> x) const { return (long long)x.first * M + x.second; }
    };
    unordered_map<pair<int, int>, int, chash> mp[N];
    long long p_pow[N];
    long long q_pow[N];
    long long inv_p[N];
    long long inv_q[N];
    long long pref_p[N];
    long long pref_q[N];
    int dp[N];
    set<int> sizes;

    pair<long long, long long> calc(string s) {
        int n = s.size();
        long long p = 0, q = 0;
        for (int i = 0; i < n; i++) {
            p = (p + p_pow[i] * (s[i] - 'a' + 1)) % M;
            q = (q + q_pow[i] * (s[i] - 'a' + 1)) % M;
        }
        return make_pair(p, q);
    }


    int minimumCost(string a, vector<string>& words, vector<int>& costs) {
        p_pow[0] = 1, q_pow[0] = 1;
        inv_p[0] = 1, inv_q[0] = 1;
        inv_p[1] = INV_P, inv_q[1] = INV_Q;
        for (int i = 1; i < a.size(); i++) {
            p_pow[i] = (p_pow[i - 1] * P) % M;
            q_pow[i] = (q_pow[i - 1] * Q) % M;
            if (i > 1) {
                inv_p[i] = (inv_p[i - 1] * INV_P) % M;
                inv_q[i] = (inv_q[i - 1] * INV_Q) % M;
            }
        }
        for (int i = 0; i < words.size(); i++) {
            int m = words[i].size();
            auto it = mp[m].find(calc(words[i]));
            if (it == mp[m].end()) {
                mp[m][calc(words[i])] = costs[i];
            } else {
                it->second = min(it->second, costs[i]);
            }
            sizes.insert(m);
        }
        int n = a.size();
        long long p = 0, q = 0;
        for (int i = 0; i < n; i++) {
            p = (p + p_pow[i] * (a[i] - 'a' + 1)) % M;
            q = (q + q_pow[i] * (a[i] - 'a' + 1)) % M;
            pref_p[i] = p;
            pref_q[i] = q;
        }
        for (int i = 0; i < n; i++) {
            dp[i] = INF;
            for (int x : sizes) {
                if (x > i + 1) {
                    break;
                }
                int l = i - x + 1;
                long long p = (pref_p[i] - ((l == 0) ? 0 : pref_p[l - 1]) + M) * inv_p[l] % M;
                long long q = (pref_q[i] - ((l == 0) ? 0 : pref_q[l - 1]) + M) * inv_q[l] % M;
                auto it = mp[x].find(make_pair(p, q));
                if (it == mp[x].end()) {
                    continue;
                }
                dp[i] = min(dp[i], ((l == 0) ? it->second : dp[l - 1] + it->second));
            }
        }
        if (dp[n - 1] == INF) {
            return -1;
        }
        return dp[n - 1];

    }
};
