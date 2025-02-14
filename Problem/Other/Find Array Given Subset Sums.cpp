//https://leetcode.com/contest/weekly-contest-255/problems/find-array-given-subset-sums/
class Solution {
public:
    vector<int> ans;

    void calc(multiset<int> st) {
        if (st.size() == 2) {
            ans.push_back(*st.rbegin() - *st.begin());

            return;
        }
        auto it = st.rbegin();
        it++;
        int mn = (*st.rbegin() - *it);
        ans.push_back(mn);
        multiset<int> nx;
        while (st.size()) {
            int x = *st.rbegin();
            st.erase(st.find(x));
            st.erase(st.find(x - mn));
            nx.insert(x - mn);
        }
        calc(nx);
    }

    vector<int> recoverArray(int n, vector<int>& sums) {
        multiset<int> st(sums.begin(), sums.end());
        calc(st);
        for (int i = 0; i < 1 << n; i++) {
            int sum = 0;
            vector<int> v;
            for (int j = 0; j < n; j++) {
                int c = (1 << j) & i;
                if (c) {
                    sum += ans[j];
                    v.push_back(ans[j]);
                } else {
                    v.push_back(-ans[j]);
                }
            }
            if (sum == *st.rbegin()) {
                return v;
            }
        }
        return ans;
    }
};
