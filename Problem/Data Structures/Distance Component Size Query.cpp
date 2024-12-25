//https://atcoder.jp/contests/abc356/tasks/abc356_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long R = (long long)1e18 + 5;
const int MAX = 2e7 + 5;

long long k;

struct Node {
    long long lf;
    long long rt;
    bool setValid;
    long long setVal;
    long long left;
    long long right;
    Node() : lf(R), rt(-1), setValid(false), setVal(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;
tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> t;

void compose(int parent, int node) {
    if (nodes[parent].setValid) {
        nodes[node].setValid = true;
        nodes[node].setVal = nodes[parent].setVal;
    }
}

void apply(int node, long long l, long long r) {
    if (nodes[node].setValid) {
        if (nodes[node].setVal > k) {
            nodes[node].lf = l;
            nodes[node].rt = r;
        } else {
            nodes[node].lf = R;
            nodes[node].rt = -1;
        }
    }
    if (l != r) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        compose(node, nodes[node].left);
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        compose(node, nodes[node].right);
    }
    nodes[node].setValid = false;
    nodes[node].setVal = 0;
}

void setUpdate(int node, long long l, long long r, long long lq, long long rq, long long val) {
    if (l > rq || lq > r || lq > rq) {
        return;
    }
    if (lq <= l && rq >= r) {
        nodes[node].setValid = true;
        nodes[node].setVal = val;
        return;
    }
    long long mid = (l + r) / 2;
    apply(node, l, r);

    setUpdate(nodes[node].left, l, mid, lq, rq, val);
    setUpdate(nodes[node].right, mid + 1, r, lq, rq, val);

    apply(nodes[node].left, l, mid);
    apply(nodes[node].right, mid + 1, r);
    nodes[node].lf = min(nodes[nodes[node].left].lf, nodes[nodes[node].right].lf);
    nodes[node].rt = max(nodes[nodes[node].left].rt, nodes[nodes[node].right].rt);
}

long long query(int node, long long l, long long r, long long lq, long long rq, int f) {
    if (r < lq || l > rq) {
        return (f == 0 ? -1 : R);
    }
    apply(node, l, r);

    if (lq <= l && rq >= r) {
        return (f == 0 ? nodes[node].rt : nodes[node].lf);
    }

    long long mid = (l + r) / 2;
    long long ans = (f == 0 ? -1 : R);
    if (nodes[node].left != -1) {
        if (f == 0) {
            ans = max(ans, query(nodes[node].left, l, mid, lq, rq, f));
        } else {
            ans = min(ans, query(nodes[node].left, l, mid, lq, rq, f));
        }
    }
    if (nodes[node].right != -1) {
        if (f == 0) {
            ans = max(ans, query(nodes[node].right, mid + 1, r, lq, rq, f));
        } else {
            ans = min(ans, query(nodes[node].right, mid + 1, r, lq, rq, f));
        }
    }
    return ans;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int q;
    cin >> q >> k;
    while (q--) {
        int c; long long x;
        cin >> c >> x;
        if (t.size() == 0) {
            t.insert(x);
            continue;
        }
        if (c == 1) {
            long long lf, rt;
            auto it = t.find(x);
            if (it != t.end()) {
                if (t.size() == 1) {
                    setUpdate(0, 0, R - 1, 0, R - 1, 0);
                } else {
                    it++;
                    if (it == t.end()) {
                        rt = -1;
                    } else {
                        rt = *it;
                    }
                    it--;
                    if (it != t.begin()) {
                        it--;
                        lf = *it;
                    } else {
                        lf = -1;
                    }
                    if (rt == -1) {
                        setUpdate(0, 0, R - 1, lf + 1, R - 1, 0);
                    } else if (lf == -1) {
                        setUpdate(0, 0, R - 1, 0, rt - 1, 0);
                    } else {
                        setUpdate(0, 0, R - 1, lf + 1, rt - 1, rt - lf);
                    }
                }
                t.erase(x);
            } else {
                auto it = t.lower_bound(x);
                if (it == t.end()) {
                    rt = -1;
                } else {
                    rt = *it;
                }
                if (it == t.begin()) {
                    lf = -1;
                } else {
                    it--;
                    lf = *it;
                }
                if (lf != -1) {
                    setUpdate(0, 0, R - 1, lf + 1, x - 1, x - lf);
                }
                if (rt != -1) {
                    setUpdate(0, 0, R - 1, x + 1, rt - 1, rt - x);
                }
                setUpdate(0, 0, R - 1, x, x, 0);
                t.insert(x);
            }
        } else {
            if (k == 0) {
                cout << 1 << endl;
            } else {
                long long rt = query(0, 0, R - 1, x + 1, R - 1, 1);
                long long lf = query(0, 0, R - 1, 0, x - 1, 0);
                int ans = t.order_of_key(rt) - t.order_of_key(lf);
                cout << ans << endl;

            }
        }
    }
    return 0;
}
