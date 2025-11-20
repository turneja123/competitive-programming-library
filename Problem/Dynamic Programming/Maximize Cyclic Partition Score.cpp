//https://leetcode.com/problems/maximize-cyclic-partition-score/description/
using ll = long long;
const int N = 1005;
const ll INF = 1e18;

struct Node {
    pair<ll, int> sum;
    ll lazy;
    Node() {
        lazy = 0;
        sum = {-INF, -INF};
    }
    Node(ll x, int y) {
        lazy = 0;
        sum = {x, y};

    }
};

pair<ll, int> dp[N];
Node segtree[4 * N];


class Solution {
public:
    Node combine(Node left, Node right) {
        Node node = Node();
        node.sum = max(left.sum, right.sum);
        return node;
    }

    void compose(int parent, int child) {
        segtree[child].lazy += segtree[parent].lazy;
    }

    void apply(int node, int l, int r) {
        segtree[node].sum.first += segtree[node].lazy;
        if (l != r) {
            compose(node, 2 * node + 1);
            compose(node, 2 * node + 2);
        }
        segtree[node].lazy = 0;
    }

    void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
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

    void setUpdate(int node, int l, int r, int ind, pair<ll, int> val) {
        apply(node, l, r);
        if (l == r) {
            segtree[node] = Node(val.first, val.second);
            return;
        }

        int mid = (l + r) / 2;
        if (ind <= mid) {
            setUpdate(2 * node + 1, l, mid, ind, val);
        } else {
            setUpdate(2 * node + 2, mid + 1, r, ind, val);
        }
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    pair<ll, int> getSum(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return {-INF, -INF};
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree[node].sum;
        }
        int mid = (l + r) / 2;
        return max(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        segtree[node] = Node();
        if (l == r) {
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, node * 2 + 1);
        build(mid + 1, r, node * 2 + 2);
    }

    pair<ll, int> calc(int n, vector<int> &a, ll add) {
        pair<ll, int> ans = {0, 0};
        dp[0] = {0, 0};
        stack<tuple<int, int, int>> mn, mx;
        mn.push(make_tuple(0, 0, a[0]));
        mx.push(make_tuple(0, 0, a[0]));
        build(0, n, 0);
        setUpdate(0, 0, n, 0, make_pair(0, 0));
        for (int i = 1; i <= n; i++) {
            int j = i;
            while (mn.size()) {
                auto [l, r, v] = mn.top();
                if (v >= a[i - 1]) {
                    incUpdate(0, 0, n, l, r, v - a[i - 1]);
                } else {
                    break;
                }
                j = l;
                mn.pop();
            }
            if (j <= i - 1) {
                mn.push(make_tuple(j, i - 1, a[i - 1]));
            }
            mn.push(make_tuple(i, i, (i == n ? -1 : a[i])));
            j = i;
            while (mx.size()) {
                auto [l, r, v] = mx.top();
                if (v <= a[i - 1]) {
                    incUpdate(0, 0, n, l, r, a[i - 1] - v);
                } else {
                    break;
                }
                j = l;
                mx.pop();
            }
            if (j <= i - 1) {
                mx.push(make_tuple(j, i - 1, a[i - 1]));
            }
            mx.push(make_tuple(i, i, (i == n ? -1 : a[i])));
            dp[i] = getSum(0, n, 0, i - 1, 0);
            dp[i].first -= add;
            dp[i].second++;
            ans = max(ans, dp[i]);
            setUpdate(0, 0, n, i, dp[i]);
        }
        return ans;

    }

    long long maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int mn = 1e9, mx = -1e9;
        for (int i = 0; i < n; i++) {
            mn = min(nums[i], mn);
            mx = max(nums[i], mx);
        }

        vector<int> id;
        int x = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == mn && !x) {
                id.push_back((n - i) % n);
                int j = (i + 1) % n;
                id.push_back((n - j) % n);
                x = 1;
            }
        }

        ll ans = 0;
        for (int j : id) {
            vector<int> a(n);
            for (int i = 0; i < n; i++) {
                a[(i + j) % n] = nums[i];
            }
            ll l = 0, r = mx - mn, opt = 0;
            while (l <= r) {
                ll mid = (l + r) / 2;
                if (calc(n, a, mid).second >= k) {
                    opt = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            pair<ll, int> x = calc(n, a, opt);

            ans = max(ans, x.first + (ll)opt * k);
        }
        return ans;
    }
};
