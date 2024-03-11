//https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-ii/description/
class Solution {
public:
    void indices(string s, string a, vector<int> &pos) {
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
        }
        p_pow = 1, q_pow = 1;
        long long p_sub = 0, q_sub = 0;
        for (int j = a.size() - 1; j >= 0; j--) {
            long long c = (s[j] - 'a') + 1;
            p_sub = (p_sub + c * p_pow) % M;
            q_sub = (q_sub + c * q_pow) % M;
            if (j != 0) {
                p_pow = (p_pow * P) % M;
                q_pow = (q_pow * Q) % M;
            }
        }
        if (p_sub == p && q_sub == q) {
            pos.push_back(0);
        }
        for (int j = a.size(); j < s.size(); j++) {
            long long c_prev = (s[j - a.size()] - 'a') + 1;
            long long c = (s[j] - 'a') + 1;
            p_sub = ((((p_sub - (c_prev * p_pow) % M) + M) % M) * P + c) % M;
            q_sub = ((((q_sub - (c_prev * q_pow) % M) + M) % M) * Q + c) % M;
            if (p_sub == p && q_sub == q) {
                pos.push_back(j - a.size() + 1);
            }
        }
        return;
        
    }
    
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> posa;
        vector<int> posb;
        vector<int> ans;
        if (s.size() < a.size() || s.size() < b.size()) {
            return posa;
        }
        indices(s, a, posa);
        indices(s, b, posb);
        if (posa.empty()) {
            return posa;
        }
        if (posb.empty()) {
            return posb;
        }
        for (int i : posa) {
            auto it = lower_bound(posb.begin(), posb.end(), i);
            if (it == posb.end()) {
                --it;
            }
            if (it != posb.end()) {
                if (abs(*it - i) <= k) {
                    ans.push_back(i);
                } else if (it != posb.begin()) {
                    --it;
                    if (abs(i - *it) <= k) {
                        ans.push_back(i);
                    }
                }
            }
        }
        return ans; 
    }
};