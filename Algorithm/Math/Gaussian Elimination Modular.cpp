//https://codeforces.com/contest/1411/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 512;
const ll M = 998244353;

int deg[N];
int grundy[N];
int mex[N];
int cnt[N];
vector<int> adj[N];

long long modPow(long long a, long long y) {
    a = (a + M * M) % M;
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int Gauss(vector<vector<ll>> a, vector<ll> &ans) {
    int n = a.size(), m = (int)a[0].size() - 1;
    vector <int> pos(m, -1);
    int free_var = 0;
    int det = 1, rank = 0;
    for (int col = 0, row = 0; col < m && row < n; col++) {
        int mx = row;
        for (int k = row; k < n; k++) {
            if (a[k][col] > a[mx][col]) {
                mx = k;
            }
        }
        if (a[mx][col] == 0) {
            det = 0;
            continue;
        }
        for (int j = col; j <= m; j++) {
            swap(a[mx][j], a[row][j]);
        }
        if (row != mx) {
            det = det == 0 ? 0 : M - det;
        }
        det = 1LL * det * a[row][col] % M;
        pos[col] = row;
        int inv = modPow(a[row][col], M - 2);
        for (int i = 0; i < n && inv; i++) {
            if (i != row && a[i][col]) {
                int x = ((long long)a[i][col] * inv) % M;
                for (int j = col; j <= m && x; j++){
                    if (a[row][j]) {
                        a[i][j] = (M * M + a[i][j] - ((long long)a[row][j] * x)) % M;
                    }
                }
            }
        }
        row++; ++rank;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; i++){
        if (pos[i] == -1) {
            free_var++;
        } else {
            ans[i] = ((long long)a[pos[i]][m] * modPow(a[pos[i]][i], M - 2)) % M;
        }
    }
    for (int i = 0; i < n; i++) {
        long long val = 0;
        for (int j = 0; j < m; j++) {
            val = (val + ((long long)ans[j] * a[i][j])) % M;
        }
        if (val != a[i][m]) return -1; //no solution
    }
    return free_var; //has solution
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        deg[v]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    vector<int> sorted;
    while (q.size()) {
        int u = q.front();
        q.pop();
        sorted.push_back(u);
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    reverse(sorted.begin(), sorted.end());
    for (int u : sorted) {
        for (int v : adj[u]) {
            mex[grundy[v]]++;
        }
        for (int i = 0; i <= n; i++) {
            if (mex[i] == 0) {
                grundy[u] = i;
                break;
            }
        }
        for (int v : adj[u]) {
            mex[grundy[v]]--;
        }
        cnt[grundy[u]]++;
    }
    vector<vector<ll>> v(K, vector<ll>(K + 1, 0));
    for (int i = 0; i < K; i++) {
        v[i][i] += (M - 1);
        for (int j = 0; j < K; j++) {
            v[i][i ^ j] = (v[i][i ^ j] + cnt[j] * modPow(n + 1, M - 2)) % M;
        }
        if (i != 0) {
            v[i][K] = (M - modPow(n + 1, M - 2)) % M;
        } else {
            v[i][K] = 0;
        }
    }
    vector<ll> ans;
    Gauss(v, ans);
    cout << ans[0] % M;
    return 0;
}
