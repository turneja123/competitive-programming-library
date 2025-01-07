//https://dmoj.ca/problem/utso24p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
char op[N];

int segtree[4 * N];
int setVal[4 * N];
bool setValid[4 * N];
int sum[4 * N];
int val[N];
int seg_val[4 * N];
int border[N];

void compose(int parent, int child) {
    if (setValid[parent]) {
        setValid[child] = 1;
        setVal[child] = setVal[parent];
    }
    return;
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        segtree[node] = setVal[node];
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
        setValid[node] = true;
        setVal[node] = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
}

void update_val(int l, int r, int node, int ind, int val) {
    if (l == r) {
        seg_val[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        update_val(l, mid, 2 * node + 1, ind, val);
    } else {
        update_val(mid + 1, r, 2 * node + 2, ind, val);
    }
    seg_val[node] = seg_val[2 * node + 1] + seg_val[2 * node + 2];
}

void update_sum(int l, int r, int node, int ind, int val) {
    if (l == r) {
        sum[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        update_sum(l, mid, 2 * node + 1, ind, val);
    } else {
        update_sum(mid + 1, r, 2 * node + 2, ind, val);
    }
    sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
}

int getVal(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    if (l >= lq && r <= rq) {
        return seg_val[node];
    }
    int mid = (l + r) / 2;
    return getVal(l, mid, lq, rq, 2 * node + 1) +
           getVal(mid + 1, r, lq, rq, 2 * node + 2);
}

int getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    if (l >= lq && r <= rq) {
        return sum[node];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}

int get(int l, int r, int node, int ind) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return get(l, mid, 2 * node + 1, ind);
    } else {
        return get(mid + 1, r, 2 * node + 2, ind);
    }
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        sum[node] = (a[l] + 1) % 2;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    sum[node] = sum[node * 2 + 1] + sum[node * 2 + 2];
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    string s;
    cin >> s;
    for (int i = 0; i < n - 1; i++) {
        op[i] = s[i];
    }
    build(0, n - 1, 0);
    int last = 0;
    for (int i = 1; i < n; i++) {
        if (op[i - 1] != 'x') {
            border[last] = i - 1;
            val[last] = getSum(0, n - 1, last, i - 1, 0);
            setUpdate(0, 0, n - 1, last, i - 1, last);
            update_val(0, n - 1, 0, last, (val[last] == 0 ? 1 : 0));
            last = i;
        }
    }
    border[last] = n - 1;
    val[last] = getSum(0, n - 1, last, n - 1, 0);
    setUpdate(0, 0, n - 1, last, n - 1, last);
    update_val(0, n - 1, 0, last, (val[last] == 0 ? 1 : 0));
    for (int i = 0; i < q; i++) {
        char c;
        cin >> c;
        if (c == 'V') {
            int j;
            cin >> j;
            j--;
            a[j]++;
            int last = get(0, n - 1, 0, j);
            if (a[j] % 2 == 0) {
                val[last]++;
                update_val(0, n - 1, 0, last, (val[last] == 0 ? 1 : 0));
                update_sum(0, n - 1, 0, j, 1);
            } else {
                val[last]--;
                update_val(0, n - 1, 0, last, (val[last] == 0 ? 1 : 0));
                update_sum(0, n - 1, 0, j, 0);
            }
        } else if (c == 'O') {
            int j;
            cin >> j;
            j--;
            if (op[j] == 'x') {
                op[j] = '+';
                int last = get(0, n - 1, 0, j);
                int lf = getSum(0, n - 1, last, j, 0), rt = getSum(0, n - 1, j + 1, border[last], 0);
                val[j + 1] = rt, border[j + 1] = border[last];
                val[last] = lf, border[last] = j;
                update_val(0, n - 1, 0, last, (val[last] == 0 ? 1 : 0));
                update_val(0, n - 1, 0, j + 1, (val[j + 1] == 0 ? 1 : 0));
                setUpdate(0, 0, n - 1, j + 1, border[j + 1], j + 1);
            } else {
                op[j] = 'x';
                int last = get(0, n - 1, 0, j), last_r = get(0, n - 1, 0, j + 1);
                border[last] = border[last_r];
                val[last_r] = 0, border[last_r] = 0;
                update_val(0, n - 1, 0, j + 1, 0);
                val[last] = getSum(0, n - 1, last, border[last], 0);
                update_val(0, n - 1, 0, last, (val[last] == 0 ? 1 : 0));
                setUpdate(0, 0, n - 1, j + 1, border[last], last);
            }
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int lastl = get(0, n - 1, 0, l);
            int suml = getSum(0, n - 1, l, min(r, border[lastl]), 0);
            int lastr = get(0, n - 1, 0, r);
            int sumr, summid;
            if (lastl != lastr) {
                sumr = getSum(0, n - 1, lastr, min(r, border[lastr]), 0);
                if (border[lastl] + 1 <= lastr - 1) {
                    summid = getVal(0, n - 1, border[lastl] + 1, lastr - 1, 0);
                } else {
                    summid = 0;
                }
            } else {
                sumr = 1, summid = 0;
            }
            suml = (suml > 0 ? 0 : 1);
            sumr = (sumr > 0 ? 0 : 1);

            int midval = (suml % 2 + summid % 2 + sumr % 2) % 2;
            int lf = lastl - 1, rt = border[lastr] + 1;
            if (lastl < l) {
                int s = getSum(0, n - 1, lastl, l - 1, 0);
                if (s != 0) {
                    midval = 0;
                }
            }
            if (border[lastr] > r) {
                int s = getSum(0, n - 1, r + 1, border[lastr], 0);
                if (s != 0) {
                    midval = 0;
                }
            }
            int L = 0, R = 0;
            if (lf >= 0) {
                L = getVal(0, n - 1, 0, lf, 0);
            }
            if (rt < n) {
                R = getVal(0, n - 1, rt, n - 1, 0);
            }
            int ans = (L + R + midval) % 2;
            if (ans == 0) {
                cout << "even" << endl;
            } else {
                cout << "odd" << endl;
            }
        }
    }
    return 0;
}
