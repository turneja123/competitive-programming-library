//https://leetcode.com/contest/weekly-contest-378/problems/palindrome-rearrangement-queries/
const int N = 1e5 + 5;
int prefa[N][26];
int prefb[N][26];
int pref[N];

class Solution {
public:
    struct Interval {
        int start;
        int end;
    };

    vector<Interval> sub(Interval A, Interval B) {
        vector<Interval> ans;

        int is = max(A.start, B.start);
        int ie = min(A.end, B.end);

        if (is > ie) {
            ans.push_back({A.start, A.end});
            return ans;
        }

        if (A.start < is) {
            ans.push_back({A.start, is - 1});
        }

        if (ie < A.end) {
            ans.push_back({ie + 1, A.end});
        }

        return ans;
    }

    vector<Interval> add(Interval A, Interval B) {
        Interval left, right;
        if (A.start <= B.start) {
            left = A;
            right = B;
        } else {
            left = B;
            right = A;
        }

        std::vector<Interval> ans;
        if (left.end + 1 >= right.start) {
            ans.push_back({left.start, std::max(left.end, right.end)});
        } else {
            ans.push_back(left);
            ans.push_back(right);
        }

        return ans;
    }


    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        string a = "", b = "";
        int n = s.size();
        for (int i = 0; i < n / 2; i++) {
            a += s[i];
        }
        for (int i = n / 2; i < n; i++) {
            b += s[i];
        }
        reverse(b.begin(), b.end());
        n /= 2;
        for (int i = 0; i < n; i++) {
            if (i != 0) {
                for (int j = 0; j < 26; j++) {
                    prefa[i][j] = prefa[i - 1][j];
                    prefb[i][j] = prefb[i - 1][j];
                }
                pref[i] = pref[i - 1];
            } else {
                for (int j = 0; j < 26; j++) {
                    prefa[i][j] = 0;
                    prefb[i][j] = 0;
                }
                pref[i] = 0;
            }
            prefa[i][a[i] - 'a']++;
            prefb[i][b[i] - 'a']++;
            if (a[i] != b[i]) {
                pref[i]++;
            }
        }


        vector<bool> ans;
        for (int i = 0; i < queries.size(); i++) {
            bool cur = true;
            int la = queries[i][0], ra = queries[i][1], lb = queries[i][2], rb = queries[i][3];
            lb = (n - 1) - (lb - n), rb = (n - 1) - (rb - n);
            swap(lb, rb);
            vector<Interval> un = add({la, ra}, {lb, rb});
            int ct = 0;
            for (Interval in : un) {
                ct += pref[in.end];
                if (in.start != 0) {
                    ct -= pref[in.start - 1];
                }
            }
            if (ct != pref[n - 1]) {
                cur = false;
            }

            vector<int> havea(26, 0), haveb(26, 0);
            for (int j = 0; j < 26; j++) {
                havea[j] = prefa[ra][j];
                if (la != 0) {
                    havea[j] -= prefa[la - 1][j];
                }

                haveb[j] = prefb[rb][j];
                if (lb != 0) {
                    haveb[j] -= prefb[lb - 1][j];
                }
            }

            vector<Interval> diffa = sub({la, ra}, {lb, rb});
            for (Interval in : diffa) {
                for (int j = 0; j < 26; j++) {
                    havea[j] -= prefb[in.end][j];
                    if (in.start != 0) {
                        havea[j] += prefb[in.start - 1][j];
                    }
                }
            }

            vector<Interval> diffb = sub({lb, rb}, {la, ra});
            for (Interval in : diffb) {
                for (int j = 0; j < 26; j++) {
                    haveb[j] -= prefa[in.end][j];
                    if (in.start != 0) {
                        haveb[j] += prefa[in.start - 1][j];
                    }
                }
            }

            for (int j = 0; j < 26; j++) {
                if (havea[j] < 0 || havea[j] != haveb[j]) {
                    cur = false;
                }
            }
            ans.push_back(cur);
        }
        return ans;
    }
};
