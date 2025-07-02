//https://judge.yosupo.jp/problem/k_shortest_walk
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long INF = 1e18;

template<typename T>
struct Heap {
  struct Node{
    Node* ch[2] = {0, 0};
    int sz; T val;
    int from, to;
    Node(T val, int from, int to): sz(1), val(val), from(from), to(to) {}
  };
  Node* root = 0;
  Heap(Node* t = 0): root(t) {}
  Node* meld(Node* a, Node* b) {
    if (!b) return a ? new Node(*a) : 0;
    if (!a) return b ? new Node(*b) : 0;
    a = new Node(*a); b = new Node(*b);
    if (a->val > b->val) swap(a, b);
    a->ch[1] = meld(a->ch[1], b);
    if (!a->ch[0] || a->ch[0]->sz < a->ch[1]->sz) swap(a->ch[0], a->ch[1]);
    a->sz = (a->ch[1] ? a->ch[1]->sz : 0) + 1;
    return a;
  }
  Heap meld(Heap b) {
    return Heap(meld(root, b.root));
  }
  Heap insert(T x, int from, int to) {
    return Heap(meld(root, new Node(x, from, to)));
  }
  Heap pop() {
    return Heap(meld(root->ch[0], root->ch[1]));
  }
  T top() {
    return root ? root->val : T(-1);
  }
  bool empty() {
    return !root;
  }
};

vector<tuple<int, int, int>> adj[N];
vector<tuple<int, int, int>> rev[N];


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
    vector<Heap<ll>> h(n);
    for (int i = 0; i < n; ++i) {
        h[i] = Heap<ll>();
    }
    queue<int> q;
    q.emplace(en);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        if (par[u] != -1) {
            h[u] = h[u].meld(h[par[u]]);
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
    priority_queue<tuple<ll, Heap<ll>::Node*>, vector<tuple<ll, Heap<ll>::Node*>>, decltype(comp)> Q(comp);
    Heap<ll> s;
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
        if (cur->ch[0]) {
            Q.emplace(w + cur->ch[0]->val - cur->val, cur->ch[0]);
        }
        if (cur->ch[1]) {
            Q.emplace(w + cur->ch[1]->val - cur->val, cur->ch[1]);
        }
        if (h[cur->to].root) {
            Q.emplace(w + h[cur->to].root->val, h[cur->to].root);
        }
    }
    while (ans.size() < k) {
        ans.push_back(-1);
    }
    return ans;
}

int main() {
    IOS;
    int n, m, st, en, k;
    cin >> n >> m >> st >> en >> k;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[v].push_back({u, wt, i});
        rev[u].push_back({v, wt, i});
    }
    vector<ll> ans = eppstein(n, st, en, k);
    for (auto x : ans) {
        cout << x << endl;
    }
    return 0;
}
