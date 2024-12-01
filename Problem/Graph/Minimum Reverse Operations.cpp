//https://leetcode.com/contest/weekly-contest-339/problems/minimum-reverse-operations/
const int N = 1e5 + 5;
class Solution {
public:
    bool ban[N];
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        set<int> st[2];
        for (int i : banned) {
            ban[i] = true;
        }
        vector<int> dist(n, N);
        for (int i = 0; i < n; i++) {
            if (!ban[i] && i != p) {
                st[i % 2].insert(i);
            }
        }
        queue<int> q;
        dist[p] = 0;
        q.push(p);
        while (q.size()) {
            int i = q.front();
            q.pop();
            int l = max(0, k - (i + 1)), r = k - 1 - max(0, (i - (n - k)));

            int leftmost = i - k + 1;
            int j = leftmost + l * 2;

            int m = (i % 2) ^ ((k + 1) % 2);
            auto it = st[m].lower_bound(j);
            while (it != st[m].end() && *it <= leftmost + r * 2) {
                dist[*it] = dist[i] + 1;
                q.push(*it);
                it = st[m].erase(it);
            }
        }
        for (int i = 0; i < n; i++) {
            if (dist[i] == N) {
                dist[i] = -1;
            }
        }
        return dist;
    }
};
