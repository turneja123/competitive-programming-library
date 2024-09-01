//https://leetcode.com/contest/biweekly-contest-138/problems/find-the-count-of-good-integers/
long long ans[11][10];
class Solution {
public:
    long long f[15];
    set<vector<int>> st[10];

    long long calc(int n, vector<int> &v) {
        long long ans = 0;
        long long a = 0, denom = 1; vector<int> d;
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < v[j]; k++) {
                d.push_back(j);
            }
            denom = (denom * f[v[j]]);
        }
        long long ways = f[n] / denom;
        if (v[0] > 0) {
            denom = denom * f[v[0] - 1];
            denom = denom / f[v[0]];
            ways = ways - f[n - 1] / denom;
        }
        ans = ways;
        return ans;
    }

    void precalc() {
        f[0] = 1;
        for (long long i = 1; i < 11; i++) {
            f[i] = f[i - 1] * i;
        }
        for (long long i = 1; i < 100000; i++) {
            string s = to_string(i);
            string rev = s;
            reverse(rev.begin(), rev.end());
            string palin = s + rev;
            vector<int> d(10, 0);
            long long t = i, ct = 0;
            while (t > 0) {
                d[t % 10] += 2;
                ct += 2;
                t /= 10;
            }
            for (int k = 1; k < 10; k++) {
                if (stoll(palin) % k == 0) {
                    if (st[k].find(d) == st[k].end()) {
                        ans[ct][k] += calc(ct, d);
                        st[k].insert(d);
                    }
                }
            }
            if (ct + 1 < 11) {
                for (int c = 0; c < 10; c++) {
                    d[c]++;
                    palin = s + to_string(c) + rev;
                    for (int k = 1; k < 10; k++) {
                        if (stoll(palin) % k == 0) {
                            if (st[k].find(d) == st[k].end()) {
                                ans[ct + 1][k] += calc(ct + 1, d);
                                st[k].insert(d);
                            }
                        }
                    }
                    d[c]--;
                }
            }
        }
        return;
    }


    long long countGoodIntegers(int n, int k) {
        if (n == 1) {
            return 9 / k;
        }
        if (ans[5][6] == 0) {
            precalc();
        }
        return ans[n][k];
    }
};
