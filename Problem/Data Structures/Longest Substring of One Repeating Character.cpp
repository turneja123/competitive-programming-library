//https://leetcode.com/contest/weekly-contest-285/problems/longest-substring-of-one-repeating-character/
const int N = 1e5 + 5;
const int INF = 1e9;

struct Node {
    long long pref;
    long long suf;
    long long sum;
    long long val;
    Node() : pref(0), suf(0), sum(0), val(0) {}
    Node(long long x) : pref(x), suf(x), sum(x), val(x) {}
};

Node segtree[26][4 * N];

class Solution {
public:
    Node combine(Node left, Node right) {
        Node node = Node();
        node.sum = left.sum + right.sum;
        node.pref = max(left.pref, left.sum + right.pref);
        node.suf = max(right.suf, right.sum + left.suf);
        node.val = max({left.val, right.val, node.pref, node.suf, left.suf + right.pref});
        return node;
    }

    void update(int l, int r, int ind, int val, int node, int n) {
        if (l == r) {
            segtree[n][node] = Node(val);
            return;
        }

        int mid = (l + r) / 2;
        if (ind >= l && ind <= mid) {
            update(l, mid, ind, val, 2 * node + 1, n);
        } else {
            update(mid + 1, r, ind, val, 2 * node + 2, n);
        }
        segtree[n][node] = combine(segtree[n][2 * node + 1], segtree[n][2 * node + 2]);
    }


    void build(int l, int r, int node, int n, string &a) {
        if (l > r) {
            return;
        }
        if (l == r) {
            int c = a[l] - 'a';
            if (c == n) {
                segtree[n][node] = Node(1);
            } else {
                segtree[n][node] = Node(-INF);
            }
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1, n, a);
        build(mid + 1, r, 2 * node + 2, n, a);
        segtree[n][node] = combine(segtree[n][2 * node + 1], segtree[n][2 * node + 2]);
    }

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.size();
        for (int i = 0; i < 26; i++) {
            build(0, n - 1, 0, i, s);
        }
        vector<int> ans;
        for (int i = 0; i < queryCharacters.size(); i++) {
            int c = s[queryIndices[i]] - 'a';
            update(0, n - 1, queryIndices[i], -INF, 0, c);
            s[queryIndices[i]] = queryCharacters[i];
            c = s[queryIndices[i]] - 'a';
            update(0, n - 1, queryIndices[i], 1, 0, c);
            int cur = 0;
            for (int j = 0; j < 26; j++) {
                cur = max((long long)cur, segtree[j][0].val);
            }
            ans.push_back(cur);
        }
        return ans;
    }
};
