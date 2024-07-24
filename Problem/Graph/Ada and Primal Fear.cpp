//https://www.spoj.com/problems/ADAFEAR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const int INF = 1e9;

vector<int> primes;

struct Edge {
    int u, v;
    int cap, cost;
    Edge(int u, int v, int cap, int cost) : u(u), v(v), cap(cap), cost(cost) {}
};

vector<int> adj[N];
vector<Edge> edges;

void add_edge(int u, int v, int cap, int cost) {
    adj[u].push_back(edges.size());
    edges.emplace_back(u, v, cap, cost);
    adj[v].push_back(edges.size());
    edges.emplace_back(v, u, 0, -cost);
}

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    priority_queue<pair<int, int>> q;
    q.push(make_pair(0, v0));
    p.assign(n, -1);
    while (!q.empty()) {
        int u = q.top().second, nw = -q.top().first;
        q.pop();
        if (nw != d[u]) {
            continue;
        }
        for (int e : adj[u]) {
            int v = edges[e].v;
            if (edges[e].cap > 0 && d[v] > d[u] + edges[e].cost) {
                d[v] = d[u] + edges[e].cost;
                p[v] = e;
                q.push(make_pair(-d[v], v));

            }
        }
    }
}

int min_cost_flow(int N, int K, int s, int t) {
    int flow = 0;
    int ans = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF) {
            break;
        }

        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, edges[p[cur]].cap);
            cur = edges[p[cur]].u;
        }
        flow += f;
        ans += f * d[t];
        cur = t;
        while (cur != s) {
            edges[p[cur]].cap -= f;
            edges[p[cur] ^ 1].cap += f;
            cur = edges[p[cur]].u;
        }
    }

    if (flow < K) {
        return -1;
    } else {
        return ans;
    }
}


int main() {
    IOS;
    primes.push_back(1);
    vector<bool> is_prime(N, true);
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int n;
    cin >> n;
    int s = 0, t = n + primes.size() + 1;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        for (int j = 0; j < primes.size(); j++) {
            if (a % primes[j] == 0) {
                int cost = a / primes[j];
                add_edge(i + 1, j + n + 1, 1, cost);
            }
        }
        add_edge(s, i + 1, 1, 0);
    }
    add_edge(n + 1, t, n, 0);
    for (int j = 1; j < primes.size(); j++) {
        add_edge(j + n + 1, t, 1, 0);
    }

    cout << min_cost_flow(n + primes.size() + 2, n, s, t);
    return 0;
}
