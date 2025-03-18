//https://www.spoj.com/problems/SRTMACH/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 98765431;

vector<int> p[2];

long long modPow(long long a, long long y) {
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

long long calc_hash(vector<int> &p) {
    long long ans = 0, pw = 1, n = p.size();
    for (int i = 0; i < n; i++) {
        ans += (long long)(p[i] + 1) * pw;
        pw *= n + 1;
    }
    return ans;
}

vector<int> calc_perm(vector<int> &a, vector<int> &b) {
    int n = a.size();
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = a[b[i]];
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        p[0].resize(n), p[1].resize(n);
        for (int i = 0; i < n; i++) {
            cin >> p[0][i];
            p[0][i]--;
        }
        for (int i = 0; i < n; i++) {
            cin >> p[1][i];
            p[1][i]--;
        }
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        set<long long> seen;
        vector<vector<int>> perms;
        queue<vector<int>> q;
        seen.insert(calc_hash(v));
        perms.push_back(v);
        q.push(v);
        while (q.size()) {
            vector<int> v = q.front();
            q.pop();
            for (int i = 0; i < 2; i++) {
                vector<int> u = calc_perm(v, p[i]);
                if (seen.find(calc_hash(u)) == seen.end()) {
                    seen.insert(calc_hash(u));
                    perms.push_back(u);
                    q.push(u);
                }
            }
        }
        long long ans = 0;
        int k = perms.size();
        for (int j = 0; j < k; j++) {
            vector<int> v = perms[j];
            vector<bool> vis(n, false);
            int ct = 0;
            for (int i = 0; i < n; i++) {
                if (!vis[i]) {
                    int u = i;
                    while (!vis[u]) {
                        vis[u] = true;
                        u = v[u];
                    }
                    ct++;
                }
            }
            ans = (ans + modPow(m, ct)) % M;
        }
        ans = ans * modPow(k, M - 2) % M;
        cout << ans << endl;
        p[0].clear(), p[1].clear();
    }
    return 0;
}
