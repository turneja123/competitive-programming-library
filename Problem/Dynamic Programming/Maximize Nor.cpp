//https://codeforces.com/contest/2103/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 18;

int a[N];
int val[N];
int ans[N];
map<int, int> seen[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            int last;
            int suf = 0;
            int j = i;
            for (; j < n; j++) {
                if (j == i) {
                    last = a[i];
                } else {
                    int nw = 0;
                    for (int p = 0; p < k; p++) {
                        int c1 = last & (1 << p), c2 = a[j] & (1 << p);
                        if (c1 == 0 && c2 == 0) {
                            nw += 1 << p;
                        }
                    }
                    last = nw;
                }
                val[j] = last;
                auto it = seen[j].find(last);
                if (it != seen[j].end()) {
                    j++;
                    suf = it->second;
                    break;
                }
            }
            for (int k = j - 1; k >= i; k--) {
                suf = max(suf, val[k]);
                seen[k][val[k]] = suf;
                ans[k] = max(ans[k], suf);
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
            seen[i].clear();
            ans[i] = 0;
        }
        cout << endl;
    }

    return 0;
}
