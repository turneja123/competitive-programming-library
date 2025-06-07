//https://basecamp.eolymp.com/en/problems/11855
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<long long> ans(x, 0);
        for (int j = 0; j < x; j++) {
            map<int, int> freq;
            for (int i = 0; i < n; i++) {
                int s = 0;
                for (int k = 0; k <= j; k++) {
                    int c = a[i] & (1 << k);
                    if (c) {
                        s += 1 << k;
                    }
                }
                ans[j] += freq[s];
                freq[s]++;
            }
        }
        for (int j = 0; j < x; j++) {
            cout << ans[j] + n << " ";
        }
        cout << endl;
    }
    return 0;
}
