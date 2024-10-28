//https://www.codechef.com/problems/NORMAL
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
int pref[N];
int last[4];

map<int, int> mp;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        last[1] = -1, last[2] = -1, last[3] = -1;
        long long ans = 0;
        int sum = 0, l = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                ans += i - max(last[2], last[3]);
            } else if (a[i] == 3) {
                ans += i - max(last[1], last[2]);
            }
            last[a[i]] = i;
            sum += a[i] - 2;
            pref[i] = sum;
            if (a[i] == 2) {
                if (mp[0] == 0) {
                    mp[0]++;
                }
                while (l < i) {
                    mp[pref[l]]++;
                    l++;
                }

            }
            ans += mp[sum];
        }
        cout << ans << endl;
        mp.clear();


    }
    return 0;
}
