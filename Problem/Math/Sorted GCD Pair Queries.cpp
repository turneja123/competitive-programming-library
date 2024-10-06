//https://leetcode.com/contest/weekly-contest-418/problems/sorted-gcd-pair-queries/
const int N = 1e5 + 5;
class Solution {
public:
    long long freq[N];
    long long ct[N];

    vector<int> gcdValues(vector<int>& a, vector<long long>& queries) {
        int mx = 0;
        for (int i = 0; i < a.size(); i++) {
            mx = max(mx, a[i]);
            freq[a[i]]++;
        }
        for (int i = 1; i <= mx; i++) {
            long long pref = 0;
            for (int j = i; j <= mx; j += i) {
                ct[i] += freq[j] * (freq[j] - 1) / 2 + pref * freq[j];
                pref += freq[j];
            }
        }
        for (int i = mx; i > 0; i--) {
            for (int j = i * 2; j <= mx; j += i) {
                ct[i] -= ct[j];
            }
        }
        set<pair<long long, int>> st;
        long long pref = 0;
        for (int i = 1; i <= mx; i++) {
            if (ct[i] == 0) {
                continue;
            }
            st.insert(make_pair(pref, i));
            pref += ct[i];
        }
        vector<int> ans;
        for (int i = 0; i < queries.size(); i++) {
            auto it = st.lower_bound(make_pair(queries[i], N));
            it--;
            ans.push_back(it->second);
        }
        return ans;
    }
};
