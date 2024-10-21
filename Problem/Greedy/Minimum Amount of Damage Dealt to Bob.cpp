//https://leetcode.com/contest/biweekly-contest-138/problems/minimum-amount-of-damage-dealt-to-bob/
const int N = 1e5 + 5;
pair<long long, long long> a[N];
class Solution {
public:
    static bool comp(pair<long long, long long> a, pair<long long, long long> b) {
        //return (long double)a.first / a.second > (long double)b.first / b.second;
        return a.first * b.second > a.second * b.first;
    }

    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        int n = health.size();
        long long sum = 0, p = power;
        for (int i = 0; i < n; i++) {
            a[i].first = damage[i];
            health[i] = health[i] / p + ((health[i] % p) ? 1 : 0);
            a[i].second = health[i];
            sum += damage[i];
        }
        sort(a, a + n, comp);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long h = a[i].second, d = a[i].first;
            ans += h * sum;
            sum -= d;
        }
        return ans;

    }
};
