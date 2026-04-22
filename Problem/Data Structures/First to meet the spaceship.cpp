//https://www.spoj.com/problems/MEETSHIP/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6e5 + 5;

vector<int> compr;

int X[N];
int V[N];

struct Node {
    bool setValid;
    int setVal;
    int l;
    int r;
    Node() {
        setValid = 0;
    }
    Node(int j)  {
        setValid = 0;
        l = j;
        r = j;

    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.l = left.l;
    node.r = right.r;
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
        segtree[node].l = segtree[node].setVal;
        segtree[node].r = segtree[node].setVal;
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].setValid = false;
}


void setUpdate(int node, int l, int r, int lq, int rq, ll val) {
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


void build(int l, int r, int node, int j) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(j);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1, j);
    build(mid + 1, r, node * 2 + 2, j);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

vector<pair<int, int>> add[N], rem[N];
vector<int> add_t[N], rem_t[N];

int want[N];
vector<int> ans[N];

int comp(int i, int j, int x) {
    ll d = (ll)abs(x - X[i]) * V[j] - (ll)abs(x - X[j]) * V[i];
    if (d < 0) {
        return 0;
    }
    if (d == 0) {
        return 1;
    }
    return 2;
}

int found = -1;

void walk(int l, int r, int node, int i, int f, int dir) {
    if (l == r) {
        found = l;
        return;
    }
    int mid = (l + r) / 2;
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    if (dir == 1) {
        int c = comp(i, segtree[2 * node + 1].r, compr[mid]);
        if (c >= f) {
            walk(l, mid, 2 * node + 1, i, f, dir);
        } else {
            walk(mid + 1, r, 2 * node + 2, i, f, dir);
        }
    } else {
        int c = comp(i, segtree[2 * node + 2].l, compr[mid + 1]);
        if (c >= f) {
            walk(mid + 1, r, 2 * node + 2, i, f, dir);
        } else {
            walk(l, mid, 2 * node + 1, i, f, dir);
        }
    }
}



void traverse(int l, int r, int node, int lq, int rq, int i, int f, int dir) {
    if (l > rq || lq > r || found != -1) {
        return;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        if (dir == 1) {
            int c = comp(i, segtree[node].r, compr[r]);
            if (c >= f) {
                walk(l, r, node, i, f, dir);
                return;
            }
        } else {
            int c = comp(i, segtree[node].l, compr[l]);
            if (c >= f) {
                walk(l, r, node, i, f, dir);
                return;
            }
        }
        return;
    }
    int mid = (l + r) / 2;
    if (dir == 1) {
        traverse(l, mid, 2 * node + 1, lq, rq, i, f, dir);
        traverse(mid + 1, r, 2 * node + 2, lq, rq, i, f, dir);
    } else {
        traverse(mid + 1, r, 2 * node + 2, lq, rq, i, f, dir);
        traverse(l, mid, 2 * node + 1, lq, rq, i, f, dir);
    }



}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;

    vector<tuple<int, int, int>> a;
    for (int i = 0; i < n; i++) {
        int x, v;
        cin >> x >> v;
        X[i] = x;
        V[i] = v;
        compr.push_back(x);
        a.push_back({v, x, i});
    }
    vector<int> queries;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        queries.push_back(x);
        compr.push_back(x);
    }

    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    for (int i = 0; i < q; i++) {
        want[lower_bound(compr.begin(), compr.end(), queries[i]) - compr.begin()] = 1;
    }

    int m = compr.size();
    build(0, m - 1, 0, get<2>(a[0]));
    int t = 0;
    for (auto [v, x, i] : a) {
        if (t == 0) {
            add[0].push_back({i, t});
            rem[m].push_back({i, t});
            add_t[0].push_back(t);
            rem_t[m].push_back(t);
            t++;
            continue;
        }
        int pos = lower_bound(compr.begin(), compr.end(), x) - compr.begin();
        found = -1;


        traverse(0, m - 1, 0, pos, m - 1, i, 1, 1);
        if (found == pos) {
            add[pos].push_back({i, t});
            rem[pos + 1].push_back({i, t});
            setUpdate(0, 0, m - 1, pos, pos, i);
            t++;
            continue;
        }
        int RL = (found == -1 ? m - 1 : found - 1);

        found = -1;
        traverse(0, m - 1, 0, pos, m - 1, i, 2, 1);
        int RR = (found == -1 ? m - 1 : found - 1);

        found = -1;
        traverse(0, m - 1, 0, 0, pos, i, 1, 2);
        int LR = (found == -1 ? 0 : found + 1);

        found = -1;
        traverse(0, m - 1, 0, 0, pos, i, 2, 2);
        int LL = (found == -1 ? 0 : found + 1);

        add[LL].push_back({i, t});
        rem[RR + 1].push_back({i, t});

        add_t[LR].push_back(t);
        rem_t[RL + 1].push_back(t);
        setUpdate(0, 0, m - 1, LL, RR, i);

        t++;
    }
    set<pair<int, int>> st;
    set<int> st_t;
    for (int i = 0; i < m; i++) {
        for (auto [j, t] : add[i]) {
            st.insert({t, j});
        }
        for (auto t : add_t[i]) {
            st_t.insert(t);
        }

        for (auto [j, t] : rem[i]) {
            st.erase({t, j});
        }
        for (auto t : rem_t[i]) {
            st_t.erase(t);
        }

        int t = *st_t.rbegin();
        auto it = st.rbegin();
        while (it != st.rend() && it->first >= t) {
            ans[i].push_back(it->second);
            it++;
        }
        sort(ans[i].begin(), ans[i].end());
    }
    for (int i = 0; i < q; i++) {
        int pos = lower_bound(compr.begin(), compr.end(), queries[i]) - compr.begin();
        cout << ans[pos].size() << " ";
        for (int j = 0; j < ans[pos].size(); j++) {
            cout << ans[pos][j] + 1 << " ";
        }
        cout << endl;

    }

    return 0;
}
