//https://leetcode.com/contest/weekly-contest-339/problems/mice-and-cheese/
class Solution {
public:
    static bool comp(pair<int, int> a, pair<int, int> b) {
        return a.first - a.second > b.first - b.second;
    }

    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size();
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++) {
            a.push_back(make_pair(reward1[i], reward2[i]));
        }
        sort(a.begin(), a.end(), comp);
        int ans = 0;
        for (int i = 0; i < k; i++) {
            ans += a[i].first;
        }
        for (int i = k; i < n; i++) {
            ans += a[i].second;
        }
        return ans;
    }
};
