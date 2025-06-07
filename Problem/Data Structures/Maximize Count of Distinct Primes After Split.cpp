//https://leetcode.com/contest/weekly-contest-452/problems/maximize-count-of-distinct-primes-after-split/description/
const int N = 1e5 + 5;
bool is_prime[N];
struct Node {
    int sum;
    int lazy;
    Node() {
        lazy = 0;
    }
    Node(int x) : sum(x), lazy(0) {}
};

Node segtree[4 * N];
set<int> st[N];

class Solution {
public:
    int ans = 0;

    void sieve(int N) {
        if (is_prime[2]) {
            return;
        }
        for (int i = 2; i < N; i++) {
            is_prime[i] = true;
        }
        for (int i = 2; i < N; i++) {
            if (is_prime[i]) {
                for (int j = 2 * i; j < N; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }

    Node combine(Node left, Node right) {
        Node node = Node();
        node.sum = max(left.sum, right.sum);
        return node;
    }

    void compose(int parent, int child) {
        segtree[child].lazy += segtree[parent].lazy;
    }

    void apply(int node, int l, int r) {
        segtree[node].sum += segtree[node].lazy;
        if (l != r) {
            compose(node, 2 * node + 1);
            compose(node, 2 * node + 2);
        }
        segtree[node].lazy = 0;
    }

    void incUpdate(int node, int l, int r, int lq, int rq, int add) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            segtree[node].lazy += add;
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

    long long getSum(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return -N;
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree[node].sum;
        }
        int mid = (l + r) / 2;
        return max(getSum(l, mid, lq, rq, 2 * node + 1),
               getSum(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[node] = Node(0);
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, node * 2 + 1);
        build(mid + 1, r, node * 2 + 2);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    void add(int i, int x, int f, int n) {
        ans -= min(2, (int)st[x].size());
        if (st[x].size() >= 2) {
            incUpdate(0, 0, n - 1, 0, *st[x].begin(), 1);
            incUpdate(0, 0, n - 1, *st[x].rbegin() + 1, n - 1, 1);
        }
        if (f == 0) {
            st[x].insert(i);
        } else {
            st[x].erase(i);
        }
        ans += min(2, (int)st[x].size());
        if (st[x].size() >= 2) {
            incUpdate(0, 0, n - 1, 0, *st[x].begin(), -1);
            incUpdate(0, 0, n - 1, *st[x].rbegin() + 1, n - 1, -1);
        }
    }

    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        sieve(N);
        int n = nums.size();
        build(0, n - 1, 0);
        vector<int> cl;
        for (int i = 0; i < n; i++) {
            if (is_prime[nums[i]]) {
                add(i, nums[i], 0, n);
            }
            cl.push_back(nums[i]);
        }
        vector<int> v;
        for (int i = 0; i < queries.size(); i++) {
            int j = queries[i][0], x = queries[i][1];
            if (is_prime[nums[j]]) {
                add(j, nums[j], 1, n);
            }
            nums[j] = x;
            if (is_prime[nums[j]]) {
                add(j, nums[j], 0, n);
            }
            cl.push_back(nums[j]);
            v.push_back(ans + getSum(0, n - 1, 0, n - 1, 0));
        }
        for (int x : cl) {
            st[x].clear();
        }
        return v;
    }
};
