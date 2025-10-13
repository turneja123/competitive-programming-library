//https://www.spoj.com/problems/CLFLARR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        queries.push_back(make_tuple(l, r, x));
    }
    reverse(queries.begin(), queries.end());

    vector<int> ans(n, 0), go(n + 1);
    for (int i = 0; i <= n; i++) {
        go[i] = i;
    }

    auto ptr = [&](int j) -> int {
        if (go[j] == j) {
            return j;
        }
        int p = j;
        while (go[j] != j) {
            j = go[j];
        }
        while (go[p] != p) {
            int tmp = go[p];
            go[p] = j;
            p = tmp;
        }
        return j;
    };

    for (auto [l, r, x] : queries) {
        int j = ptr(l);
        while (j <= r) {
            if (ans[j] == 0) {
                ans[j] = x;
            }
            go[j] = ptr(j + 1);
            j = go[j];
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
