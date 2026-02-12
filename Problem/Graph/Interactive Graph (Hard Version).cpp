//https://codeforces.com/contest/2196/problem/C2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 100;

int sz[N];
int k;
vector<int> st;
vector<pair<int, int>> ans;

void dfs(int u) {
    st.push_back(u);
    sz[u] = 1;
    k++;
    while (1) {
        cout << "? " << k << endl;
        int q;
        cin >> q;
        vector<int> p;
        for (int i = 0; i < q; i++) {
            int u;
            cin >> u;
            p.push_back(u);
        }
        int ok = 1;
        for (int i = 0; i < st.size(); i++) {
            if (i == p.size() || st[i] != p[i]) {
                ok = 0;
                break;
            }
        }
        if (!ok) {
            break;
        }
        int v = p[st.size()];
        ans.push_back({u, v});
        if (!sz[v]) {
            dfs(v);
        } else {
            k += sz[v];
        }
        sz[u] += sz[v];
    }
    st.pop_back();
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        k = 1;
        for (int i = 1; i <= n; i++) {
            if (!sz[i]) {
                dfs(i);
            } else {
                k += sz[i];
            }
        }
        cout << "! " << ans.size() << endl;
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i].first << " " << ans[i].second << endl;
        }
        ans.clear();
        for (int i = 1; i <= n; i++) {
            sz[i] = 0;
        }
    }
    return 0;
}
