//https://leetcode.com/contest/weekly-contest-294/problems/sum-of-total-strength-of-wizards/
const int N = 1e5 + 5;
const long long M = 1e9 + 7;

struct Node {
    bool setValid;
    long long setVal;
    long long sum;
    long long summn;
    long long prod;
    long long lazy;
    Node() {
        setValid = 0;
        setVal = 0;
        sum = 0;
        summn = 0;
        prod = 0;
        lazy = 0;
    }
};



class Solution {
public:
    Node segtree[4 * N];


    Node combine(Node left, Node right) {
        Node node = Node();
        node.sum = (left.sum + right.sum) % M;
        node.summn = (left.summn + right.summn) % M;
        node.prod = (left.prod + right.prod) % M;
        return node;
    }

    void compose(int parent, int child) {
        if (segtree[parent].setValid) {
            segtree[child].setValid = 1;
            segtree[child].setVal = segtree[parent].setVal;
        }
        segtree[child].lazy = (segtree[child].lazy + segtree[parent].lazy) % M;
    }

    void apply(int node, int l, int r) {
        if (segtree[node].setValid) {
            segtree[node].summn = segtree[node].setVal * (r - l + 1) % M;
            segtree[node].prod = segtree[node].sum * segtree[node].setVal % M;
        }
        segtree[node].sum = (segtree[node].sum + segtree[node].lazy * (r - l + 1)) % M;

        segtree[node].prod = (segtree[node].prod + segtree[node].summn * segtree[node].lazy) % M;
        if (l != r) {
            compose(node, 2 * node + 1);
            compose(node, 2 * node + 2);
        }
        segtree[node].setValid = false;
        segtree[node].lazy = 0;
    }

    void incUpdate(int node, int l, int r, int lq, int rq, int add) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            segtree[node].lazy = (segtree[node].lazy + add) % M;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        incUpdate(node * 2 + 1, l, mid, lq, rq, add);
        incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    void setUpdate(int node, int l, int r, int lq, int rq, int val) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            segtree[node].setValid = true;
            segtree[node].setVal = val;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        setUpdate(node * 2 + 1, l, mid, lq, rq, val);
        setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    long long getSum(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return 0;
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree[node].prod;
        }
        int mid = (l + r) / 2;
        return (getSum(l, mid, lq, rq, 2 * node + 1) + getSum(mid + 1, r, lq, rq, 2 * node + 2)) % M;
    }


    int totalStrength(vector<int>& a) {
        stack<pair<int, int>> s;
        s.push(make_pair(-1, -1));
        int n = a.size();
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            while (s.top().first > a[i]) {
                s.pop();
            }
            setUpdate(0, 0, n - 1, s.top().second + 1, i, a[i]);
            incUpdate(0, 0, n - 1, 0, i, a[i]);
            ans = (ans + getSum(0, n - 1, 0, i, 0)) % M;
            s.push(make_pair(a[i], i));
        }
        return ans;
    }
};
