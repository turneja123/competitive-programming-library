//https://www.codechef.com/problems/KSIZEGCD?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
int ans[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            ans[i + 1] = 0;
        }
        map<int, int> last;
        last[a[0]] = 0;
        ans[1] = a[0];
        for (int i = 1; i < n; i++) {
            map<int, int> mp;
            mp[a[i]] = i, ans[1] = max(ans[1], a[i]);
            for (auto it = last.begin(); it != last.end(); ++it) {
                int x = __gcd(it->first, a[i]);
                auto itt = mp.find(x);
                if (itt == mp.end()) {
                    mp[x] = it->second;
                } else {
                    mp[x] = min(mp[x], it->second);
                }

                ans[i - it->second + 1] = max(ans[i - it->second + 1], x);
            }
            last = mp;
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i + 1] << " ";
        }
        cout << endl;
    }


    return 0;
}
