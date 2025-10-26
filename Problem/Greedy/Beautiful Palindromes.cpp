//https://codeforces.com/contest/2162/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int freq[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            freq[a[i]]++;
        }
        int ct = 0;
        vector<pair<int, int>> sorted;
        for (int i = 1; i <= n; i++) {
            if (freq[i]) {
                ct++;
            }
            sorted.push_back({freq[i], i});
        }
        sort(sorted.begin(), sorted.end());
        vector<int> ans;
        if (ct == n) {
            for (int i = 1; i <= n; i++) {
                ans.push_back(a[i]);
            }
        } else if (ct == n - 1) {
            ans.push_back(sorted[0].second);
            int x;
            for (int i = 1; i <= n; i++) {
                if (a[n] != i && sorted[0].second != i) {
                    x = i;
                    break;
                }
            }
            ans.push_back(x);

            for (int i = 1; i <= n; i++) {
                if (x != i && sorted[0].second != i) {
                    ans.push_back(i);
                }
            }
        } else {
            for (auto [_, i] : sorted) {
                ans.push_back(i);
            }
        }
        for (int i = 0; i < k; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
        for (int i = 1; i <= n; i++) {
            freq[i] = 0;
        }
    }

  return 0;
}
