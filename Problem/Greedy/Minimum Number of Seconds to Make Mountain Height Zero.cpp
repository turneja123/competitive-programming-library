//https://leetcode.com/contest/weekly-contest-416/problems/minimum-number-of-seconds-to-make-mountain-height-zero/
class Solution {
public:
    long long minNumberOfSeconds(int x, vector<int>& a) {
        priority_queue<tuple<long long, long long, long long>> pq;
        long long ans = 0;
        for (int i = 0; i < a.size(); i++) {
            pq.push(tuple(-a[i], 1, a[i]));
        }
        while (x > 0 && pq.size()) {
            long long s = -get<0>(pq.top()), ct = get<1>(pq.top()), k = get<2>(pq.top());
            ans = max(ans, s);
            x--;
            ct++;
            pq.pop();
            pq.push(make_tuple(-(s + ct * k), ct, k));
        }
        return ans;
    }
};
