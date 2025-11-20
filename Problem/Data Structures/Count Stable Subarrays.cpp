//https://leetcode.com/problems/count-stable-subarrays/description/
struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    BIT(int _n, vector<int> &a) {
        n = _n;
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                t[j] += t[i];
            }
        }
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, long long val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
class Solution {
public:
    long long s(int n) {
        return (long long)n * (n + 1) / 2;
    }

    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        stack<int> st;
        vector<int> a(n);
        BIT bit_sum(n), bit_ct(n);
        vector<pair<int, int>> ord;
        for (int i = 0; i < n; i++) {
            while (st.size() && nums[st.top()] <= nums[i]) {
                st.pop();
            }
            if (st.empty()) {
                a[i] = -1;
            } else {
                a[i] = st.top();
            }
            if (i != 0) {
                a[i] = max(a[i], a[i - 1]);
            }
            st.push(i);
            bit_sum.upd(i + 1, a[i]);
            ord.push_back({a[i], i});
        }
        sort(ord.begin(), ord.end());
        int q = queries.size();
        vector<tuple<int, int, int>> queries_sorted;
        for (int i = 0; i < q; i++) {
            queries_sorted.push_back(make_tuple(queries[i][0], queries[i][1], i));
        }
        sort(queries_sorted.begin(), queries_sorted.end());
        vector<long long> ans(q);
        for (int i = 0, j = 0; i < q; i++) {
            auto [l, r, ind] = queries_sorted[i];
            while (j < n && ord[j].first + 1 < l) {
                bit_sum.upd(ord[j].second + 1, -ord[j].first);
                bit_ct.upd(ord[j].second + 1, 1);
                j++;
            }
            ans[ind] = s(r) - s(l - 1) - bit_sum.query(l + 1, r + 1) - bit_ct.query(l + 1, r + 1) * (l - 1);
        }
        return ans;
    }
};
