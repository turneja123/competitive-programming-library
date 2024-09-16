//https://leetcode.com/contest/weekly-contest-415/problems/minimum-number-of-valid-strings-to-form-target-ii/
const long long N = 5e4 + 5;
const long long M = 1e9 + 7, P = 26, Q = 53;
long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];

class Solution {
public:
    set<pair<long long, long long>> st[N];
    pair<long long, long long> h[N];
    int segtree[4 * N];
    int setVal[4 * N];
    bool setValid[4 * N];

    void compose(int parent, int child) {
        if (setValid[parent]) {
            if (setValid[child]) {
                setVal[child] = min(setVal[child], setVal[parent]);
            } else {
                setValid[child] = 1;
                setVal[child] = setVal[parent];
            }

        }
    }

    void apply(int node, int l, int r) {
        if (setValid[node]) {
            segtree[node] = min(segtree[node], setVal[node]);
        }
        if (l != r) {
            compose(node, 2 * node + 1);
            compose(node, 2 * node + 2);
        }
        setValid[node] = false;
    }

    void setUpdate(int node, int l, int r, int lq, int rq, int val) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            if (setValid[node]) {
                setVal[node] = min(setVal[node], val);
            } else {
                setValid[node] = true;
                setVal[node] = val;
            }
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        setUpdate(node * 2 + 1, l, mid, lq, rq, val);
        setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
    }

    int getMin(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return N;
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree[node];
        }
        int mid = (l + r) / 2;
        return min(getMin(l, mid, lq, rq, 2 * node + 1),
               getMin(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[node] = N;
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, node * 2 + 1);
        build(mid + 1, r, node * 2 + 2);
        segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
    }

    long long modPow(long long a, long long y) {
        long long res = 1;
        while(y > 0) {
            if(y % 2 != 0) {
                res = (res * a) % M;
            }
            y /= 2;
            a = (a * a) % M;
        }
        return res;
    }
    void precalc() {
        pw_p[0] = 1, pw_q[0] = 1;
        inv_p[0] = 1, inv_q[0] = 1;
        for (int i = 1; i < N; i++) {
            pw_p[i] = pw_p[i - 1] * P % M;
            pw_q[i] = pw_q[i - 1] * Q % M;
            inv_p[i] = modPow(pw_p[i], M - 2);
            inv_q[i] = modPow(pw_q[i], M - 2);
        }
    }
    void calc(string &s) {
        int n = s.size();
        long long p = 0, q = 0;
        for (int i = 0; i < n; i++) {
            p = (p + pw_p[i] * (s[i] - 'a' + 1)) % M;
            q = (q + pw_q[i] * (s[i] - 'a' + 1)) % M;
            st[i].insert(make_pair(p, q));
        }

    }
    pair<long long, long long> get(int l, int r) {
        pair<long long, long long> ans = h[r];
        if (l != 0) {
            ans.first = (h[r].first - h[l - 1].first + M) % M * inv_p[l] % M;
            ans.second = (h[r].second - h[l - 1].second + M) % M * inv_q[l] % M;
        }
        return ans;
    }



    int minValidStrings(vector<string>& words, string s) {
        if (pw_p[0] == 0) {
            precalc();
        }
        int n = s.size();
        build(0, n - 1, 0);
        for (int i = 0; i < words.size(); i++) {
            calc(words[i]);
        }
        long long p = 0, q = 0;
        for (int i = 0; i < n; i++) {
            p = (p + pw_p[i] * (s[i] - 'a' + 1)) % M;
            q = (q + pw_q[i] * (s[i] - 'a' + 1)) % M;
            h[i] = make_pair(p, q);
        }
        for (int i = 0; i < n; i++) {
            int cur = ((i == 0) ? 0 : getMin(0, n - 1, i - 1, i - 1, 0));
            if (i != 0 && cur == N) {
                return -1;
            }
            int l = i, r = n - 1, lim = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                pair<long long, long long> val = get(i, mid);
                if (st[mid - i].find(val) != st[mid - i].end()) {
                    l = mid + 1;
                    lim = mid;
                } else {
                    r = mid - 1;
                }
            }
            if (i == 0 && lim == -1) {
                return -1;
            }
            if (lim != -1) {
                setUpdate(0, 0, n - 1, i, lim, cur + 1);
            }

        }
        int ans = getMin(0, n - 1, n - 1, n - 1, 0);
        if (ans == N) {
            return -1;
        }
        return ans;
    }
};
