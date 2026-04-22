//https://leetcode.com/problems/good-subsequence-queries/description/
const int N = 5e4 + 5;

vector<int> divs[N];
int spf[N];
int freq[N];
int prime_freq[N];

class Solution {
public:

    void precalc() {
        for (int i = 1; i < N; i++) {
            spf[i] = i;
        }
        for (int i = 2; i < N; i++) {
            if (spf[i] == i) {
                for (int j = 2 * i; j < N; j += i) {
                    spf[j] = min(spf[j], i);
                }
            }
        }

        for (int i = 1; i < N; i++) {
            for (int j = i; j < N; j += i) {
                divs[j].push_back(i);
            }
        }
    }

    int countGoodSubseq(vector<int>& nums, int p, vector<vector<int>>& queries) {
        if (divs[2].empty()) {
            precalc();
        }
        int n = nums.size(), m = 0;
        multiset<pair<int, int>> st;
        for (int i = 0; i < n; i++) {
            if (nums[i] % p == 0) {
                int x = nums[i] / p;
                for (int d : divs[x]) {
                    freq[d]++;
                }
                int last = -1;
                while (x > 1) {
                    if (last == spf[x]) {
                        x /= spf[x];
                        continue;
                    }
                    if (prime_freq[spf[x]] != 0) {
                        st.erase({prime_freq[spf[x]], spf[x]});
                    }
                    prime_freq[spf[x]]++;
                    st.insert({prime_freq[spf[x]], spf[x]});
                    last = spf[x];
                    x /= spf[x];
                }
                m++;
            }
        }
        int ans = 0;
        for (int j = 0; j < queries.size(); j++) {
            int i = queries[j][0], y = queries[j][1];
            if (nums[i] % p == 0) {
                int x = nums[i] / p;
                for (int d : divs[x]) {
                    freq[d]--;
                }
                int last = -1;
                while (x > 1) {
                    if (last == spf[x]) {
                        x /= spf[x];
                        continue;
                    }
                    st.erase({prime_freq[spf[x]], spf[x]});
                    prime_freq[spf[x]]--;
                    if (prime_freq[spf[x]] != 0) {
                        st.insert({prime_freq[spf[x]], spf[x]});
                    }
                    last = spf[x];
                    x /= spf[x];
                }
                m--;
            }
            nums[i] = y;
            if (nums[i] % p == 0) {
                int x = nums[i] / p;
                for (int d : divs[x]) {
                    freq[d]++;
                }
                int last = -1;
                while (x > 1) {
                    if (last == spf[x]) {
                        x /= spf[x];
                        continue;
                    }
                    if (prime_freq[spf[x]] != 0) {
                        st.erase({prime_freq[spf[x]], spf[x]});
                    }
                    prime_freq[spf[x]]++;
                    st.insert({prime_freq[spf[x]], spf[x]});
                    last = spf[x];
                    x /= spf[x];
                }
                m++;
            }
            if (st.empty()) {
                ans += m > 1 || (n != m && m > 0);
                continue;
            }
            if (st.rbegin()->first == m) {
                continue;
            }
            if (st.rbegin()->first < m - 1 || n != m) {
                ans++;
                continue;
            }
            auto it = st.rbegin();
            long long need = 1;
            while (it != st.rend() && it->first == m - 1) {
                need *= it->second;
                if (need > N) {
                    break;
                }
                it++;
            }

            ans += (need < N ? freq[need] > 0 : 0);
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] % p == 0){
                int x = nums[i] / p;
                for (int d : divs[x]) {
                    freq[d]--;
                }
                int last = -1;
                while (x > 1) {
                    if (last == spf[x]) {
                        x /= spf[x];
                        continue;
                    }
                    prime_freq[spf[x]]--;
                    last = spf[x];
                    x /= spf[x];
                }
                m--;
            }
        }
        return ans;
    }
};
