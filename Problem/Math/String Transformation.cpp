//https://leetcode.com/contest/weekly-contest-362/problems/string-transformation/
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 9923, INV_Q = 452282579;
const int N = 5e5 + 5;

class Solution {
public:
    long long pw_p[N], pw_q[N];
    long long inv_p[N], inv_q[N];

    pair<long long, long long> pref[N];

    vector<long long> mul_poly(int n, vector<long long> &a, vector<long long> &b, vector<long long> &tr) {
        vector<long long> res(n * 2 + 1, 0);
        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < n + 1; j++) {
                res[i + j] = (res[i + j] + a[i] * b[j]) % M;
            }
        }
        for (int i = 2 * n; i > n; --i) {
            for (int j = 0; j < n; j++) {
                res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % M;
            }
        }
        res.resize(n + 1);
        return res;
    }

    long long solve(vector<long long> &c, vector<long long> &s, long long k) {
        int n = c.size();
        if (n == 0) {
            return 0;
        }
        if (k < n) {
            return s[k];
        }
        vector<long long> x(n + 1), a(x);
        x[0] = 1, a[1] = 1;
        for (++k; k; k /= 2) {
            if (k % 2) {
                x = mul_poly(n, x, a, c);
            }
            a = mul_poly(n, a, a, c);
        }
        long long res = 0;
        for (int i = 0; i < n; i++) {
            res = (res + x[i + 1] * s[i]) % M;
        }
        return res;
    }

    pair<long long, long long> calc(string s) {
        int n = s.size();
        long long p = 0, q = 0;
        long long p_pow = 1, q_pow = 1;
        for (int i = 0; i < n; i++) {
            p = (p + p_pow * (s[i] - 'a' + 1)) % M;
            q = (q + q_pow * (s[i] - 'a' + 1)) % M;
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
        }
        return make_pair(p, q);
    }


    pair<long long, long long> mul(pair<long long, long long> a, pair<long long, long long> b) {
        return make_pair(a.first * b.first % M, a.second * b.second % M);
    }

    pair<long long, long long> sub(pair<long long, long long> a, pair<long long, long long> b) {
        return make_pair((a.first - b.first + M) % M, (a.second - b.second + M) % M);
    }

    pair<long long, long long> add(pair<long long, long long> a, pair<long long, long long> b) {
        return make_pair((a.first + b.first + M) % M, (a.second + b.second + M) % M);
    }

    int numberOfWays(string s, string t, long long k) {
        int n = s.size();
        /*dp[0][0] = 1;
        for (int j = 1; j <= k; j++) {
            for (int i = 0; i < n; i++) {
                for (int k = 0; k < n; k++) {
                    dp[j][i] += dp[j - 1][k];
                }
                dp[j][i] -= dp[j - 1][i];
                cout << dp[j][i] << " ";
            }
            cout << endl;
        }*/
        //a(n) = (n - 2) * a(n - 1) + (n - 1) * a(n - 2), a(0) = 0, a(1) = 1
        vector<long long> S{0, 1}, C{n - 2, n - 1};
        long long dp = solve(C, S, k);
        pw_p[0] = 1, pw_q[0] = 1;
        inv_p[0] = 1, inv_q[0] = 1;
        for (int i = 1; i < n; i++) {
            pw_p[i] = pw_p[i - 1] * P % M;
            pw_q[i] = pw_q[i - 1] * Q % M;
            inv_p[i] = inv_p[i - 1] * INV_P % M;
            inv_q[i] = inv_q[i - 1] * INV_Q % M;
        }
        for (int i = 0; i < n; i++) {
            pref[i].first = ((i == 0 ? 0 : pref[i - 1].first) + (s[i] - 'a' + 1) * pw_p[i]) % M;
            pref[i].second = ((i == 0 ? 0 : pref[i - 1].second) + (s[i] - 'a' + 1) * pw_q[i]) % M;
        }
        long long ans = 0;
        pair<long long, long long> need = calc(t);
        for (int i = 0; i < n - 1; i++) {
            pair<long long, long long> h = mul(sub(pref[n - 1], pref[i]), make_pair(inv_p[i + 1], inv_q[i + 1]));
            h = add(h, mul(pref[i], make_pair(pw_p[n - 1 - i], pw_q[n - 1 - i])));
            if (h == need) {
                ans = (ans + dp) % M;
            }
        }
        if (k % 2 == 1) {
            dp--;
        } else {
            dp++;
        }
        dp = (dp + M) % M;
        if (pref[n - 1] == need) {
            ans = (ans + dp) % M;
        }
        return ans;
    }
};
