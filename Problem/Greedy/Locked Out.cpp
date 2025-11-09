//https://codeforces.com/contest/2161/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
set<int> st[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            st[a[i]].insert(i);
        }
        int ans = 0;
        for (int i = n - 1; i >= 1; i--) {
            vector<int> rem;

            for (int j : st[i]) {
                if (st[i + 1].size()) {
                    auto it = st[i + 1].lower_bound(j);
                    if (it == st[i + 1].end()) {
                        break;
                    }
                    st[i + 1].erase(it);
                    ans++;
                    rem.push_back(j);
                } else {
                    break;
                }
            }
            for (int j : rem) {
                st[i].erase(j);
            }
        }
        cout << ans << endl;
        for (int i = 0; i <= n; i++) {
            st[i].clear();
        }


    }
    return 0;
}
