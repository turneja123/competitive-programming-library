//https://codeforces.com/contest/2196/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
vector<int> pos[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] <= n) {
                pos[a[i]].push_back(i);
            }
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i; (ll)i * j <= n; j++) {
                if (pos[i].size() < pos[j].size()) {
                    for (int k : pos[i]) {
                        if (k - i * j >= 0 && a[k - i * j] == j) {
                            ans++;
                        }
                        if (k + i * j < n && a[k + i * j] == j && i != j) {
                            ans++;
                        }
                    }
                } else {
                    for (int k : pos[j]) {
                        if (k - i * j >= 0 && a[k - i * j] == i) {
                            ans++;
                        }
                        if (k + i * j < n && a[k + i * j] == i && i != j) {
                            ans++;
                        }
                    }
                }
            }
        }
        cout << ans << endl;
        for (int i = 1; i <= n; i++) {
            pos[i].clear();
        }
    }
    return 0;
}
