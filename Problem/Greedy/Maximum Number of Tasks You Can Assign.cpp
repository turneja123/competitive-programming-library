//https://leetcode.com/contest/biweekly-contest-65/problems/maximum-number-of-tasks-you-can-assign/
class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        int n = workers.size(), m = tasks.size();
        int l = 1, r = min(n, m), ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            multiset<int> a, b;
            int have = pills;
            for (int i = 0; i < mid; i++) {
                a.insert(workers[n - 1 - i]);
                b.insert(tasks[i]);
            }
            while (a.size() && b.size()) {
                int w = *a.begin();
                auto it = b.upper_bound(w);
                if (it != b.begin()) {
                    it--;
                    a.erase(a.begin());
                    b.erase(it);
                } else if (have == 0) {
                    break;
                } else {
                    have--;
                    w += strength;
                    it = b.upper_bound(w);
                    if (it != b.begin()) {
                        it--;
                        a.erase(a.begin());
                        b.erase(it);
                    } else {
                        break;
                    }
                }
            }
            if (a.empty() && b.empty()) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
