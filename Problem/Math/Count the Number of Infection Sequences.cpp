//https://leetcode.com/contest/weekly-contest-374/problems/count-the-number-of-infection-sequences/
const int N = 1e5 + 5;
const long long M = 1e9 + 7;

long long inv[N];
long long fact[N];
long long factinv[N];
long long pw[N];

class Solution {
public:
    int mark[N];

    void precalc() {
        fact[0] = 1, factinv[0] = 1, pw[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
            pw[i] = pw[i - 1] * 2 % M;
        }
        return;
    }

    long long binomial(long long n, long long k) {
        return fact[n] * factinv[k] % M * factinv[n - k] % M;
    }

    int numberOfSequence(int n, vector<int>& sick) {
        if (pw[0] == 0) {
            precalc();
        }
        int last = 0;
        for (int x : sick) {
            mark[x] = true;
        }
        vector<pair<int, int>> ways;
        for (int i = 0; i < n; i++) {
            if (mark[i]) {
                if (last != i) {
                    ways.push_back(make_pair(i - last, (last == 0 ? pw[0] : pw[i - last - 1])));
                }
                last = i + 1;
            }
        }
        int m = n - sick.size();
        if (last != n) {
            ways.push_back(make_pair(n - last, 1));
        }
        long long ans = 1;
        for (int i = 0; i < ways.size(); i++) {
            ans = ans * ways[i].second % M * binomial(m, ways[i].first) % M;
            m -= ways[i].first;
        }
        return ans;
    }
};
