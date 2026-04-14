//https://codeforces.com/contest/2165/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 1e6 + 5;


int a[N];
int seg_item[N];
int R[N];
int R_less[N];
int pos[N];

vector<tuple<int, int, int>> queries_init[N];
vector<pair<int, int>> events[N];
vector<pair<int, int>> queries[N];
vector<int> ivals[N];


struct Node {
    bool setValid;
    int setVal;
    int mx;
    int mn;
    ll sum;


    Node() {
        setValid = 0, setVal = 0;
    }
    Node(int x)  {
        setValid = 0;
        setVal = 0;
        mx = x;
        mn = x;
        sum = x;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = left.sum + right.sum;
    node.mx = max(left.mx, right.mx);
    node.mn = min(left.mn, right.mn);
    return node;
}

void compose(int parent, int child) {
    if (segtree[parent].setValid) {
        segtree[child].setValid = 1;
        segtree[child].setVal = segtree[parent].setVal;
    }
}

void apply(int node, int l, int r) {
    if (segtree[node].setValid) {
        segtree[node].sum = (ll)segtree[node].setVal * (r - l + 1);
        segtree[node].mx = segtree[node].setVal;
        segtree[node].mn = segtree[node].setVal;
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].setValid = false;
    segtree[node].setVal = 0;
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

int mode = 0;

void upd(int l, int r, int node, int ind, int val) {
    apply(node, l, r);
    if (l == r) {
        if (mode == 1 && segtree[node].mn < val) {
            return;
        }
        segtree[node] = Node(val);
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        upd(l, mid, 2 * node + 1, ind, val);
    } else {
        upd(mid + 1, r, 2 * node + 2, ind, val);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int found = -1;

void walk(int l, int r, int node, int val) {
    apply(node, l, r);
    if (l == r) {
        found = l;
        return;
    }
    int mid = (l + r) / 2;
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    if (segtree[2 * node + 2].mx > val) {
        walk(mid + 1, r, 2 * node + 2, val);
    } else {
        walk(l, mid, 2 * node + 1, val);
    }
}

void traverse(int l, int r, int node, int lq, int rq, int val) {
    if (l > rq || lq > r || found != -1) {
        return;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        if (segtree[node].mx > val) {
            walk(l, r, node, val);
        }
        return;
    }
    int mid = (l + r) / 2;
    traverse(mid + 1, r, 2 * node + 2, lq, rq, val);
    traverse(l, mid, 2 * node + 1, lq, rq, val);
}

long long getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].sum;
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}

int getMin(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return N;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].mn;
    }
    int mid = (l + r) / 2;
    return min(getMin(l, mid, lq, rq, 2 * node + 1), getMin(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(seg_item[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            seg_item[i] = -1;
            pos[a[i]] = i;
        }
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && a[i] > a[st.top()]) {
                st.pop();
            }
            if (st.size()) {
                R[i] = st.top();
            } else {
                R[i] = n;
            }
            st.push(i);
        }
        while (st.size()) {
            st.pop();
        }
        build(0, n - 1, 0);
        for (int i = 0; i < n; i++) {
            if (i != 0 && R[i] != n) {
                queries_init[a[R[i]]].push_back({i - 1, a[i], R[i]});
            }
        }
        for (int i = 0; i < n; i++) {
            for (auto [x, y, z] : queries_init[i]) {
                found = -1;
                traverse(0, n - 1, 0, 0, x, y);
                if (found != -1) {
                    events[y].push_back({found, z});
                }
            }
            upd(0, n - 1, 0, pos[i], i);
        }

        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && a[i] < a[st.top()]) {
                st.pop();
            }
            if (st.size()) {
                R_less[i] = st.top();
            } else {
                R_less[i] = n;
            }
            st.push(i);
        }
        for (int i = 0; i < n; i++) {
            int j = R_less[i];
            if (j < n - 1) {
                queries[a[i]].push_back({i, j + 1});
            }
        }


        for (int i = 0; i < n; i++) {
            seg_item[i] = n;
        }
        build(0, n - 1, 0);
        mode = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (auto [l, r] : queries[i]) {
                int best = getMin(0, n - 1, r, n - 1, 0);
                if (best < n) {
                    ivals[l].push_back(best);
                }
            }
            for (auto [j, x] : events[i]) {
                upd(0, n - 1, 0, j, x);
            }
        }
        for (int i = 0; i < n; i++) {
            seg_item[i] = 0;
        }
        build(0, n - 1, 0);
        ll ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int r : ivals[i]) {
                setUpdate(0, 0, n - 1, r, n - 1, 1);
            }
            ans += getSum(0, n - 1, i, n - 1, 0);
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            queries_init[i].clear();
            events[i].clear();
            queries[i].clear();
            ivals[i].clear();
        }
        mode = 0;
    }

    return 0;
}
