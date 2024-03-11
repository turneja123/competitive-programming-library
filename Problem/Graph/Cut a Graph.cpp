//solution for https://www.e-olymp.com/en/problems/3728
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<string, pair<int, int>> queries[N];

int sz[N];
int parent[N];
string ans[N];

int dsu_find(int a) {
    if (a == parent[a]) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[a] < sz[b]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
    }
    for (int i = 0; i < k; i++) {
        cin >> queries[i].first >> queries[i].second.first >> queries[i].second.second;
    }
    for (int i = 1; i <= n; i++) {
        sz[i] = 1;
        parent[i] = i;
    }
    for (int i = k - 1; i >= 0; i--) {
        int a = queries[i].second.first, b = queries[i].second.second;
        if (queries[i].first == "ask") {
            if (dsu_find(a) == dsu_find(b)) {
                ans[i] = "YES";
            } else {
                ans[i] = "NO";
            }
        } else {
            a = dsu_find(a);
            b = dsu_find(b);
            dsu_unite(a, b);
            ans[i] = "X";
        }
    }
    for (int i = 0; i < k; i++) {
        if (ans[i] != "X") {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
