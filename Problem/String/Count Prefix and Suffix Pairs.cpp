//https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/
class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        map<pair<long long, long long>, long long> mp;
        long long P = 26;
        long long Q = 53;
        long long M = 1e9 + 7;
        
        long long ans = 0;
        int n = words.size();
        for (int i = 0; i < n; i++) {
            long long p_pow = 1;
            long long q_pow = 1;
            long long p_pref = 0, q_pref = 0;
            long long p_suf = 0, q_suf = 0;
            
            for (int j = 0; j < words[i].size(); j++) {
                long long c_pref = (words[i][j] - 'a') + 1;
                long long c_suf = (words[i][words[i].size() - 1 - j] - 'a') + 1;
                p_pref = (p_pref + c_pref * p_pow) % M;
                q_pref = (q_pref + c_pref * q_pow) % M;
                p_pow = (p_pow * P) % M;
                q_pow = (q_pow * Q) % M;
                p_suf = (p_suf * P + c_suf) % M;
                q_suf = (q_suf * Q + c_suf) % M;
    
                
                if (p_pref == p_suf && q_pref == q_suf) {
                    pair<long long, long long> hash = make_pair(p_pref, q_pref);
                    if (mp.find(hash) != mp.end()) {
                        ans += mp[hash];
                    }
                }  
            }
            pair<long long, long long> hash = make_pair(p_pref, q_pref);
            mp[hash]++;
            
        }
        return ans;
    }
};