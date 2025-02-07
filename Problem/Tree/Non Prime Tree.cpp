//https://codeforces.com/contest/2040/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

vector<int> adj[N];
bool is_prime[N];
int ans[N];
int deg[N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

set<int> even, all, odd;

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            if (ans[u] % 2 == 0) {
                if (even.size()) {
                    auto it = even.begin();
                    while (it != even.end()) {
                        if (abs(*it - ans[u]) != 2) {
                            ans[v] = *it;
                            even.erase(ans[v]);
                            all.erase(ans[v]);
                            break;
                        }
                        it++;
                    }
                }
                if (ans[v] == 0) {
                    auto it = all.begin();
                    while (it != all.end()) {
                        if (!is_prime[abs(*it - ans[u])]) {
                            ans[v] = *it;
                            all.erase(ans[v]);
                            odd.erase(ans[v]);
                            break;
                        }
                        it++;
                    }
                }
            } else {
                if (odd.size()) {
                    auto it = odd.begin();
                    while (it != odd.end()) {
                        if (abs(*it - ans[u]) != 2) {
                            ans[v] = *it;
                            odd.erase(ans[v]);
                            all.erase(ans[v]);
                            break;
                        }
                        it++;
                    }
                }
                if (ans[v] == 0) {
                    auto it = all.begin();
                    while (it != all.end()) {
                        if (!is_prime[abs(*it - ans[u])]) {
                            ans[v] = *it;
                            all.erase(ans[v]);
                            even.erase(ans[v]);
                            break;
                        }
                        it++;
                    }
                }
            }
            dfs(v, u);
        }
    }
    return;
}

int main() {
    IOS;
    sieve(N);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++, deg[v]++;
        }
        int mx = 0, st = -1;
        for (int i = 0; i < n; i++) {
            ans[i] = 0;
            if (deg[i] > mx) {
                mx = deg[i];
                st = i;
            }
        }
        for (int i = 1; i <= 2 * n; i++) {
            all.insert(i);
            if (i % 2 == 0) {
                even.insert(i);
            } else {
                odd.insert(i);
            }
        }
        ans[st] = 2;
        all.erase(2);
        even.erase(2);
        dfs(st, st);
        odd.clear();
        even.clear();
        all.clear();
        bool can = true;
        for (int i = 0; i < n; i++) {
            if (ans[i] == 0) {
                can = false;
            }
            adj[i].clear();
            deg[i] = 0;
        }
        if (!can) {
            cout << -1;
        } else {
            for (int i = 0; i < n; i++) {
                cout << ans[i] << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
