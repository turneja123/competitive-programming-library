//https://leetcode.com/contest/weekly-contest-373/problems/count-beautiful-substrings-ii/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
class Solution {
public:
    struct chash {
        long long operator()(pair<int, int> x) const { return (long long)x.first* 50005 + x.second; }
    };
    gp_hash_table<pair<int, int>, int, chash> mp[4000];
    vector<int> good[4000];

    bool vow(char c) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            return true;
        }
        return false;
    }
    long long beautifulSubstrings(string s, int k) {
        pair<int, int> p = {0, 0};
        long long ans = 0;
        k *= 4;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                int x = (i - j + k) % k;
                if ((x * x) % k == 0) {
                    good[i].push_back(j);
                }
            }
        }
        for (int i = 1; i <= s.size(); i++) {
            if (vow(s[i - 1])) {
                p.first++;
            } else {
                p.second++;
            }
            int mn = min(p.first, p.second);
            p.first -= mn, p.second -= mn;
            int d = i % k;
            for (int j : good[d]) {
                auto it = mp[j].find(p);
                if (it != mp[j].end()) {
                    ans += it->second;
                }
            }
            mp[d][p]++;
            if (p.first == 0 && p.second == 0 && ((long long)i * i) % k == 0) {
                ans++;
            }
        }
        return ans;

    }
};
