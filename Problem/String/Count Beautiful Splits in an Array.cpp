//https://leetcode.com/contest/weekly-contest-428/problems/count-beautiful-splits-in-an-array/
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;
const int N = 5005;
class Solution {
public:
    pair<long long, long long> h[N];
    long long p_pow[N], q_pow[N];
    long long p_inv[N], q_inv[N];
    int beautifulSplits(vector<int>& a) {
        long long p = 0, q = 0;
        int n = a.size();
        for (int i = 0; i < n; i++) {
            p_pow[i] = (i == 0 ? 1 : p_pow[i - 1] * P % M);
            q_pow[i] = (i == 0 ? 1 : q_pow[i - 1] * Q % M);
            p_inv[i] = (i == 0 ? 1 : p_inv[i - 1] * INV_P % M);
            q_inv[i] = (i == 0 ? 1 : q_inv[i - 1] * INV_Q % M);
            p = (p + p_pow[i] * (a[i] + 1)) % M;
            q = (q + q_pow[i] * (a[i] + 1)) % M;
            h[i] = make_pair(p, q);
        }
        int ans = 0;
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                bool can = false;
                if (i <= j - i) {
                    pair<long long, long long> lf = h[i - 1];
                    pair<long long, long long> rt = make_pair((h[i + i - 1].first - h[i - 1].first + M) * p_inv[i] % M, (h[i + i - 1].second - h[i - 1].second + M) * q_inv[i] % M);
                    if (rt.first == lf.first && rt.second == lf.second) {
                        can = true;
                    }
                }
                if (j - i <= n - j) {
                    pair<long long, long long> lf = make_pair((h[j - 1].first - h[i - 1].first + M) * p_inv[i] % M, (h[j - 1].second - h[i - 1].second + M) * q_inv[i] % M);;
                    pair<long long, long long> rt = make_pair((h[j + j - i - 1].first - h[j - 1].first + M) * p_inv[j] % M, (h[j + j - i - 1].second - h[j - 1].second + M) * q_inv[j] % M);
                    if (rt.first == lf.first && rt.second == lf.second) {
                        can = true;
                    }
                }
                if (can) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
