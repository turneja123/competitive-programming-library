//https://leetcode.com/problems/greatest-common-divisor-traversal/description/
class Solution {
public:
    int dsu_find(int p, vector<int> &parent) {
        if (parent[p] == p) {
            return p;
        }
        parent[p] = dsu_find(parent[p], parent);
        return parent[p];
    }

    void dsu_merge(int a, int b, vector<int> &parent, vector<int> &sz) {
        if (sz[a] > sz[b]) {
            swap(a, b);
        }
        parent[a] = b;
        sz[b] += sz[a];
        return;
    }

    void merge_group(vector<int> &group, vector<int> &parent, vector<int> &sz) {
        int a = dsu_find(group[0], parent);
        for (int j = 1; j < group.size(); j++) {
            int b = dsu_find(group[j], parent);
            a = dsu_find(a, parent);
            if (a != b) {
                dsu_merge(a, b, parent, sz);
            }
        }
    }

    bool canTraverseAllPairs(vector<int>& nums) {
        int N = 2e5;
        int m = sqrt(N), n = nums.size();
        vector<bool> composite(m, false);
        vector<int> primes;
        for (int i = 2; i < m; i++) {
            if (!composite[i]) {
                primes.push_back(i);
                for (int j = i * 2; j < m; j += i) {
                    composite[j] = true;
                }
            }
        }
        vector<int> parent(n);
        vector<int> sz(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        vector<vector<int>> heavy(N);
        for (int i = 0; i < primes.size(); i++) {
            vector<int> group;
            for (int j = 0; j < n; j++) {
                if (nums[j] % primes[i] == 0) {
                    group.push_back(j);
                    while(nums[j] % primes[i] == 0) {
                        nums[j] /= primes[i];
                    }
                }
            }
            if (group.size()) {
                merge_group(group, parent, sz);
            }
        }
        for (int i = 0; i < n; i++) {
            heavy[nums[i]].push_back(i);
        }
        for (int i = 2; i < N; i++) {
            if (heavy[i].size()) {
                merge_group(heavy[i], parent, sz);
            }
        }
        return sz[dsu_find(0, parent)] == n;
    }
};