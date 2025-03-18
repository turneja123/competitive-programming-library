//https://leetcode.com/contest/biweekly-contest-152/problems/longest-common-prefix-of-k-strings-after-removal/
const int MAX = 2e5 + 5;
struct Node {
    int val;
    vector<int> child;
    Node() : val(0), child(vector<int>(26, -1)) {}
};

Node nodes[MAX];
int idx = 0;

class Solution {
public:
    multiset<int> best;

    void add(int node, int i, int a, int k, string &s) {
        nodes[node].val += a;
        if (nodes[node].val == k && a == 1) {
            best.insert(i);
        }
        if (nodes[node].val == k - 1 && a == -1) {
            best.erase(best.find(i));
        }
        if (i == s.size()) {
            return;
        }
        int c = s[i] - 'a';
        if (nodes[node].child[c] == -1) {
            nodes[node].child[c] = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].child[c], i + 1, a, k, s);
        return;
    }


    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        nodes[idx++] = Node();
        int n = words.size();
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            add(0, 0, 1, k, words[i]);
        }
        for (int i = 0; i < n; i++) {
            add(0, 0, -1, k, words[i]);
            if (best.empty()) {
                ans.push_back(0);
            } else {
                ans.push_back(*best.rbegin());

            }
            add(0, 0, 1, k, words[i]);
        }
        idx = 0;
        return ans;
    }
};
