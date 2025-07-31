//https://atcoder.jp/contests/abc411/tasks/abc411_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int root[N];
string s[N];
pair<int, int> parent[N];

int idx = 0;

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    int cur = idx++;
    for (int i = 1; i <= n; i++) {
        root[i] = idx++;
    }
    for (int i = 0, j = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int p;
            cin >> p;
            root[p] = cur;
        } else if (t == 2) {
            int p;
            cin >> p >> s[j];
            parent[idx] = {root[p], j++};
            root[p] = idx++;
        } else {
            int p;
            cin >> p;
            cur = root[p];
        }
    }
    vector<int> ans;
    while (cur > n) {
        ans.push_back(parent[cur].second);
        cur = parent[cur].first;
    }
    reverse(ans.begin(), ans.end());
    for (int j : ans) {
        cout << s[j];
    }
    return 0;
}
