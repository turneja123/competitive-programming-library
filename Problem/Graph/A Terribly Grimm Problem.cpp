//https://www.spoj.com/problems/GRIMM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
vector<long long> factors;

__int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

__int128 mult(__int128 a, __int128 b, __int128 mod) {
    return (__int128)a * b % mod;
}

__int128 f(__int128 x, __int128 c, __int128 mod) {
    return (mult(x, x, mod) + c) % mod;
}

__int128 binpower(__int128 base, __int128 e, __int128 mod) {
    __int128 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        e >>= 1;
    }
    return result;
}

__int128 rho(__int128 n) {
    __int128 c = rand() % (n + 1);
    __int128 x = rand() % (n + 1);
    __int128 xx = x;
    __int128 g = 1;
    if (n % 2 == 0) {
        return 2;
    }

    while (g == 1) {
        x = f(x, c, n);
        xx = f(xx, c, n);
        xx = f(xx, c, n);
        g = __gcd(abs(x - xx), n);
    }
    return g;
}

bool check_composite(__int128 n, __int128 a, __int128 d, int s) {
    __int128 x = binpower(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1) {
            return false;
        }
    }
    return true;
};


bool is_prime(__int128 n) {
    if (n < 2) {
        return false;
    }
    int r = 0;
    __int128 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : primes) {
        if (n == a) {
            return true;
        }
        if (check_composite(n, a, d, r)) {
            return false;
        }
    }
    return true;
}

void factor(__int128 n) {
    if (n == 1) {
        return;
    }
    if (is_prime(n)) {
        factors.push_back(n);
        return;
    }

    __int128 divisor = rho(n);
    factor(divisor);
    factor(n / divisor);
    return;
}
const int N = 5005;
const int INF = 1e9;

int s, t;

vector<long long> a[N];
long long pr[N];
bool vis[N];

struct Edge {
    int v, u;
    int cap, flow = 0;
    Edge(int v, int u, int cap) : v(v), u(u), cap(cap) {}
};

vector<Edge> edges;
vector<int> adj[N];
int m = 0;
vector<int> level, ptr;
queue<int> q;

void add_edge(int v, int u, int cap) {
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
}

bool bfs() {
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int id : adj[v]) {
            if (edges[id].cap - edges[id].flow < 1) {
                continue;
            }
            if (level[edges[id].u] != -1 || vis[edges[id].u]) {
                continue;
            }
            level[edges[id].u] = level[v] + 1;
            q.push(edges[id].u);
        }
    }
    return level[t] != -1;
}

int dfs(int v, int pushed) {
    if (pushed == 0) {
        return 0;
    }
    if (v == t) {
        return pushed;
    }
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
        int id = adj[v][cid];
        int u = edges[id].u;
        if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1 || vis[u]) {
            continue;
        }
        int tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
        if (tr == 0) {
            continue;
        }
        edges[id].flow += tr;
        edges[id ^ 1].flow -= tr;
        return tr;
    }
    return 0;
}

int flow() {
    int f = 0;
    while (true) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
        if (!bfs()) {
            break;
        }
        fill(ptr.begin(), ptr.end(), 0);
        while (int pushed = dfs(s, INF)) {
            f += pushed;
        }
    }
    return f;
}

int main(){
    srand(time(NULL));
	IOS;
	while (1) {
        long long l, r;
        cin >> l >> r;
        if (l == 0 && r == 0) {
            break;
        }
        set<long long> st;
        map<long long, int> mp;

        for (long long n = l; n <= r; n++) {
            factor(n);
            sort(factors.begin(), factors.end());
            int i = 0, j = 0, m = factors.size();
            while (i < m) {
                long long cur = factors[i];
                while (i < m && factors[i] == cur) {
                    i++;
                }
                a[n - l].push_back(cur);
                st.insert(cur);
                j = i;
            }
            factors.clear();
        }
        s = 0, t = 1 + (r - l + 1) + st.size();

        for (long long x : st) {
            pr[mp.size()] = x;
            add_edge((r - l + 1) + 1 + mp.size(), t, 1);
            mp[x] = mp.size();
        }
        for (long long n = l; n <= r; n++) {
            add_edge(s, n - l + 1, 1);
            for (int i = 0; i < a[n - l].size(); i++) {
                add_edge(n - l + 1, (r - l + 1) + 1 + mp[a[n - l][i]], 1);
            }
        }
        vector<Edge> temp = edges;
        vector<long long> ans;
        for (long long n = l; n <= r; n++) {
            for (int i = 0; i < a[n - l].size(); i++) {
                int x = mp[a[n - l][i]];
                if (vis[(r - l + 1) + 1 + x]) {
                    continue;
                }
                vis[n - l + 1] = true;
                vis[(r - l + 1) + 1 + x] = true;
                if (n == r) {
                    ans.push_back(a[n - l][i]);
                    break;
                }
                edges = temp;
                level.resize(t + 1);
                ptr.resize(t + 1);
                int f = flow();
                level.clear();
                ptr.clear();
                if (f == r - n) {
                    ans.push_back(a[n - l][i]);
                    break;
                }
                vis[n - l + 1] = false;
                vis[(r - l + 1) + 1 + x] = false;
            }

        }
        for (long long x : ans) {
            cout << x << " ";
        }
        cout << endl;
        edges.clear();
        for (int i = 0; i <= t; i++) {
            adj[i].clear();
            a[i].clear();
            vis[i] = false;
            m = 0;
        }
	}
	//4302407360 4302407712
	return 0;
}
