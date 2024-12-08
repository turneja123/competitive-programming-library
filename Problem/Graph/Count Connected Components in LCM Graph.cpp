//https://leetcode.com/contest/biweekly-contest-145/problems/count-connected-components-in-lcm-graph/
const int N = 2e5 + 5;
class Solution {
public:
    int parent[N];
    int sz[N];

    int dsu_find(int a) {
        if (parent[a] == a) {
            return a;
        }
        return parent[a] = dsu_find(parent[a]);
    }

    void dsu_unite(int a, int b) {
        if (sz[b] > sz[a]) {
            swap(a, b);
        }
        sz[a] += sz[b];
        parent[b] = a;
    }

    int countComponents(vector<int>& nums, int threshold) {
        int n = nums.size();
        int ans = 0;

        for (int i = 1; i <= threshold; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] > threshold) {
                ans++;
            }
        }

        for (int k = 0; k < n; k++) {
            int i = nums[k];
            for (int j = 2 * i; j <= threshold; j += i) {
                int a = dsu_find(i), b = dsu_find(j);
                if (a != b) {
                    dsu_unite(a, b);
                }
            }
        }

        set<int> seen;
        for (int i = 0; i < n; i++) {
            if (nums[i] <= threshold) {
                int a = dsu_find(nums[i]);
                auto it = seen.find(a);
                if (it == seen.end()) {
                    ans++;
                    seen.insert(a);
                }
            }
        }
        return ans;
    }
};
