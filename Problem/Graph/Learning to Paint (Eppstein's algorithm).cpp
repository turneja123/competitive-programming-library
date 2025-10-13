//https://codeforces.com/contest/1942/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long INF = 1e18;
const ll ADD = 1e6 + 5;
const int MAX = 1e7;

int idx = 0;


struct Node {
    int ch[2] = {-1, -1};
    int sz; ll val;
    int from, to;
    Node()  {}
    Node(Node &id)  {
        ch[0] = id.ch[0];
        ch[1] = id.ch[1];
        sz = id.sz;
        val = id.val;
        from = id.from;
        to = id.to;
    }
    Node(ll val, int from, int to): sz(1), val(val), from(from), to(to) {}
};

Node nodes[MAX];

struct Heap {

  int root = -1;
  Heap(int t = -1): root(t) {}
  int meld(int a, int b) {
    if (b == -1) {
        if (a != -1) {
            return a;
        } else {
            return -1;
        }
    }
    if (a == -1) {
        if (b != -1) {
            return b;
        } else {
            return -1;
        }
    }
    nodes[idx++] = Node(nodes[a]);
    a = idx - 1;
    if (nodes[a].val > nodes[b].val) swap(a, b);
    nodes[a].ch[1] = meld(nodes[a].ch[1], b);
    if (nodes[a].ch[0] == -1 || nodes[nodes[a].ch[0]].sz < nodes[nodes[a].ch[1]].sz) swap(nodes[a].ch[0], nodes[a].ch[1]);
    nodes[a].sz = (nodes[a].ch[1] != -1 ? nodes[nodes[a].ch[1]].sz : 0) + 1;
    return a;
  }
  Heap meld(Heap b) {
    return Heap(meld(root, b.root));
  }
  Heap insert(ll x, int from, int to) {
    nodes[idx++] = Node(x, from, to);
    return Heap(meld(root, idx - 1));
  }
  Heap pop() {
    return Heap(meld(nodes[root].ch[0], nodes[root].ch[1]));
  }
  ll top() {
    return root != -1 ? nodes[root].val : -1;
  }
  bool empty() {
    return root == -1;
  }
};

vector<tuple<int, ll, int>> adj[N];
vector<tuple<int, ll, int>> rev[N];


vector<ll> eppstein(int n, int st, int en, int k) {
    vector<ll> d(n, INF);
    vector<int> par(n, -1);
    vector<int> idx(n, -1);
    vector<vector<int>> t(n);
    priority_queue<pair<ll, int>> pq;
    pq.emplace(0, en);
    d[en] = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        w = -w;
        pq.pop();
        for (auto [v, cost, id] : adj[u]) {
            if (d[v] > w + cost) {
                d[v] = w + cost;
                par[v] = u;
                idx[v] = id;
                pq.emplace(-d[v], v);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (par[i] != -1) {
            t[par[i]].push_back(i);
        }
    }
    vector<Heap> h(n);
    queue<int> q;
    q.emplace(en);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        if (par[u] != -1) {
            //h[u] = h[u].meld(h[par[u]]);
            h[u] = h[par[u]];
        }
        for (auto [v, cost, id]: rev[u]) {
            if (id != idx[u]) {
                h[u] = h[u].insert(cost - d[u] + d[v], u, v);
            }
        }
        for (auto v : t[u]) {
            q.emplace(v);
        }
    }
    auto comp = [](auto s, auto t) { return get<0>(s) > get<0>(t); };
    priority_queue<tuple<ll, int>, vector<tuple<ll, int>>, decltype(comp)> Q(comp);
    Heap s;
    s = s.insert(d[st], -1, st);
    Q.emplace(d[st], s.root);
    vector<ll> ans;
    while (!Q.empty()) {
        auto [w, cur] = Q.top();
        Q.pop();
        if (w >= INF) {
            break;
        }
        ans.push_back(w);
        if ((ans.size()) == k) {
            break;
        }
        if (nodes[cur].ch[0] != -1) {
            Q.emplace(w + nodes[nodes[cur].ch[0]].val - nodes[cur].val, nodes[cur].ch[0]);
        }
        if (nodes[cur].ch[1] != -1) {
            Q.emplace(w + nodes[nodes[cur].ch[1]].val - nodes[cur].val, nodes[cur].ch[1]);
        }
        if (h[nodes[cur].to].root != -1) {
            Q.emplace(w + nodes[h[nodes[cur].to].root].val, h[nodes[cur].to].root);
        }
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, st, en, k;
        cin >> n >> k;
        st = 0, en = n;
        vector<vector<int>> a(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                cin >> a[i][j];
            }
        }
        int e = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int u, v; ll wt;
                u = i, v = min(n, j + 2), wt = ADD * (v - i) - a[i][j];
                adj[v].push_back({u, wt, e});
                rev[u].push_back({v, wt, e});
                e++;
            }
            int u = i, v = i + 1, wt = ADD;
            adj[v].push_back({u, wt, e});
            rev[u].push_back({v, wt, e});
            e++;
        }
        vector<ll> ans = eppstein(n + 1, st, en, k);
        for (auto x : ans) {
            cout << -x + n * ADD << " ";
        }
        cout << endl;
        for (int i = 0; i <= n; i++) {
            adj[i].clear();
            rev[i].clear();
        }
        idx = 0;
    }
    return 0;
}
