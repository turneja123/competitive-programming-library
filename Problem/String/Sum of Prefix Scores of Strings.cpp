//https://leetcode.com/problems/sum-of-prefix-scores-of-strings/description/?envType=problem-list-v2&envId=trie
const int MAX = 1e6 + 3;
struct Node {
    int val;
    vector<int> child;
    Node() : val(0), child(vector<int>(26, -1)) {}
};
Node nodes[MAX];
class Solution {
public:
    int idx = 0;
    int query(int node, int i, string &s) {
        if (i == s.size()) {
            return nodes[node].val;
        }
        int c = s[i] - 'a';
        if (nodes[node].child[c] == -1) {
            return nodes[node].val;
        } else {
            return nodes[node].val + query(nodes[node].child[c], i + 1, s);
        }
    }

    void add(int node, int i, string &s) {
        if (i == s.size()) {
            nodes[node].val++;
            return;
        }
        int c = s[i] - 'a';
        if (nodes[node].child[c] == -1) {
            nodes[node].child[c] = idx;
            nodes[idx++] = Node();

        }
        nodes[node].val -= nodes[nodes[node].child[c]].val;
        add(nodes[node].child[c], i + 1, s);
        nodes[node].val += nodes[nodes[node].child[c]].val;
        return;
    }

    vector<int> sumPrefixScores(vector<string>& words) {
        nodes[idx++] = Node();
        for (int i = 0; i < words.size(); i++) {
            add(0, 0, words[i]);
        }
        vector<int> ans;
        for (int i = 0; i < words.size(); i++) {
            ans.push_back(query(0, 0, words[i]) - words.size());
        }
        return ans;
    }
};
