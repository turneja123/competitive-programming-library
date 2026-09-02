//https://atcoder.jp/contests/arc221/tasks/arc221_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> solve(int n) {
    if (n == 1) {
        return {0, 1};
    }
    vector<int> p = solve(n - 1);
    int m = (1 << (n - 1)) - 1;
    vector<int> l(m + 1), r(m + 1), ans((1 << n));
    for (int i = 1; i <= m; i++) {
        l[i] = p[i] + 1;
        r[i] = p[i] + m;
    }
    r[1] = (1 << n) - 1;
    for (int i = 1 << (n - 2); i <= m; i++) {
        swap(l[i], r[i]);
    }
    ans[1] = 1;
    for (int i = 1; i <= m; i++) {
        int j = 1 << (31 - __builtin_clz(i));
        ans[i + j] = l[i];
        ans[i + 2 * j] = r[i];
    }
    return ans;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> ans = solve(n);
    for (int i = 1; i < (1 << n); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
