//https://leetcode.com/problems/find-the-number-of-subarrays-where-boundary-elements-are-maximum/description/
class Solution {
public:
    map<int, vector<int>> mp;
    long long a[100005];
    long long segtree[400020];

    long long rmq(int l, int r, int lq, int rq, int node) {
        if (lq <= l && rq >= r) {
            return segtree[node];
        }

        if (l > rq || r < lq) {
            return 0;
        }

        int mid = (l + r) / 2;
        return max(rmq(l, mid, lq, rq, 2 * node + 1),
                   rmq(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[node] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
    }
    
    long long numberOfSubarrays(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
            a[i] = nums[i];
        }
        long long ans = 0;
        build(0, n - 1, 0);
        for (int i = 0; i < n; i++) {
            auto it = mp.find(a[i]);
            int m = (it->second).size();
            int l = 0, r = lower_bound((it->second).begin(), (it->second).end(), i) - (it->second).begin(), pos = -1, rq = r;
            while (l <= r) {
                int mid = (l + r) / 2;
                int lq = (it->second)[mid];
                if (rmq(0, n - 1, lq, i, 0) == a[i]) {
                    r = mid - 1;
                    pos = mid;
                } else {
                    l = mid + 1;
                }
            }
            if (pos != -1) {
                ans += rq - pos + 1;
            }
        }
        return ans;
        
    }
};