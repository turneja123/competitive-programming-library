//https://codeforces.com/contest/1325/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;
const int INF = 1e9;

int spf[N];
bool is_prime[N];
int freq[N];
int dist[N];

vector<int> adj[N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

int bfs(int s, int n) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    queue<pair<int, int>> q;
    q.push(make_pair(s, -1));
    int ans = INF;
    while (q.size()) {
        int u = q.front().first, p = q.front().second;
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(make_pair(v, u));
            } else if (v != p) {
                ans = min(ans, dist[u] + dist[v] + 1);
            }
        }
    }
    return ans;
}

int main() {
    IOS;
    sieve(N);
    int n;
    cin >> n;
    int ans = N;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int prod = 1;
        while (a > 1) {
            int p = spf[a], e = 0;
            while (a % p == 0) {
                a /= p;
                e++;
            }
            if (e % 2 == 1) {
                prod *= p;
            }
        }
        freq[prod]++;
        if (freq[prod] > 1) {
            ans = min(ans, 2);
        }
        if (prod == 1) {
            ans = 1;
        }
        if (is_prime[prod]) {
            adj[1].push_back(prod);
            adj[prod].push_back(1);
        } else {
            adj[spf[prod]].push_back(prod / spf[prod]);
            adj[prod / spf[prod]].push_back(spf[prod]);
        }
    }
    if (ans == 1 || ans == 2) {
        cout << ans;
        return 0;
    }
    for (int i = 1; i < 2000; i++) {
        if (i == 1 || is_prime[i]) {
            ans = min(ans, bfs(i, N));
        }
    }
    if (ans == N) {
        ans = -1;
    }
    cout << ans;
    return 0;
}
