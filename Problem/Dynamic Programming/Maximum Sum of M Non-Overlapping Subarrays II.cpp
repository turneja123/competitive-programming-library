//https://leetcode.com/problems/maximum-sum-of-m-non-overlapping-subarrays-ii/
using ll = long long;

class Solution {
public:

    pair<ll, int> calc(ll cost, vector<int> &a, int l, int r) {

        int n = a.size();
        vector<ll> pref(n + 1);
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] + a[i - 1];
        }

        vector<pair<ll, int>> dp(n + 1), take(n + 1);

        multiset<pair<ll, int>> st;
        int lq = 0, rq = 0;
        for (int i = 0; i < l; i++) {
            take[i] = make_pair(-pref[i], 0);
        }
        for (int i = l; i <= n; i++) {
            dp[i] = dp[i - 1];
            while (i - rq >= l) {
                st.insert(take[rq]);
                rq++;
            }
            while (i - lq > r) {
                st.erase(st.find(take[lq]));
                lq++;
            }
            auto it = st.rbegin();
            dp[i] = max(dp[i], make_pair(it->first + pref[i] - cost, it->second + 1));
            take[i] = make_pair(dp[i].first - pref[i], dp[i].second);
        }
        return dp[n];
    }

    long long maximumSum(vector<int>& a, int m, int l, int r) {
        int n = a.size();
        vector<ll> pref(n + 1);
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] + a[i - 1];
        }
        ll best = -1e10;
        vector<ll> take(n + 1);
        multiset<ll> st;
        int lq = 0, rq = 0;
        for (int i = 0; i < l; i++) {
            take[i] = -pref[i];
        }
        for (int i = l; i <= n; i++) {
            while (i - rq >= l) {
                st.insert(take[rq]);
                rq++;
            }
            while (i - lq > r) {
                st.erase(st.find(take[lq]));
                lq++;
            }
            auto it = st.rbegin();
            best = max(best, *it + pref[i]);
            take[i] = -pref[i];
        }
        if (best <= 0) {
            return best;
        }
        auto x = calc(0, a, l, r);
        if (x.second < m) {
            return x.first;
        }

        ll lb = 0, rb = 1e10, spl;
        while (lb <= rb) {
            ll mid = (lb + rb) / 2;
            if (calc(mid, a, l, r).second >= m) {
                spl = mid;
                lb = mid + 1;
            } else {
                rb = mid - 1;
            }
        }
        x = calc(spl, a, l, r);
        ll ans = x.first + spl * m;
        return ans;
    }
};
