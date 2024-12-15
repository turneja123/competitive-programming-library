//https://leetcode.com/problems/largest-component-size-by-common-factor/description/
const int N = 1e5 + 5;
vector<int> divs[N];
bool seen[N];
class Solution {
public:
    int parent[N];
    int sz[N];

    void precalc() {
        for (int i = 2; i < N; i++) {
            for (int j = i; j < N; j += i) {
                divs[j].push_back(i);
            }
        }
    }

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

    int largestComponentSize(vector<int>& nums) {
        if (divs[2].size() == 0) {
            precalc();
        }
        vector<int> q;

        for (int i = 0; i < nums.size(); i++) {
            seen[nums[i]] = true;
            q.push_back(nums[i]);
            sz[nums[i]] = 1;
            parent[nums[i]] = nums[i];
        }

        for (int i = 0; i < nums.size(); i++) {
            for (int x : divs[nums[i]]) {
                if (!seen[x]) {
                    seen[x] = true;
                    parent[x] = nums[i];
                    q.push_back(x);
                } else {
                    int a = dsu_find(x), b = dsu_find(nums[i]);
                    if (a != b) {
                        dsu_unite(a, b);
                    }

                }
            }
        }
        int ans = 1;
        for (int i = 0; i < nums.size(); i++) {
            ans = max(ans, sz[dsu_find(nums[i])]);
        }
        for (int x : q) {
            seen[x] = false;
        }
        return ans;
    }
};
