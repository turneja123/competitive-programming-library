//https://atcoder.jp/contests/arc215/tasks/arc215_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);



int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> last(n, -1);
        vector<int> ans(2 * n), sols;
        for (int i = 0; i < 2 * n; i++) {
            int a;
            cin >> a;
            a--;
            if (last[a] == -1) {
                ans[i] = (i == 0 ? 0 : ans[i - 1]);
            } else {
                ans[i] = !ans[last[a]];
            }
            last[a] = i;
            if (i != 0 && ans[i] != ans[i - 1]) {
                sols.push_back(i);
            }
        }
        cout << sols.size() << endl;
        for (int i : sols) {
            cout << i << " ";
        }
        cout << endl;

    }

    return 0;
}
