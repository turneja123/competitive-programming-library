//https://leetcode.com/problems/longest-common-suffix-queries/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
class Solution {
public:
    struct chash {
        long long operator()(pair<long long, long long> x) const { return x.first* (long long)(1000000007) + x.second; }
    };
    gp_hash_table<pair<long long, long long>, pair<int, int>, chash> mp;
    
    void calc_hash(string a, int i) {
        long long P = 26;
        long long Q = 53;
        long long M = 1e9 + 7;
        
        long long p_pow = 1;
        long long q_pow = 1;
        long long p = 0, q = 0;
            
        for (int j = a.size() - 1; j >= 0; j--) {
            long long c = (a[j] - 'a') + 1;
            p = (p + c * p_pow) % M;
            q = (q + c * q_pow) % M;
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
            auto it = mp.find(make_pair(p, q));
            if (it == mp.end()) {
                mp[make_pair(p, q)] = make_pair(a.size(), i);
            } else {
                if (a.size() < (it->second).first) {
                    (it->second).first = a.size();
                    (it->second).second = i;
                }
            }
        }
        return; 
    }
    
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        int mx = 1e6, dflt = -1;
        for (int i = 0; i < wordsContainer.size(); i++) {
            calc_hash(wordsContainer[i], i);
            if (wordsContainer[i].size() < mx) {
                mx = wordsContainer[i].size();
                dflt = i;
            }
        }
        int n = wordsQuery.size();
        vector<int> ans(n, -1);
        for (int i = 0; i < n; i++) {
            int cur = dflt;
            long long P = 26;
            long long Q = 53;
            long long M = 1e9 + 7;

            long long p_pow = 1;
            long long q_pow = 1;
            long long p = 0, q = 0;

            for (int j = wordsQuery[i].size() - 1; j >= 0; j--) {
                long long c = (wordsQuery[i][j] - 'a') + 1;
                p = (p + c * p_pow) % M;
                q = (q + c * q_pow) % M;
                p_pow = (p_pow * P) % M;
                q_pow = (q_pow * Q) % M;
                auto it = mp.find(make_pair(p, q));
                if (it != mp.end()) {
                    cur = (it->second).second;
                } 
            }
            ans[i] = cur;
        }
        return ans;
    }
};