//https://leetcode.com/contest/biweekly-contest-58/problems/maximum-product-of-the-length-of-two-palindromic-substrings/
const int N = 1e5 + 5;
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

struct Node {
    int val;
    int lazypref;
    int lazysuf;
    Node() {
        val = 0, lazypref = -1, lazysuf = -1;
    }
};


struct Seg {
    vector<Node> segtree;

    Seg(int n) {
        segtree.resize(4 * n);
    }

    Node combine(Node left, Node right) {
        Node node = Node();
        node.val = max(left.val, right.val);
        return node;
    }

    void apply(int node, int l, int r) {
        if (segtree[node].lazypref != -1) {
            segtree[node].val = max(segtree[node].val, segtree[node].lazypref);
            if (l != r) {
                int mid = (l + r) / 2;
                segtree[2 * node + 1].lazypref = max(segtree[2 * node + 1].lazypref, segtree[node].lazypref - (r - mid));
                segtree[2 * node + 2].lazypref = max(segtree[2 * node + 2].lazypref, segtree[node].lazypref);
            }
        }
        if (segtree[node].lazysuf != -1) {
            segtree[node].val = max(segtree[node].val, segtree[node].lazysuf);
            if (l != r) {
                int mid = (l + r) / 2;
                segtree[2 * node + 1].lazysuf = max(segtree[2 * node + 1].lazysuf, segtree[node].lazysuf);
                segtree[2 * node + 2].lazysuf = max(segtree[2 * node + 2].lazysuf, segtree[node].lazysuf - (mid - l + 1));
            }
        }
        segtree[node].lazypref = -1;
        segtree[node].lazysuf = -1;
    }

    void prefUpdate(int node, int l, int r, int lq, int rq, int val) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            segtree[node].lazypref = max(segtree[node].lazypref, val - (rq - r));
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        prefUpdate(node * 2 + 1, l, mid, lq, rq, val);
        prefUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    void sufUpdate(int node, int l, int r, int lq, int rq, int val) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            segtree[node].lazysuf = max(segtree[node].lazysuf, val - (l - lq));
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        sufUpdate(node * 2 + 1, l, mid, lq, rq, val);
        sufUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    int getMax(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return 0;
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree[node].val;
        }
        int mid = (l + r) / 2;
        return max(getMax(l, mid, lq, rq, 2 * node + 1), getMax(mid + 1, r, lq, rq, 2 * node + 2));
    }

};

class Solution {
public:
    long long pw_p[N], pw_q[N];
    long long inv_p[N], inv_q[N];

    pair<long long, long long> pref[N], suf[N];

    pair<long long, long long> get_pref(int l, int r, int n) {
        pair<long long, long long> ans = pref[r];
        if (l != 0) {
            ans.first = (ans.first - pref[l - 1].first + M) * inv_p[l] % M;
            ans.second = (ans.second - pref[l - 1].second + M) * inv_q[l] % M;
        }
        return ans;
    }

    pair<long long, long long> get_suf(int l, int r, int n) {
        pair<long long, long long> ans = suf[l];
        if (r != n - 1) {
            ans.first = (ans.first - suf[r + 1].first + M) * inv_p[n - 1 - r] % M;
            ans.second = (ans.second - suf[r + 1].second + M) * inv_q[n - 1 - r] % M;
        }
        return ans;
    }


    long long maxProduct(string s) {
        int n = s.size();
        pw_p[0] = 1, pw_q[0] = 1;
        inv_p[0] = 1, inv_q[0] = 1;
        for (int i = 1; i < n; i++) {
            pw_p[i] = pw_p[i - 1] * P % M;
            pw_q[i] = pw_q[i - 1] * Q % M;
            inv_p[i] = inv_p[i - 1] * INV_P % M;
            inv_q[i] = inv_q[i - 1] * INV_Q % M;
        }
        for (int i = 0; i < n; i++) {
            pref[i].first = ((i == 0 ? 0 : pref[i - 1].first) + (s[i] - 'a' + 1) * pw_p[i]) % M;
            pref[i].second = ((i == 0 ? 0 : pref[i - 1].second) + (s[i] - 'a' + 1) * pw_q[i]) % M;
        }
        for (int i = n - 1; i >= 0; i--) {
            suf[i].first = ((i == n - 1 ? 0 : suf[i + 1].first) + (s[i] - 'a' + 1) * pw_p[n - 1 - i]) % M;
            suf[i].second = ((i == n - 1 ? 0 : suf[i + 1].second) + (s[i] - 'a' + 1) * pw_q[n - 1 - i]) % M;
        }
        Seg pref(n), suf(n);
        for (int i = 0; i < n; i++) {
            int l = 0, r = min(i, n - 1 - i), ans = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                pair<long long, long long> h1 = get_pref(i - mid, i, n);
                pair<long long, long long> h2 = get_suf(i, i + mid, n);
                if (h1.first == h2.first && h1.second == h2.second) {
                    ans = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if (ans > 0) {
                pref.prefUpdate(0, 0, n - 1, i + 1, i + ans, ans);
                suf.sufUpdate(0, 0, n - 1, i - ans, i - 1, ans);
            }
        }
        long long ans = 1;
        for (int i = 0; i < n - 1; i++) {
            int lf = pref.getMax(0, n - 1, 0, i, 0), rt = suf.getMax(0, n - 1, i + 1, n - 1, 0);
            ans = max(ans, (long long)(1 + 2 * lf) * (1 + 2 * rt));
        }
        return ans;
    }
};
