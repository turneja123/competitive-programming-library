//https://leetcode.com/contest/weekly-contest-248/problems/longest-common-subpath/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;


class Solution {
public:
    struct chash {
        long long operator()(pair<long long, long long> x) const { return x.first* M + x.second; }
    };

    gp_hash_table<pair<long long, long long>, int, chash> mp;


    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        int mn = 1e5 + 5, m = paths.size();
        for (int i = 0; i < m; i++) {
            if (paths[i].size() < mn) {
                mn = paths[i].size();
            }
        }
        int l = 1, r = mn, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            for (int j = 0; j < m; j++) {
                gp_hash_table<pair<long long, long long>, int, chash> cur;

                long long p = 0, q = 0;
                long long p_pow = 1, q_pow = 1;
                for (int i = 0; i < mid; i++) {
                    p = (p + p_pow * (paths[j][i] + 1)) % M;
                    q = (q + q_pow * (paths[j][i] + 1)) % M;
                    if (i != mid - 1) {
                        p_pow = (p_pow * P) % M;
                        q_pow = (q_pow * Q) % M;
                    }
                }
                pair<long long, long long> sub = make_pair(p, q);
                cur[sub]++;
                for (int i = mid; i < paths[j].size(); i++) {
                    p = ((p - (paths[j][i - mid] + 1) + M) * INV_P + p_pow * (paths[j][i] + 1)) % M;
                    q = ((q - (paths[j][i - mid] + 1) + M) * INV_Q + q_pow * (paths[j][i] + 1)) % M;
                    sub = make_pair(p, q);
                    cur[sub]++;
                }
                for (auto it : cur) {
                    mp[it.first] += 1;
                }
            }
            bool f = false;
            for (auto it : mp) {
                if (it.second == m) {
                    f = true;
                    break;
                }
            }
            mp.clear();
            if (f) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
