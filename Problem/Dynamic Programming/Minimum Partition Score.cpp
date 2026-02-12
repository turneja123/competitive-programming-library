//https://leetcode.com/problems/minimum-partition-score
using ll = long long;
const ll INF = 1e18;
class Solution {
public:
    struct CHT {
        vector<ll> m, b;
        int ptr = 0;

        bool bad(int l1, int l2, int l3) {
            return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query min),(slope inc+query max)
            return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  > 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query max), (slope inc+query min)
        }

        void add(ll _m, ll _b) {
            m.push_back(_m);
            b.push_back(_b);
            int s = m.size();
            while(s >= 3 && bad(s - 3, s - 2, s - 1)) {
                s--;
                m.erase(m.end() - 2);
                b.erase(b.end() - 2);
            }
        }

        ll f(int i, ll x) {
            return m[i] * x + b[i];
        }

        //(slope dec+query min), (slope inc+query max) -> x increasing
        //(slope dec+query max), (slope inc+query min) -> x decreasing
        ll query(ll x) {
            if (m.empty()) {
                return INF;
            }
            if(ptr >= m.size()) ptr = m.size() - 1;
            while(ptr < m.size() - 1 && f(ptr + 1, x) < f(ptr, x)) ptr++; // > for max
            return f(ptr, x);
        }

        ll bs(int l, int r, ll x) {
            int mid = (l + r) / 2;
            if(mid + 1 < m.size() && f(mid + 1, x) < f(mid, x)) return bs(mid + 1, r, x); // > for max
            if(mid - 1 >= 0 && f(mid - 1, x) < f(mid, x)) return bs(l, mid - 1, x); // > for max
            return f(mid, x);
        }
    };


    long long minPartitionScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, INF));
        vector<CHT> cht(k + 1);
        cht[0].add(0, 0);
        ll s = 0;
        for (int i = 1; i <= n; i++) {
            s += nums[i - 1];
            for (int j = min(k, i); j > 0; j--) {
                dp[i][j] = s * s + s + cht[j - 1].query(s);
                cht[j].add(-2 * s, dp[i][j] + s * s - s);
            }
        }
        return dp[n][k] / 2;
    }
};
