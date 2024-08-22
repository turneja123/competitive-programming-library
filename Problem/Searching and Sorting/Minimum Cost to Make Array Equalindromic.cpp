//https://leetcode.com/contest/weekly-contest-376/problems/minimum-cost-to-make-array-equalindromic/
vector<int> p;
class Solution {
public:
    const int N = 10000;
    long long pref[100005];
    int prod[8];
    
    void gen() {
        if (p.size()) {
            return;
        }
        prod[0] = 1;
        for (int i = 1; i < 7; i++) {
            prod[i] = prod[i - 1] * 10;
        }
        for (int i = 1; i < 10; i++) {
            p.push_back(i);
        }
        
        for (int i = 1; i < N; i++) {
            int j = 0, t = i, rev = 0;
            while (t > 0) {
                rev = rev * 10 + t % 10;
                t /= 10, j++;
            }
            int x = prod[j] * i + rev;
            p.push_back(x);
            for (int d = 0; d < 10 && j < 5; d++) {
                x = prod[j + 1] * i + prod[j] * d + rev;
                p.push_back(x);
            }
        }
        sort(p.begin(), p.end());
        return;
    }
    
    
    long long calc(int x, vector<int> a) {
        int r = lower_bound(a.begin(), a.end(), x) - a.begin(), n = a.size();
        long long ans = 0;
        if (r != 0) {
            ans += (long long)r * x - pref[r - 1];
        }
        if (r != n) {
            ans += pref[n - 1] - ((r == 0) ? 0 : pref[r - 1]) - (long long)(n - r) * x;
        }
        return ans;
    }
    
    long long minimumCost(vector<int>& a) {
        int n = a.size();
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            pref[i] = ((i == 0) ? a[i] : pref[i - 1] + a[i]);
        }
       
        long long ans = 1e18;
        gen();
        int x = lower_bound(p.begin(), p.end(), a[n / 2]) - p.begin();
        for (int i = max(0, x - 3); i < min((int)p.size(), x + 3); i++) {
            ans = min(ans, calc(p[i], a));
          
        }
        if (n % 2 == 0) {
            int x = lower_bound(p.begin(), p.end(), a[n / 2 - 1]) - p.begin();
            for (int i = max(0, x - 3); i < min((int)p.size(), x + 3); i++) {
                ans = min(ans, calc(p[i], a));

            }
        }
        return ans;
    }
};