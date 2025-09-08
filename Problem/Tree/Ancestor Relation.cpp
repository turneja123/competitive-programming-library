//https://atcoder.jp/contests/arc197/tasks/arc197_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const ll M = 998244353;

ll fact[N];
int deg[N];
int val[N];
bitset<N> g[N];

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first) {
        return a.first > b.first;
    }
    return a.second < b.second;
}

int main() {
    IOS;
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int b;
                cin >> b;
                g[i][j] = b;
            }
            deg[i] = g[i].count();
        }
        ll ans = 1;
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) {
            v.push_back({deg[i], i});
        }
        sort(v.begin(), v.end(), comp);
        if (v[0].second != 0 || v[0].first != n) {
            ans = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (g[i][j] && (g[i] & g[j]).count() != min(deg[i], deg[j])) {
                    ans = 0;
                }
            }
        }
        int i = 1;
        while (i < n) {
            int d = v[i].first;
            int j = i;
            while (i < n && v[i].first == d) {
                for (int k = j; k <= i; k++) {
                    if ((g[v[k].second] & g[v[i].second]).count() == deg[v[i].second]) {
                        val[k]++;
                        break;
                    }
                }
                i++;
            }
            for (int k = j; k < i; k++) {
                ans = ans * fact[val[k]] % M;
                val[k] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = 0;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
