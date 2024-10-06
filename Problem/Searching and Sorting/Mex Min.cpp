//https://atcoder.jp/contests/abc194/tasks/abc194_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

int a[N];
vector<int> pos[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    int ans = n;
    for (int i = 0; i < n; i++) {
        pos[i].push_back(n);
        int last = -1;
        for (int ind : pos[i]) {
            if (ind - last > m) {
                ans = i;
            }
            last = ind;
        }
        if (ans == i) {
            break;
        }
    }
    cout << ans;

    return 0;
}
