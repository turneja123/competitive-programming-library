//https://leetcode.com/contest/biweekly-contest-140/problems/find-the-occurrence-of-first-almost-equal-substring/
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;
const int N = 3e5 + 5;

long long p_pow[N];
long long q_pow[N];
long long p_inv[N];
long long q_inv[N];
pair<long long, long long> h[N];
pair<long long, long long> h_pat[N];

class Solution {
public:
    void precalc() {
        p_pow[0] = 1, q_pow[0] = 1;
        p_inv[0] = 1, q_inv[0] = 1;
        for (int i = 1; i < N; i++) {
            p_pow[i] = p_pow[i - 1] * P % M;
            q_pow[i] = q_pow[i - 1] * Q % M;
            p_inv[i] = p_inv[i - 1] * INV_P % M;
            q_inv[i] = q_inv[i - 1] * INV_Q % M;
        }
    }

    void calc(string s) {
        int n = s.size();
        long long p = 0, q = 0;
        for (int i = 0; i < n; i++) {
            p = (p + p_pow[i] * (s[i] - 'a' + 1)) % M;
            q = (q + q_pow[i] * (s[i] - 'a' + 1)) % M;
            h_pat[i] = make_pair(p, q);
        }
        return;
    }

    int minStartingIndex(string s, string pattern) {
        if (p_pow[0] == 0) {
            precalc();
        }
        calc(pattern);
        int m = pattern.size(), n = s.size();
        long long p = 0, q = 0;
        for (int i = 0; i < n; i++) {
            p = (p + p_pow[i] * (s[i] - 'a' + 1)) % M;
            q = (q + q_pow[i] * (s[i] - 'a' + 1)) % M;
            h[i] = make_pair(p, q);
        }


        for (int i = 0; i < n; i++) {
            if (n - i < m) {
                break;
            }
            int l = i, r = i + m - 1, mismatch = r + 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                long long p = (h[mid].first - ((i == 0) ? 0 : h[i - 1].first) + M) * p_inv[i] % M;
                long long q = (h[mid].second - ((i == 0) ? 0 : h[i - 1].second) + M) * q_inv[i] % M;
                if (p != h_pat[mid - i].first || q != h_pat[mid - i].second) {
                    mismatch = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (mismatch == i + m || mismatch == i + m - 1) {
                return i;
            }
            mismatch++;
            long long p = (h[i + m - 1].first - h[mismatch - 1].first + M) * p_inv[mismatch] % M;
            long long q = (h[i + m - 1].second - h[mismatch - 1].second + M) * q_inv[mismatch] % M;

            long long p_pat = (h_pat[m - 1].first - h_pat[mismatch - i - 1].first + M) * p_inv[mismatch - i] % M;
            long long q_pat = (h_pat[m - 1].second - h_pat[mismatch - i - 1].second + M) * q_inv[mismatch - i] % M;
            if (p == p_pat && q == q_pat) {
                return i;
            }
        }
        cout << endl;
        return -1;
    }
};
