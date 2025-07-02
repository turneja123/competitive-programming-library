//https://ocpc2025s.eolymp.space/en/compete/sk55ojcma10djasruv04qdm2fo/problem/7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e6 + 5;
const long long INF = 1e18;

template<typename T>
struct Heap {
  struct Node{
    Node* ch[2] = {0, 0};
    int sz; T val;
    int from, to;
    Node* prev;
    Node(T val, int from, int to, Node* prev = nullptr): sz(1), val(val), from(from), to(to), prev(prev) {}
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

int a[105][105];
int e = 0;


void eppstein(int n, int st, int en, int k, int x) {
    vector<ll> d(n, -INF);
    vector<int> par(n, -1);
    vector<int> idx(n, -1);
    vector<vector<int>> t(n);
    priority_queue<pair<ll, int>> pq;
    pq.emplace(0, en);
    d[en] = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        for (auto [v, cost, id] : adj[u]) {
            if (d[v] < w + cost) {
                d[v] = w + cost;
                par[v] = u;
                idx[v] = id;
                pq.emplace(d[v], v);
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
                h[u] = h[u].insert(-(cost - d[u] + d[v]), u, v);
            }
        }
        for (auto v : t[u]) {
            q.emplace(v);
        }
    }
    auto comp = [](auto s, auto t) { return get<0>(s) < get<0>(t); };
    priority_queue<tuple<ll, Heap<ll>::Node*>, vector<tuple<ll, Heap<ll>::Node*>>, decltype(comp)> Q(comp);
    Heap<ll> s;
    s = s.insert(d[st], -1, st);
    Q.emplace(d[st], s.root);
    vector<ll> ans;
    while (!Q.empty()) {
        auto [w, cur] = Q.top();
        Q.pop();
        if (w <= 0) {
            break;
        }
        ans.push_back(w);
        if ((ans.size()) == k) {
            cout << w << endl;
            auto *node = cur;
            vector<pair<int, int>> edges;
            while (node) {
                edges.push_back({node->from, node->to});
                node = node->prev;
            }
            reverse(edges.begin(), edges.end());
            int mask_last = 0;
            vector<int> out(x);
            int cur = 0;
            for (int i = 1; i < edges.size(); i++) {
                int id = edges[i].second;
                while (cur != edges[i].first) {
                    int col = (par[cur] - 1) / (1 << x);
                    int mask = (par[cur] - 1) % (1 << x);
                    int bit = mask - mask_last;
                    for (int j = 0; j < x; j++) {
                        if (bit == (1 << j)) {
                            out[j] = col;
                        }
                    }
                    mask_last = mask;
                    cur = par[cur];
                }

                int col = (id - 1) / (1 << x);
                int mask = (id - 1) % (1 << x);
                int bit = mask - mask_last;
                for (int j = 0; j < x; j++) {
                    if (bit == (1 << j)) {
                        out[j] = col;
                    }
                }
                mask_last = mask;
                cur = id;
            }
            while (cur != en) {
                int col = (par[cur] - 1) / (1 << x);
                int mask = (par[cur] - 1) % (1 << x);
                int bit = mask - mask_last;
                for (int j = 0; j < x; j++) {
                    if (bit == (1 << j)) {
                        out[j] = col;
                    }
                }
                mask_last = mask;
                cur = par[cur];
            }
            ll S = 0;
            for (int i = 0; i < x; i++) {
                cout << out[i] + 1 << " ";
                S += a[i][out[i]];
            }
            assert(S == w);
            break;
        }
        if (cur->ch[0]) {
            auto *node = new Heap<ll>::Node(*cur->ch[0]);
            node->prev = cur->prev;
            Q.emplace(w - cur->ch[0]->val + cur->val, node);
        }
        if (cur->ch[1]) {
            auto *node = new Heap<ll>::Node(*cur->ch[1]);
            node->prev = cur->prev;
            Q.emplace(w - cur->ch[1]->val + cur->val, node);
        }
        if (h[cur->to].root) {
            auto *node = new Heap<ll>::Node(*h[cur->to].root);
            node->prev = cur;
            Q.emplace(w - h[cur->to].root->val, node);
        }
    }
    if (ans.size() < k) {
        cout << -1;
    }
    return;
}

void add_edge(int u, int v, int wt) {
    adj[v].push_back({u, wt, e});
    rev[u].push_back({v, wt, e});
    e++;
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    add_edge(0, 1, 0);
    for (int i = 0; i < n; i++) {
        add_edge(0, 1 + (1 << i), a[i][0]);
    }
    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            for (int mask = 0; mask < 1 << n; mask++) {
                int c = mask & (1 << i);
                if (c == 0) {
                    add_edge(1 + (j - 1) * (1 << n) + mask, 1 + j * (1 << n) + (mask + (1 << i)), a[i][j]);
                }
            }
        }
        for (int mask = 0; mask < 1 << n; mask++) {
            add_edge(1 + (j - 1) * (1 << n) + mask, 1 + j * (1 << n) + mask, 0);
        }

    }
    int st = 0, en = 1 + (m - 1) * (1 << n) + ((1 << n) - 1);
    eppstein(en + 1, st, en, k, n);
    return 0;
}
