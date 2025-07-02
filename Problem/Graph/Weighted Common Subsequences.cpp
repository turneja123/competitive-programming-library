//https://ocpc2025s.eolymp.space/en/compete/m9rs3cu3vp6lv7kjgk9aaqsa1s/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e6 + 5;

const long long INF = 1e18;
const ll ADD = 1e9;

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
    if (ans.size() < k) {
        cout << -1;
        exit(0);
    }
    return ans;
}

int e = 0;

void add_edge(int u, int v, ll wt) {
    adj[v].push_back({u, wt, e});
    rev[u].push_back({v, wt, e});
    e++;
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;
    vector<ll> fa(n), fb(m);
    for (int i = 0; i < n; i++) {
        cin >> fa[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> fb[i];
    }
    cin >> k;
    int st = 0, en = 2 * n * m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j < m - 1) add_edge(i * m + j, i * m + j + 1, ADD);
            if (i < n - 1) add_edge(i * m + j, (i + 1) * m + j + n * m, ADD);
            if (i < n - 1) add_edge(i * m + j + n * m, (i + 1) * m + j + n * m, ADD);
            if (a[i] == b[j]) {
                if (i < n - 1 && j < m - 1) add_edge(i * m + j, (i + 1) * m + j + 1, 2 * ADD - fa[i] * fb[j]);
                if (i < n - 1 && j < m - 1) add_edge(i * m + j + n * m, (i + 1) * m + j + 1,  2 * ADD - fa[i] * fb[j]);
                add_edge(i * m + j, en, (n - i + m - j) * ADD - fa[i] * fb[j]);
                add_edge(i * m + j + n * m, en, (n - i + m - j) * ADD - fa[i] * fb[j]);

            }
        }
    }
    //add_edge(n * m - 1, en, 0);
    //add_edge(2 * n * m - 1, en, 0);
    vector<ll> ans = eppstein(en + 1, st, en, k);
    for (int i = 0; i < k; i++) {
        cout << -(ans[i] - ADD * (n + m)) << endl;
    }
    return 0;
}
